target := ../vplayer_tests

# Useful Variables
test_lib_dir := ../$(LIB_DIR)/gtest/lib

modules := player database ui


# Compilation options and flags
CXXFLAGS += -g

LDFLAGS  += -pthread -L$(test_lib_dir) -lgtest -lgtest_main


# Tracked Files
objects      := $(foreach module,$(modules),$(wildcard ../$(BIN_DIR)/$(module)/*.o))
objects      += $(wildcard ../$(BIN_DIR)/player/input_plugins/*.o)
objects      += $(wildcard ../$(BIN_DIR)/player/output_plugins/*.o)
test_objects  = $(foreach module,$(modules),$(wildcard ../$(BIN_DIR)/test/$(module)/*.o))  # Has to be evaluated at runtime since these objects will be made at each module
test_objects += $(wildcard ../$(BIN_DIR)/test/player/input_plugins/*.o)
test_objects += $(wildcard ../$(BIN_DIR)/test/player/output_plugins/*.o)
lib_objects  := $(wildcard $(test_lib_dir)/libgtest*.a)


# TEST MODULES

.PHONY: all $(modules)
all: $(modules) $(target)

$(target): $(modules)
	$(CXX) $(CXXFLAGS) $(objects) $(test_objects) $(lib_objects) -o $(target) $(LDFLAGS)

$(modules): 
	$(MAKE) --directory=$@ -f Makefile.mk


.PHONY: clean
clean:
	for d in $(modules);                              \
	do 								                  \
		$(MAKE) --directory=$$d -f Makefile.mk clean; \
	done
