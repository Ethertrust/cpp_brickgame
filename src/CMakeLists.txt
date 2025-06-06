cmake_minimum_required(VERSION 3.23)
project(CPP3_BrickGame_v2_0_1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Устанавливаем флаги компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# Поиск Qt6
if(DEFINED ENV{QTDIR})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{QTDIR}")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Общие включаемые директории
include_directories(
    brick_game/snake
    brick_game/tetris
    brick_game/common
    controller
    gui/console
    gui/desktop
    gui/console/common
    gui/console/snake
    gui/console/tetris
)

# Общие исходные файлы
set(BRICK_GAME_TETRIS_LIB ${CMAKE_CURRENT_SOURCE_DIR}/static_L/tetris_back.a)
# set(BRICK_GAME_SNAKE_LIB ${CMAKE_CURRENT_SOURCE_DIR}/static_L/snake_back.a )
set(COMMON_SOURCES
    brick_game/snake/fsm_snake.cc
    brick_game/snake/fsm_snake.h
    # brick_game/tetris/TetrisModel.cc
    # brick_game/tetris/TetrisModel.h
    # brick_game/tetris/Tetromino.h
    # brick_game/tetris/Tetromino.cc
    brick_game/common/common.h
    brick_game/snake/back_snake.h
    brick_game/snake/back_snake.cc
)

# # Консольное приложение
# add_executable(consoleBrickGame
#     ${COMMON_SOURCES}
#     controller/SnakeController.h
#     controller/TetrisController.h
#     gui/console/snake/SnakeConsoleView.cc
#     gui/console/snake/SnakeConsoleView.h
#     gui/console/common/BrickGameConsoleView.cc
#     gui/console/common/BrickGameConsoleView.h
#     gui/console/BrickGameConsole.cc
#     gui/console/common/BaseView.cc
#     gui/console/common/BaseView.h
#     gui/console/tetris/TetrisConsoleView.cc
# )

# target_link_libraries(consoleBrickGame PRIVATE ncurses)

# Десктопное приложение
add_executable(desktopBrickGame
    ${COMMON_SOURCES}
    controller/SnakeController.h
    controller/TetrisController.h
    gui/desktop/snake/main.cc
    gui/desktop/snake/View.cc
    gui/desktop/snake/View.h
)

target_link_libraries(desktopBrickGame PRIVATE ${BRICK_GAME_TETRIS_LIB}  Qt6::Core Qt6::Gui Qt6::Widgets) #$(BRICK_GAME_SNAKE_LIB)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(desktopBrickGame)
endif()