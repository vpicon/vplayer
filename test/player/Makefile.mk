module := player

# Compilation options and flags
include_dirs := ../../$(INCLUDE_DIR)/$(module)
include_dirs += ../../$(LIB_DIR)/gtest/googletest/include


CXXFLAGS += $(addprefix -I,$(include_dirs))


# Tracked Files
sources := $(wildcard *.cpp)
sources += $(wildcard  input_plugins/*.cpp)
sources += $(wildcard output_plugins/*.cpp)

headers := $(wildcard ../../$(INCLUDE_DIR)/$(module)/*.h)

test_objects := $(patsubst %.cpp,../../$(BIN_DIR)/test/$(module)/%.o,$(sources))


# Targets
.PHONY: all
all: $(test_objects)

# Compilation rules
../../$(BIN_DIR)/test/$(module)/%.o: %.cpp $(headers)
	$(CXX) $(CXXFLAGS) $< -o $@ -c 


.PHONY: clean
clean: 
	-rm $(test_objects)
