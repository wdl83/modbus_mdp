all: \
	bw_test.Makefile \
	master_cli.Makefile \
	master_worker.Makefile \
	tlog_dump.Makefile
	make -f bw_test.Makefile
	make -f master_cli.Makefile
	make -f master_worker.Makefile
	make -f tlog_dump.Makefile

clean:
	rm *.o -f
	rm *.elf -f
