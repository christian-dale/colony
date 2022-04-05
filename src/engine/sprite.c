#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include "sprite.h"
#include "../engine/config.h"
#include "../engine/render.h"
#include "../options.h"

SDL_Texture* spritesheet;
SDL_Rect spriteSatelitte01 = { 0, 0, 32, 32 };
SDL_Rect spriteHeart01 = { 32, 16, 16, 16 };
SDL_Rect spriteOxygen01 = { 32, 0, 16, 16 };
SDL_Rect spriteCurrency01 = { 32 + 16, 16, 16, 16 };
SDL_Rect spriteSpace01 = { 32 * 2, 0, 32, 32 };
SDL_Rect spriteMoon01 = { 32, 32, 32, 32 };
SDL_Rect spriteShip01 = { 32 + 16, 0, 16, 16 };
SDL_Rect spriteEmpty = { 0, 0, 0, 0 };
SDL_Rect spriteUnit01 = { 32 * 2, 32, 32, 32 };
SDL_Rect spriteUnit02 = { 0, 32 * 2, 32, 32 };
SDL_Rect spriteUnit03 = { 32, 32 * 2, 32, 32 };
SDL_Rect spriteUnit04 = { 32 * 2, 32 * 2, 32, 32 };
SDL_Rect spriteUnit05 = { 32 * 3, 32 * 2, 32, 32 };
SDL_Rect spriteUnit06 = { 32 * 4, 32 * 2, 32, 16 };
SDL_Rect spriteUnit07 = { 32 * 5, 32 * 2, 32, 32 };
SDL_Rect spriteAsteroid01 = { 0, 32, 16, 16 };
SDL_Rect spriteDmg01 = { 0, 32 * 3, 32, 32 };
SDL_Rect spriteDmg02 = { 32, 32 * 3, 32, 32 };
SDL_Rect spriteDmg03 = { 32 * 2, 32 * 3, 32, 32 };
SDL_Rect spriteDmg04 = { 32 * 3, 32 * 3, 32, 32 };
SDL_Rect spriteMessage01 = { 0, 32 * 4, 32 * 2, 32 };
SDL_Rect spritePause = { 32 * 3, 32 * 4, 8, 8 };
SDL_Rect spriteAttack = { (32 * 3) + 8, 32 * 4, 8, 8 };
SDL_Rect spriteAttackCancel = { (32 * 3) + 16, 32 * 4, 8, 8 };

SpriteAnim spriteAnim01;
SpriteAnim spriteAnim02;
SpriteAnim spriteAnim03;
SpriteAnim spriteAnim04;

SDL_Rect spriteAlphabet[128];

SpriteAnim Sprite_AnimCreate(SDL_Rect* sprites, int length) {
	SpriteAnim spriteAnim = { length, 0, sprites };
	return spriteAnim;
}

void DrawSpriteHUD(SDL_Rect sprite, int x, int y, int w, int h) {
	SDL_Rect textureRect = { x, y, w, h };
	RenderTexture(spritesheet, sprite, textureRect, 0, NULL);
}

void DrawSprite(SDL_Rect sprite, int x, int y, int w, int h, int rotation, Color* color) {
	SDL_Rect textureRect = { x * zoom + offset.x, y * zoom + offset.y, w * zoom, h * zoom };
	RenderTexture(spritesheet, sprite, textureRect, rotation, color);
}

void DrawTextHUD(const char* text, int x, int y) {
	for (int i = 0; i < strlen(text); i++) {
		DrawSpriteHUD(spriteAlphabet[(int) text[i]], x + 8 * i, y, 8, 8);
	}
}

void DrawText(const char* text, int x, int y) {
	for (int i = 0; i < strlen(text); i++) {
		SDL_Rect textureRect = { (x + 8 * i) * zoom + offset.x, y * zoom + offset.y, 8, 8 };
		RenderTexture(spritesheet, spriteAlphabet[(int) text[i]], textureRect, 0, NULL);
	}
}

void Sprite_Init() {
	spritesheet = IMG_LoadTexture(renderer, "assets/spritesheet.png");

	SDL_Rect anim[4] = { spriteUnit01, spriteUnit02, spriteUnit03, spriteUnit04 };

	spriteAnim01 = Sprite_AnimCreate(anim, 4);
	spriteAnim02 = Sprite_AnimCreate(anim, 4);
	spriteAnim03 = Sprite_AnimCreate(anim, 4);
	spriteAnim04 = Sprite_AnimCreate(anim, 4);

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			SDL_Rect character = { 32 * 3 + j * 8, i * 8, 8, 8 };
			spriteAlphabet[(4 * i + j) + 65] = character;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			SDL_Rect character = { 32 * 4 + j * 8, i * 8, 8, 8 };
			spriteAlphabet[(4 * i + j) + 48] = character;
		}
	}
}