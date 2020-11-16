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

CXXFLAGS  = -Wall -Werror -Wshadow -pedantic 
CXXFLAGS += -std=c++17

LDFLAGS :=

export SHELL CXX CXXFLAGS LDFLAGS


# DIRECTORIES

SOURCE_DIR  := src
INCLUDE_DIR := include
TEST_DIR    := test
LIB_DIR     := lib
BIN_DIR     := bin

export SOURCE_DIR  INCLUDE_DIR  TEST_DIR  LIB_DIR  BIN_DIR


# MODULES

player      := $(SOURCE_DIR)/player
database    := $(SOURCE_DIR)/database
ui          := $(SOURCE_DIR)/ui
modules     := $(player) $(database) $(ui)

application := $(SOURCE_DIR)
test        := $(TEST_DIR)


.PHONY: all $(modules) $(application)
all: $(application)


$(application) $(modules):
	$(MAKE) --directory=$@ -f Makefile.mk

$(application): $(modules)
$(ui): $(player) $(database)


.PHONY: test $(test)
test: $(test)

$(test): $(modules)
	$(MAKE) --directory=$@ -f Makefile.mk


.PHONY: clean
clean:
	for d in $(application) $(modules);                \
	do                                                 \
		$(MAKE) --directory=$$d -f Makefile.mk clean;  \
	done
