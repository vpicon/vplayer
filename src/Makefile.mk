target := ../vplayer

# Util Variables
modules := player database ui

# Compilation options and flags
include_dirs := ../$(INCLUDE_DIR) ../$(INCLUDE_DIR)/player

CXXFLAGS += $(addprefix -I,$(include_dirs))
LDFLAGS  += $(shell pkg-config --cflags --libs libpulse)
LDFLAGS  += -lpthread


# Tracked Files
sources := $(wildcard *.cpp)

headers := $(wildcard ../$(INCLUDE_DIR)/*.h)

objects        := $(patsubst %.cpp,../$(BIN_DIR)/%.o,$(sources))
module_objects  = $(foreach module,$(modules),$(wildcard ../$(BIN_DIR)/$(module)/*.o)) # Has to be evaluated at run time since these objects will be made in each module
module_objects += $(wildcard ../$(BIN_DIR)/player/input_plugins/*.o) 
module_objects += $(wildcard ../$(BIN_DIR)/player/output_plugins/*.o) 


# Build Rules 
.PHONY: all $(modules)
all: $(modules) $(target)

$(target): $(objects)
	$(CXX) $(CXXFLAGS) $(objects) $(module_objects) -o $@ $(LDFLAGS)

$(modules):
	$(MAKE) -C $@ -f Makefile.mk


$(objects): ../$(BIN_DIR)/%.o: %.cpp $(headers)
	$(CXX) $(CXXFLAGS) $< -o $@ -c



.PHONY: clean
clean:
	-rm $(objects)
	for d in $(modules);                              \
	do                                                \
		$(MAKE) --directory=$$d -f Makefile.mk clean; \
	done


.PHONY: cleanall
cleanall: clean
	-rm $(target)
