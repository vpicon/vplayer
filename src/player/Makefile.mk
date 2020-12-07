module := player

# Directories
include_dirs := ../../$(INCLUDE_DIR)
include_dirs += ../../$(INCLUDE_DIR)/$(module)

build_dir := ../../$(BIN_DIR)/$(module)

# Compilation flags and options
CC := gcc
CFLAGS   := $(addprefix -I,$(include_dirs))

CXXFLAGS += $(addprefix -I,$(include_dirs))


# Main target of the makefile
target := lib$(module).a


# Tracked Files
sources := $(wildcard *.cpp)
input_sources  := $(wildcard  input_plugins/*.cpp)
output_sources := $(wildcard output_plugins/*.cpp)
output_sources += $(wildcard output_plugins/*.c)

headers := $(wildcard ../../$(INCLUDE_DIR)/$(module)/*.h)

objects := $(patsubst %.cpp,$(build_dir)/%.o,$(sources))
input_objects := $(patsubst %.cpp,$(build_dir)/%.o,$(input_sources))
output_objects := $(patsubst %.cpp,$(build_dir)/%.o,$(output_sources))
output_objects += $(patsubst %.c,$(build_dir)/%.o,$(output_sources))


# Targets
$(build_dir)/$(target): $(objects) $(input_objects) $(output_objects) $(headers)
	$(AR) $(ARFLAGS) $(build_dir)/$(target) $(objects) $(input_objects) $(output_objects)


# Compilation rules
$(objects):$(build_dir)/%.o: %.cpp $(headers)
	$(CXX) $(CXXFLAGS) $< -o $@ -c 

# Compile input plugins
$(input_objects):$(build_dir)/input_plugins/%.o: input_plugins/%.cpp $(headers)
	$(CXX) $(CXXFLAGS) $< -o $@ -c 

# Compile output plugins
$(build_dir)/output_plugins/PulseaudioOutput.o: output_plugins/PulseaudioOutput.cpp $(headers)
	$(CXX) $(CXXFLAGS) $< -o $@ -c 

$(build_dir)/output_plugins/Pulse.o: output_plugins/Pulse.c $(headers)
	$(CC) $(CFLAGS) $< -o $@ -c $(shell pkg-config --cflags libpulse)


.PHONY: clean
clean: 
	-rm $(objects)

.PHONY: cleanall
cleanall:
	-rm $(build_dir)/$(target)
