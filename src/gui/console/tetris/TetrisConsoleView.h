// Copyright 2025 shericen
#ifndef GUI_CONSOLE_TETRIS_TETRISCONSOLEVIEW_H_
#define GUI_CONSOLE_TETRIS_TETRISCONSOLEVIEW_H_

#include "../../controller/TetrisController.h"
#include "../common/BaseView.h"

namespace s21 {

class TetrisConsoleView : public BaseView {
 public:
  explicit TetrisConsoleView(TetrisController *c = nullptr);
  void Start() override;

 private:
  UserAction t_action_;

  TetrisModel *t_data_;
  TetrisController *controller_;
  void TetrisMainLoop();
  void ModelConnect();
  void GameRendering();
  void Rendering();
};

}  // namespace s21
#endif  // GUI_CONSOLE_TETRIS_TETRISCONSOLEVIEW_H_
