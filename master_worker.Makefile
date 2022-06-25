include Makefile.defs


TARGET = master_worker

CXXSRCS = \
	master_worker.cpp \
	mdp/MutualHeartbeatMonitor.cpp \
	mdp/Worker.cpp \
	mdp/Worker.cpp \
	mdp/WorkerTask.cpp \
	mdp/ZMQIdentity.cpp \
	mdp/ZMQWorkerContext.cpp \
	modbus_tools/Master.cpp \
	modbus_tools/SerialPort.cpp \
	modbus_tools/crc.cpp \
	modbus_tools/json.cpp

include Makefile.rules
