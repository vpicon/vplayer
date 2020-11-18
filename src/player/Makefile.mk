module := player

# Compilation options and flags
include_dirs := ../../$(INCLUDE_DIR)
include_dirs += ../../$(INCLUDE_DIR)/$(module)

CXXFLAGS += $(addprefix -I,$(include_dirs))


# Tracked Files
sources := $(wildcard *.cpp)
sources += $(wildcard  input_plugins/*.cpp)
sources += $(wildcard output_plugins/*.cpp)

headers := $(wildcard ../../$(INCLUDE_DIR)/$(module)/*.h)

objects := $(patsubst %.cpp,../../$(BIN_DIR)/$(module)/%.o,$(sources))


# Targets
.PHONY: all
all: $(objects)

.PHONY: clean
clean: 
	-rm $(objects)


# Compilation rules
../../$(BIN_DIR)/$(module)/%.o: %.cpp $(headers)
	$(CXX) $(CXXFLAGS) $< -o $@ -c 