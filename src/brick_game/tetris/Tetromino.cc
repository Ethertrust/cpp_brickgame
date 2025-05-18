// Copyright 2025 shericen
#include "Tetromino.h"

namespace s21 {

Tetromino::Tetromino() {
  t_coords_.resize(4);
  SetRandomShape();
}

Tetromino::Tetromino(const Tetromino &other) {
  if (this != &other) {
    shape_ = other.shape_;
    position_ = other.position_;
    t_coords_ = other.t_coords_;
  }
}

Tetromino &Tetromino::operator=(const Tetromino &other) {
  if (this != &other) {
    shape_ = other.shape_;
    position_ = other.position_;
    t_coords_ = other.t_coords_;
  }
  return *this;
}

int Tetromino::GetMinX() {
  int res = t_coords_[0].x;
  for (int i = 0; i < 4; i++) {
    res = std::min(res, t_coords_[i].x);
  }
  return res;
}

int Tetromino::GetMaxX() {
  int res = t_coords_[0].x;
  for (int i = 0; i < 4; i++) {
    res = std::max(res, t_coords_[i].x);
  }
  return res;
}

int Tetromino::GetMinY() {
  int res = t_coords_[0].y;
  for (int i = 0; i < 4; i++) {
    res = std::min(res, t_coords_[i].y);
  }
  return res;
}

int Tetromino::GetMaxY() {
  int res = t_coords_[0].y;
  for (int i = 0; i < 4; i++) {
    res = std::max(res, t_coords_[i].y);
  }
  return res;
}

void Tetromino::Rotate() {

  // int center_x = GetMaxX() - 1;
  // int center_y = GetMaxY() - 1;

  // std::vector<Coordinates> oldCoords(4);
  // int rotationMatrix[2][2] = {{0, -1}, {1, 0}};
  std::pair<int, int> old_coords = {t_coords_[0].x, t_coords_[0].y};
  old_coords.first = old_coords.first - TetroCoords::coordsTable[static_cast<int>(shape_)][static_cast<int>(position_)][0][1];
  old_coords.second = old_coords.second - TetroCoords::coordsTable[static_cast<int>(shape_)][static_cast<int>(position_)][0][0];
  // for (int i = 0; i < 4; i++) {
  //   int x = t_coords_[i].x - (center_x);
  //   int y = t_coords_[i].y - (center_y);
  //   int newX = rotationMatrix[0][0] * x + rotationMatrix[0][1] * y + (center_x);
  //   int newY = rotationMatrix[1][0] * x + rotationMatrix[1][1] * y + (center_y);
  //   t_coords_[i] = {newX, newY};
  // }

  SetShape(shape_, static_cast<TetroPosition>(((static_cast<int>(position_))+1)%4));
  // int difX = t_coords_[0].x + old_coords.first;
  // int difY = t_coords_[0].y + old_coords.second;
  for (int i = 0; i < 4; i++)
    t_coords_[i] = {t_coords_[i].x + old_coords.first, t_coords_[i].y + old_coords.second};
  // t_coords_ = newCoords;
  // while (GetMinY() <= 0) {
  //   MoveDown();
  // }
  // while (GetMaxX() >= static_cast<int>(GameSizes::kFieldWidth)) {
  //   MoveLeft();
  // }
  // while (GetMinX() < 0) {
  //   MoveRight();
  // }
}

void Tetromino::SetRandomShape() {
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_int_distribution<int> distribution(1, 7);
  auto rand_shape = static_cast<TetroShape>(distribution(gen));
  SetShape(rand_shape, Top);
  for (int i = 0; i < 4; i++){
    t_coords_[i].x = t_coords_[i].x + (GameSizes::kFieldWidth / 2);
    t_coords_[i].y = t_coords_[i].y + 1;
  }
}

void Tetromino::SetShape(TetroShape s, TetroPosition p) {
  shape_ = s;
  position_ = p;
  for (int i = 0; i < 4; i++) {
    t_coords_[i].x = TetroCoords::coordsTable[static_cast<int>(s)][static_cast<int>(p)][i][1];
    t_coords_[i].y = TetroCoords::coordsTable[static_cast<int>(s)][static_cast<int>(p)][i][0];
  }
}

void Tetromino::MoveDown() {
  if (GetMaxY() < GameSizes::kFieldHeight) 
  for (auto &i : t_coords_) {
    i.y += 1;
  }
}

void Tetromino::MoveLeft() {
  if (GetMinX() >= 1) 
  for (auto &i : t_coords_) {
    i.x -= 1;
  }
}

void Tetromino::MoveRight() {
  if (GetMaxX() != GameSizes::kFieldWidth - 1)
  for (auto &i : t_coords_) {
    i.x += 1;
  }
}

}  // namespace s21
