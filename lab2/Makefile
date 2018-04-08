CC=gcc
CFLAGS=-I.
DEPS = hello.h
OBJ = helloworld.o hello.o 

all: helloworld

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

helloworld: $(OBJ)
		gcc -o $@ $^ $(CFLAGS)

clean:
               rm hello.o helloworld.o helloworld