include Makefile.defs

OBJ_DIR = obj

# DEFS =

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS)

TARGET = master_cli

#LDFLAGS +=

# CSRCS =

CXXSRCS = \
		Master.cpp \
		SerialPort.cpp \
		crc.cpp \
		json.cpp \
		master_cli.cpp

include Makefile.rules

clean:
	rm $(OBJ_DIR) -rf
