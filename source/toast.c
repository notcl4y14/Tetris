#include <game/toast.h>

#include <game/defines.h>
#include <game/main.h>
#include <game/state.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Toast Toast_new () {
	Toast toast;
	Toast_init(&toast);
	return toast;
}

void Toast_init (Toast* toast) {
	toast->message = calloc(TOAST_MAX_MESSAGE_LEN, sizeof(char));
	toast->isVisible = false;
	toast->duration = 0;
}

void Toast_free (Toast* toast) {
	free(toast->message);

	toast->message = NULL;
	toast->isVisible = false;
	toast->duration = 0;
}

void Toast_message (Toast* toast, char* message, int32 duration) {
	int32 messageLen = strlen(message);

	if (messageLen >= TOAST_MAX_MESSAGE_LEN) {
		message = "ERROR_MAX_LEN";
	}

	strcpy(toast->message, message);
	toast->isVisible = true;
	toast->duration = duration;
}

void Toast_update (Toast* toast) {
	if (toast->duration == 0) {
		toast->isVisible = false;
	}

	toast->duration--;
}

void Toast_render (Toast* toast) {
	if (!toast->isVisible) {
		return;
	}
	
	uint8 alpha = 255;

	if (toast->duration < GAME_FPS_TARGET) {
		alpha = ((float)toast->duration / GAME_FPS_TARGET) * 255;
	}

	SDL_SetRenderDrawBlendMode(sdlRender, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdlRender, 50, 50, 50, alpha);

	const SDL_FRect destRect = {
		.x = (WINDOW_WIDTH / 2) - (TOAST_RENDER_WIDTH / 2),
		.y = (WINDOW_HEIGHT - TOAST_RENDER_HEIGHT - 20),
		.w = TOAST_RENDER_WIDTH,
		.h = TOAST_RENDER_HEIGHT,
	};

	SDL_RenderFillRect(sdlRender, &destRect);

	TTF_SetTextString(sdlText, toast->message, 0);
	TTF_SetTextColor(sdlText, 200, 200, 200, alpha);
	TTF_DrawRendererText(
		sdlText,
		destRect.x + 4,
		destRect.y + 4
	);
}