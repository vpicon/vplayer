module := player

# Directories
include_dirs := ../../$(INCLUDE_DIR)  ../../$(INCLUDE_DIR)/$(module)
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
output_sources := $(wildcard output_plugins/*.cpp) \
	              $(wildcard output_plugins/*.c)

headers := $(wildcard ../../$(INCLUDE_DIR)/$(module)/*.h)

objects := $(patsubst %.cpp,$(build_dir)/%.o,$(sources))
input_objects  := $(patsubst %.cpp,$(build_dir)/%.o,$(input_sources))
output_objects := $(filter %.o,$(patsubst %.cpp,$(build_dir)/%.o,$(output_sources))) \
				  $(filter %.o,$(patsubst %.c,$(build_dir)/%.o,$(output_sources)))


# Formatting Output
# 	@param1: command
# 	@param2: command string rep
#	@param3: module name
define format_command
	printf "%-80b%b" "  $(NO_COLOR)$(2)$(OBJ_COLOR) $(3)/$(@F) $(NO_COLOR)...";     			  			\
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


# Targets
$(build_dir)/$(target): $(objects) $(input_objects) $(output_objects) $(headers)
	@$(call format_command,$(AR) $(ARFLAGS) $(build_dir)/$(target) $(objects) $(input_objects) $(output_objects),$(AR_STRING),$(module))


# Compilation rules
$(objects):$(build_dir)/%.o: %.cpp $(headers)
	@$(call format_command,$(CXX) -c $(CXXFLAGS) $< -o $@,$(COM_STRING),$(module))

# Compile input plugins
$(input_objects):$(build_dir)/input_plugins/%.o: input_plugins/%.cpp $(headers)
	@$(call format_command,$(CXX) -c $(CXXFLAGS) $< -o $@,$(COM_STRING),$(module)/input_plugins)

# Compile output plugins
$(build_dir)/output_plugins/PulseaudioOutput.o: output_plugins/PulseaudioOutput.cpp $(headers)
	@$(call format_command,$(CXX) -c $(CXXFLAGS) $< -o $@,$(COM_STRING),$(module)/output_plugins)

$(build_dir)/output_plugins/Pulse.o: output_plugins/Pulse.c $(headers)
	@$(call format_command,$(CC) $(CFLAGS) $< -o $@ -c $(shell pkg-config --cflags libpulse),$(COM_STRING),$(module)/output_plugins)
	


.PHONY: clean
clean: 
	-rm $(objects) $(input_objects) $(output_objects)

.PHONY: cleanall
cleanall:
	-rm $(build_dir)/$(target)
