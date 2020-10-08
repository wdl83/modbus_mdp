include Makefile.defs

DEFS = \
	   -I ..

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
