target := ../vplayer_tests

# Useful Variables
modules := player database ui

# Directories
test_lib_dir := ../$(LIB_DIR)/gtest/lib

build_dir := ../$(BIN_DIR)/test


# Compilation flags and options
CXXFLAGS += $(addprefix -I,$(include_dirs))
LDFLAGS  += -lpthread

# Module Librares flags
LDFLAGS  += -L../$(BIN_DIR)/player   -lplayer
LDFLAGS  += -L../$(BIN_DIR)/database -ldatabase

# Third Party Libraries flags
MPG123FLAGS := -lmpg123
PULSEFLAGS  := $(shell pkg-config --cflags --libs libpulse)
SQLITEFLAGS := -lsqlite3
GTESTFLAGS  := -pthread -L$(test_lib_dir) -lgtest -lgtest_main

LDFLAGS += $(MPG123FLAGS) $(PULSEFLAGS) $(SQLITEFLAGS) $(GTESTFLAGS)


# Tracked Files
test_objects  = $(foreach module,$(modules),$(wildcard $(build_dir)/$(module)/*.o))  # Has to be evaluated at runtime since these objects will be made at each module
test_objects += $(wildcard $(build_dir)/player/input_plugins/*.o)
test_objects += $(wildcard $(build_dir)/player/output_plugins/*.o)


# TEST MODULES

.PHONY: all $(modules)
all: $(modules) $(target)

$(target): $(modules)
	$(CXX) $(CXXFLAGS) $(objects) $(test_objects) -o $(target) $(LDFLAGS)

$(modules): 
	$(MAKE) --directory=$@ -f Makefile.mk


.PHONY: clean
clean:
	for d in $(modules);                              \
	do 								                  \
		$(MAKE) --directory=$$d -f Makefile.mk clean; \
	done


.PHONY: cleanall
cleanall: clean
	-rm $(target)
