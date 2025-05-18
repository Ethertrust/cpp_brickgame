// Copyright 2025 shericen
#ifndef BRICK_GAME_TETRIS_TETRISMODEL_H_
#define BRICK_GAME_TETRIS_TETRISMODEL_H_

#include <algorithm>
#include <utility>
#include <vector>

#include "../common/BaseModel.h"
#include "Tetromino.h"

namespace s21 {

struct TetrisGameData {
  bool is_modified;
  int t_score;
  int t_best_score;
  int t_level;
  GameState t_game_status;
  Tetromino t_curr;
  Tetromino t_projection;
  Tetromino t_next;
  std::vector<std::vector<std::pair<bool, int>>> t_field_;

  TetrisGameData()
      : is_modified(true),
        t_score(0),
        t_best_score(0),
        t_level(1),
        t_game_status(GameState::kStart),
        t_curr(),
        t_projection(),
        t_next(),
        t_field_() {}
  bool operator==(const TetrisGameData& other) const {
    return t_score == other.t_score && t_best_score == other.t_best_score &&
           t_level == other.t_level && t_game_status == other.t_game_status &&
           t_curr == other.t_curr && t_field_ == other.t_field_;
  }
  bool operator!=(const TetrisGameData& other) const {
    return !(*this == other);
  }
};

class TetrisModel : public BaseModel {
 public:
  TetrisModel();
  ~TetrisModel();

  TetrisGameData& GetTetrisGameData() { return t_data_; }
  void SetGameDataDefault();
  void UpdateModelData(UserAction act = UserAction::kNoSig);

  using Action = void (TetrisModel::*)();

  const Action kTetrisActionTable[6][9] = {
      // kStart
      {nullptr, nullptr, nullptr, nullptr, nullptr, &TetrisModel::StartGame,
       &TetrisModel::StartGame, &TetrisModel::ExitGame, nullptr},
      // kSpawn
      {&TetrisModel::SpawnNewTetromino, &TetrisModel::SpawnNewTetromino,
       &TetrisModel::SpawnNewTetromino, &TetrisModel::SpawnNewTetromino,
       &TetrisModel::SpawnNewTetromino, &TetrisModel::SpawnNewTetromino,
       &TetrisModel::SpawnNewTetromino, &TetrisModel::SpawnNewTetromino,
       &TetrisModel::SpawnNewTetromino},
      // kMoving,
      {nullptr, &TetrisModel::MoveTetrominoLeft,
       &TetrisModel::MoveTetrominoRight, &TetrisModel::MoveTetrominoDown,
       &TetrisModel::RotateTetromino, &TetrisModel::DropTetromino,
       &TetrisModel::DropTetromino, &TetrisModel::ExitGame,
       &TetrisModel::SetPause},
      // kCollide,
      {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
       nullptr},
      // kPause,
      {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
       &TetrisModel::CancelPause, &TetrisModel::ExitGame,
       &TetrisModel::CancelPause},
      // kGameOver,
      {&TetrisModel::ExitGame, &TetrisModel::ExitGame, &TetrisModel::ExitGame,
       &TetrisModel::ExitGame, &TetrisModel::ExitGame, &TetrisModel::ExitGame,
       &TetrisModel::ExitGame, &TetrisModel::ExitGame, &TetrisModel::ExitGame}};

 private:
  TetrisGameData t_data_;
  uint64_t last_moving_time_{};
  uint64_t curr_delay_{};

  bool CheckCollide();
  void UpdateBoard();
  void UpdatePlayerResults(int completed_lines);
  void InitializeBoard();
  void PlacePiece();
  int ClearLines();
  void SetProjection();
  void UpdateLevel();
  bool TryToMove(Tetromino* t, UserAction direction);

  // FSM ACTION METHODS
  void MoveTetrominoLeft();
  void MoveTetrominoRight();
  void MoveTetrominoDown();
  void DropTetromino();
  void RotateTetromino();
  void SpawnNewTetromino();
  void SetPause();
  void CancelPause();
  void ExitGame();
  // void Collide();
  void StartGame();
};

}  // namespace s21
#endif  // BRICK_GAME_TETRIS_TETRISMODEL_H_
