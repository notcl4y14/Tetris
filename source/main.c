#include <game/main.h>

#include <game/tetris/block.h>
#include <game/tetris/grid.h>
#include <game/tetris/shape.h>
#include <game/tetris/state.h>
#include <game/defines.h>
#include <game/state.h>
#include <game/toast.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SDL_Window* sdlWindow;
SDL_Renderer* sdlRender;
TTF_TextEngine* sdlTextEngine;
TTF_Font* sdlFont;
TTF_Text* sdlText;
GameState gameState;
TetrisState tetrisState;
Toast toast;

void update () {
	if (tetrisState.isPlaying && gameState.tickCount % (GAME_FPS_TARGET / 2) == 0) {
		TetrisState_update(&tetrisState);
	}
	
	Toast_update(&toast);
}

void render () {
	SDL_SetRenderDrawColor(sdlRender, 10, 10, 10, 255);
	SDL_RenderClear(sdlRender);
	
	TetrisState_render(&tetrisState);
	
	// I am aware that this kind of approach is terrible (or terrifying)
	{
		char* str = calloc(32, sizeof(char));
		snprintf(str, 32, "Score: %d", tetrisState.score);

		TTF_SetTextColor(sdlText, 200, 200, 200, 255);

		TTF_SetTextString(sdlText, str, 0);
		TTF_DrawRendererText(sdlText,
			TETRIS_RENDER_GRID_X + TETRIS_GRID_WIDTH * (TETRIS_RENDER_GRID_SCALE + TETRIS_RENDER_GRID_SPACE) + 20,
			100);

		snprintf(str, 32, "High Score: %d", tetrisState.highScore);

		TTF_SetTextString(sdlText, str, 0);
		TTF_DrawRendererText(sdlText,
			TETRIS_RENDER_GRID_X + TETRIS_GRID_WIDTH * (TETRIS_RENDER_GRID_SCALE + TETRIS_RENDER_GRID_SPACE) + 20,
			115);

		snprintf(str, 32, "[P] - Pause/Unpause");

		TTF_SetTextString(sdlText, str, 0);
		TTF_DrawRendererText(sdlText,
			TETRIS_RENDER_GRID_X + TETRIS_GRID_WIDTH * (TETRIS_RENDER_GRID_SCALE + TETRIS_RENDER_GRID_SPACE) + 20,
			145);

		snprintf(str, 32, "[R] - Restart");

		TTF_SetTextString(sdlText, str, 0);
		TTF_DrawRendererText(sdlText,
			TETRIS_RENDER_GRID_X + TETRIS_GRID_WIDTH * (TETRIS_RENDER_GRID_SCALE + TETRIS_RENDER_GRID_SPACE) + 20,
			160);

		snprintf(str, 32, "Made by notcl4y in 5 days");

		TTF_SetTextString(sdlText, str, 0);
		TTF_DrawRendererText(sdlText,
			TETRIS_RENDER_GRID_X + TETRIS_GRID_WIDTH * (TETRIS_RENDER_GRID_SCALE + TETRIS_RENDER_GRID_SPACE) + 20,
			190);

		free(str);
	}

	Toast_render(&toast);

	SDL_RenderPresent(sdlRender);
}

int main () {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	TTF_Init();

	sdlWindow = SDL_CreateWindow("Tetris", 512, 512, SDL_WINDOW_RESIZABLE);
	sdlRender = SDL_CreateRenderer(sdlWindow, 0);
	sdlTextEngine = TTF_CreateRendererTextEngine(sdlRender);
	sdlFont = TTF_OpenFont("Roboto.ttf", 15);
	sdlText = TTF_CreateText(sdlTextEngine, sdlFont, NULL, 0);
	gameState = GameState_new();
	tetrisState = TetrisState_new();
	toast = Toast_new();

	TetrisState_start(&tetrisState);

	Toast_message(&toast, "Hello World!", GAME_FPS_TARGET * 5);

	while (!gameState.shouldQuit) {
		// TODO: Implement an event handling system
		SDL_Event e;
		SDL_Keycode keycode;

		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_EVENT_QUIT:
				gameState.shouldQuit = true;
				break;
			
			case SDL_EVENT_KEY_DOWN:
				keycode = e.key.key;

				     if (keycode == SDLK_LEFT)  TetrisState_moveLeft(&tetrisState);
				else if (keycode == SDLK_RIGHT) TetrisState_moveRight(&tetrisState);
				else if (keycode == SDLK_UP)    TetrisState_rotate(&tetrisState);
				else if (keycode == SDLK_R)     TetrisState_start(&tetrisState);
				else if (keycode == SDLK_P)     tetrisState.isPlaying = !tetrisState.isPlaying;

				if (keycode == SDLK_R) {
					Toast_message(&toast, "Restart", GAME_FPS_TARGET * 3);
				}

				if (keycode == SDLK_P) {
					if (tetrisState.isOver) {
						Toast_message(&toast, "Cannot unpause", GAME_FPS_TARGET * 3);
					} else if (!tetrisState.isPlaying) {
						Toast_message(&toast, "Paused", GAME_FPS_TARGET * 5);
					} else if (tetrisState.isPlaying) {
						Toast_message(&toast, "Unpaused", GAME_FPS_TARGET * 3);
					}
				}

				// Prevent the game over screen from pausing
				if (tetrisState.isOver) {
					tetrisState.isPlaying = 0;
				}

				break;
			}
		}

		update();
		render();

		gameState.tickCount++;

		SDL_Delay(1000 / GAME_FPS_TARGET);
	}

	TetrisState_free(&tetrisState);
	GameState_free(&gameState);
	Toast_free(&toast);
	TTF_DestroyText(sdlText);
	TTF_CloseFont(sdlFont);
	TTF_DestroyRendererTextEngine(sdlTextEngine);
	SDL_DestroyRenderer(sdlRender);
	SDL_DestroyWindow(sdlWindow);

	TTF_Quit();
	SDL_Quit();
	return 0;
}