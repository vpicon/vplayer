module := database

# Compilation options and flags
include_dirs := ../../$(INCLUDE_DIR)/$(module)
include_dirs += ../../$(LIB_DIR)/gtest/googletest/include


CXXFLAGS += $(addprefix -I,$(include_dirs))


# Tracked Files
sources := $(wildcard *.cpp)

headers := $(wildcard ../../$(INCLUDE_DIR)/$(module)/*.h)

test_objects := $(patsubst %.cpp,../../$(BIN_DIR)/test/$(module)/%.o,$(sources))



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
.PHONY: all
all: $(test_objects)

# Compilation rules
../../$(BIN_DIR)/test/$(module)/%.o: %.cpp $(headers)
	@$(call format_command,$(CXX) $(CXXFLAGS) $< -o $@ -c,$(COM_STRING),$(module))


.PHONY: clean
clean: 
	-rm $(test_objects)
