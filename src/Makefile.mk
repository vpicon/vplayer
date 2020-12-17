target := ../vplayer

# Util Variables
modules := player database ui

# Directories
include_dirs := ../$(INCLUDE_DIR) 
build_dir := ../$(BIN_DIR)


# Compilation flags and options
CXXFLAGS    += $(addprefix -I,$(include_dirs))
LIBCXXFLAGS := $(shell pkg-config gtkmm-3.0 --cflags) # gtk cflags


# Module Librares flags
LDFLAGS  += -L$(build_dir)/player   -lplayer
LDFLAGS  += -L$(build_dir)/database -ldatabase
LDFLAGS  += -L$(build_dir)/ui       -lui

# Std flags
LDFLAGS  += -lpthread

# Third Party Libraries flags
MPG123FLAGS := -lmpg123
PULSEFLAGS  := $(shell pkg-config libpulse --libs)
SQLITEFLAGS := -lsqlite3
GTKMMFLAGS  := $(shell pkg-config gtkmm-3.0 --libs)

LDFLAGS += $(MPG123FLAGS) $(PULSEFLAGS) $(SQLITEFLAGS) $(GTKMMFLAGS)


# Tracked Files
sources := $(wildcard *.cpp)
headers := $(wildcard ../$(INCLUDE_DIR)/*.h)
objects := $(patsubst %.cpp,$(build_dir)/%.o,$(sources))



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


# Build Rules 
.PHONY: all $(modules) objects_format
all: $(target)


$(target): $(modules) objects_format $(objects) 
	@printf "%b" "$(MODULE_COLOR)Linking application $(@F) objects and libraries:$(NO_COLOR)\n"
	@$(call format_command,$(CXX) $(objects) -o $@ $(LDFLAGS),$(LD_STRING))


$(modules):
	@printf "%b" "$(MODULE_COLOR)Building $(@) module:$(NO_COLOR)\n"
	@$(MAKE) -C $@ -f Makefile.mk


objects_format:
	@printf "%b" "$(MODULE_COLOR)Building application objects:$(NO_COLOR)\n"

$(objects): $(build_dir)/%.o: %.cpp $(headers)
	@$(call format_command,$(CXX) -c $(CXXFLAGS) $(LIBCXXFLAGS) $< -o $@,$(COM_STRING))



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
