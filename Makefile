#Makefile for hr_test

CC=gcc
MAKE=make
MODULE=hr_test

modules:
	echo "start to compile module: "$(MODULE)
	$(CC) -g hr_test.c -lrt -o $(MODULE)
	echo "compile done!"
	echo "xxxx"

clean:
	rm -f $(MODULE)
	rm -f $(MODULE).txt
	echo "zzz"

rebuild:
	make clean
	make modules
