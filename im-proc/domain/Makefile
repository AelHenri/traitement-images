ROOT=../bcl

CC = gcc
CFLAGS  = -Wall -Wextra -std=c99 -I$(ROOT)/include 
LDFLAGS = -L$(ROOT)/lib -lbcl

PEPPER=../data/pepper.ppm

OBJ=move.o\
	shear.o\
	domain.o

SRC=move.c\
	shear.c\
	domain.h\
	domain.c

BIN=move\
	shear

all: $(BIN)

move: move.o move.o
	$(CC) move.o $(LDFLAGS) -o $@

shear: shear.o domain.o
	$(CC) shear.o domain.o $(LDFLAGS) -o $@

move.o: move.c 
shear.o: shear.c domain.h domain.o
domain.o: domain.h domain.c

test: test-move test-shear

test-move: all
	./move 0 30 $(PEPPER) a.ppm; pvisu a.ppm; read 
	./move 30 0 $(PEPPER) a.ppm; pvisu a.ppm; read
	./move 30 30 $(PEPPER) a.ppm; pvisu a.ppm; read
	./move -30 -30 $(PEPPER) a.ppm; pvisu a.ppm; read 	
	rm -rf a.ppm;
	killall pvisu

test-shear: all
	./shear h 30  $(PEPPER) a.ppm; pvisu a.ppm; read 
	./shear h -30  $(PEPPER) a.ppm; pvisu a.ppm; read
	./shear v 30 $(PEPPER) a.ppm; pvisu a.ppm; read
	./shear v -30 $(PEPPER) a.ppm; pvisu a.ppm; read
	rm -rf a.ppm;
	killall pvisu

clean:
	rm -f $(OBJ) *~ 

cleanall: clean
	rm -rf $(BIN) *.ppm* 

.PHONY: all clean cleanall 
