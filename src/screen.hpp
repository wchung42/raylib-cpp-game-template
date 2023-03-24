#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include "texture_manager.hpp"
#include "sound_manager.hpp"
#include <memory>

//----------------------------------------------------------------------------------
// Base Screen class declaration
//----------------------------------------------------------------------------------
typedef enum GameScreen { UNKNOWN = -1, LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING } GameScreen;

class Screen
{
protected:
	int m_framesCounter {};
	int m_nextScreen {};
	std::shared_ptr<TextureManager> m_textureManager;
	std::shared_ptr<SoundManager> m_soundManager;
public:
	Screen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager);
	~Screen();
	virtual void updateScreen(float deltaTime);
	virtual void drawScreen();

	int getNextScreen() const { return m_nextScreen; } // Return the next screen

};


//----------------------------------------------------------------------------------
// Logo Screen class declaration
//----------------------------------------------------------------------------------
class LogoScreen : public Screen
{
private:
	int m_logoPositionX {};
	int m_logoPositionY {};
	int m_lettersCount {};
	int m_topSideRecWidth {};
	int m_leftSideRecHeight {};
	int m_bottomSideRecWidth {};
	int m_rightSideRecHeight {};
	int m_state {};				// Logo animation states
	float m_alpha {1.0f};         // Useful for fading
public:
	LogoScreen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager);
	~LogoScreen();
	void updateScreen(float deltaTime) override;
	void drawScreen() override;
};


//----------------------------------------------------------------------------------
// Title Screen class declaration
//----------------------------------------------------------------------------------
class TitleScreen : public Screen
{
private:
public:
	TitleScreen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager);
	~TitleScreen();
	void updateScreen(float deltaTime) override;
	void drawScreen() override;
};


//----------------------------------------------------------------------------------
// Options Screen class declaration
//----------------------------------------------------------------------------------
class OptionsScreen : public Screen
{
public:
	OptionsScreen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager);
	~OptionsScreen();
	void updateScreen(float deltaTime);
	void drawScreen();
};


//----------------------------------------------------------------------------------
// Gameplay Screen class declaration
//----------------------------------------------------------------------------------
class GameplayScreen : public Screen
{
public:
	GameplayScreen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager);
	~GameplayScreen();
	void updateScreen(float deltaTime) override;
	void drawScreen();
};


//----------------------------------------------------------------------------------
// Ending Screen class declaration
//----------------------------------------------------------------------------------
class EndingScreen : public Screen
{
public:
	EndingScreen(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<SoundManager> soundManager);
	~EndingScreen();
	void updateScreen(float deltaTime) override;
	void drawScreen();
};