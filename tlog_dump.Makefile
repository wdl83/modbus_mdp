include Makefile.defs

DEFS = \
	   -I ../ \
	   -I ../zmqpp-root/include

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS)

TARGET = tlog_dump

# CSRCS =

CXXSRCS = \
		tlog_dump.cpp

include Makefile.rules
