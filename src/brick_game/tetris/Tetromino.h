// Copyright 2025 shericen
#ifndef BRICK_GAME_TETRIS_TETROMINO_H_
#define BRICK_GAME_TETRIS_TETROMINO_H_

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>

#include "../common/Constants.h"

namespace s21 {

enum struct TetroShape {
  NoShape,
  SShape,
  ZShape,
  LineShape,
  TShape,
  SquareShape,
  MirroredLShape,
  LShape
};

typedef enum TetroPosition { Top, Right, Bottom, Left } position;

namespace TetroCoords {
static constexpr int coordsTable[8][4][4][2] = {
    {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
     {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
     {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
     {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},  // NoShape
    {{{1, -1}, {1, 0}, {0, 0}, {0, 1}},
     {{0, -1}, {1, -1}, {1, 0}, {2, 0}},
     {{1, -1}, {1, 0}, {0, 0}, {0, 1}},
     {{0, -1}, {1, -1}, {1, 0}, {2, 0}}},  // SShape
    {{{0, -1}, {0, 0}, {1, 0}, {1, 1}},
     {{0, 0}, {1, 0}, {1, -1}, {2, -1}},
     {{0, -1}, {0, 0}, {1, 0}, {1, 1}},
     {{0, 0}, {1, 0}, {1, -1}, {2, -1}}},  // ZShape
    {{{0, -2}, {0, -1}, {0, 0}, {0, 1}},
     {{-1, -1}, {0, -1}, {1, -1}, {2, -1}},
     {{0, -2}, {0, -1}, {0, 0}, {0, 1}},
     {{-1, -1}, {0, -1}, {1, -1}, {2, -1}}},  // LineShape
    {{{1, 1}, {1, 0}, {1, -1}, {0, 0}},
     {{2, 0}, {1, 0}, {0, 0}, {1, 1}},
     {{1, -1}, {1, 0}, {1, 1}, {2, 0}},
     {{0, 0}, {1, 0}, {2, 0}, {1, -1}}},  // TShape
    {{{0, -1}, {0, 0}, {1, 0}, {1, -1}},
     {{0, -1}, {0, 0}, {1, 0}, {1, -1}},
     {{0, -1}, {0, 0}, {1, 0}, {1, -1}},
     {{0, -1}, {0, 0}, {1, 0}, {1, -1}}},  // SquareShape
    {{{0, -1}, {1, -1}, {1, 0}, {1, 1}},
     {{0, 0}, {0, -1}, {1, -1}, {2, -1}},
     {{1, 1}, {0, 1}, {0, 0}, {0, -1}},
     {{2, -1}, {2, 0}, {1, 0}, {0, 0}}},  // MirroredLShape
    {{{1, -1}, {1, 0}, {1, 1}, {0, 1}},
     {{0, -1}, {1, -1}, {2, -1}, {2, 0}},
     {{0, 1}, {0, 0}, {0, -1}, {1, -1}},
     {{2, 0}, {1, 0}, {0, 0}, {0, -1}}}  // LShape
};
};  // namespace TetroCoords

class Tetromino {
 public:
  Tetromino();
  Tetromino(const Tetromino &other);
  Tetromino &operator=(const Tetromino &other);

  std::vector<Coordinates> GetCoords() { return t_coords_; }

  bool operator==(const Tetromino &other) const {
    return shape_ == other.shape_ && t_coords_ == other.t_coords_;
  }
  bool operator!=(const Tetromino &other) const { return !(*this == other); }

  void SetShape(TetroShape s, TetroPosition p);
  void SetRandomShape();

  TetroShape GetShape() { return shape_; }
  void Rotate();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

  int GetMinX();
  int GetMaxX();
  int GetMinY();
  int GetMaxY();

 private:
  TetroShape shape_;
  TetroPosition position_;
  std::vector<Coordinates> t_coords_;
};

}  // namespace s21
#endif  // BRICK_GAME_TETRIS_TETROMINO_H_
