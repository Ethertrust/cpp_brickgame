#ifndef FSM_MATRIX
#define FSM_MATRIX

#ifdef __cplusplus
extern "C" {
#endif

#include "tetris_back.h"

/**
 * @brief Enum with possible game states
 *
 */
typedef enum GameState { kStart, kSpawn, kMoving, kCollide, kPause, kGameOver } GameState;

/**
 * @brief Enum with possible user Action
 *
 */
typedef enum {
  kNoSig,
  kLeft,
  kRight,
  kDown,
  kUp,
  kSpaceBtn,
  kEnterBtn,
  kEscBtn,
  kTabBtn
} UserAction;

/**
 * @brief struct with all info for game map
 * @param model contains game map, score, level, speed and highscore of game
 * @param GameState current active state
 */
typedef struct {
  GameState t_game_status;
  Model* model;
} TetrisModel;

void init_tetris_model(TetrisModel **state);

// UserAction player_input(int input);
// void game_pause();
// int game_input(TetrisModel* state);
bool game_process(TetrisModel* state);
void TetrisUpdateModelData(TetrisModel* state, UserAction act);
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

#ifdef __cplusplus
}
#endif
#endif