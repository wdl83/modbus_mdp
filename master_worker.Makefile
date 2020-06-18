include Makefile.defs

DEFS = \
	   -I ../ \
	   -I ../zmqpp-root/include

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS) 

TARGET = master_worker

LDFLAGS += \
	-L ../zmqpp-root/lib \
	-lpthread \
	-lzmq \
	-lzmqpp

# CSRCS =

CXXSRCS = \
	../mdp/MutualHeartbeatMonitor.cpp \
	../mdp/Worker.cpp \
	../mdp/Worker.cpp \
	../mdp/WorkerTask.cpp \
	../mdp/ZMQIdentity.cpp \
	../mdp/ZMQWorkerContext.cpp \
	Master.cpp \
	SerialPort.cpp \
	crc.cpp \
	json.cpp \
	master_worker.cpp

include Makefile.rules
