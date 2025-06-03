// Copyright 2025 shericen
#ifndef BRICK_GAME_COMMON_BACKSNAKE_H_
#define BRICK_GAME_COMMON_BACKSNAKE_H_

#define FILE_SCORE "./game_info/snake_highscore_list.txt"
#include <sys/time.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "../common/common.h"

struct Coordinates {
  Coordinates() : x(0), y(0) {}
  Coordinates(int x_, int y_) : x(x_), y(y_) {}
  bool operator==(const Coordinates& other) const {
    return (x == other.x && y == other.y);
  }
  int x;
  int y;
};

namespace s21 {

enum class Direction { kUp, kDown, kRight, kLeft };

class Model {
 private:
  void UpdateFruitPos();
  bool is_victory;
  GameInfo_t *info;
  Coordinates fruit_coord;

 public:
  Model();
  ~Model() {
    SaveScore(FILE_SCORE);
    snake_coord.clear();
  }
  GameInfo_t& GetGameInfo() {return *info;};
  GameInfo_t G_GameInfo() {return *info;};
  const bool& GetIsVictory() {return is_victory;};
  const int& GetFruitX() {return fruit_coord.x;};
  const int& GetFruitY() {return fruit_coord.y;};
  const std::vector<Coordinates>& GetSnakeCoords() {return snake_coord;};
  uint64_t GetCurrTime();
  void SaveScore(const std::string &file_name);
  int LoadScore(const std::string &file_name);
  void SetGameDataDefault(int score);
  GameInfo_t temp;

 protected:
  std::vector<Coordinates> snake_coord;
  void UpdateFruitPos(int x, int y);
  bool CheckSnakeLife();
  bool CheckSnakeEating();
  uint64_t last_moving_time_{};
  uint64_t curr_time_{};
  uint64_t curr_delay_{};
  // bool is_modified;
};

Model *get_set_current_map(Model *state);

}  // namespace s21
#endif  // BRICK_GAME_COMMON_BACKSNAKE_H_
