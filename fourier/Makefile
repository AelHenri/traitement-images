ROOT=../bcl

CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -I$(ROOT)/include 
LDFLAGS= -L$(ROOT)/lib -lbcl -lfftw3 -lm

OBJ= fft.o test-fft.o 
SRC= fft.h fft.c test-fft.c 
BIN= test-fft 

all: $(BIN)

test-fft: test-fft.o fft.o 
	$(CC) test-fft.o fft.o $(LDFLAGS) -o $@

fft.o: fft.c fft.h
test-fft.o: test-fft.c fft.h

test:
	@echo "nothing to perform, no instructions"

pdf:
	a2ps -4 -AFill --line-numbers=1 -g -EC $(SRC) --medium=letter -o all.ps
	ps2pdf all.ps all.pdf

clean:
	rm -f $(OBJ) *~ *.ps 

cleanall: clean
	rm -rf $(BIN) *.ppm*  *.pdf

.PHONY: all clean cleanall pdf
