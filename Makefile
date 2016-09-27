CFLAGS:=-O3
override CFLAGS+=-Wall -Wextra -D_POSIX_C_SOURCE=201112L -D_XOPEN_SOURCE

C_SOURCES:=$(shell find -name '*.c')
C_OBJS:=$(patsubst %.c,%.o,$(CLIENT_SOURCES))

.PHONY: all clean

all: pong-client pong-server

clean:
	rm -rf $(C_OBJS) build/

pong-client: client/pong_client.o shared/display.o
	mkdir -p build/
	$(CC) $^ -o build/$@

pong-server:
	mkdir -p build/
	$(CC) $^ -o build/$@
