include Makefile.defs

OBJ_DIR = obj

# DEFS =

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS)

TARGET = chslv

#LDFLAGS +=

# CSRCS =

CXXSRCS = \
		chslv.cpp

include Makefile.rules

clean:
	rm $(OBJ_DIR) -rf
