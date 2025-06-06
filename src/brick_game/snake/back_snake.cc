// Copyright 2025 shericen

#include "back_snake.h"

#include <sys/time.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

namespace s21 {

// Model *get_set_current_map(Model *state) {
//   static Model *state_;
//   if (state != NULL) {
//     state_ = state;
//   }
//   return state_;
// }

// GameInfo_t updateCurrentState() {
//   Model *state = get_set_current_map(NULL);
//   // GameInfo_t *temp = new GameInfo_t();
//   state->GetGameInfo();
//   // temp->next = NULL;
//   // temp->score =  state->GetGameInfo().score;
//   // temp->high_score =  state->GetGameInfo().high_score;
//   // temp->level =  state->GetGameInfo().level;
//   // temp->speed =  state->GetGameInfo().speed;
//   // temp->pause =  state->GetGameInfo().pause;
//   // for (int i = 0; i < GameSizes::kFieldHeight; ++i)
//   //   for (int j = 0; j < GameSizes::kFieldWidth; ++j)
//   //       temp->field[i][j] =  state->GetGameInfo().field[i][j];
//   // std::cout << temp->level;
//   return  state->GetGameInfo();
// }

// Model::Model() : is_victory(false) {
//     info = new GameInfo_t();
//     info->high_score = LoadScore(FILE_SCORE);
//     SetGameDataDefault(info->score);
//     // get_set_current_map(this);
// }

// GameInfo_t& Model::GetGameInfo() { 
//   // updateCurrentState();
//   // *this->info = temp;
//   // GameInfo_t temp = this->updateCurrentState();
//   this->updateCurrentState();
//   return *this->info;
// }

Model::Model() : is_victory(false) {
  info = new GameInfo_t;
  LoadScore(FILE_SCORE);
  SetGameDataDefault(0);
  updateCurrentState();
  // ref_info = GetGameInfo();
  // get_set_current_map(this);
  std::cerr << "Model off!\n";
}
Model::~Model() {
  SaveScore(FILE_SCORE);
  // snake_coord.clear();
  // delete &snake_coord;
  // delete info;
}

bool Model::checkinfoptr() {return info != nullptr;}

GameInfo_t Model::updateCurrentState() {
  std::cerr << "updateCurrentState on!\n";
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
  std::cerr << "updateCurrentState off!\n";
  return *info;
}

const bool& Model::GetIsVictory() {return is_victory;}
const int& Model::GetFruitX() {return fruit_coord.x;}
const int& Model::GetFruitY() {return fruit_coord.y;}
const std::vector<Coordinates>& Model::GetSnakeCoords() {return snake_coord;}
const int& Model::GetScore() { return info->score; }
const int& Model::GetHighScore() { return info->high_score; }
const int& Model::GetLevel() { return info->level; }

void Model::SetGameDataDefault(int score = 0) {
  std::cerr << "SetGameDataDefault on!\n";
  curr_delay_ = GameSizes::kIntervalMs[0];
  last_moving_time_ = curr_time_ = GetCurrTime();
  info->score = score;
  info->level = 1;
  snake_coord.clear();
  snake_coord.reserve(200);

  snake_coord.push_back({5, GameSizes::kFieldHeight / 2});
  snake_coord.push_back({5, GameSizes::kFieldHeight / 2 + 1});
  snake_coord.push_back({5, GameSizes::kFieldHeight / 2 + 2});
  snake_coord.push_back({5, GameSizes::kFieldHeight / 2 + 3});

  UpdateFruitPos();
  std::cerr << "SetGameDataDefault off!\n";
}

void Model::UpdateFruitPos() {
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_int_distribution<int> width_distribution(
      0, GameSizes::kFieldWidth - 1);
  std::uniform_int_distribution<int> height_distribution(
      0, GameSizes::kFieldHeight - 1);

  fruit_coord.x = width_distribution(gen);
  fruit_coord.y = height_distribution(gen);

  for (const auto& i : snake_coord) {
    if (fruit_coord.x == i.x && fruit_coord.y == i.y)
      UpdateFruitPos();
  }
}

void Model::UpdateFruitPos(int x, int y) {
  fruit_coord.x = x;
  fruit_coord.y = y;
}

bool Model::CheckSnakeLife() {
  bool alive = true;
  for (std::size_t i = 1; i < snake_coord.size(); ++i) {
    if (snake_coord[0] == snake_coord[i]) {
      alive = false;
      // game_status = GameState_t::kCollide;
    }
  }
  if (snake_coord[0].x < 0 ||
      snake_coord[0].x >= GameSizes::kFieldWidth) {
          alive = false;
      // game_status = GameState_t::kCollide;
  }
  if (snake_coord[0].y < 0 ||
      snake_coord[0].y >= GameSizes::kFieldHeight) {
      alive = false;
      // game_status = GameState_t::kCollide;
  }
  return alive;
}

bool Model::CheckSnakeEating() {
  bool alive = true;
  if (snake_coord[0] == fruit_coord) {
    snake_coord.push_back({-1, -1});
    info->score++;
    if (info->score % 5 == 0 && info->level < 10) {
      info->level++;
      curr_delay_ = GameSizes::kIntervalMs[info->level - 1];
    }
    if (info->score > info->high_score) {
      info->high_score = info->score;
    }
    if (info->score == 200) {
      is_victory = true;
      alive = false;
    }
    UpdateFruitPos();
  }
  return alive;
}

uint64_t Model::GetCurrTime() {
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  return static_cast<uint64_t>(tv.tv_sec) * 1000 + tv.tv_usec / 1000;
}

void Model::SaveScore(const std::string &file_name) {
  std::cerr << "SaveScore вызван!\n";
  std::ofstream file(file_name);
  if (file.is_open()) {
    file << this->info->high_score;
  }
  else {
    std::ofstream new_file(file_name);
    if (new_file.is_open()) new_file << this->info->high_score;
    new_file.close();
  }
  file.close();
}

void Model::LoadScore(const std::string &file_name) {
    std::cerr << "LoadScore вызван!\n";
    std::ifstream file(file_name);
    if ((file.is_open())) file >> this->info->high_score;
    else this->info->high_score = 0;
    file.close();
    std::cerr << "LoadScore завершен!\n";
}

// int Model::LoadScore(const std::string &file_name) {
//   std::ifstream file(file_name);
//   if (file.is_open()) {
//     file >> this->info->high_score;
//     file.close();
//   }
//   return this->info->score;
// }

}  // namespace s21
