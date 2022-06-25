ifndef OBJ_DIR
OBJ_DIR = ${PWD}/obj
export OBJ_DIR
endif

ifndef DST_DIR
DST_DIR = ${PWD}/dst
export DST_DIR
endif

all: master_worker.Makefile zmqpp/Makefile
	make -C zmqpp
	mkdir -p ${OBJ_DIR}/zmqpp
	make PREFIX=${OBJ_DIR}/zmqpp install -C zmqpp
	make -f master_worker.Makefile

install: master_worker.Makefile
	make -C zmqpp
	mkdir -p ${OBJ_DIR}/zmqpp
	make PREFIX=${OBJ_DIR}/zmqpp install -C zmqpp
	make -f master_worker.Makefile install

clean: master_worker.Makefile
	make -f master_worker.Makefile clean

purge:
	rm $(OBJ_DIR) -rf
