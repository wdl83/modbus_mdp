include Makefile.defs

MDP = mdp
ZMQ = zmqpp-root
OBJ_DIR = obj

DEFS = \
	   -I $(ZMQ)/include

CFLAGS += $(DEFS)
CXXFLAGS += $(DEFS) 

TARGET = master_worker

LDFLAGS += \
	-L $(ZMQ)/lib \
	-lpthread \
	-lzmq \
	-lzmqpp

# CSRCS =

CXXSRCS = \
	$(MDP)/MutualHeartbeatMonitor.cpp \
	$(MDP)/Worker.cpp \
	$(MDP)/Worker.cpp \
	$(MDP)/WorkerTask.cpp \
	$(MDP)/ZMQIdentity.cpp \
	$(MDP)/ZMQWorkerContext.cpp \
	Master.cpp \
	SerialPort.cpp \
	crc.cpp \
	json.cpp \
	master_worker.cpp

include Makefile.rules

clean:
	rm $(OBJ_DIR) -rf
