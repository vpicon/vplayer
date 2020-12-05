module := database

# Directories
include_dirs := ../../$(INCLUDE_DIR)
include_dirs += ../../$(INCLUDE_DIR)/$(module)

build_dir := ../../$(BIN_DIR)/$(module)

# Compilation flags and options
CXXFLAGS += $(addprefix -I,$(include_dirs))


# Main target of the makefile
target := lib$(module).a


# Tracked Files
sources := $(wildcard *.cpp)

headers := $(wildcard ../../$(INCLUDE_DIR)/$(module)/*.h)

objects := $(patsubst %.cpp,$(build_dir)/%.o,$(sources))


# Targets
$(build_dir)/$(target): $(objects) $(headers)
	$(AR) $(ARFLAGS) $(build_dir)/$(target) $(objects)

# Compilation rules
$(build_dir)/%.o: %.cpp $(headers)
	$(CXX) $(CXXFLAGS) $< -o $@ -c 

.PHONY: clean
clean: 
	-rm $(objects)

.PHONY: cleanall
cleanall:
	-rm $(build_dir)/$(target)
