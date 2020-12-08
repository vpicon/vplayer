# Makefile to build the entire music player application, 
# from the back end to the gui to the tests.
#
# SYNOPSIS:
# 	make [all]:    builds the entire application
# 	make test:     builds the test executable, testing the 
# 	               application code
# 	make clean:    clears all intermediary files generated 
# 	               while building the final application executable

# COMPILATION VARIABLES
SHELL := /usr/bin/bash 
CXX   := g++

CXXFLAGS := -Wall -Werror -Wshadow -pedantic -g # -Wextra 
CXXFLAGS += -std=c++17

LDFLAGS :=


AR      := ar   # Archiver
ARFLAGS := rcs  # Archiver flags

export SHELL CXX CXXFLAGS LDFLAGS AR ARFLAGS


# DIRECTORIES
SOURCE_DIR  := src
INCLUDE_DIR := include
TEST_DIR    := test
LIB_DIR     := lib
BIN_DIR     := bin

export SOURCE_DIR  INCLUDE_DIR  TEST_DIR  LIB_DIR  BIN_DIR


# FORMATTING OUTPUT
MODULE_COLOR = \033[0;34m
OBJ_COLOR    = \033[0;36m
OK_COLOR     = \033[0;32m
ERROR_COLOR  = \033[0;31m
WARN_COLOR   = \033[0;33m
NO_COLOR     = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"
AR_STRING    = "Archiving"
LD_STRING    = "Linking"

export MODULE_COLOR OBJ_COLOR OK_COLOR ERROR_COLOR WARN_COLOR NO_COLOR \
	   OK_STRING ERROR_STRING WARN_STRING COM_STRING AR_STRING LD_STRING


# MODULES

player      := $(SOURCE_DIR)/player
database    := $(SOURCE_DIR)/database
ui          := $(SOURCE_DIR)/ui
modules     := $(player) $(database) $(ui)

application := $(SOURCE_DIR)
test        := $(TEST_DIR)


.PHONY: all $(application)
all: $(application)

$(application):
	@$(MAKE) --no-print-directory --directory=$@ -f Makefile.mk


.PHONY: $(test) $(modules) 
$(test): $(modules)
	@$(MAKE) --no-print-directory --directory=$@ -f Makefile.mk

$(modules):
	@$(MAKE) --no-print-directory --directory=$@ -f Makefile.mk

.PHONY: clean
clean:
	for d in $(application) $(modules) $(test);                             \
	do                                                                      \
		$(MAKE) --no-print-directory --directory=$$d -f Makefile.mk clean;  \
	done

.PHONY: cleanall
cleanall:
	for d in $(application) $(modules) $(test);                                \
	do                                                                         \
		$(MAKE) --no-print-directory --directory=$$d -f Makefile.mk cleanall;  \
	done
