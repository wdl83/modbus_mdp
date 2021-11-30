all: \
	bw_test.Makefile \
	chslv.Makefile \
	master_cli.Makefile \
	master_worker.Makefile \
	monitor.Makefile \
	probe.Makefile \
	tlog_dump.Makefile
	make -f bw_test.Makefile
	make -f chslv.Makefile
	make -f master_cli.Makefile
	make -f master_worker.Makefile
	make -f monitor.Makefile
	make -f probe.Makefile
	make -f tlog_dump.Makefile

clean:
	rm *.o -f
	rm *.elf -f
