CC=gcc
CFLAGS=-I. -g -w
DEPS = hash.h
OBJ = passgenerator.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
passgenerator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)