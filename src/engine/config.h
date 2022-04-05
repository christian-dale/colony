#ifndef CONFIG_H_
#define CONFIG_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vector.h"

typedef struct Config {
	int mouseX;
	int mouseY;
	float deltaTime;
	SDL_Rect viewport;
	SDL_Event event;
	bool mouseState;
	Vec2 mouseInit;
	bool quit;
	int gridW;
	int gridH;
} Config;

extern Config config;

const char* Config_JSON_Retrieve_Token(const char* config, const int tokenStart, const int tokenEnd);
const char* Config_JSON_Retrieve(const char* config, const char* name);
void Config_Load();

#endif