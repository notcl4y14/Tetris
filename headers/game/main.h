#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include <game/tetris/grid.h>
#include <game/defines.h>
#include <game/toast.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512

extern SDL_Renderer* sdlRender;
extern TTF_Font* sdlFont;
extern TTF_Text* sdlText;
extern TTF_TextEngine* sdlTextEngine;
extern Toast toast;

int main ();

#endif