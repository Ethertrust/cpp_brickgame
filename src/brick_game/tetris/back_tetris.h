/**
 * @file tetris_back.h
 * @author karstarl
 * @brief
 * @version 0.1
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef BRICK_GAME_TETRIS_BACKTETRIS_H_
#define BRICK_GAME_TETRIS_BACKTETRIS_H_
// cli
#define WINDOW_WIDTH 10
#define WINDOW_HEIGHT 21
#define SPAWN_POS_X 3
#define SPAWN_POS_Y 0
#define FILE_SCORE "./game_info/tetris_highscore_list.txt"
#define GAME_INFO_DIR "game_info"
#define BAD_ALLOC 1
#define INTERVALS \
  { 500, 420, 340, 260, 230, 200, 180, 160, 140, 125 }
// window
#define tDotSize 30
#define tFieldWidth 10
#define tFieldHeight 21
#define tSidePanelHeight 5
#define tWindowWidth 22
#define tWindowHeight 22

#include "../common/common.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
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

#ifdef __cplusplus
// C++-часть с конструкторами и операторами
struct TCoordinates {
  TCoordinates() : x(0), y(0){};
  TCoordinates(int x_, int y_) : x(x_), y(y_){};
  bool operator==(const TCoordinates& other) const {
    return (x == other.x && y == other.y);
  };

  int x;
  int y;
};

// extern "C" {
#else
// C-часть (только данные)
typedef struct {
  int x;
  int y;
} TCoordinates;
#endif

// #ifdef __cplusplus
// }  // extern "C"
// #endif

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

void UpdateLevel(Model* state);

uint64_t GetCurrTime();

/**
 * @brief moves active piece in left if is no obstacle
 * @param state current game state
 */
void try_left(Model* state);

/**
 * @brief moves active piece in right if is no obstacle
 * @param state current game state
 */
void try_right(Model* state);

/**
 * @brief moves active piece down if is no obstacle
 * @param state current game state
 * @return 1 if impossible to move down
 */
int try_down(Model* state);

/**
 * @brief rotate active piece on 90 degrees
 * @param state current game state
 */
void rotate_block(Model* state);

/**
 * @brief delete all dynamic objects
 * @param state current game state
 */
void clear_tetris(Model* state);

/**
 * @brief Get the random block object
 *
 * @return random block
 */
block_type get_random_block();

/**
 * @brief break full lines and update game score
 * @param state current game state
 * @return 1 if is game over
 */
int get_score(Model* state);

/**
 * @brief delete specified line
 * @param state current game state
 * @param line y position of line to delete
 */
void delete_line(Model* state, int line);

/**
 * @brief turns all active blocks in nonactive
 * @param state current game state
 */
void active_to_block(Model* state);

/**
 * @brief set new highscore, if score > highscore
 * @param state current game state
 */
void set_new_highscore(Model* state);

/**
 * @brief set new level depending on points scored
 * @param state current game state
 */
void set_new_level(Model* state);

// /**
//  * @brief Enum with possible user Action
//  *
//  */
// typedef enum {
//   kNoSig,
//   kLeft,
//   kRight,
//   kDown,
//   kUp,
//   kSpaceBtn,
//   kEnterBtn,
//   kEscBtn,
//   kTabBtn
// } UserAction_t;

// /**
//  * @brief make action from user input
//  *
//  * @param action current player action
//  * @param hold contain active user hold
//  */
// void userInput(UserAction_t action, bool hold);

/**
 * @brief chooses block state
 * @param buf where to save new block state
 * @param bt block type
 * @param pos block position
 * @param spawn_pos_x x coordinate for spawn position
 */
void choose_blstate(int** buf, block_type bt, position pos, int spawn_pos_x);

/**
 * @brief spawns new block
 * @param state current game state
 * @param spawn_pos_x x coordinate for spawn position
 */
void spawn_block(Model* state, int spawn_pos_x);

/**
 * @brief
 *
 * @return initialisation tetris map
 */
void init_tetris_map(Model** state);

/**
 * @brief safe memory allocation
 * @param size amount of memory
 * @return void pointer
 */
void* s21_malloc(const size_t size);

/**
 * @brief safe matrix memory allocation
 * @param y number of rows
 * @param x number of columns
 * @return int** pointer
 */
int** s21_malloc_matrix(const size_t y, const size_t x);

/**
 * @brief safe matrix memory release
 * @param matrix matrix pointer
 * @param r_size number of rows
 */
void free_matrix(int** matrix, int r_size);

void CastCoords(TCoordinates* Coordinates, Model* model);

static const uint64_t kIntervalMs[10] = INTERVALS;

static const int block_state[7][4][16] = {
    /*L_block*/ {{0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {2, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
                 {2, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {2, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0}},
    /*I_block*/
    {{0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0},
     {0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0}},
    /*T_block*/
    {{0, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
     {2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0}},
    /*square*/
    {{0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    /*Z_block*/
    {{2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
     {2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0}},
    /*RL_block*/
    {{2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
     {2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {2, 2, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0}},
    /*RZ_block*/
    {{0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
     {0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0}}};

#endif //BRICK_GAME_TETRIS_BACKTETRIS_H_