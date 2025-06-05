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
  GameInfo_t *info = nullptr;
  Coordinates fruit_coord;
  
 public:
  Model() : is_victory(false) {
    info = new GameInfo_t;
    info->high_score = LoadScore(FILE_SCORE);
    SetGameDataDefault(info->score);
    updateCurrentState();
    // ref_info = GetGameInfo();
    // get_set_current_map(this);
  }
  ~Model() {
    SaveScore(FILE_SCORE);
    snake_coord.clear();
  }
  // GameInfo_t &ref_info = GetGameInfo();
  GameInfo_t& GetGameInfo() { return *info; };
  bool checkinfoptr() {return info != nullptr;};
  GameInfo_t updateCurrentState() {
      GameInfo_t& current = GetGameInfo(); 
      info->next = nullptr;
      info->score = current.score;         
      info->high_score = current.high_score;
      info->level = current.level;
      info->speed = current.speed;
      info->pause = current.pause;
      for (int i = 0; i < GameSizes::kFieldHeight; ++i)
        for (int j = 0; j < GameSizes::kFieldWidth; ++j)
            {info->field[i][j] = current.field[i][j]>0;}
 
    return *info;
  }
  // GameInfo_t G_GameInfo() {return *info;};
  const bool& GetIsVictory() {return is_victory;};
  const int& GetFruitX() {return fruit_coord.x;};
  const int& GetFruitY() {return fruit_coord.y;};
  const std::vector<Coordinates>& GetSnakeCoords() {return snake_coord;};
  uint64_t GetCurrTime();
  void SaveScore(const std::string &file_name);
  int LoadScore(const std::string &file_name);
  void SetGameDataDefault(int score);
  // GameInfo_t temp;

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
