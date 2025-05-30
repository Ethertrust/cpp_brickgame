// Copyright 2025 shericen
#ifndef BRICK_GAME_SNAKE_SNAKEMODEL_H_
#define BRICK_GAME_SNAKE_SNAKEMODEL_H_

#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "../common/BaseModel.h"

struct Coordinates {
  Coordinates() : x(0), y(0) {}
  Coordinates(int x_, int y_) : x(x_), y(y_) {}
  bool operator==(const Coordinates& other) const {
    return (x == other.x && y == other.y);
  }
  int x;
  int y;
};

namespace s21 {

enum class Direction { kUp, kDown, kRight, kLeft };

enum class GameState { kStart, kSpawn, kMoving, kCollide, kPause, kGameOver };

struct SnakeGameData {
  Coordinates fruit_coord;
  std::vector<Coordinates> snake_coord;
  Direction direction;
  bool is_victory;
  GameState game_status;
  int curr_score;
  int best_score;
  int level;

  bool is_modified;

  SnakeGameData()
      : fruit_coord(),
        snake_coord(),
        direction(Direction::kUp),
        is_victory(false),
        game_status(GameState::kStart),
        curr_score(0),
        best_score(0),
        level(1),
        is_modified(true) {}

  bool operator==(const SnakeGameData& other) const {
    return curr_score == other.curr_score && game_status == other.game_status &&
           fruit_coord == other.fruit_coord && snake_coord == other.snake_coord;
  }
  bool operator!=(const SnakeGameData& other) const {
    return !(*this == other);
  }
};

class SnakeModel : public BaseModel {
 public:
  SnakeModel();
  ~SnakeModel();

  void UpdateData(UserAction action);

  void SetGameDataDefault();
  SnakeGameData& GetModelData();

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

  // for test
  void UpdateFruitPos(int x, int y);
  void SetGameDataDefault(int score);

 private:
  SnakeGameData s_data_;
  uint64_t last_moving_time_{};
  uint64_t curr_time_{};
  uint64_t curr_delay_{};

  void UpdateFruitPos();
  void MoveSnake();
  void CheckSnakeLife();
  void CheckSnakeEating();

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

#endif  // BRICK_GAME_SNAKE_SNAKEMODEL_H_
