#ifndef DRAW_H_
#define DRAW_H_

#include <SDL2/SDL.h>
#include "../engine/vector.h"
#include "../engine/color.h"

extern Vec2 offset;
extern float zoom;

Vec2 Render_ToLocal(int x, int y);

void RenderTexture(SDL_Texture* texture, SDL_Rect rect1, SDL_Rect rect2, int rotation, Color* color);

void RenderRect(int x, int y, int width, int height, Color color);

void RenderCircle(int ox, int oy, int radius, Color color);

void RenderCircleLight(int ox, int oy, int radius, Color color);

#endif