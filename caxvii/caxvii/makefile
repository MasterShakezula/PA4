CC=gcc
CFLAGS=-I. -g -w -pthreads
DEPS = hash.h
OBJ = passgenerator.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
passgenerator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)