// Copyright 2025 shericen
#include <gtest/gtest.h>

#include "../brick_game/tetris/fsm_matrix.h"
// #include "../static_L/tetris_back.h"

class TetrisGameTest : public ::testing::Test {
 protected:
  TetrisModel *tetris_model_;
  // TetrisGameData *tetris_game_data_;
};

TEST_F(TetrisGameTest, MoveLeft) {
  init_tetris_model(&tetris_model_); 
  // tetris_model_.SetGameDataDefault();
  // tetris_game_data_ = &tetris_model_.GetTetrisGameData();
  // EXPECT_EQ(tetris_model_->t_game_status, GameState::kStart);
  // TetrisUpdateModelData(tetris_model_, static_cast<UserAction>(kSpaceBtn));
  // EXPECT_EQ(tetris_model_->t_game_status, GameState::kSpawn);
  // TetrisUpdateModelData(tetris_model_, static_cast<UserAction>(kNoSig));
  // // tetris_model_.UpdateModelData(UserAction::kNoSig);
  // EXPECT_EQ(tetris_model_->t_game_status, GameState::kMoving);

  // auto tmp_coords = tetris_game_data_->t_curr.GetCoords();
  // // tetris_model_.UpdateModelData(UserAction::kDown);
  // // tetris_model_.UpdateModelData(UserAction::kDown);
  // tetris_model_.UpdateModelData(UserAction::kLeft);
  // tetris_model_.UpdateModelData(UserAction::kLeft);

  // for (size_t i = 0; i < tmp_coords.size(); i++) {
  //   EXPECT_EQ(tmp_coords[i].x - 2, tetris_game_data_->t_curr.GetCoords()[i].x);
  // }
}

// TEST_F(TetrisGameTest, MoveLeftUntilCant) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   GTEST_LOG_(INFO) << static_cast<int>(
//       tetris_game_data_->t_curr.GetShape());  // 7
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   auto tmp_coords = tetris_game_data_->t_curr.GetCoords();

//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);

//   bool x = false;
//   for (size_t i = 0; i < tmp_coords.size(); i++) {
//     EXPECT_GE(tetris_game_data_->t_curr.GetCoords()[i].x, 0);
//     if (tetris_game_data_->t_curr.GetCoords()[i].x == 0) {
//       x = true;
//     }
//   }
//   EXPECT_TRUE(x);
//   // usleep(510 * 1000);
//   // tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   tetris_model_.UpdateModelData(s21::UserAction::kUp);
// }

// TEST_F(TetrisGameTest, MoveRightUntilCant) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   GTEST_LOG_(INFO) << static_cast<int>(
//       tetris_game_data_->t_curr.GetShape());  // 6
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   auto tmp_coords = tetris_game_data_->t_curr.GetCoords();

//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);

//   bool x = false;
//   for (size_t i = 0; i < tmp_coords.size(); i++) {
//     EXPECT_LE(tetris_game_data_->t_curr.GetCoords()[i].x, 9);
//     if (tetris_game_data_->t_curr.GetCoords()[i].x == 9) {
//       x = true;
//     }
//   }
//   EXPECT_TRUE(x);
//   // usleep(510 * 1000);
//   // tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   tetris_model_.UpdateModelData(s21::UserAction::kUp);
// }

// TEST_F(TetrisGameTest, MoveRight) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
//   tetris_model_.UpdateModelData(s21::UserAction::kRight);
// }

// TEST_F(TetrisGameTest, MoveDown) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);
//   tetris_model_.UpdateModelData(s21::UserAction::kDown);
//   tetris_model_.UpdateModelData(s21::UserAction::kDown);
//   tetris_model_.UpdateModelData(s21::UserAction::kDown);
//   tetris_model_.UpdateModelData(s21::UserAction::kDown);
//   tetris_model_.UpdateModelData(s21::UserAction::kDown);
//   tetris_model_.UpdateModelData(s21::UserAction::kDown);
//   tetris_model_.UpdateModelData(s21::UserAction::kDown);
//   tetris_model_.UpdateModelData(s21::UserAction::kDown);
//   tetris_model_.UpdateModelData(s21::UserAction::kDown);
// }

