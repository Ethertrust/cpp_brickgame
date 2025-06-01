#ifndef BRICK_GAME_TETRIS_FSMETRIS_H_
#define BRICK_GAME_TETRIS_FSMETRIS_H_

#include "back_tetris.h"

/**
 * @brief struct with all info for game map
 * @param model contains game map, score, level, speed and highscore of game
 * @param GameState_t current active state
 */
typedef struct {
  GameState_t t_game_status;
  Model* model;
} TetrisModel;

void init_tetris_model(TetrisModel** state);

// UserAction_t player_input(int input);
// void game_pause();
// int game_input(TetrisModel* state);
bool game_process(TetrisModel* state);
void TetrisUpdateModelData(TetrisModel* state, UserAction_t act);
// void game_loop_2();
void MoveTetrominoLeft(TetrisModel* state);
void MoveTetrominoRight(TetrisModel* state);
void MoveTetrominoDown(TetrisModel* state);
void DropTetromino(TetrisModel* state);
void RotateTetromino(TetrisModel* state);
void SetPause(TetrisModel* state);
void CancelPause(TetrisModel* state);
void ExitGame(TetrisModel* state);
void StartGame(TetrisModel* state);
/**
 * @brief spawn new block on tetris map
 * @param state current game state
 * @param block type of spawn block
 */
void SpawnNewTetromino(TetrisModel* state);

/**
 * @brief set new game state or return current game state if *state == NULL
 * @param state current game state
 * @return current game state
 */
TetrisModel* get_set_current_map(TetrisModel* state);

typedef void (*Action)(TetrisModel*);

const Action kTetrisActionTable[6][9] = {
    // kStart
    {NULL, NULL, NULL, NULL, NULL, StartGame, StartGame, ExitGame, NULL},
    // kSpawn
    {SpawnNewTetromino, SpawnNewTetromino, SpawnNewTetromino, SpawnNewTetromino,
     SpawnNewTetromino, SpawnNewTetromino, SpawnNewTetromino, SpawnNewTetromino,
     SpawnNewTetromino},
    // kMoving
    {NULL, MoveTetrominoLeft, MoveTetrominoRight, MoveTetrominoDown,
     RotateTetromino, DropTetromino, DropTetromino, ExitGame, SetPause},
    // kCollide
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    // kPause
    {NULL, NULL, NULL, NULL, NULL, NULL, CancelPause, ExitGame, CancelPause},
    // kGameOver
    {ExitGame, ExitGame, ExitGame, ExitGame, ExitGame, ExitGame, ExitGame,
     ExitGame, ExitGame}};

#endif //BRICK_GAME_TETRIS_FSMETRIS_H_