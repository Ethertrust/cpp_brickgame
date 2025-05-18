// Copyright 2025 shericen
#include "BrickGameConsoleView.h"

namespace s21 {

BrickGameConsoleView::BrickGameConsoleView(SnakeController *s_c,
                                           TetrisController *t_c)
    : snake_view_(s_c), tetris_view_(t_c) {}

void BrickGameConsoleView::Start() {
  setlocale(LC_ALL, "");
  InitNcurses();
  MainLoop();
}

void BrickGameConsoleView::InitNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);

  start_color();
  InitColors();
}

void BrickGameConsoleView::MainLoop() {
  Choose ch = InitMenu();

  while (ch != Choose::kGameOver) {
    if (ch == Choose::kSnake) {
      snake_view_.Start();
    } else if (ch == Choose::kTetris) {
      tetris_view_.Start();
    }
    ch = InitMenu();
  }

  curs_set(1);
  endwin();
}

void BrickGameConsoleView::InitColors() {
  init_color((int16_t)ColorIndex::kRed, 1000, 0, 0);
  init_color((int16_t)ColorIndex::kGreen, 0, 1000, 0);
  init_color((int16_t)ColorIndex::kCyan, 0, 1000, 1000);
  init_color((int16_t)ColorIndex::kPurple, 1000, 0, 1000);
  init_color((int16_t)ColorIndex::kYellow, 1000, 1000, 0);
  init_color((int16_t)ColorIndex::kOrange, 1000, 500, 0);
  init_color((int16_t)ColorIndex::kBlue, 0, 0, 1000);
  init_color((int16_t)ColorIndex::kGray, 500, 500, 500);

  init_pair(1, (int16_t)ColorIndex::kRed,
            (int16_t)ColorIndex::kRed);  // Красный
  init_pair(2, (int16_t)ColorIndex::kGreen,
            (int16_t)ColorIndex::kGreen);  // Зеленый
  init_pair(3, (int16_t)ColorIndex::kCyan,
            (int16_t)ColorIndex::kCyan);  // Голубой
  init_pair(4, (int16_t)ColorIndex::kPurple,
            (int16_t)ColorIndex::kPurple);  // Фиолетовый
  init_pair(5, (int16_t)ColorIndex::kYellow,
            (int16_t)ColorIndex::kYellow);  // Желтый
  init_pair(6, (int16_t)ColorIndex::kOrange,
            (int16_t)ColorIndex::kOrange);  // Оранжевый
  init_pair(7, (int16_t)ColorIndex::kBlue,
            (int16_t)ColorIndex::kBlue);  // Синий
  init_pair(8, (int16_t)ColorIndex::kGray,
            (int16_t)ColorIndex::kGray);  // Серый
}

}  // namespace s21
