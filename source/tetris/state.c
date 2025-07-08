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

TetrisState TetrisState_new () {
	TetrisState state;
	TetrisState_init(&state);
	return state;
}

void TetrisState_init (TetrisState* state) {
	state->grid = TetrisGrid_new(TETRIS_GRID_WIDTH, TETRIS_GRID_HEIGHT);
	state->currentShape = TetrisShape_new();
	state->isPlaying = 0;
	state->isOver = 0;
	state->score = 0;
	state->highScore = 0;
}

void TetrisState_free (TetrisState* state) {
	TetrisGrid_free(&state->grid);
	TetrisShape_free(&state->currentShape);

	state->isPlaying = 0;
	state->isOver = 0;
	state->score = 0;
	state->highScore = 0;
}

void TetrisState_start (TetrisState* state) {
	TetrisGrid_clear(&state->grid);
	char shapeType = rand() % 7;
	TetrisState_changeShape(state, shapeType);
	state->currentShape.x = 3;
	state->isPlaying = 1;
	state->isOver = 0;
	state->score = 0;
}

void TetrisState_stop (TetrisState* state) {
	state->isPlaying = 0;
	state->isOver = 1;

	if (state->score > state->highScore) {
		state->highScore = state->score;
		Toast_message(&toast, "NEW RECORD", GAME_FPS_TARGET * 5);
	}
}

void TetrisState_moveLeft (TetrisState* state) {
	for (int i = 0; i < TETRIS_SHAPE_BLOCK_AMOUNT; i++) {
		TetrisShapeBlock shapeBlock = state->currentShape.blocks[i];

		if (state->currentShape.x + shapeBlock.x == 0) {
			return;
		}

		TetrisBlock leftGridBlock = TetrisGrid_get(
			&state->grid,
			state->currentShape.x + shapeBlock.x - 1,
			state->currentShape.y + shapeBlock.y);

		if (leftGridBlock.color != 0) {
			return;
		}
	}

	state->currentShape.x--;
}

void TetrisState_moveRight (TetrisState* state) {
	for (int i = 0; i < TETRIS_SHAPE_BLOCK_AMOUNT; i++) {
		TetrisShapeBlock shapeBlock = state->currentShape.blocks[i];

		if (state->currentShape.x + shapeBlock.x == TETRIS_GRID_WIDTH - 1) {
			return;
		}

		TetrisBlock rightGridBlock = TetrisGrid_get(
			&state->grid,
			state->currentShape.x + shapeBlock.x + 1,
			state->currentShape.y + shapeBlock.y);

		if (rightGridBlock.color != 0) {
			return;
		}
	}

	state->currentShape.x++;
}

void TetrisState_rotate (TetrisState* state) {
	TetrisShape_rotateCW(&state->currentShape);

	char shouldUndo = TetrisShape_collides(&state->currentShape, &state->grid, 0, 0);

	// Undoing the changes by rotating 90 degress counter-clockwise
	if (shouldUndo == 1) {
		TetrisShape_rotateCCW(&state->currentShape);
	}
}

void TetrisState_changeShape (TetrisState* state, char shapeType) {
	// Yes, this is bad
	if (shapeType == TETRIS_SHAPE_TYPE_I) {
		state->currentShape.blocks[0] = (TetrisShapeBlock) { 0, -2 };
		state->currentShape.blocks[1] = (TetrisShapeBlock) { 0, -1 };
		state->currentShape.blocks[2] = (TetrisShapeBlock) { 0,  0 };
		state->currentShape.blocks[3] = (TetrisShapeBlock) { 0,  1 };
		state->currentShape.y = 2;
		state->currentShape.color = TETRIS_SHAPE_TYPE_I + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_O) {
		state->currentShape.blocks[0] = (TetrisShapeBlock) { 0, 0 };
		state->currentShape.blocks[1] = (TetrisShapeBlock) { 0, 1 };
		state->currentShape.blocks[2] = (TetrisShapeBlock) { 1, 0 };
		state->currentShape.blocks[3] = (TetrisShapeBlock) { 1, 1 };
		state->currentShape.y = 0;
		state->currentShape.color = TETRIS_SHAPE_TYPE_O + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_S) {
		state->currentShape.blocks[0] = (TetrisShapeBlock) {  0,  0 };
		state->currentShape.blocks[1] = (TetrisShapeBlock) { -1,  1 };
		state->currentShape.blocks[2] = (TetrisShapeBlock) {  0,  1 };
		state->currentShape.blocks[3] = (TetrisShapeBlock) {  1,  0 };
		state->currentShape.y = 0;
		state->currentShape.color = TETRIS_SHAPE_TYPE_S + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_Z) {
		state->currentShape.blocks[0] = (TetrisShapeBlock) {  0,  0 };
		state->currentShape.blocks[1] = (TetrisShapeBlock) { -1, -1 };
		state->currentShape.blocks[2] = (TetrisShapeBlock) {  0, -1 };
		state->currentShape.blocks[3] = (TetrisShapeBlock) {  1,  0 };
		state->currentShape.y = 1;
		state->currentShape.color = TETRIS_SHAPE_TYPE_Z + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_L) {
		state->currentShape.blocks[0] = (TetrisShapeBlock) {  0,  0 };
		state->currentShape.blocks[1] = (TetrisShapeBlock) {  0, -1 };
		state->currentShape.blocks[2] = (TetrisShapeBlock) {  0,  1 };
		state->currentShape.blocks[3] = (TetrisShapeBlock) {  1,  1 };
		state->currentShape.y = 1;
		state->currentShape.color = TETRIS_SHAPE_TYPE_L + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_J) {
		state->currentShape.blocks[0] = (TetrisShapeBlock) {  0,  0 };
		state->currentShape.blocks[1] = (TetrisShapeBlock) {  0, -1 };
		state->currentShape.blocks[2] = (TetrisShapeBlock) {  0,  1 };
		state->currentShape.blocks[3] = (TetrisShapeBlock) { -1,  1 };
		state->currentShape.y = 1;
		state->currentShape.color = TETRIS_SHAPE_TYPE_J + 1;
	} else if (shapeType == TETRIS_SHAPE_TYPE_T) {
		state->currentShape.blocks[0] = (TetrisShapeBlock) {  0,  0 };
		state->currentShape.blocks[1] = (TetrisShapeBlock) { -1,  0 };
		state->currentShape.blocks[2] = (TetrisShapeBlock) {  1,  0 };
		state->currentShape.blocks[3] = (TetrisShapeBlock) {  0,  1 };
		state->currentShape.y = 0;
		state->currentShape.color = TETRIS_SHAPE_TYPE_T + 1;
	}

	state->currentShape.type = shapeType;
}

void TetrisState_update (TetrisState* state) {
	char canGoBottom = !TetrisShape_collides(&state->currentShape, &state->grid, 0, 1);
	char isStuck = TetrisShape_collides(&state->currentShape, &state->grid, 0, 0);

	if (canGoBottom) {
		state->currentShape.y++;
		return;
	}
	
	if (isStuck) {
		Toast_message(&toast, "Game Over", GAME_FPS_TARGET * 5);
		TetrisState_stop(state);
	}

	TetrisShape_applyToGrid(&state->currentShape, &state->grid);

	int addScore = 0;
	TetrisGrid_processLines(&state->grid, &addScore);
	state->score += addScore;
	
	char shapeType = rand() % 7;
	TetrisState_changeShape(state, shapeType);
	state->currentShape.x = 3;
}

void TetrisState_render (TetrisState* state) {
	TetrisGrid_render(&state->grid);
	TetrisShape_render(&state->currentShape);
}