// Copyright 2025 shericen
#ifndef GUI_DESKTOP_SNAKE_VIEW_H_
#define GUI_DESKTOP_SNAKE_VIEW_H_

#include <QDebug>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QWidget>
#include <QCloseEvent>
#include <utility>

#include "../../../controller/SnakeController.h"
#include "../../../controller/TetrisController.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

enum class CurrentGame { kNone, kSnake, kTetris };

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

  const QColor kColors[10] = {
      QColor(147, 147, 147),  // gray
      QColor(255, 0, 0),      // red
      QColor(103, 250, 0),    // green
      QColor(5, 240, 250),    // cyan
      QColor(250, 5, 249),    // purple
      QColor(250, 235, 5),    // yellow
      QColor(250, 124, 5),    // orange
      QColor(5, 20, 250),     // blue
      QColor(255, 255, 255),  // white
      QColor(0, 0, 0),        // black
  };

 protected:
  void keyPressEvent(QKeyEvent *) override;
  void paintEvent(QPaintEvent *event) override;
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void on_playAgain_clicked();
  void on_closeGame_clicked();
  void on_start_tetris_btn_clicked();
  void on_start_snake_btn_clicked();
  void on_exit_btn_clicked();

 private:
  QTimer *m_timer_;
  Ui::View *ui_;
  CurrentGame current_game_{};
  UserAction_t action_{};
  SnakeModel *s_data_;
  TetrisModel *t_data_;
  SnakeController *snake_controller_ = nullptr;
  TetrisController *tetris_controller_= nullptr;

  void ClearField();
  void GameOver(bool is_victory, int level, int score);
  void UpdateAll();
  void UpdateSnakeModel();
  void UpdateTetrisModel();
  void TetrisGameRendering();
  void SnakeGameRendering();
  static void StartWindowRendering(QLabel *p_label);
  static void PauseWindowRendering(QLabel *p_label);
};

}  // namespace s21

#endif  // GUI_DESKTOP_SNAKE_VIEW_H_
