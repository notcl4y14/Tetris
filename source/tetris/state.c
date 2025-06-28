#include <game/tetris/state.h>

#include <game/tetris/block.h>
#include <game/tetris/grid.h>
#include <game/tetris/shape.h>
#include <game/main.h>
#include <game/state.h>
#include <game/toast.h>

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

TetrisState_s TetrisState_new () {
	TetrisState_s state;
	TetrisState_init(&state);
	return state;
}

void TetrisState_init (TetrisState_s* state) {
	state->grid = TetrisGrid_new(TETRIS_GRID_WIDTH, TETRIS_GRID_HEIGHT);
	state->shape = TetrisShape_new();
	state->isPlaying = 0;
	state->isOver = 0;
	state->score = 0;
	state->highScore = 0;
}

void TetrisState_free (TetrisState_s* state) {
	TetrisGrid_free(&state->grid);
	TetrisShape_free(&state->shape);

	state->isPlaying = 0;
	state->isOver = 0;
	state->score = 0;
	state->highScore = 0;
}

void TetrisState_start (TetrisState_s* state) {
	TetrisGrid_clear(&state->grid);
	char shapeType = rand() % 7;
	TetrisState_changeShape(state, shapeType);
	state->shape.x = 3;
	state->isPlaying = 1;
	state->isOver = 0;
	state->score = 0;
}

void TetrisState_stop (TetrisState_s* state) {
	state->isPlaying = 0;
	state->isOver = 1;

	if (state->score > state->highScore) {
		state->highScore = state->score;
		Toast_message(&toast, "NEW RECORD", GAME_FPS_TARGET * 5);
	}
}

void TetrisState_moveLeft (TetrisState_s* state) {
	for (int i = 0; i < TETRIS_SHAPE_BLOCK_AMOUNT; i++) {
		TetrisShapeBlock_s shapeBlock = state->shape.blocks[i];

		if (state->shape.x + shapeBlock.x == 0) {
			return;
		}

		TetrisBlock_s leftGridBlock = TetrisGrid_get(
			&state->grid,
			state->shape.x + shapeBlock.x - 1,
			state->shape.y + shapeBlock.y);

		if (leftGridBlock.color != 0) {
			return;
		}
	}

	state->shape.x--;
}

void TetrisState_moveRight (TetrisState_s* state) {
	for (int i = 0; i < TETRIS_SHAPE_BLOCK_AMOUNT; i++) {
		TetrisShapeBlock_s shapeBlock = state->shape.blocks[i];

		if (state->shape.x + shapeBlock.x == TETRIS_GRID_WIDTH - 1) {
			return;
		}

		TetrisBlock_s rightGridBlock = TetrisGrid_get(
			&state->grid,
			state->shape.x + shapeBlock.x + 1,
			state->shape.y + shapeBlock.y);

		if (rightGridBlock.color != 0) {
			return;
		}
	}

	state->shape.x++;
}

void TetrisState_rotate (TetrisState_s* state) {
	TetrisShape_rotateCW(&state->shape);

	char shouldUndo = TetrisShape_collides(&state->shape, &state->grid, 0, 0);

	// Undoing the changes by rotating 90 degress counter-clockwise
	if (shouldUndo == 1) {
		TetrisShape_rotateCCW(&state->shape);
	}
}

