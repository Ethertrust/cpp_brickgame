#ifndef FSM_MATRIX
#define FSM_MATRIX

#include "../brick_game/tetris/tetris_back_3.h"
#include "../gui/cli/tetris_frontend.h"
#include <sys/time.h>

UserAction player_input(int input);
void game_pause();
int game_input(TetrisModel* state);
bool game_process(TetrisModel* state);
void TetrisUpdateModelData(TetrisModel** state, UserAction act);
void game_loop_2();
void StartGame(TetrisModel *state);

#endif