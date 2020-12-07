target := ../vplayer

# Util Variables
modules := player database ui

# Directories
include_dirs := ../$(INCLUDE_DIR) 

build_dir := ../$(BIN_DIR)


# Compilation flags and options
CXXFLAGS += $(addprefix -I,$(include_dirs))
CXXFLAGS += $(shell pkg-config gtkmm-3.0 --cflags) # gtk cflags


# Module Librares flags
LDFLAGS  += -L$(build_dir)/player   -lplayer
LDFLAGS  += -L$(build_dir)/database -ldatabase
LDFLAGS  += -L$(build_dir)/ui       -lui

# Std flags
LDFLAGS  += -lpthread

# Third Party Libraries flags
    # player 
MPG123FLAGS := -lmpg123
PULSEFLAGS  := $(shell pkg-config libpulse --libs)
    # database
SQLITEFLAGS := -lsqlite3
	# ui
GTKMMFLAGS  := $(shell pkg-config gtkmm-3.0 --libs)


LDFLAGS += $(MPG123FLAGS) $(PULSEFLAGS) $(SQLITEFLAGS) $(GTKMMFLAGS)


# Tracked Files
sources := $(wildcard *.cpp)

headers := $(wildcard ../$(INCLUDE_DIR)/*.h)

objects := $(patsubst %.cpp,../$(BIN_DIR)/%.o,$(sources))


# Build Rules 
.PHONY: all $(modules)
all: $(modules) $(target)

$(target): $(objects)
	$(CXX) $(objects) -o $@ $(LDFLAGS)

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
	for d in $(modules);                                 \
	do                                                   \
		$(MAKE) --directory=$$d -f Makefile.mk cleanall; \
	done
