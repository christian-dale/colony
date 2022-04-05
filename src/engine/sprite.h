#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL2/SDL.h>
#include "color.h"

typedef struct SpriteAnim {
	int length;
	int index;
	SDL_Rect* sprites;
} SpriteAnim;

extern SDL_Texture* spritesheet;
extern SDL_Rect spriteSatelitte01;
extern SDL_Rect spriteHeart01;
extern SDL_Rect spriteOxygen01;
extern SDL_Rect spriteCurrency01;
extern SDL_Rect spriteSpace01;
extern SDL_Rect spriteMoon01;
extern SDL_Rect spriteShip01;
extern SDL_Rect spriteEmpty;
extern SDL_Rect spriteUnit01;
extern SDL_Rect spriteUnit02;
extern SDL_Rect spriteUnit03;
extern SDL_Rect spriteUnit04;
extern SDL_Rect spriteUnit05;
extern SDL_Rect spriteUnit06;
extern SDL_Rect spriteUnit07;
extern SDL_Rect spriteAsteroid01;
extern SDL_Rect spriteDmg01;
extern SDL_Rect spriteDmg02;
extern SDL_Rect spriteDmg03;
extern SDL_Rect spriteDmg04;
extern SDL_Rect spriteMessage01;
extern SDL_Rect spritePause;
extern SDL_Rect spriteAttack;
extern SDL_Rect spriteAttackCancel;

extern SpriteAnim spriteAnim01;
extern SpriteAnim spriteAnim02;
extern SpriteAnim spriteAnim03;
extern SpriteAnim spriteAnim04;

extern SDL_Rect spriteAlphabet[128];

SpriteAnim Sprite_AnimCreate(SDL_Rect* sprites, int length);

void DrawSpriteHUD(SDL_Rect sprite, int x, int y, int w, int h);

void DrawSprite(SDL_Rect sprite, int x, int y, int w, int h, int rotation, Color* color);

void DrawTextHUD(const char* text, int x, int y);

void DrawText(const char* text, int x, int y);

void Sprite_Init();

#endif