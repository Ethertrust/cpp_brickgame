// Copyright 2025 shericen
#ifndef BRICK_GAME_SNAKE_BACKSNAKE_H_
#define BRICK_GAME_SNAKE_BACKSNAKE_H_

#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "back_snake.h"

namespace s21 {

// enum class GameState_t { kStart, kSpawn, kMoving, kCollide, kPause, kGameOver };

// struct SnakeGameData {
//   Coordinates fruit_coord;
//   std::vector<Coordinates> snake_coord;
//   Direction direction;
//   bool is_victory;
//   GameState_t game_status;
//   int curr_score;
//   int best_score;
//   int level;

//   bool is_modified;

//   SnakeGameData()
//       : fruit_coord(),
//         snake_coord(),
//         direction(Direction::kUp),
//         is_victory(false),
//         game_status(GameState_t::kStart),
//         curr_score(0),
//         best_score(0),
//         level(1),
//         is_modified(true) {}

//   bool operator==(const SnakeGameData& other) const {
//     return curr_score == other.curr_score && game_status == other.game_status &&
//            fruit_coord == other.fruit_coord && snake_coord == other.snake_coord;
//   }
//   bool operator!=(const SnakeGameData& other) const {
//     return !(*this == other);
//   }
// };

class SnakeModel : public Model {
 public:
//   SnakeModel() { }
//   ~SnakeModel();

  void UpdateData(UserAction_t action);
  // void SetGameDataDefault();
  SnakeModel& GetModelData();
  const GameState_t& GetGameStatus() {return game_status;};
  const Direction& GetDirection() {return direction;};

 private:
  // SnakeGameData s_data_;
  Direction direction = Direction::kUp;
  GameState_t game_status = GameState_t::kStart;
  using Action = void (SnakeModel::*)();
  const Action kSnakeActionTable[6][9] = {
      // kStart
      {nullptr, nullptr, nullptr, nullptr, nullptr, &SnakeModel::StartGame,
       &SnakeModel::StartGame, &SnakeModel::ExitGame, nullptr},
      // kSpawn
      {&SnakeModel::Spawn, &SnakeModel::Spawn, &SnakeModel::Spawn,
       &SnakeModel::Spawn, &SnakeModel::Spawn, &SnakeModel::Spawn,
       &SnakeModel::Spawn, &SnakeModel::Spawn, &SnakeModel::Spawn},
      // kMoving,
      {nullptr, &SnakeModel::MoveHeadLeft, &SnakeModel::MoveHeadRight,
       &SnakeModel::MoveHeadDown, &SnakeModel::MoveHeadUp,
       &SnakeModel::SetPause, nullptr, &SnakeModel::ExitGame,
       &SnakeModel::SetPause},
      // kCollide,
      {&SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide,
       &SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide,
       &SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide},
      // kPause,
      {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
       &SnakeModel::CancelPause, &SnakeModel::ExitGame,
       &SnakeModel::CancelPause},
      // kGameOver,
      {&SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame,
       &SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame,
       &SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame}};
  void MoveSnake();
  // FSM ACTION METHODS
  void MoveHeadLeft();
  void MoveHeadRight();
  void MoveHeadDown();
  void MoveHeadUp();
  void Spawn();
  void SetPause();
  void CancelPause();
  void ExitGame();
  void Collide();
  void StartGame();
  void MoveSnakeBody();
};  // class SnakeModel

}  // namespace s21

#endif  // BRICK_GAME_SNAKE_BACKSNAKE_H_
