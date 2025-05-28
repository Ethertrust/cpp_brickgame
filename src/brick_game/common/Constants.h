// Copyright 2025 shericen
#ifndef BRICK_GAME_COMMON_CONSTANTS_H_
#define BRICK_GAME_COMMON_CONSTANTS_H_

#include <iostream>
#include <vector>

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

// enum class GameState { kStart, kSpawn, kMoving, kCollide, kPause, kGameOver
// };

enum class UserAction {
  kNoSig = 0,
  kLeft,      // 1
  kRight,     // 2
  kDown,      // 3
  kUp,        // 4
  kSpaceBtn,  // 5
  kEnterBtn,  // 6
  kEscBtn,    // 7
  kTabBtn     // 8
};

}  // namespace s21

#endif  // BRICK_GAME_COMMON_CONSTANTS_H_
