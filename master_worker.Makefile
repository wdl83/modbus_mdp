include Makefile.defs

DEFS = \
	   -I ../ \
	   -I ../zmqpp-root/include

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS) 

TARGET = master_worker

LDFLAGS += \
	-L ../zmqpp-root/lib \
	-lmodbus \
	-lpthread \
	-lzmq \
	-lzmqpp

# CSRCS =

CXXSRCS = \
	../mdp/Worker.cpp \
	../mdp/MutualHeartbeatMonitor.cpp \
	../mdp/Worker.cpp \
	../mdp/WorkerTask.cpp \
	../mdp/ZMQIdentity.cpp \
	../mdp/ZMQWorkerContext.cpp \
	Master.cpp \
	json.cpp \
	master_worker.cpp

include Makefile.rules
