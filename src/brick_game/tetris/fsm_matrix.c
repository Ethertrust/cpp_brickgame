#include "fsm_matrix.h"

#include <stdio.h>

UserAction player_input(int input) {
  UserAction action = 0;
  switch (input) {
    case KEY_LEFT:
      action = kLeft;
      break;
    case KEY_RIGHT:
      action = kRight;
      break;
    case KEY_DOWN:
      action = kDown;
      break;
    case KEY_UP:
      action = kUp;
      break;
    case 'p':
    case 'P':
      action = kPause;
      break;
    case 'q':
    case 'Q':
      action = kTerminate;
      break;
    case 's':
    case 'S':
      action = kStart;
      break;
    default:
      break;
  }
  return action;
}

void game_pause() {
  print_pause();
  char c = 0;
  while (c != 'p' && c != 's' && c != 'q') c = getch();
}

void StartGame(TetrisModel *state) {
  // SetGameDataDefault();
  state.t_game_status = GameState::kSpawn;
}

void UpdateModelData(TetrisModel** state, UserAction act) {
  t_data_.is_modified = false;
  TetrisModel data_cast = t_data_;

  uint64_t curr_time = last_moving_time_;
  if (t_data_.t_game_status != GameState::kPause) {
    curr_time = GetCurrTime();
  }

  Action func = kTetrisActionTable[static_cast<int>((*state)->t_game_status)]
                                  [static_cast<int>(act)];
  if (func) {
    (this->*func)();
  }

  if (t_data_.t_game_status == GameState::kMoving) {
    if (curr_time - last_moving_time_ > curr_delay_) {
      last_moving_time_ = curr_time;
      if (CheckCollide()) UpdateBoard();
      MoveTetrominoDown();
    }
    UpdateLevel();
  }

  if (t_data_ != data_cast) {
    t_data_.is_modified = true;
  }
}

void game_loop_2() {
  bool is_game = true;
  TetrisModel state = {};
  init_tetris_map(&state);
  print_start_menu(*state.info);
  state.block = get_random_block();
  spawn_new_block(&state);
  state.next_block = get_random_block();
  clock_t timer_1 = clock();

  while (is_game) {
    set_new_level(&state);
    print_game_window(updateCurrentState(), state.block, state.next_block);
    refresh();
    if (clock() - timer_1 > state.info->speed) {
      is_game = game_process(&state);
      timer_1 = clock();
    }

    int input_result = game_input(&state);
    if (input_result == 1)
      timer_1 = 0;
    else if (input_result == 2)
      is_game = false;

    if (state.info->high_score < state.info->score) set_new_highscore(&state);
  }
  print_end_menu(state.info->score);
  clear_tetris(&state);
}

int game_input(TetrisModel *state) {
  int result = 0;
  int input = 0;
  if (kbhit()) {
    input = getch();
    UserAction t = player_input(input);
    userInput(t, true);
    if (t == Down) result = 1;
    clear();
    print_game_window(updateCurrentState(), state->block, state->next_block);
    refresh();
    if (t == Terminate) result = 2;
    if (t == Pause) {
      game_pause();
    }
  }

  return result;
}

bool game_process(TetrisModel *state) {
  bool result = true;
  if (try_down(state)) {
    active_to_block(state);
    clear();
    if (get_score(state)) {
      result = false;
    } else {
      state->block = state->next_block;
      spawn_new_block(state);
      state->next_block = get_random_block();
    }
  }
  print_game_window(updateCurrentState(), state->block, state->next_block);
  refresh();
  return result;
}