// Copyright 2025 shericen
#include <QApplication>

#include "View.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  // s21::SnakeModel s_model;
  // s21::SnakeController s_controller(&s_model);
  // TetrisController t_controller;
  s21::View* v = new s21::View();
  v->show();
  return QApplication::exec();
}
