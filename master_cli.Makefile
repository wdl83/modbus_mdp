include Makefile.defs

DEFS = -I ../

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS)

TARGET = master_cli

LDFLAGS += -lmodbus

# CSRCS =

CXXSRCS = \
		Master.cpp \
		json.cpp \
		master_cli.cpp

include Makefile.rules
