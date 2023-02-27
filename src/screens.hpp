#pragma once

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen { UNKNOWN = -1, LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING } GameScreen;

//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
//extern GameScreen currentScreen;
//extern Font font;
//extern Music music;
//extern Sound fxCoin;

//----------------------------------------------------------------------------------
// Logo Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitLogoScreen();
void UpdateLogoScreen();
void DrawLogoScreen();
void UnloadLogoScreen();
int FinishLogoScreen();

//----------------------------------------------------------------------------------
// Title Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitTitleScreen();
void UpdateTitleScreen();
void DrawTitleScreen();
void UnloadTitleScreen();
int FinishTitleScreen();

//----------------------------------------------------------------------------------
// Options Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitOptionsScreen();
void UpdateOptionsScreen();
void DrawOptionsScreen();
void UnloadOptionsScreen();
int FinishOptionsScreen();

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitGameplayScreen();
void UpdateGameplayScreen();
void DrawGameplayScreen();
void UnloadGameplayScreen();
int FinishGameplayScreen();

//----------------------------------------------------------------------------------
// Ending Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitEndingScreen();
void UpdateEndingScreen();
void DrawEndingScreen();
void UnloadEndingScreen();
int FinishEndingScreen();