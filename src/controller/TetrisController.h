// Copyright 2025 karstarl
#ifndef CONTROLLER_TETRISCONTROLLER_H_
#define CONTROLLER_TETRISCONTROLLER_H_

// #include "../brick_game/tetris/TetrisModel.h"
#include "../static_L/tetris_back.h"
// #include "../brick_game/tetris/fsm_matrix.h"

// namespace s21 {

class TetrisController {
 public:
  explicit TetrisController(TetrisModel *model = nullptr) : model_(model) {}
  ~TetrisController() { clear_tetris(model_->model);
  free(model_);};

  void UpdateModelData(int act = 0) {
    std::cout << "state -> "<<model_->t_game_status << "act -> "<<act;
    TetrisUpdateModelData(model_, static_cast<UserAction>(act));
    std::cout << 2;
  }

  void SetModelDataDefault() { init_tetris_model(&model_); }
  
  TetrisModel &GetModelData() { return *model_; }
  std::vector<s21::Coordinates> GetCoords() { 
    t_coords_.resize(4);
    // Создаём временные C-массивы
    std::vector<int * > first_elements;
    std::vector<int * > second_elements;

    for (auto& p : t_coords_) {
        first_elements.push_back(&p.x);
        second_elements.push_back(&p.y);
    }
    std::cout << "violation";
    CastCoords(first_elements.data(), second_elements.data(), model_->model);
    // int j = 0;
    // for(int i = 0; i<4; ) { 

    //     t_coords_[i].x = j%4 + tFieldWidth / 2 -1; 
    //     t_coords_[i].y = j/4; 
    //     ++i;
    //   }
    //   while(block_state[model_->model->next_block][0][++j]==0);
    //   t_coords_[i].x = j%4 + tFieldWidth / 2 -1; 
    //   t_coords_[i].y = j/4; 
    //   ++i;
    //   ++j;
    // }
    return t_coords_; 
  }

 private:
  TetrisModel *model_;
  std::vector<s21::Coordinates> t_coords_;
};

// }  // namespace s21
#endif  // CONTROLLER_TETRISCONTROLLER_H_
