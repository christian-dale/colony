#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <SDL2/SDL.h>

typedef enum GameState {
	GameState_Main, GameState_Menu, GameState_Game, GameState_Pause
} GameState;

typedef struct Options {
	int screenHeight;
	int screenWidth;
	int gameState;
	int tutorialState;
} Options;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

#endif