#include "screen.hpp"

//----------------------------------------------------------------------------------
// Base Screen class definitions
//----------------------------------------------------------------------------------

Screen::Screen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager) 
    : m_textureManager(textureManager), m_soundManager(soundManager)
{

}

Screen::~Screen() 
{

}

void Screen::updateScreen(float deltaTime)
{
	// Update screen
}

void Screen::drawScreen()
{
	// Draw screen
}


//----------------------------------------------------------------------------------
// Logo Screen class definitions
//----------------------------------------------------------------------------------

LogoScreen::LogoScreen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager)
    : Screen(textureManager, soundManager)
{
    m_lettersCount = 0;

    m_logoPositionX = GetScreenWidth() / 2 - 128;
    m_logoPositionY = GetScreenHeight() / 2 - 128;

    m_topSideRecWidth = 16;
    m_leftSideRecHeight = 16;
    m_bottomSideRecWidth = 16;
    m_rightSideRecHeight = 16;

    m_state = 0;
    m_alpha = 1.0f;
}

LogoScreen::~LogoScreen()
{
    //Unload resources
}

void LogoScreen::updateScreen(float deltaTime)
{
    if (m_state == 0)                 // State 0: Top-left square corner blink logic
    {
        m_framesCounter++;

        if (m_framesCounter == 80)
        {
            m_state = 1;
            m_framesCounter = 0;      // Reset counter... will be used later...
        }
    }
    else if (m_state == 1)            // State 1: Bars animation logic: top and left
    {
        m_topSideRecWidth += 8;
        m_leftSideRecHeight += 8;

        if (m_topSideRecWidth == 256) m_state = 2;
    }
    else if (m_state == 2)            // State 2: Bars animation logic: bottom and right
    {
        m_bottomSideRecWidth += 8;
        m_rightSideRecHeight += 8;

        if (m_bottomSideRecWidth == 256) m_state = 3;
    }
    else if (m_state == 3)            // State 3: "raylib" text-write animation logic
    {
        m_framesCounter++;

        if (m_lettersCount < 10)
        {
            if (m_framesCounter / 12)   // Every 12 frames, one more letter!
            {
                m_lettersCount++;
                m_framesCounter = 0;
            }
        }
        else    // When all letters have appeared, just fade out everything
        {
            if (m_framesCounter > 200)
            {
                m_alpha -= 0.02f;

                if (m_alpha <= 0.0f)
                {
                    m_alpha = 0.0f;
                    m_nextScreen = 1;   // Jump to next screen
                }
            }
        }
    }
}

void LogoScreen::drawScreen(void)
{
    if (m_state == 0)         // Draw blinking top-left square corner
    {
        if ((m_framesCounter / 10) % 2)
        {
            DrawRectangle(m_logoPositionX, m_logoPositionY, 16, 16, BLACK);
        }
    }
    else if (m_state == 1)    // Draw bars animation: top and left
    {
        DrawRectangle(m_logoPositionX, m_logoPositionY, m_topSideRecWidth, 16, BLACK);
        DrawRectangle(m_logoPositionX, m_logoPositionY, 16, m_leftSideRecHeight, BLACK);
    }
    else if (m_state == 2)    // Draw bars animation: bottom and right
    {
        DrawRectangle(m_logoPositionX, m_logoPositionY, m_topSideRecWidth, 16, BLACK);
        DrawRectangle(m_logoPositionX, m_logoPositionY, 16, m_leftSideRecHeight, BLACK);

        DrawRectangle(m_logoPositionX + 240, m_logoPositionY, 16, m_rightSideRecHeight, BLACK);
        DrawRectangle(m_logoPositionX, m_logoPositionY + 240, m_bottomSideRecWidth, 16, BLACK);
    }
    else if (m_state == 3)    // Draw "raylib" text-write animation + "powered by"
    {
        DrawRectangle(m_logoPositionX, m_logoPositionY, m_topSideRecWidth, 16, Fade(BLACK, m_alpha));
        DrawRectangle(m_logoPositionX, m_logoPositionY + 16, 16, m_leftSideRecHeight - 32, Fade(BLACK, m_alpha));

        DrawRectangle(m_logoPositionX + 240, m_logoPositionY + 16, 16, m_rightSideRecHeight - 32, Fade(BLACK, m_alpha));
        DrawRectangle(m_logoPositionX, m_logoPositionY + 240, m_bottomSideRecWidth, 16, Fade(BLACK, m_alpha));

        DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, m_alpha));

        DrawText(TextSubtext("raylib", 0, m_lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, m_alpha));

        if (m_framesCounter > 20) DrawText("powered by", m_logoPositionX, m_logoPositionY - 27, 20, Fade(DARKGRAY, m_alpha));
    }
}


//----------------------------------------------------------------------------------
// Options Screen Functions Definition
//----------------------------------------------------------------------------------

OptionsScreen::OptionsScreen(std::shared_ptr<TextureManager> textureManager,  std::shared_ptr<SoundManager> soundManager)
    : Screen(textureManager, soundManager)
{
 
}

OptionsScreen::~OptionsScreen()
{

}

void OptionsScreen::updateScreen(float deltaTime)
{
    // TODO: Update OPTIONS screen variables here!
}

void OptionsScreen::drawScreen()
{
    // TODO: Draw OPTIONS screen here!
}


//----------------------------------------------------------------------------------
// Title Screen Class Definition
//----------------------------------------------------------------------------------

TitleScreen::TitleScreen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager)
    : Screen(textureManager, soundManager)
{

}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::updateScreen(float deltaTime)
{
    // TODO: Update TITLE screen variables here!

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;   // OPTIONS
        m_nextScreen = 2;   // GAMEPLAY
    }
}

void TitleScreen::drawScreen()
{
    // TODO: Draw TITLE screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    raylib::Vector2 titlePosition {20, 10};
    raylib::DrawText("TITLE SCREEN", titlePosition.GetX(), titlePosition.GetY(), 20, DARKGREEN);
    raylib::Vector2 instructionPosition = {120, 220};
    raylib::DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", instructionPosition.GetX(), instructionPosition.GetY(), 30, DARKGREEN);
}


//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

GameplayScreen::GameplayScreen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager)
    : Screen(textureManager, soundManager)
{

}

GameplayScreen::~GameplayScreen()
{
    
}

void GameplayScreen::updateScreen(float deltaTime)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        m_nextScreen = 1;
    }
}

// Gameplay Screen Draw logic
void GameplayScreen::drawScreen()
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    raylib::Vector2 titlePosition {20, 10};
    raylib::DrawText("GAMEPLAY SCREEN", titlePosition.GetX(), titlePosition.GetY(), 20, MAROON);
    raylib::Vector2 instructionPosition {120, 220};
    raylib::DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", instructionPosition.GetX(), instructionPosition.GetY(), 30, MAROON);
}


//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

EndingScreen::EndingScreen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager)
    : Screen(textureManager, soundManager)
{

}

EndingScreen::~EndingScreen()
{

}

void EndingScreen::updateScreen(float deltaTime)
{
    // TODO: Update ENDING screen variables here!

    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        m_nextScreen = 1;
    }
}

// Ending Screen Draw logic
void EndingScreen::drawScreen()
{
    // TODO: Draw ENDING screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    raylib::Vector2 titlePosition {20, 10};
    raylib::DrawText("ENDING SCREEN", titlePosition.GetX(), titlePosition.GetY(), 20, DARKBLUE);
    raylib::Vector2 instructionPosition {120, 220};
    raylib::DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", instructionPosition.GetX(), instructionPosition.GetY(), 30, DARKBLUE);
}