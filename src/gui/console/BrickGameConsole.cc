// Copyright 2025 shericen
#include "common/BrickGameConsoleView.h"

int main() {
  s21::SnakeModel s_model;
  s21::SnakeController s_controller(&s_model);
  s21::TetrisController t_controller();
  s21::BrickGameConsoleView view(&s_controller, &t_controller);
  view.Start();
  return 0;
}
