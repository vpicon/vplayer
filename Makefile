# Compiler
CXX := g++


# Compiler options and flags
CFLAGS  = -Wall -Werror -Wshadow -pedantic 
CFLAGS += -I$(INCLUDE_DIR)

CXXFLAGS := -std=c++17 -O3
CXXFLAGS += $(CFLAGS)


# Linker options and flags
LDFLAGS :=


# Directories
SOURCE_DIR  := src
INCLUDE_DIR := include
TEST_DIR    := test
LIB_DIR     := lib
BIN_DIR     := bin


# Executables
TARGET := vplayer
TEST_TARGET := testvplayer


# Tracked Files 
SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SOURCES))

TEST_SOURCES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp,$(BIN_DIR)/test/%.o,$(TEST_SOURCES))


# Executable Building Rules
all: $(TARGET) dirs

$(TARGET):


test: $(TEST_TARGET) dirs

$(TEST_TARGET): $(TEST_OBJECTS) $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) -o $@


# Compilation Rules
$(OBJECTS): $(BIN_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) -c 


$(TEST_OBJECTS): $(BIN_DIR)/test/%.o: $(TEST_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) -c


# Utility Rules
dirs: 
	if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi
	if [ ! -d $(BIN_DIR)/test ]; then mkdir $(BIN_DIR)/test; fi

clean:
	-rm -r bin/

cleanall: clean
	-rm $(TARGET) $(TEST_TARGET)


.PHONY: all test dirs clean cleanall 
