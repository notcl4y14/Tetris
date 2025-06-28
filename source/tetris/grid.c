#include <game/tetris/grid.h>

#include <game/tetris/block.h>
#include <game/defines.h>
#include <game/main.h>

#include <SDL3/SDL.h>

#include <stdlib.h>
#include <string.h>

TetrisGrid_s TetrisGrid_new (int w, int h) {
	TetrisGrid_s grid;
	TetrisGrid_init(&grid, w, h);
	return grid;
}

void TetrisGrid_init (TetrisGrid_s* grid, int w, int h) {
	grid->blocks = calloc(w * h, sizeof(TetrisBlock_s));
	grid->width = w;
	grid->height = h;
}

void TetrisGrid_free (TetrisGrid_s* grid) {
	free(grid->blocks);

	grid->blocks = NULL;
	grid->width = 0;
	grid->height = 0;
}

TetrisBlock_s TetrisGrid_get (TetrisGrid_s* grid, int x, int y) {
	return grid->blocks[x + y * grid->width];
}

void TetrisGrid_set (TetrisGrid_s* grid, int x, int y, TetrisBlock_s block) {
	grid->blocks[x + y * grid->width] = block;
}

void TetrisGrid_clear (TetrisGrid_s* grid) {
	memset(grid->blocks, 0, 8 * 16 * sizeof(TetrisBlock_s));
}

void TetrisGrid_processLines (TetrisGrid_s* grid, int* score) {
	int scoreAdd = 0;
	TetrisGrid_emptyLines(grid, &scoreAdd);
	TetrisGrid_fallLines(grid);
	*score += scoreAdd;
}

void TetrisGrid_fallLines (TetrisGrid_s* grid) {
	for (int row = 0; row < grid->height; row++) {
		int emptyInRow = 0;

		for (int col = 0; col < grid->width; col++) {
			if (grid->blocks[col + row * grid->width].color == 0) {
				emptyInRow++;
			}
		}

		if (emptyInRow == grid->width) {
			TetrisBlock_s* copyDest = &grid->blocks[1 * grid->width];
			TetrisBlock_s* copySrc = &grid->blocks[0];
			int copySize = row * grid->width * sizeof(TetrisBlock_s);
			memcpy(copyDest, copySrc, copySize);
			memset(copySrc, 0, grid->width * sizeof(TetrisBlock_s));
		}
	}
}

void TetrisGrid_emptyLines (TetrisGrid_s* grid, int* score) {
	int linesCleared = 0;

	for (int row = 0; row < grid->height; row++) {
		int blocksInRow = 0;

		for (int col = 0; col < grid->width; col++) {
			if (grid->blocks[col + row * grid->width].color != 0) {
				blocksInRow++;
			}
		}

		if (blocksInRow == grid->width) {
			linesCleared++;

			for (int col = 0; col < grid->width; col++) {
				grid->blocks[col + row * grid->width].color = 0;
			}
		}
	}

	if (linesCleared == 0) {
		*score = 0;
	} else if (linesCleared == 1) {
		*score = 100;
	} else if (linesCleared == 2) {
		*score = 300;
	} else if (linesCleared == 3) {
		*score = 500;
	} else if (linesCleared == 4) {
		*score = 800;
	}
}

void TetrisGrid_render (TetrisGrid_s* grid) {
	for (int i = 0; i < grid->width * grid->height; i++) {
		TetrisBlock_s block = grid->blocks[i];
		
		     if (block.color == 0) SDL_SetRenderDrawColor(sdlRender, 0, 0, 0, 255);
		else if (block.color == 1) SDL_SetRenderDrawColor(sdlRender, 255, 0, 0, 255);
		else if (block.color == 2) SDL_SetRenderDrawColor(sdlRender, 0, 255, 0, 255);
		else if (block.color == 3) SDL_SetRenderDrawColor(sdlRender, 0, 0, 255, 255);
		else if (block.color == 4) SDL_SetRenderDrawColor(sdlRender, 255, 255, 0, 255);
		else if (block.color == 5) SDL_SetRenderDrawColor(sdlRender, 255, 0, 255, 255);
		else if (block.color == 6) SDL_SetRenderDrawColor(sdlRender, 0, 255, 255, 255);
		else if (block.color == 7) SDL_SetRenderDrawColor(sdlRender, 255, 128, 255, 255);

		const SDL_FRect destRect = {
			.x = (i % grid->width) * (TETRIS_RENDER_GRID_SCALE + TETRIS_RENDER_GRID_SPACE) + TETRIS_RENDER_GRID_X,
			.y = (i / grid->width) * (TETRIS_RENDER_GRID_SCALE + TETRIS_RENDER_GRID_SPACE) + TETRIS_RENDER_GRID_Y,
			.w = TETRIS_RENDER_GRID_SCALE,
			.h = TETRIS_RENDER_GRID_SCALE,
		};

		SDL_RenderFillRect(sdlRender, &destRect);
	}
}