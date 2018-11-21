all: mario_test

clean:
	rm -f mario_test mario_test.o

mario: mario_test.c \
	gcc -g -std=c99 -O3 -Wall -fPIC -DLINUX32 -D__DEBUG__  -gstabs+ \
	-o mario_test \
	mario_test.c \
	-I/usr/local/include/ \
	-L/usr/local/lib/ -L/usr/lib/ \
	-lpthread
