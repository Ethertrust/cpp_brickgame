// tetris_back.h
#ifndef TETRIS_BACK_H
#define TETRIS_BACK_H

#ifdef __cplusplus
extern "C" {
#endif

#define tDotSize 30
#define tFieldWidth 10
#define tFieldHeight 20
#define tSidePanelHeight 5
#define tWindowWidth 22
#define tWindowHeight 21
#include <stdint.h>

/**
 * @brief Enum with possible game states
 *
 */
typedef enum { kStart, kSpawn, kMoving, kCollide, kPause, kGameOver } GameState;

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
 * @brief enum with all block types of tetris
 *
 */
typedef enum block_type {
  L_block,
  I_block,
  T_block,
  square,
  Z_block,
  RL_block,
  RZ_block
} block_type;

/**
 * @brief enum with all types of game cell state
 *
 */
typedef enum cell_state { empty, block, active_block } cell_state;

typedef enum position { top, left, bottom, right } position;

/**
 * @brief Struct with main game info
 *
 * @param field Main tetris map
 * @param next Don`t use in tetris but need for other games
 * @param score Contains current score
 * @param high_score Contains best score of all games
 * @param level Contains difficult of game
 * @param speed not used in tetris
 * @param pause
 */
typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Contains 2 point of Rectangle shape
 *
 */
typedef struct {
  int x1;
  int x2;
  int y1;
  int y2;
  position pos;
} Rectangle_t;

/**
 * @brief struct with all info for game map
 * @param info contains game map, score, level, speed and highscore of game
 * @param block current active block
 * @param next_block next spawn block, when @param block get down
 * @param rect contains position of current active block
 */
typedef struct {
  GameInfo_t* info;
  block_type block;
  block_type next_block;
  Rectangle_t rect;
  uint64_t last_moving_time_;
  uint64_t curr_delay_;
} Model;

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

/**
 * @brief delete all dynamic objects
 * @param state current game state
 */
void clear_tetris(Model* state);

void CastCoords(int **x, int **y, Model *model);
// static const int block_state[7][4][16] = {
//   /*L_block*/ {{0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                {2, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
//                {2, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                {2, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0}},
//   /*I_block*/
//   {{0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0},
//    {0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0}},
//   /*T_block*/
//   {{0, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 2, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
//    {2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 2, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0}},
//   /*square*/
//   {{0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
//   /*Z_block*/
//   {{2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
//    {2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0}},
//   /*RL_block*/
//   {{2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 2, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
//    {2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {2, 2, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0}},
//   /*RZ_block*/
//   {{0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
//    {0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0}}};

void init_tetris_map(TetrisModel** state);
void TetrisUpdateModelData(TetrisModel* state, UserAction act);
int c_library_calculate(float value);

#ifdef __cplusplus
}
#endif

#endif  // TETRIS_BACK_H