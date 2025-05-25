#include "fsm_matrix.h"

#include <stdio.h>


// UserAction player_input(int input) {
//   UserAction action = 0;
//   switch (input) {
//     case KEY_LEFT:
//       action = kLeft;
//       break;
//     case KEY_RIGHT:
//       action = kRight;
//       break;
//     case KEY_DOWN:
//       action = kDown;
//       break;
//     case KEY_UP:
//       action = kUp;
//       break;
//     case 'p':
//     case 'P':
//       action = kPause;
//       break;
//     case 'q':
//     case 'Q':
//       action = kTerminate;
//       break;
//     case 's':
//     case 'S':
//       action = kStart;
//       break;
//     default:
//       break;
//   }
//   return action;
// }

// void game_pause() {
//   print_pause();
//   char c = 0;
//   while (c != 'p' && c != 's' && c != 'q') c = getch();
// }

void init_tetris_model(TetrisModel **state) {
  (*state) = (TetrisModel*)calloc(1, sizeof(TetrisModel));
  init_tetris_map(&((*state)->model));
}

void SpawnNewTetromino(TetrisModel *state) {
  switch (state->model->block) {
    case L_block:
      spawn_block(state->model, SPAWN_POS_X);
      break;
    case I_block:
      spawn_block(state->model, SPAWN_POS_X);
      break;
    case T_block:
      spawn_block(state->model, SPAWN_POS_X);
      break;
    case square:
      spawn_block(state->model, SPAWN_POS_X);
      break;
    case Z_block:
      spawn_block(state->model, SPAWN_POS_X);
      break;
    case RL_block:
      spawn_block(state->model, SPAWN_POS_X);
      break;
    case RZ_block:
      spawn_block(state->model, SPAWN_POS_X);
      break;
    default:
      break;
  }
  state->t_game_status = kMoving; 
  fprintf(stdout, "\n3.5\n");
}

void MoveTetrominoLeft(TetrisModel *state){ try_left(state->model); }
void MoveTetrominoRight(TetrisModel *state){ try_right(state->model); }
void MoveTetrominoDown(TetrisModel *state){ try_down(state->model); }
void DropTetromino(TetrisModel *state){ while(!(try_down(state->model))); }
void RotateTetromino(TetrisModel *state){ rotate_block(state->model); }

void SetPause(TetrisModel *state) { state->t_game_status = kPause; fprintf(stdout, "\n5\n");  }

void CancelPause(TetrisModel *state) { state->t_game_status = kMoving; fprintf(stdout, "\n4\n");  }

void ExitGame(TetrisModel *state) { state->t_game_status = kGameOver; fprintf(stdout, "\n6\n");  }

void StartGame(TetrisModel *state) { state->t_game_status = kSpawn; fprintf(stdout, "\n3\n"); }

void TetrisUpdateModelData(TetrisModel* state, UserAction act) {
  uint64_t curr_time = state->model->last_moving_time_;
  if (state->t_game_status != kPause) {
    curr_time = GetCurrTime();
  }

  Action func = kTetrisActionTable[(int)(state->t_game_status)]
                                  [(int)(act)];
  if (func) {
    (*func)(state);
  }

  if (state->t_game_status == kMoving) {
    if (curr_time - state->model->last_moving_time_ > state->model->curr_delay_) {
      state->model->last_moving_time_ = curr_time;
      game_process(state);
      MoveTetrominoDown(state);
    }
    UpdateLevel(state->model);
  }
}

// void game_loop_2() {
//   bool is_game = true;
//   TetrisModel state = {};
//   init_tetris_map(&state);
//   print_start_menu(*state.info);
//   state.block = get_random_block();
//   spawn_new_block(&state);
//   state.next_block = get_random_block();
//   clock_t timer_1 = clock();

//   while (is_game) {
//     set_new_level(&state);
//     print_game_window(updateCurrentState(), state.block, state.next_block);
//     refresh();
//     if (clock() - timer_1 > state.info->speed) {
//       is_game = game_process(&state);
//       timer_1 = clock();
//     }

//     int input_result = game_input(&state);
//     if (input_result == 1)
//       timer_1 = 0;
//     else if (input_result == 2)
//       is_game = false;

//     if (state.info->high_score < state.info->score) set_new_highscore(&state);
//   }
//   print_end_menu(state.info->score);
//   clear_tetris(&state);
// }

// int game_input(TetrisModel *state) {
//   int result = 0;
//   int input = 0;
//   if (kbhit()) {
//     input = getch();
//     UserAction t = player_input(input);
//     userInput(t, true);
//     if (t == Down) result = 1;
//     clear();
//     print_game_window(updateCurrentState(), state->block, state->next_block);
//     refresh();
//     if (t == Terminate) result = 2;
//     if (t == Pause) {
//       game_pause();
//     }
//   }

//   return result;
// }

bool game_process(TetrisModel *state) {
  bool result = true;
  if (try_down(state->model)) {
    active_to_block(state->model);
    if (get_score(state->model)) {
      result = false;
    } else {
      state->model->block = state->model->next_block;
      SpawnNewTetromino(state);
      state->model->next_block = get_random_block();
    }
  }
  return result;
}