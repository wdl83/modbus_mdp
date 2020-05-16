all: master_worker.Makefile master_cli.Makefile
	make -f master_worker.Makefile
	make -f master_cli.Makefile

clean:
	rm *.o -f
	rm *.elf -f
