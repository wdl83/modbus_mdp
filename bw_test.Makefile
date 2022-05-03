include Makefile.defs

OBJ_DIR = obj

#DEFS =

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS)

TARGET = bw_test

#LDFLAGS +=

# CSRCS =

CXXSRCS = \
		Master.cpp \
		SerialPort.cpp \
		crc.cpp \
		json.cpp \
		bw_test.cpp

include Makefile.rules

clean:
	rm $(OBJ_DIR) -rf
