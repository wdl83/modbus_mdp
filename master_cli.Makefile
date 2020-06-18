include Makefile.defs

DEFS = \
	   -I ../ \
	   -I ../zmqpp-root/include

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
