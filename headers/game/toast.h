#ifndef GAME_TOAST_H
#define GAME_TOAST_H

#include <game/defines.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define TOAST_MAX_MESSAGE_LEN 25
#define TOAST_RENDER_WIDTH 100
#define TOAST_RENDER_HEIGHT 25

typedef struct Toast {
	char* message;
	int32 duration;
	bool  isVisible;
	TTF_Text* sdlText;
} Toast;

Toast Toast_new ();
void Toast_init (Toast* toast);
void Toast_free (Toast* toast);
void Toast_message (Toast* toast, char* message, int32 duration);
void Toast_update (Toast* toast);
void Toast_render (Toast* toast);

#endif