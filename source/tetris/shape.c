#include <game/tetris/shape.h>

#include <game/tetris/block.h>
#include <game/tetris/grid.h>
#include <game/main.h>

#include <SDL3/SDL.h>

#include <stddef.h>
#include <stdlib.h>

TetrisShape TetrisShape_new () {
	TetrisShape shape;
	TetrisShape_init(&shape);
	return shape;
}

void TetrisShape_init (TetrisShape* shape) {
	shape->blocks = calloc(TETRIS_SHAPE_BLOCK_AMOUNT, sizeof(TetrisShapeBlock));
	shape->x = 0;
	shape->y = 0;
	shape->type = 0;
	shape->color = 0;
}

void TetrisShape_free (TetrisShape* shape) {
	free(shape->blocks);
	
	shape->blocks = NULL;
	shape->x = 0;
	shape->y = 0;
	shape->type = 0;
	shape->color = 0;
}

void TetrisShape_rotateCW_base (TetrisShape* shape) {
	for (int i = 0; i < TETRIS_SHAPE_BLOCK_AMOUNT; i++) {
		TetrisShapeBlock* shapeBlock = &shape->blocks[i];
		int prevX = shapeBlock->x;
		shapeBlock->x = -shapeBlock->y;
		shapeBlock->y = prevX;
	}
}

void TetrisShape_rotateCCW_base (TetrisShape* shape) {
	for (int i = 0; i < TETRIS_SHAPE_BLOCK_AMOUNT; i++) {
		TetrisShapeBlock* shapeBlock = &shape->blocks[i];
		int prevX = shapeBlock->x;
		shapeBlock->x = shapeBlock->y;
		shapeBlock->y = -prevX;
	}
}

void TetrisShape_rotateCW (TetrisShape* shape) {
	if (shape->type == TETRIS_SHAPE_TYPE_O) {
		return;
	}

	TetrisShape_rotateCW_base(shape);
}

void TetrisShape_rotateCCW (TetrisShape* shape) {
	if (shape->type == TETRIS_SHAPE_TYPE_O) {
		return;
	}

	TetrisShape_rotateCCW_base(shape);
}

char TetrisShape_collides (TetrisShape* shape, TetrisGrid* grid, int offsetX, int offsetY) {
	for (int i = 0; i < TETRIS_SHAPE_BLOCK_AMOUNT; i++) {
		TetrisShapeBlock shapeBlock = shape->blocks[i];

		int realBlockX = shape->x + shapeBlock.x + offsetX;
		int realBlockY = shape->y + shapeBlock.y + offsetY;

		if (realBlockX < 0 || realBlockX >= TETRIS_GRID_WIDTH) {
			return 1;
		} else if (realBlockY < 0 || realBlockY >= TETRIS_GRID_HEIGHT) {
			return 1;
		}

		TetrisBlock gridBlock = TetrisGrid_get(grid, realBlockX, realBlockY);

		if (gridBlock.color != 0) {
			return 1;
		}
	}
	
	return 0;
}

void TetrisShape_applyToGrid (TetrisShape* shape, TetrisGrid* grid) {
	for (int i = 0; i < TETRIS_SHAPE_BLOCK_AMOUNT; i++) {
		TetrisShapeBlock block = shape->blocks[i];
		
		TetrisGrid_set(grid, shape->x + block.x, shape->y + block.y, (TetrisBlock) {shape->color});
	}
}

void TetrisShape_render (TetrisShape* shape) {
	for (int i = 0; i < TETRIS_SHAPE_BLOCK_AMOUNT; i++) {
		TetrisShapeBlock block = shape->blocks[i];
		
		     if (shape->color == 0) SDL_SetRenderDrawColor(sdlRender, 0, 0, 0, 255);
		else if (shape->color == 1) SDL_SetRenderDrawColor(sdlRender, 255, 0, 0, 255);
		else if (shape->color == 2) SDL_SetRenderDrawColor(sdlRender, 0, 255, 0, 255);
		else if (shape->color == 3) SDL_SetRenderDrawColor(sdlRender, 0, 0, 255, 255);
		else if (shape->color == 4) SDL_SetRenderDrawColor(sdlRender, 255, 255, 0, 255);
		else if (shape->color == 5) SDL_SetRenderDrawColor(sdlRender, 255, 0, 255, 255);
		else if (shape->color == 6) SDL_SetRenderDrawColor(sdlRender, 0, 255, 255, 255);
		else if (shape->color == 7) SDL_SetRenderDrawColor(sdlRender, 255, 128, 255, 255);

		const SDL_FRect destRect = {
			.x = (shape->x + block.x) * (TETRIS_RENDER_GRID_SCALE + TETRIS_RENDER_GRID_SPACE) + TETRIS_RENDER_GRID_X,
			.y = (shape->y + block.y) * (TETRIS_RENDER_GRID_SCALE + TETRIS_RENDER_GRID_SPACE) + TETRIS_RENDER_GRID_Y,
			.w = TETRIS_RENDER_GRID_SCALE,
			.h = TETRIS_RENDER_GRID_SCALE,
		};

		SDL_RenderFillRect(sdlRender, &destRect);
	}
}