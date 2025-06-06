// Copyright 2025 shericen
#include "fsm_snake.h"

namespace s21 {


void SnakeModel::SetSnakeDataDefault(int score) {
  SetGameDataDefault(score);
  game_status = GameState_t::kStart;
  direction = Direction::kUp;
}

void SnakeModel::UpdateData(UserAction_t action) {
  // s_data_.is_modified = false;
  // SnakeGameData data_cast = s_data_;

  curr_time_ = last_moving_time_;
  if (game_status != GameState_t::kPause) {
    curr_time_ = GetCurrTime();
  }

  Action func = kSnakeActionTable[static_cast<int>(game_status)]
                                 [static_cast<int>(action)];
  if (func) {
    (this->*func)();
  }

  if (game_status == GameState_t::kMoving) {
    if (curr_time_ - last_moving_time_ > curr_delay_) {
      MoveSnake();
    }
  }
  // if (checkinfoptr()) this->updateCurrentState();
  // if (s_data_ != data_cast) s_data_.is_modified = true;
}

SnakeModel& SnakeModel::GetModelData() { 
  // updateCurrentState();
  return *this; }

// void SnakeModel::SetGameDataDefault() {
//   curr_delay_ = GameSizes::kIntervalMs[0];
//   last_moving_time_ = curr_time_ = GetCurrTime();
//   s_data_.curr_score = 0;
//   s_data_.level = 1;
//   s_data_.direction = Direction::kUp;
//   s_data_.game_status = GameState_t::kStart;
//   s_data_.snake_coord.clear();
//   s_data_.snake_coord.reserve(200);

//   s_data_.snake_coord.push_back({5, GameSizes::kFieldHeight / 2});
//   s_data_.snake_coord.push_back({5, GameSizes::kFieldHeight / 2 + 1});
//   s_data_.snake_coord.push_back({5, GameSizes::kFieldHeight / 2 + 2});
//   s_data_.snake_coord.push_back({5, GameSizes::kFieldHeight / 2 + 3});

//   UpdateFruitPos();
// }

void SnakeModel::MoveSnakeBody() {
  for (auto i = snake_coord.size(); i > 0; --i) {
    snake_coord[i] = snake_coord[i - 1];
  }
}

void SnakeModel::MoveSnake() {
  switch (direction) {
    case Direction::kUp:
      MoveHeadUp();
      break;
    case Direction::kDown:
      MoveHeadDown();
      break;
    case Direction::kLeft:
      MoveHeadLeft();
      break;
    case Direction::kRight:
      MoveHeadRight();
      break;
  }
}

void SnakeModel::MoveHeadLeft() {
  if (direction == Direction::kRight) return;
  direction = Direction::kLeft;
  MoveSnakeBody();
  snake_coord[0].x -= 1;

  if(!CheckSnakeEating()) Collide();
  if(!CheckSnakeLife()) Collide();
  last_moving_time_ = curr_time_;
}

void SnakeModel::MoveHeadRight() {
  if (direction == Direction::kLeft) return;
  direction = Direction::kRight;
  MoveSnakeBody();
  snake_coord[0].x += 1;
  if(!CheckSnakeEating()) Collide();
  if(!CheckSnakeLife()) Collide();
  last_moving_time_ = curr_time_;
}

void SnakeModel::MoveHeadUp() {
  if (direction == Direction::kDown) return;
  direction = Direction::kUp;
  MoveSnakeBody();
  snake_coord[0].y -= 1;
  if(!CheckSnakeEating()) Collide();
  if(!CheckSnakeLife()) Collide();
  last_moving_time_ = curr_time_;
}

void SnakeModel::MoveHeadDown() {
  if (direction == Direction::kUp) return;
  direction = Direction::kDown;
  MoveSnakeBody();
  snake_coord[0].y += 1;
  if(!CheckSnakeEating()) Collide();
  if(!CheckSnakeLife()) Collide();
  last_moving_time_ = curr_time_;
}

void SnakeModel::Spawn() { game_status = GameState_t::kMoving; }

void SnakeModel::SetPause() { game_status = GameState_t::kPause; }

void SnakeModel::CancelPause() { game_status = GameState_t::kMoving; }

void SnakeModel::ExitGame() { game_status = GameState_t::kGameOver; }

void SnakeModel::Collide() { game_status = GameState_t::kGameOver; }

void SnakeModel::StartGame() { game_status = GameState_t::kSpawn; }

}  // namespace s21
