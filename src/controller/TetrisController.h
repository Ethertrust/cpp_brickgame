// Copyright 2025 shericen
#ifndef CONTROLLER_TETRISCONTROLLER_H_
#define CONTROLLER_TETRISCONTROLLER_H_

// #include "../brick_game/tetris/TetrisModel.h"
#include "../static_L/tetris_back.h"

namespace s21 {

class TetrisController {
 public:
  explicit TetrisController(TetrisModel *model = nullptr) : model_(model) {}
  ~TetrisController() = default;

  void UpdateModelData(UserAction act = UserAction::kNoSig) {
    TetrisUpdateModelData(model_, act);
  }

  void SetModelDataDefault() { init_tetris_map(&model_->model); }
  Model &GetModelData() { return *(model_->model); }

 private:
  TetrisModel *model_;
  // TetrisModel *model_;
};

}  // namespace s21
#endif  // CONTROLLER_TETRISCONTROLLER_H_
