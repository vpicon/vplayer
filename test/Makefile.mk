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



# Formatting Output
# 	@param1: command
# 	@param2: command string rep
#	@param3: module name
define format_command
	printf "%-80b%b" "  $(NO_COLOR)$(2)$(OBJ_COLOR) $(3)$(@F) $(NO_COLOR)...";     			  			\
	$(1) 2> $@.log; 																    \
	RESULT=$$?;  																	    \
	if [ $$RESULT -ne 0 ]; then 													    \
		printf "%b" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; 				    \
	elif [ -s $@.log ]; then 														    \
		printf "%b" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n";   				        \
	else  																			    \
		printf "%b" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n";                        \
	fi; 																			    \
	cat $@.log; 															 		    \
	rm -f $@.log; 																	    \
	exit $$RESULT
endef


# TEST MODULES

.PHONY: all $(modules)
all: $(modules) $(target)

$(target): $(modules)
	@printf "%b" "$(MODULE_COLOR)Linking test objects and libraries:$(NO_COLOR)\n"
	@$(call format_command,$(CXX) $(CXXFLAGS) $(objects) $(test_objects) -o $(target) $(LDFLAGS),$(LD_STRING))

$(modules): 
	@printf "%b" "$(MODULE_COLOR)Building $(@) tests:$(NO_COLOR)\n"
	@$(MAKE) --directory=$@ -f Makefile.mk


.PHONY: clean
clean:
	for d in $(modules);                              \
	do 								                  \
		$(MAKE) --directory=$$d -f Makefile.mk clean; \
	done


.PHONY: cleanall
cleanall: clean
	-rm $(target)
