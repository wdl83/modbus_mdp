all: \
	bw_test.Makefile \
	chslv.Makefile \
	master_cli.Makefile \
	master_worker.Makefile \
	monitor.Makefile \
	probe.Makefile \
	tlog_dump.Makefile \
	zmqpp/Makefile
	mkdir -p zmqpp-root
	make -C zmqpp
	make PREFIX=${PWD}/zmqpp-root install -C zmqpp
	make -f bw_test.Makefile
	make -f chslv.Makefile
	make -f master_cli.Makefile
	make -f master_worker.Makefile
	make -f monitor.Makefile
	make -f probe.Makefile
	make -f tlog_dump.Makefile

clean: \
	bw_test.Makefile \
	master_cli.Makefile \
	master_worker.Makefile \
	monitor.Makefile \
	probe.Makefile \
	tlog_dump.Makefile 
	make -f bw_test.Makefile clean
	make -f master_cli.Makefile clean
	make -f master_worker.Makefile clean
	make -f monitor.Makefile clean
	make -f probe.Makefile clean
	make -f tlog_dump.Makefile clean