// TEST_F(TetrisGameTest, Rotate) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   GTEST_LOG_(INFO) << static_cast<int>(tetris_game_data_->t_curr.GetShape());
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);
//   // usleep(510 * 1000);
//   // tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   tetris_model_.UpdateModelData(s21::UserAction::kUp);
//   tetris_model_.UpdateModelData(s21::UserAction::kUp);
//   tetris_model_.UpdateModelData(s21::UserAction::kUp);
// }

// TEST_F(TetrisGameTest, LeftBorderRotate) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   GTEST_LOG_(INFO) << static_cast<int>(
//       tetris_game_data_->t_curr.GetShape());  //
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kLeft);
//   tetris_model_.UpdateModelData(s21::UserAction::kUp);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);
// }

// TEST_F(TetrisGameTest, Drop) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
// }

// TEST_F(TetrisGameTest, Collide) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   for (int i = 0; i < 20; i++) {
//     tetris_model_.UpdateModelData(s21::UserAction::kDown);
//   }
//   usleep(510 * 1000);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   // EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);
// }

// TEST_F(TetrisGameTest, SetAndCancelPause) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   tetris_model_.UpdateModelData(s21::UserAction::kTabBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kPause);

//   tetris_model_.UpdateModelData(s21::UserAction::kTabBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   tetris_model_.UpdateModelData(s21::UserAction::kEscBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kGameOver);
// }

// TEST_F(TetrisGameTest, GameOver) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   while (tetris_game_data_->t_game_status != s21::GameState::kGameOver) {
//     tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   }
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kGameOver);
// }

// TEST_F(TetrisGameTest, AutoMovingDown) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   auto tmp_coords = tetris_game_data_->t_curr.GetCoords();

//   usleep(510 * 1000);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);

//   for (size_t i = 0; i < tmp_coords.size(); i++) {
//     EXPECT_EQ(tmp_coords[i].y + 1, tetris_game_data_->t_curr.GetCoords()[i].y);
//   }
// }

// TEST_F(TetrisGameTest, ClearOneLine) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   for (int i = 19; i < 20; ++i) {  // filling 1 lines
//     for (int j = 0; j < 10; ++j) {
//       tetris_game_data_->t_field_[i][j].first = true;
//     }
//   }

//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_score, 100);
// }

// TEST_F(TetrisGameTest, ClearTwoLines) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   for (int i = 18; i < 20; ++i) {  // filling 2 lines
//     for (int j = 0; j < 10; ++j) {
//       tetris_game_data_->t_field_[i][j].first = true;
//     }
//   }

//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_score, 300);
// }

// TEST_F(TetrisGameTest, ClearThreeLines) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   for (int i = 17; i < 20; ++i) {  // filling 3 lines
//     for (int j = 0; j < 10; ++j) {
//       tetris_game_data_->t_field_[i][j].first = true;
//     }
//   }

//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_score, 700);
// }

// TEST_F(TetrisGameTest, ClearFourLines) {
//   tetris_model_.SetGameDataDefault();
//   tetris_game_data_ = &tetris_model_.GetTetrisGameData();
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kStart);
//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kSpawn);
//   tetris_model_.UpdateModelData(s21::UserAction::kNoSig);
//   EXPECT_EQ(tetris_game_data_->t_game_status, s21::GameState::kMoving);

//   for (int i = 16; i < 20; ++i) {  // filling 4 lines
//     for (int j = 0; j < 10; ++j) {
//       tetris_game_data_->t_field_[i][j].first = true;
//     }
//   }

//   tetris_model_.UpdateModelData(s21::UserAction::kSpaceBtn);
//   EXPECT_EQ(tetris_game_data_->t_score, 1500);
// }
