include Makefile.defs

DEFS = \
	   -I ..

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS)

TARGET = monitor

#LDFLAGS +=

# CSRCS =

CXXSRCS = \
		SerialPort.cpp \
		monitor.cpp

include Makefile.rules
