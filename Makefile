all: maritcp

clean:
	rm -f maritcp *.o

maritcp: mario.c config.c function.c collect.c \
			mario/mario_akg.c mario/mario_conn.c mario/mario_network.c mario/mario.c mario/mario_log.c mario/mario_util.c mario/mario_table.h

	gcc -g -std=c99 -O3 -Wall -fPIC -DLINUX32 -D__DEBUG__  -gstabs+ \
	-o maritcp \
	mario.c config.c function.c collect.c \
	mario/mario.c mario/mario_akg.c mario/mario_conn.c mario/mario_network.c mario/mario_log.c mario/mario_util.c \
	-I/usr/local/include/ \
	-L/usr/local/lib/ -L/usr/lib/ \
	-lpthread -levent