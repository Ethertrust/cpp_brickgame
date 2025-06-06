// Copyright 2025 karstarl
#ifndef CONTROLLER_SNAKECONTROLLER_H_
#define CONTROLLER_SNAKECONTROLLER_H_

#include "../brick_game/snake/fsm_snake.h"

namespace s21 {

class SnakeController {
 public:
  explicit SnakeController() {model_ = new SnakeModel();}
  ~SnakeController() {
  delete model_;
  }
  void UpdateModelData(UserAction_t action = UserAction_t::kUp) {
    model_->UpdateData(action);
  }

  void SetModelDataDefault() { model_->SetGameDataDefault(0); }
  SnakeModel &GetModelData() { //model_->updateCurrentState();
    return *model_; }

 private:
  SnakeModel *model_;
};

}  // namespace s21
#endif  // CONTROLLER_SNAKECONTROLLER_H_
