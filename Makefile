CFLAGS ?= -g -Wall -std=gnu11

example: example.c libhexdump.c hexdump.h
	$(CC) $(CFLAGS) -I. -o $@ example.c libhexdump.c

clean:
	-rm -rf example example.dSYM
