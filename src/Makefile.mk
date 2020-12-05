target := ../vplayer

# Util Variables
modules := player database ui

# Directories
include_dirs := ../$(INCLUDE_DIR) 

build_dir := ../$(BIN_DIR)


# Compilation flags and options
CXXFLAGS += $(addprefix -I,$(include_dirs))
LDFLAGS  += -lpthread

# Module Librares flags
LDFLAGS  += -L$(build_dir)/player   -lplayer
LDFLAGS  += -L$(build_dir)/database -ldatabase


# Third Party Libraries flags
MPG123FLAGS := -lmpg123
PULSEFLAGS  := $(shell pkg-config --cflags --libs libpulse)
SQLITEFLAGS := -lsqlite3

LDFLAGS += $(MPG123FLAGS) $(PULSEFLAGS) $(SQLITEFLAGS)


# Tracked Files
sources := $(wildcard *.cpp)

headers := $(wildcard ../$(INCLUDE_DIR)/*.h)

objects := $(patsubst %.cpp,../$(BIN_DIR)/%.o,$(sources))


# Build Rules 
.PHONY: all $(modules)
all: $(modules) $(target)

$(target): $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o $@ $(LDFLAGS)

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
