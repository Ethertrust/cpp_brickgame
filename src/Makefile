# Compiler and flags
TEST_FLAGS := -lgtest_main -lgtest
GCC := g++ -Wall -Wextra -Werror -std=c++20
CC := gcc
CCP := g++
CFLAGS := -I. -g -std=c11 -Wall -Werror -Wextra
CPPFLAGS := -g -std=c++20 -Wall -Werror -Wextra
GCO := -fprofile-arcs -ftest-coverage -O0

# Directories and files
DIR_BACK_TETRIS := brick_game/tetris
BUILD_DIR := ../build
IMAGE_DIR := images
SRC_DIR := .
EXTENSIONS := cc cpp h
DIR_LIBRARY_TETRIS := static_L

RM_RULE := rm -rf test *.dSYM coverage report res *.info *.gcda *.gcno snake_game ../build ../BrickGame_v2-0.tar.gz SnakeScore.txt TetrisScore.txt

# File discovery function
find_files = $(foreach ext,$(EXTENSIONS),$(wildcard $(1)/*.$(ext))) $(foreach d,$(wildcard $(1)/*),$(call find_files,$(d)))
SRC_FILES := $(call find_files,$(SRC_DIR))
CC_FILES := $(filter-out ./gui/desktop/main.cc ./gui/desktop/SnakeView.cc, $(filter %.cc,$(SRC_FILES)))

LIBRARY_BACK_TETRIS := $(patsubst %.c,%.o,$(wildcard $(DIR_BACK_TETRIS)/*.c))

TEST_SOURCES :=  tests/tetris_test.cc #tests/snake_test.cc\


GCOV_SOURCES := brick_game/common/BaseModel.cc \
				brick_game/snake/SnakeModel.cc \
				brick_game/tetris/TetrisModel.cc \
				brick_game/tetris/Tetromino.cc

# Targets
.PHONY: all install uninstall clean dvi dist test

all: install test

install: libbrick_game
	mkdir -p $(BUILD_DIR)
	cp -rf $(IMAGE_DIR) $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ../src && make

uninstall: clean

libbrick_game: $(LIBRARY_BACK_TETRIS)
	ar rcs $(DIR_LIBRARY_TETRIS)/tetris_back.a $^
	-rm $(DIR_BACK_TETRIS)/*.o

run_desktop:
	$(BUILD_DIR)/desktopBrickGame

run_cli:
	$(BUILD_DIR)/consoleBrickGame

test: $(TEST_SOURCES) $(DIR_LIBRARY_TETRIS)/tetris_back.a
	$(GCC) $(TEST_FLAGS) -g -o $@ $^
	./$@

clean:
	$(RM_RULE) coverage_report*

dvi:
	open ../dvi/dvi.pdf
#GOVNO

dist: clean
	@echo "Creating a distribution..."
	@mkdir -p BrickGames
	@cp -r brick_game/ controller/ gui/ images/ ./BrickGames
	@cp CMakeLists.txt Makefile ./BrickGames
	@echo "Distribution packaging..."
	@tar -cvzf BrickGame_v2-0.tar.gz BrickGames/
	@mv BrickGame_v2-0.tar.gz ../
	@rm -rf BrickGames/
	@echo "\033[33mDistribution created: CPP3_BrickGame_v2.0/BrickGame_v2-0.tar.gz\033[0m"

gcov_report: clean
	mkdir -p coverage
	$(GCC) $(TEST_FLAGS) $(GCO) $(TEST_SOURCES) -o coverage/report
	./coverage/report
	cd coverage/ && \
		gcovr \
			--root ../ \
			--exclude '.*/tests/.*' \
			--exclude-throw-branches \
			--html --html-details -o coverage_report.html

style_check:
	clang-format -style=Google -n $(SRC_FILES)

style_fix:
	clang-format -style=Google -i $(SRC_FILES)

cpplint:
	$@ --filter=-build/header_guard $(SRC_FILES)

cppcheck:
	$@ --language=c++ --std=c++20 $(SRC_FILES)

valgrind:
	$(GCC) $(TEST_FLAGS) -g -o test $(TEST_SOURCES)
	$@ -s --leak-check=full --show-leak-kinds=all ./test

# Pattern rule for object files
%.o: %.cc
	$(CCP) $(CPPFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@