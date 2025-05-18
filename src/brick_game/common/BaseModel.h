// Copyright 2025 shericen
#ifndef BRICK_GAME_COMMON_BASEMODEL_H_
#define BRICK_GAME_COMMON_BASEMODEL_H_

#include <sys/time.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "Constants.h"
namespace s21 {

class BaseModel {
 public:
  static uint64_t GetCurrTime();
  static void SaveScore(int score, const std::string &file_name);
  static int LoadScore(const std::string &file_name);
};

}  // namespace s21
#endif  // BRICK_GAME_COMMON_BASEMODEL_H_
