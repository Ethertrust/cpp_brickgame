// Copyright 2025 shericen
#ifndef GUI_CONSOLE_SNAKE_SNAKECONSOLEVIEW_H_
#define GUI_CONSOLE_SNAKE_SNAKECONSOLEVIEW_H_

#include <string>
#include <vector>

#include "../../controller/SnakeController.h"
#include "../common/BaseView.h"

namespace s21 {

class SnakeConsoleView : public BaseView {
 public:
  explicit SnakeConsoleView(SnakeController *c);
  ~SnakeConsoleView() = default;

  void Start() override;

 private:
  void Rendering();
  void SnakeMainLoop();
  void ModelConnect();
  void GameRendering();

  UserAction action_{};
  SnakeGameData *data_;
  SnakeController *controller_;
};

}  // namespace s21

#endif  // GUI_CONSOLE_SNAKE_SNAKECONSOLEVIEW_H_
