example: example.c libhexdump.c hexdump.h
	$(CC) $(CFLAGS) -I. -o $@ example.c libhexdump.c

clean:
	-rm -f example
