include Makefile.defs

ZMQ = zmqpp-root

CXXFLAGS += \
	-I $(ZMQ)/include

LDFLAGS += \
	-L $(ZMQ)/lib \
	-lpthread \
	-lzmq \
	-lzmqpp

TARGET = master_worker

CXXSRCS = \
	Master.cpp \
	SerialPort.cpp \
	crc.cpp \
	json.cpp \
	master_worker.cpp \
	mdp/MutualHeartbeatMonitor.cpp \
	mdp/Worker.cpp \
	mdp/Worker.cpp \
	mdp/WorkerTask.cpp \
	mdp/ZMQIdentity.cpp \
	mdp/ZMQWorkerContext.cpp

include Makefile.rules
