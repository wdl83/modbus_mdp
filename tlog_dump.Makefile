include Makefile.defs

OBJ_DIR = obj

# DEFS =

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS)

TARGET = tlog_dump

# CSRCS =

CXXSRCS = \
		tlog_dump.cpp

include Makefile.rules

clean:
	rm $(OBJ_DIR) -rf
