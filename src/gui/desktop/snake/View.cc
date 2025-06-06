// Copyright 2025 shericen
#include "View.h"

#include "ui_View.h"

namespace s21 {

View::View(QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::View),
      current_game_(CurrentGame::kNone),
      action_(UserAction_t::kNoSig),
      s_data_(nullptr),
      t_data_(nullptr) {
  ui_->setupUi(this);
  move(1000, 300);
  setWindowTitle("Snake Game");
  ui_->stackedWidget->setCurrentIndex(1);
  // tetris_controller_->SetModelDataDefault();
  // t_data_ = &tetris_controller_->GetModelData();
  // snake_controller_->SetModelDataDefault();
  // s_data_ = &snake_controller_->GetModelData();
  m_timer_ = new QTimer(this);
  connect(m_timer_, &QTimer::timeout, this, &View::UpdateAll);
}

View::~View() {
  if (m_timer_ != nullptr) delete m_timer_;
  delete ui_;
}

void View::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  switch (key) {
    case Qt::Key_Left:
      action_ = UserAction_t::kLeft;
      break;
    case Qt::Key_Right:
      action_ = UserAction_t::kRight;
      break;
    case Qt::Key_Up:
      action_ = UserAction_t::kUp;
      break;
    case Qt::Key_Down:
      action_ = UserAction_t::kDown;
      break;
    case Qt::Key_Enter:
      action_ = UserAction_t::kEnterBtn;
      break;
    case Qt::Key_Tab:
      action_ = UserAction_t::kTabBtn;
      break;
    case Qt::Key_Space:
      action_ = UserAction_t::kSpaceBtn;
      break;
    case Qt::Key_Escape:
      action_ = UserAction_t::kEscBtn;
      break;
    default:
      break;
  }
}

void View::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  if (current_game_ == CurrentGame::kSnake) {
    if (s_data_->GetGameStatus() != GameState_t::kGameOver &&
        s_data_->GetGameStatus() != GameState_t::kCollide) {
      if (s_data_->GetGameStatus() == GameState_t::kStart) {
        StartWindowRendering(ui_->SnakeInfoLabel);
      } else if (s_data_->GetGameStatus() == GameState_t::kPause) {
        PauseWindowRendering(ui_->SnakeInfoLabel);
      } else {
        ui_->SnakeInfoLabel->setText("");
        SnakeGameRendering();
      }
    } else {
      ClearField();
      GameOver(s_data_->GetIsVictory(), s_data_->GetGameInfo().high_score, s_data_->GetGameInfo().score);
    }
  } else if (current_game_ == CurrentGame::kTetris) {
    if (t_data_->t_game_status != kGameOver &&
        t_data_->t_game_status != kCollide) {
      if (t_data_->t_game_status == kStart) {
        StartWindowRendering(ui_->TetrisInfoLabel);
      } else if (t_data_->t_game_status == kPause) {
        PauseWindowRendering(ui_->TetrisInfoLabel);
      } else {
        ui_->TetrisInfoLabel->setText("");
        TetrisGameRendering();
      }
    } else {
      ClearField();
      GameOver(false, t_data_->model->info->high_score,
               t_data_->model->info->score);
    }
  }
}

void View::ClearField() {
  QPainter painter(this);
  painter.eraseRect(rect());
  painter.end();
}

void View::GameOver(bool is_victory, int level, int score) {
  m_timer_->stop();
  ui_->stackedWidget->setCurrentIndex(0);
  if (is_victory) {
    ui_->GameStatus->setText("YOU WON!!!");
  } else {
    ui_->GameStatus->setText("GAME OVER!");
  }
  ui_->MenuCurrScore->setText(QString::number(score));
  ui_->MenuBestScore->setText(QString::number(level));
}

void View::UpdateAll() {
  if (current_game_ == CurrentGame::kSnake) {
    if (snake_controller_) UpdateSnakeModel();
  } else if (current_game_ == CurrentGame::kTetris) {
    if (tetris_controller_) UpdateTetrisModel();
  }
  repaint();
}

