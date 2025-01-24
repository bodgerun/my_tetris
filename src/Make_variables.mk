# main ------------------------------------------------------------------------

CC                := gcc
CFLAGS            := -std=c11 -Wall -Wextra -Werror -g 
TEST_FLAGS        := 
CHECK_FLAGS       := -lcheck -lpthread
LINUX_FLAGS       :=

# game library ----------------------------------------------------------------

GAME_DIR          := game
GAME_BLD_DIR      := $(GAME_DIR)/build
GAME_DGR_DIR      := $(GAME_DIR)/diagram
GAME_HDR_DIR      := $(GAME_DIR)/headers
GAME_MOD_DIR      := $(GAME_DIR)/modules
GAME_OBJ_DIR      := $(GAME_DIR)/objects

GAME_OBJ_FILES    := $(GAME_OBJ_DIR)/tetris_environment.o \
                     $(GAME_OBJ_DIR)/tetris_field.o \
                     $(GAME_OBJ_DIR)/tetris_next.o \
                     $(GAME_OBJ_DIR)/tetris_piece.o \
                     $(GAME_OBJ_DIR)/tetris_check.o \
                     $(GAME_OBJ_DIR)/tetris_fsm.o 

# interface -------------------------------------------------------------------

INTF_DIR          := interface
INTF_HDR_DIR      := $(INTF_DIR)/headers
INTF_MOD_DIR      := $(INTF_DIR)/modules
INTF_OBJ_DIR      := $(INTF_DIR)/objects

INTF_OBJ_FILES    := $(INTF_OBJ_DIR)/interface_main.o \
                     $(INTF_OBJ_DIR)/interface_utils.o \
                     $(INTF_OBJ_DIR)/interface_input.o \
                     $(INTF_OBJ_DIR)/interface_frontend.o \
                     $(INTF_OBJ_DIR)/interface_debug.o 

# tests -----------------------------------------------------------------------

TEST_DIR          := tests
TEST_MOD_DIR      := $(TEST_DIR)/modules
TEST_OBJ_DIR      := $(TEST_DIR)/objects

TEST_OBJ_FILES    := $(TEST_OBJ_DIR)/test.o \
                     $(TEST_OBJ_DIR)/test_tetris_piece.o \
                     $(TEST_OBJ_DIR)/test_tetris_next.o \
                     $(TEST_OBJ_DIR)/test_tetris_field.o \
                     $(TEST_OBJ_DIR)/test_tetris_check.o \
                     $(TEST_OBJ_DIR)/test_tetris_environment.o \
                     $(TEST_OBJ_DIR)/test_tetris_fsm.o

# source code -----------------------------------------------------------------

SRC_CODE_FILES    := $(GAME_HDR_DIR)/*.h \
                     $(GAME_MOD_DIR)/*.c \
                     $(INTF_HDR_DIR)/*.h \
                     $(INTF_MOD_DIR)/*.c \
                     $(TEST_MOD_DIR)/*.h \
                     $(TEST_MOD_DIR)/*.c

# destination directory -------------------------------------------------------

DST_DIR           := ../dst
EXEC              := $(DST_DIR)/Tetris

# messages --------------------------------------------------------------------

GREEN             := "\033[0;32m"
RESET             := "\033[0m"
MSG_DVI           := "\nNo documentation can be generated\n"
MSG_LEAKS         := "\nLeaks is not supported on Linux\n"
MSG_VALGRIND      := "\nValgrind is not supported on MacOS\n"

# MacOS vs Linux --------------------------------------------------------------

ifeq ($(shell uname), Darwin)                # MacOS
OPEN_HTML         := open
VALGRIND          := @echo $(GREEN)$(MSG_VALGRIND)$(RESET)
LEAKS             := leaks -atExit -- $(EXEC) && $(RM) record.txt
LINTER            := clang-format
else                                         # Linux
LINUX_FLAGS       += -lbsd -lm -lrt -lsubunit
OPEN_HTML         := lynx
VALGRIND          := valgrind --tool=memcheck $(EXEC) && $(RM) record.txt
LEAKS             := @echo $(GREEN)$(MSG_LEAKS)$(RESET)
LINTER            := clang-format-13
endif

# test flags ------------------------------------------------------------------

ifeq ($(MAKECMDGOALS), test)
TEST_FLAGS        += -fprofile-arcs -ftest-coverage
else ifeq ($(MAKECMDGOALS), gcov_report)
TEST_FLAGS        += -fprofile-arcs -ftest-coverage
endif
