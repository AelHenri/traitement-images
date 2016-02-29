ROOT=../bcl

CC = gcc
CFLAGS  = -Wall -Wextra -std=c99 -I$(ROOT)/include 
LDFLAGS = -L$(ROOT)/lib -lbcl -lm

PEPPER=../data/pepper.ppm

OBJ= color-transfer.o

SRC= color-transfer.c	 

BIN= color-transfer	

all: $(BIN)

color-transfer: color-transfer.o color-transfer.o
	$(CC) color-transfer.o $(LDFLAGS) -o $@

color-transfer.o: color-transfer.c 

clean:
	rm -f $(OBJ) *~ 

cleanall: clean
	rm -rf $(BIN) *.ppm* 

.PHONY: all clean cleanall 
