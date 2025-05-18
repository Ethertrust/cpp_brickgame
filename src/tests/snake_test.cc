// Copyright 2025 shericen
#include <gtest/gtest.h>

#include "../brick_game/snake/SnakeModel.h"

class SnakeGameTest : public ::testing::Test {
 protected:
  s21::SnakeModel snake_model_;
  s21::SnakeGameData *snake_game_data_;
};

TEST_F(SnakeGameTest, MoveSnakeUp) {
  snake_model_.SetGameDataDefault();
  snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kUp);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kUp);
}

TEST_F(SnakeGameTest, MoveSnakeLeft) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kLeft);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kLeft);
}

TEST_F(SnakeGameTest, MoveSnakeRight) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kRight);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kRight);
}

TEST_F(SnakeGameTest, MoveSnakeAround) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kRight);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kRight);
  snake_model_.UpdateData(s21::UserAction::kDown);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kDown);
  snake_model_.UpdateData(s21::UserAction::kLeft);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kLeft);
  snake_model_.UpdateData(s21::UserAction::kUp);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::kUp);
}

TEST_F(SnakeGameTest, AutoMovingUp) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  usleep(510 * 1000);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
}

TEST_F(SnakeGameTest, AutoMovingLeft) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kLeft);
  usleep(510 * 1000);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
}

TEST_F(SnakeGameTest, AutoMovingRight) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kRight);
  usleep(510 * 1000);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
}

TEST_F(SnakeGameTest, AutoMovingDown) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kRight);
  snake_model_.UpdateData(s21::UserAction::kDown);
  usleep(510 * 1000);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
}

TEST_F(SnakeGameTest, SetAndCancelPauseAndExit) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kTabBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kPause);
  snake_model_.UpdateData(s21::UserAction::kTabBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kEscBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kGameOver);
}

TEST_F(SnakeGameTest, CollideGameOver) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  while (snake_game_data_->game_status != s21::GameState::kGameOver) {
    snake_model_.UpdateData(s21::UserAction::kUp);
  }
}

TEST_F(SnakeGameTest, WinGameOver) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.SetGameDataDefault(199);
  snake_model_.UpdateFruitPos(5, (s21::GameSizes::kFieldHeight / 2) - 1);
  snake_model_.UpdateData(s21::UserAction::kUp);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kGameOver);
}

TEST_F(SnakeGameTest, MovingRightCollide) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kRight);
  snake_model_.UpdateData(s21::UserAction::kRight);
  snake_model_.UpdateData(s21::UserAction::kRight);
  snake_model_.UpdateData(s21::UserAction::kRight);
  snake_model_.UpdateData(s21::UserAction::kRight);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kGameOver);
}

TEST_F(SnakeGameTest, EatingAppleAndSnake) {
  snake_model_.SetGameDataDefault();
  s21::SnakeGameData *snake_game_data_ = &snake_model_.GetModelData();
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kStart);
  snake_model_.UpdateData(s21::UserAction::kSpaceBtn);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kSpawn);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  snake_model_.UpdateFruitPos(5, (s21::GameSizes::kFieldHeight / 2) - 1);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kMoving);
  snake_model_.UpdateData(s21::UserAction::kUp);
  snake_model_.UpdateData(s21::UserAction::kRight);
  snake_model_.UpdateData(s21::UserAction::kDown);
  snake_model_.UpdateData(s21::UserAction::kLeft);
  snake_model_.UpdateData(s21::UserAction::kNoSig);
  EXPECT_EQ(snake_game_data_->game_status, s21::GameState::kGameOver);
}