void View::on_playAgain_clicked() {
  if (current_game_ == CurrentGame::kTetris) {
    tetris_controller_->SetModelDataDefault();
    t_data_ = &tetris_controller_->GetModelData();
    ui_->stackedWidget->setCurrentIndex(3);
    m_timer_->start(10);
  } else if (current_game_ == CurrentGame::kSnake) {
    snake_controller_->SetModelDataDefault();
    s_data_ = &snake_controller_->GetModelData();
    ui_->stackedWidget->setCurrentIndex(2);
    m_timer_->start(10);
  } else if (current_game_ == CurrentGame::kNone) {
    ui_->stackedWidget->setCurrentIndex(1);
  }
}

void View::on_start_snake_btn_clicked() {
  // SnakeModel s_model;
  // SnakeController s_controller(&s_model);
  snake_controller_ = new SnakeController();
  current_game_ = CurrentGame::kSnake;
  snake_controller_->SetModelDataDefault();
  s_data_ = &snake_controller_->GetModelData();
  ui_->stackedWidget->setCurrentIndex(2);
  m_timer_->start(10);
}

void View::on_start_tetris_btn_clicked() {
  // TetrisController t_controller *;
  tetris_controller_ = new TetrisController();
  current_game_ = CurrentGame::kTetris;
  tetris_controller_->SetModelDataDefault();
  t_data_ = &tetris_controller_->GetModelData();
  ui_->stackedWidget->setCurrentIndex(3);
  m_timer_->start(10);
}

void View::closeEvent(QCloseEvent *event) {
  if(tetris_controller_ != nullptr) tetris_controller_->~TetrisController();
  if(snake_controller_ != nullptr)  snake_controller_->~SnakeController();
  event->accept();
}

void View::on_exit_btn_clicked() { close(); }

void View::on_closeGame_clicked() {
  if(tetris_controller_) {
    tetris_controller_->~TetrisController();
    tetris_controller_= nullptr;
  }
  if(snake_controller_) { 
    snake_controller_->~SnakeController(); 
    snake_controller_ = nullptr;
  }
  current_game_ = CurrentGame::kNone;
  ui_->stackedWidget->setCurrentIndex(1);
}

void View::UpdateSnakeModel() {
  snake_controller_->UpdateModelData(action_);
  // s_data_ = &snake_controller_->GetModelData();
  action_ = UserAction_t::kNoSig;
  ui_->CurrScore->setText(QString::number(s_data_->GetGameInfo().score));
  ui_->CurrLevel->setText(QString::number(s_data_->GetGameInfo().level));
  ui_->BestScore->setText(QString::number(s_data_->GetGameInfo().high_score));
  if (s_data_->GetGameStatus() == GameState_t::kGameOver ||
      s_data_->GetGameStatus() == GameState_t::kGameOver) {
    m_timer_->stop();
  }
}

void View::UpdateTetrisModel() {
  tetris_controller_->UpdateModelData(static_cast<int>(action_));
  // std::cout << 1;
  t_data_ = &tetris_controller_->GetModelData();
  action_ = static_cast<UserAction_t>(static_cast<int>(kNoSig));
  ui_->tetris_curr_score->setText(QString::number(t_data_->model->info->score));
  ui_->tetris_curr_level->setText(QString::number(t_data_->model->info->level));
  ui_->tetris_best_score->setText(
      QString::number(t_data_->model->info->high_score));
  if (t_data_->t_game_status == kGameOver ||
      t_data_->t_game_status == kGameOver) {
    m_timer_->stop();
  }
}