void TetrisState_changeShape (TetrisState_s* state, char shapeType) {
	if (shapeType == TETRIS_SHAPE_TYPE_I) {
		state->shape.blocks[0] = (TetrisShapeBlock_s) { 0, -2 };
		state->shape.blocks[1] = (TetrisShapeBlock_s) { 0, -1 };
		state->shape.blocks[2] = (TetrisShapeBlock_s) { 0,  0 };
		state->shape.blocks[3] = (TetrisShapeBlock_s) { 0,  1 };
		state->shape.y = 2;
		state->shape.color = TETRIS_SHAPE_TYPE_I + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_O) {
		state->shape.blocks[0] = (TetrisShapeBlock_s) { 0, 0 };
		state->shape.blocks[1] = (TetrisShapeBlock_s) { 0, 1 };
		state->shape.blocks[2] = (TetrisShapeBlock_s) { 1, 0 };
		state->shape.blocks[3] = (TetrisShapeBlock_s) { 1, 1 };
		state->shape.y = 0;
		state->shape.color = TETRIS_SHAPE_TYPE_O + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_S) {
		state->shape.blocks[0] = (TetrisShapeBlock_s) {  0,  0 };
		state->shape.blocks[1] = (TetrisShapeBlock_s) { -1,  1 };
		state->shape.blocks[2] = (TetrisShapeBlock_s) {  0,  1 };
		state->shape.blocks[3] = (TetrisShapeBlock_s) {  1,  0 };
		state->shape.y = 0;
		state->shape.color = TETRIS_SHAPE_TYPE_S + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_Z) {
		state->shape.blocks[0] = (TetrisShapeBlock_s) {  0,  0 };
		state->shape.blocks[1] = (TetrisShapeBlock_s) { -1, -1 };
		state->shape.blocks[2] = (TetrisShapeBlock_s) {  0, -1 };
		state->shape.blocks[3] = (TetrisShapeBlock_s) {  1,  0 };
		state->shape.y = 1;
		state->shape.color = TETRIS_SHAPE_TYPE_Z + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_L) {
		state->shape.blocks[0] = (TetrisShapeBlock_s) {  0,  0 };
		state->shape.blocks[1] = (TetrisShapeBlock_s) {  0, -1 };
		state->shape.blocks[2] = (TetrisShapeBlock_s) {  0,  1 };
		state->shape.blocks[3] = (TetrisShapeBlock_s) {  1,  1 };
		state->shape.y = 1;
		state->shape.color = TETRIS_SHAPE_TYPE_L + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_J) {
		state->shape.blocks[0] = (TetrisShapeBlock_s) {  0,  0 };
		state->shape.blocks[1] = (TetrisShapeBlock_s) {  0, -1 };
		state->shape.blocks[2] = (TetrisShapeBlock_s) {  0,  1 };
		state->shape.blocks[3] = (TetrisShapeBlock_s) { -1,  1 };
		state->shape.y = 1;
		state->shape.color = TETRIS_SHAPE_TYPE_J + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_T) {
		state->shape.blocks[0] = (TetrisShapeBlock_s) {  0,  0 };
		state->shape.blocks[1] = (TetrisShapeBlock_s) { -1,  0 };
		state->shape.blocks[2] = (TetrisShapeBlock_s) {  1,  0 };
		state->shape.blocks[3] = (TetrisShapeBlock_s) {  0,  1 };
		state->shape.y = 0;
		state->shape.color = TETRIS_SHAPE_TYPE_T + 1;
	}

	state->shape.type = shapeType;
}

void TetrisState_update (TetrisState_s* state) {
	char canGoBottom = !TetrisShape_collides(
		&state->shape, &state->grid, 0, 1);

	if (canGoBottom) {
		state->shape.y++;
		return;
	}
	
	char isStuck = TetrisShape_collides(
		&state->shape, &state->grid, 0, 0);
	
	if (isStuck) {
		Toast_message(&toast, "Game Over", GAME_FPS_TARGET * 5);
		TetrisState_stop(state);
	}

	TetrisShape_applyToGrid(&state->shape, &state->grid);

	int addScore = 0;
	TetrisGrid_processLines(&state->grid, &addScore);
	state->score += addScore;
	
	char shapeType = rand() % 7;
	TetrisState_changeShape(state, shapeType);
	state->shape.x = 3;
}

void TetrisState_render (TetrisState_s* state) {
	TetrisGrid_render(&state->grid);
	TetrisShape_render(&state->shape);
}