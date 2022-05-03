include Makefile.defs

OBJ_DIR = obj

# DEFS =

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS)

TARGET = probe

#LDFLAGS +=

# CSRCS =

CXXSRCS = \
		Master.cpp \
		SerialPort.cpp \
		crc.cpp \
		json.cpp \
		probe.cpp

include Makefile.rules

clean:
	rm $(OBJ_DIR) -rf
