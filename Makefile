CXX := g++

CFLAGS := -Wall -Werror -Wshadow -pedantic 
CFLAGS += -I"include" -O3

CXXFLAGS := -std=c++17
CXXFLAGS += $(CFLAGS)

LDFLAGS :=

TARGET := vplayer
TEST_TARGET := testvplayer


SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard include/*.h)
OBJECTS := $(patsubst src/%.cpp,bin/%.o,$(SOURCES))

all: $(OBJECTS) $(HEADERS)


dirs: 
	mkdir bin
	mkdir bin/test


bin/%.o: src/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) -c 


clean:
	-rm -r bin/

cleanall: clean
	-rm $(TARGET) $(TEST_TARGET)


.PHONY: all test dirs clean cleanall 
