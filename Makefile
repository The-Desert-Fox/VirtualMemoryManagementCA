CC=gcc
CFLAGS=-I.
DEPS = vmFunctions.h

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

simulate: vmSimulate.o vmFunctions.o
     $(CC) -o simulate vmSimulate.o vmFunctions.o
