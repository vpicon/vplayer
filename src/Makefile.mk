target := vplayer

# Util Variables
modules := player database ui

# Compilation options and flags
include_dirs := ../$(INCLUDE_DIR)

CXXFLAGS += $(addprefix -I,$(include_dirs))


# Tracked Files
sources := $(wildcard *.cpp)

headers := $(wildcard ../$(INCLUDE_DIR)/*.h)

objects := $(patsubst %.cpp,../$(BIN_DIR)/%.o,$(sources))
module_objects := $(foreach module,$(modules),$(wildcard ../$(BIN_DIR)/$(module)/*.o))


# Build Rules 
.PHONY: all $(modules)
all: $(modules) $(target)

$(target): $(objects)
	$(CXX) $(CXXFLAGS) $(objects) $(module_objects) -o $@

$(modules):
	$(MAKE) -C $@ -f Makefile.mk


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
