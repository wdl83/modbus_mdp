include Makefile.defs

OBJ_DIR = obj

# DEFS =

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS)

TARGET = monitor

#LDFLAGS +=

# CSRCS =

CXXSRCS = \
		SerialPort.cpp \
		monitor.cpp

include Makefile.rules

clean:
	rm $(OBJ_DIR) -rf
