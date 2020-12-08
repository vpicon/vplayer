module := ui

# Directories
include_dirs += ../../$(INCLUDE_DIR)/$(module)

build_dir := ../../$(BIN_DIR)/$(module)

# Compilation flags and options
CXXFLAGS += $(addprefix -I,$(include_dirs))
CXXFLAGS += $(shell pkg-config gtkmm-3.0 --cflags)


# Main target of the makefile
target := lib$(module).a


# Tracked Files
sources := $(wildcard *.cpp)

headers := $(wildcard ../../$(INCLUDE_DIR)/$(module)/*.h)

objects := $(patsubst %.cpp,$(build_dir)/%.o,$(sources))



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
$(build_dir)/$(target): $(objects) $(headers)
	@$(call format_command,$(AR) $(ARFLAGS) $(build_dir)/$(target) $(objects),$(AR_STRING),$(module))

# Compilation rules
$(build_dir)/%.o: %.cpp $(headers)
	@$(call format_command,$(CXX) -c $(CXXFLAGS) $< -o $@,$(COM_STRING),$(module))

.PHONY: clean
clean: 
	-rm $(objects)

.PHONY: cleanall
cleanall:
	-rm $(build_dir)/$(target)