void View::SnakeGameRendering() {
  QPainter qp(this);
  QImage apple("images/apple.png");

  QRectF appleRect(s_data_->GetFruitX() * GameSizes::kDotSize,
                   s_data_->GetFruitY() * GameSizes::kDotSize,
                   GameSizes::kDotSize, GameSizes::kDotSize);
  QImage head("images/snake_head3.png");

  QRectF head_rect(s_data_->GetSnakeCoords() [0].x * GameSizes::kDotSize,
                   s_data_->GetSnakeCoords() [0].y * GameSizes::kDotSize,
                   GameSizes::kDotSize, GameSizes::kDotSize);

  QTransform transform;
  int rot = 0;
  if (s_data_->GetDirection() == Direction::kDown) {
    rot = 180;
  } else if (s_data_->GetDirection() != Direction::kUp) {
    rot = (s_data_->GetDirection() == Direction::kLeft ? -90 : 90);
  }
  head = head.transformed(transform.rotate(rot));

  qp.drawImage(appleRect, apple);

  for (std::size_t i = 0; i < s_data_->GetSnakeCoords() .size(); ++i) {
    qp.setBrush(QColor(148, 195, 76));
    qp.setPen(QColor(148, 195, 76));
    if (i == 0) {
      qp.drawImage(head_rect, head);
    } else {
      qp.drawRect(s_data_->GetSnakeCoords() [i].x * GameSizes::kDotSize,
                  s_data_->GetSnakeCoords() [i].y * GameSizes::kDotSize,
                  GameSizes::kDotSize - 1, GameSizes::kDotSize - 1);
    }
  }
  qp.end();
}

void View::TetrisGameRendering() {
  QPainter qp(this);

  // qp.setBrush(QColor(90, 90, 90));
  qp.setPen(kColors[9]);

  // // current tetromino projection
  // qp.setBrush(kColors[0]);
  // for (const auto &item : t_data_->t_projection.GetCoords()) {
  //   qp.drawRect((item.x) * GameSizes::kDotSize,
  //               (item.y - 1) * GameSizes::kDotSize, GameSizes::kDotSize - 1,
  //               GameSizes::kDotSize - 1);
  // }

  // qp.setBrush(QColor(148, 195, 76));
  // // current tetromino
  // for (const auto &item : t_data_->t_curr.GetCoords()) {
  //   qp.setBrush(kColors[static_cast<int>(t_data_->model->block)]);
  //   qp.drawRect(item.x * tDotSize,
  //               (item.y - 1) * tDotSize, tDotSize - 1,
  //               tDotSize - 1);
  // }

  // next tetromino
  // std::cout << 0.5 ;
  for (const auto &item : tetris_controller_->GetCoords()) {
    qp.setBrush(kColors[static_cast<int>(t_data_->model->next_block) + 1]);
    qp.drawRect((item.x + 8) * tDotSize, (item.y + 2) * tDotSize, tDotSize - 1,
                tDotSize - 1);
  }
  // std::cout << 0.6 ;
  // board
  for (int i = 1; i < tFieldHeight; ++i) {
    for (int j = 0; j < tFieldWidth; ++j) {
      if (t_data_->model->info->field[i][j] == 0)
        qp.setBrush(
            kColors[9]);  // static_cast<int>(t_data_->model->field[i][j])
      else if (t_data_->model->info->field[i][j] == 1)
        qp.setBrush(
            kColors[8]);  // static_cast<int>(t_data_->model->field[i][j])
      else if (t_data_->model->info->field[i][j] == 2)
        qp.setBrush(
            kColors[static_cast<int>(t_data_->model->block) +
                    1]);  // static_cast<int>(t_data_->model->field[i][j])
      qp.drawRect(j * tDotSize, (i - 1) * tDotSize, tDotSize - 1, tDotSize - 1);
    }
  }
  // std::cout << 0.7 ;
  qp.end();
}

void View::StartWindowRendering(QLabel *p_label) {
  p_label->setText("Press space to start");
  p_label->setStyleSheet("border: none;");
}

void View::PauseWindowRendering(QLabel *p_label) {
  p_label->setText(
      "Game on pause.<br> Press Tab to continue<br> or Esc to exit");
}

}  // namespace s21
