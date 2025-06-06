// snake_back.h
#ifndef SNAKE_BACK_H
#define SNAKE_BACK_H
#include <vector>
#include <iostream>
#define FILE_SCORE "./game_info/snake_highscore_list.txt"

// Объявления функций

struct Coordinates {
  Coordinates() : x(0), y(0) {}
  Coordinates(int x_, int y_) : x(x_), y(y_) {}
  bool operator==(const Coordinates& other) const {
    return (x == other.x && y == other.y);
  }
  int x;
  int y;
};


/**
 * @brief Enum with possible game states
 *
 */
typedef enum {
  kStart,
  kSpawn,
  kMoving,
  kCollide,
  kPause,
  kGameOver
} GameState_t;

/**
 * @brief Enum with possible user Action
 *
 */
typedef enum {
  kNoSig,
  kLeft,
  kRight,
  kDown,
  kUp,
  kSpaceBtn,
  kEnterBtn,
  kEscBtn,
  kTabBtn
} UserAction_t;

namespace s21 {

namespace GameSizes {
constexpr int kDotSize = 30;
constexpr int kFieldWidth = 10;
constexpr int kFieldHeight = 20;
constexpr int kSidePanelHeight = 5;
constexpr int kWindowWidth = 22;
constexpr int kWindowHeight = 21;
static constexpr int kIntervalMs[] = {500, 420, 340, 260, 230,
                                      200, 180, 160, 140, 125};
}  // namespace GameSizes

/**
 * @brief Struct with main game info
 *
 * @param field Main tetris map
 * @param next Don`t use in tetris but need for other games
 * @param score Contains current score
 * @param high_score Contains best score of all games
 * @param level Contains difficult of game
 * @param speed not used in tetris
 * @param pause
 */
struct GameInfo_t {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;

  GameInfo_t() {
        field = new int*[GameSizes::kFieldHeight]; 
        for (size_t i = 0; i < GameSizes::kFieldHeight; ++i) {
            field[i] = new int[GameSizes::kFieldWidth];  
        }
  }

  ~GameInfo_t() {
      for (size_t i = 0; i < GameSizes::kFieldHeight; ++i) {
          delete[] field[i]; 
      }
      delete[] field;
      // field = nullptr;
  }
};

enum class Direction { kUp, kDown, kRight, kLeft };

class Model {
 private:
  void UpdateFruitPos();
  bool is_victory;
  GameInfo_t *info = nullptr;
  Coordinates fruit_coord;
  
 public:
  Model();
  ~Model(); 
  GameInfo_t& GetGameInfo();
  const int& GetScore();
  const int& GetHighScore();
  const int& GetLevel();
  bool checkinfoptr();
  GameInfo_t updateCurrentState();
  // GameInfo_t G_GameInfo() {return *info;};
  const bool& GetIsVictory();
  const int& GetFruitX();
  const int& GetFruitY();
  const std::vector<Coordinates>& GetSnakeCoords();
  uint64_t GetCurrTime();
  void SaveScore(const std::string &file_name);
  void LoadScore(const std::string &file_name);
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

class SnakeModel : public Model {
 public:
  // SnakeModel();
  // ~SnakeModel();
  void SetSnakeDataDefault(int score = 0);
  void UpdateData(UserAction_t action);
  // void SetGameDataDefault();
  SnakeModel& GetModelData();
  const GameState_t& GetGameStatus();
  const Direction& GetDirection();

 private:
  // SnakeGameData s_data_;
  Direction direction = Direction::kUp;
  GameState_t game_status = GameState_t::kStart;
  using Action = void (SnakeModel::*)();
  const Action kSnakeActionTable[6][9] = {
      // kStart
      {nullptr, nullptr, nullptr, nullptr, nullptr, &SnakeModel::StartGame,
       &SnakeModel::StartGame, &SnakeModel::ExitGame, nullptr},
      // kSpawn
      {&SnakeModel::Spawn, &SnakeModel::Spawn, &SnakeModel::Spawn,
       &SnakeModel::Spawn, &SnakeModel::Spawn, &SnakeModel::Spawn,
       &SnakeModel::Spawn, &SnakeModel::Spawn, &SnakeModel::Spawn},
      // kMoving,
      {nullptr, &SnakeModel::MoveHeadLeft, &SnakeModel::MoveHeadRight,
       &SnakeModel::MoveHeadDown, &SnakeModel::MoveHeadUp,
       &SnakeModel::SetPause, nullptr, &SnakeModel::ExitGame,
       &SnakeModel::SetPause},
      // kCollide,
      {&SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide,
       &SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide,
       &SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide},
      // kPause,
      {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
       &SnakeModel::CancelPause, &SnakeModel::ExitGame,
       &SnakeModel::CancelPause},
      // kGameOver,
      {&SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame,
       &SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame,
       &SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame}};
  void userInput(UserAction_t action, bool hold) ;
  void MoveSnake();
  // FSM ACTION METHODS
  void MoveHeadLeft();
  void MoveHeadRight();
  void MoveHeadDown();
  void MoveHeadUp();
  void Spawn();
  void SetPause();
  void CancelPause();
  void ExitGame();
  void Collide();
  void StartGame();
  void MoveSnakeBody();
};  // class SnakeModel

}  // namespace s21

#endif  // SNAKE_BACK_H