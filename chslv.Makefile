include Makefile.defs

DEFS = \
	   -I ..

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS)

TARGET = chslv

#LDFLAGS +=

# CSRCS =

CXXSRCS = \
		chslv.cpp

include Makefile.rules
