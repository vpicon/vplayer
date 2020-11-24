module    := player
submodule := $(module)/output_plugins

# Compilation options and flags
include_dirs := ../../../$(INCLUDE_DIR)
include_dirs += ../../../$(INCLUDE_DIR)/player

CC := gcc
CFLAGS   := $(addprefix -I,$(include_dirs))

CXXFLAGS += $(addprefix -I,$(include_dirs))


# Tracked Files
headers := $(wildcard ../../$(INCLUDE_DIR)/$(module)/*.h)
headers := $(wildcard ../../$(INCLUDE_DIR)/$(submodule)/*.h)


# Compile each output plugin by itself (each has its own dependencies)

# Pulseaudio
pulseaudio: ../../../$(BIN_DIR)/$(submodule)/Pulse.o \
	../../../$(BIN_DIR)/$(submodule)/PulseaudioOutput.o

../../../$(BIN_DIR)/$(submodule)/Pulse.o: Pulse.c $(headers)
	$(CC) $(CFLAGS) $< -o $@ $(LDPULSE) -c

../../../$(BIN_DIR)/$(submodule)/PulseaudioOutput.o: PulseaudioOutput.cpp $(headers)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDPULS) -c


