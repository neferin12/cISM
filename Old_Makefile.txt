vpath %.h src/headers
vpath %.c src

CC = gcc
CFLAGS = -std=gnu11 -g -Og -Wall -Wextra -Wpedantic -Wstrict-prototypes -Wwrite-strings
RM = rm -rf
#CFLAGS = -std=c11 -pedantic -Wall -Werror -pthread -g
#LIBS  = -lpthread

.PHONY: all clean

all: cism

clean:
	$(RM) cism *.o build

cism: build/fileInterface.o build/errorHandling.o build/organization.o build/main.o
	$(CC) -o $@ $^

build/%.o: %.c %.h build
	$(CC) -c $(CFLAGS) -o $@ $<

build/%.o: %.c build
	$(CC) -c $(CFLAGS) -o $@ $<

build:
	@mkdir $@


fileInterface.o: fileInterface.c fileInterface.h errorHandling.h organization.h