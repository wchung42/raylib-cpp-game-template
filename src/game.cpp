#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "game.hpp"
#include "screens.hpp"
#include <iostream>

Game::Game() {};

Game::~Game() {};

void Game::Initialize()
{
    // Initialize window
	m_window.raylib::Window::Init(m_windowWidth, m_windowHeight, m_title);
	
    // Setup and init first screen
    m_currentScreen = LOGO;
    InitLogoScreen();

    m_window.SetTargetFPS(m_targetFPS);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

	// TODO: Load textures

}


void Game::RunLoop()
{
	while (!m_window.ShouldClose())
	{
		const float dT = m_window.GetFrameTime();
		UpdateGame(dT);
		RenderGame();
	}
}

void Game::Shutdown()
{
	m_window.Close();
}

void Game::UpdateGame(float deltaTime)
{
	// Update game variables
    if (!m_onTransition)
    {
        switch (m_currentScreen)
        {
        case LOGO:
        {
            UpdateLogoScreen();

            if (FinishLogoScreen()) TransitionToScreen(TITLE);

        } break;
        case TITLE:
        {
            UpdateTitleScreen();

            if (FinishTitleScreen() == 1) TransitionToScreen(OPTIONS);
            else if (FinishTitleScreen() == 2) TransitionToScreen(GAMEPLAY);

        } break;
        case OPTIONS:
        {
            UpdateOptionsScreen();

            if (FinishOptionsScreen()) TransitionToScreen(TITLE);

        } break;
        case GAMEPLAY:
        {
            UpdateGameplayScreen();

            if (FinishGameplayScreen() == 1) TransitionToScreen(ENDING);
            //else if (FinishGameplayScreen() == 2) TransitionToScreen(TITLE);

        } break;
        case ENDING:
        {
            UpdateEndingScreen();

            if (FinishEndingScreen() == 1) TransitionToScreen(TITLE);

        } break;
        default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------
}

void Game::RenderGame()
{
	BeginDrawing();
		m_window.ClearBackground(RAYWHITE);
		//m_textColor.DrawText("Congrats! You created your first window!", 190, 200, 20);

        switch (m_currentScreen)
            {
            case LOGO: DrawLogoScreen(); break;
            case TITLE: DrawTitleScreen(); break;
            case OPTIONS: DrawOptionsScreen(); break;
            case GAMEPLAY: DrawGameplayScreen(); break;
            case ENDING: DrawEndingScreen(); break;
            default: break;
        }

        // Draw full screen rectangle in front of everything
        if (m_onTransition) DrawTransition();
	EndDrawing();
}

// Change to next screen, no transition
void Game::ChangeToScreen(GameScreen screen)
{
    // Unload current screen
    switch (m_currentScreen)
    {
        case LOGO: UnloadLogoScreen(); break;
        case TITLE: UnloadTitleScreen(); break;
        case GAMEPLAY: UnloadGameplayScreen(); break;
        case ENDING: UnloadEndingScreen(); break;
        default: break;
    }

    // Init next screen
    switch (screen)
    {
        case LOGO: InitLogoScreen(); break;
        case TITLE: InitTitleScreen(); break;
        case GAMEPLAY: InitGameplayScreen(); break;
        case ENDING: InitEndingScreen(); break;
        default: break;
    }

    m_currentScreen = screen;
}

// Request transition to next screen
void Game::TransitionToScreen(GameScreen screen)
{
    m_onTransition = true;
    m_transFadeOut = false;
    m_transFromScreen = m_currentScreen;
    m_transToScreen = screen;
    m_transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
void Game::UpdateTransition(void)
{
    if (!m_transFadeOut)
    {
        m_transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (m_transAlpha > 1.01f)
        {
            m_transAlpha = 1.0f;

            // Unload current screen
            switch (m_transFromScreen)
            {
                case LOGO: UnloadLogoScreen(); break;
                case TITLE: UnloadTitleScreen(); break;
                case OPTIONS: UnloadOptionsScreen(); break;
                case GAMEPLAY: UnloadGameplayScreen(); break;
                case ENDING: UnloadEndingScreen(); break;
                default: break;
            }

            // Load next screen
            switch (m_transToScreen)
            {
                case LOGO: InitLogoScreen(); break;
                case TITLE: InitTitleScreen(); break;
                case GAMEPLAY: InitGameplayScreen(); break;
                case ENDING: InitEndingScreen(); break;
                default: break;
            }

            m_currentScreen = m_transToScreen;

            // Activate fade out effect to next loaded screen
            m_transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        m_transAlpha -= 0.02f;

        if (m_transAlpha < -0.01f)
        {
            m_transAlpha = 0.0f;
            m_transFadeOut = false;
            m_onTransition = false;
            m_transFromScreen = -1;
            m_transToScreen = UNKNOWN;
        }
    }
}

// Draw transition effect (full-screen rectangle)
void Game::DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, m_transAlpha));
}