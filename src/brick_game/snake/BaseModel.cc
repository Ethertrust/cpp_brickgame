// Copyright 2025 shericen

#include "BaseModel.h"

#include <sys/time.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>

namespace s21 {

uint64_t BaseModel::GetCurrTime() {
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  return static_cast<uint64_t>(tv.tv_sec) * 1000 + tv.tv_usec / 1000;
}

void BaseModel::SaveScore(int score, const std::string &file_name) {
  std::ofstream file(file_name);
  if (file.is_open()) {
    file << score;
    file.close();
  }
}

int BaseModel::LoadScore(const std::string &file_name) {
  int score = 0;
  std::ifstream file(file_name);
  if (file.is_open()) {
    file >> score;
    file.close();
  }
  return score;
}

}  // namespace s21
