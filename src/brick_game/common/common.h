// Copyright 2025 shericen
#ifndef BRICK_GAME_COMMON_COMMON_H_
#define BRICK_GAME_COMMON_COMMON_H_

#ifdef __cplusplus

// #include <iostream>
// #include <vector>
namespace s21 {

namespace GameSizes {
constexpr int kDotSize = 30;
constexpr int kFieldWidth = 10;
constexpr int kFieldHeight = 20;
constexpr int kSidePanelHeight = 5;
constexpr int kWindowWidth = 22;
constexpr int kWindowHeight = 21;
static constexpr int kIntervalMs[] = {500, 420, 340, 260, 230,
                                      200, 180, 160, 140, 125};
}  // namespace GameSizes

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
struct GameInfo_t {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;

  GameInfo_t() {
        field = new int*[GameSizes::kFieldHeight];  // Выделяем массив указателей
        for (size_t i = 0; i < GameSizes::kFieldWidth; ++i) {
            field[i] = new int(i * 10);  // Выделяем память для каждого int
        }
  }

  ~GameInfo_t() {
      for (size_t i = 0; i < GameSizes::kFieldWidth; ++i) {
          delete field[i];  // Освобождаем каждый int
      }
      delete[] field;
  }
};

/**
 * @brief
 *
 * @return current game state
 */
GameInfo_t updateCurrentState();

// typedef struct {
//   int** field;
//   int** next;
//   int score;
//   int high_score;
//   int level;
//   int speed;
//   int pause;
// } GameInfo_t;

}  // namespace s21

extern "C" {
#else

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
 * @brief
 *
 * @return current game state
 */
GameInfo_t updateCurrentState();

#endif //cplusplus
#include <stdbool.h>
/**
 * @brief Enum with possible game states
 *
 */
typedef enum {
  kStart,
  kSpawn,
  kMoving,
  kCollide,
  kPause,
  kGameOver
} GameState_t;

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
} UserAction_t;

/**
 * @brief make action from user input
 *
 * @param action current player action
 * @param hold contain active user hold
 */
void userInput(UserAction_t action, bool hold);




#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // BRICK_GAME_COMMON_COMMON_H_
