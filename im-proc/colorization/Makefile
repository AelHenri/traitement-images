ROOT=../bcl

CC = gcc
CFLAGS  = -Wall -Wextra -std=c99 -I$(ROOT)/include 
LDFLAGS = -L$(ROOT)/lib -lbcl -lm

PEPPER=../data/pepper.ppm

OBJ= colorization.o

SRC= colorization.c	 

BIN= colorization	

all: $(BIN)

colorization: colorization.o colorization.o
	$(CC) colorization.o $(LDFLAGS) -o $@

colorization.o: colorization.c 

clean:
	rm -f $(OBJ) *~ 

cleanall: clean
	rm -rf $(BIN) *.ppm* 

.PHONY: all clean cleanall 
