// Copyright 2025 karstarl
#ifndef CONTROLLER_TETRISCONTROLLER_H_
#define CONTROLLER_TETRISCONTROLLER_H_

// #include "../brick_game/tetris/TetrisModel.h"
#include "../static_L/tetris_back.h"
// #include "../brick_game/tetris/fsm_matrix.h"

// namespace s21 {

class TetrisController {
 public:
  explicit TetrisController(TetrisModel *model = nullptr) : model_(model) {}
  ~TetrisController() {
    clear_tetris(model_->model);
    free(model_);
  };

  void UpdateModelData(int act = 0) {
    TetrisUpdateModelData(model_, static_cast<UserAction_t>(act));
  }

  void SetModelDataDefault() { init_tetris_model(&model_); }

  TetrisModel &GetModelData() { *model_->model->info = updateCurrentState();
    return *model_; }

  const std::vector<TCoordinates> &GetCoords() {
    t_coords_.resize(4);
    CastCoords(t_coords_.data(), model_->model);

    return t_coords_;
  }

 private:
  TetrisModel *model_;
  std::vector<TCoordinates> t_coords_;
};

// }  // namespace s21
#endif  // CONTROLLER_TETRISCONTROLLER_H_
