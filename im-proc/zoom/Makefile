ROOT=../bcl

CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -I$(ROOT)/include 
LDFLAGS= -L$(ROOT)/lib -lbcl -lfftw3 -lm

OBJ= fft.o test-fft.o copy.o padding.o filter.o
SRC= fft.h fft.c test-fft.c copy.c padding.c filter.c
BIN= test-fft copy padding filter

all: $(BIN)

test-fft: test-fft.o fft.o 
	$(CC) test-fft.o fft.o $(LDFLAGS) -o $@
fft.o: fft.c fft.h
test-fft.o: test-fft.c fft.h

copy: copy.o
	$(CC) copy.o $(LDFLAGS) -o $@

copy.o: copy.c
 
padding: padding.o fft.o
	$(CC) padding.o fft.o $(LDFLAGS) -o $@

padding.o: padding.c

filter: filter.o fft.o
	$(CC) filter.o fft.o $(LDFLAGS) -o $@

filter.o: filter.c

test: all
	@./test-fft ../data/lena-gray.ppm
	@display a.ppm&
	@read;
	@display b.ppm&
	@read;
	@killall display

pdf:
	a2ps -4 -AFill --line-numbers=1 -g -EC $(SRC) --medium=letter -o all.ps
	ps2pdf all.ps all.pdf

clean:
	rm -f $(OBJ) *~ *.ps 

cleanall: clean
	rm -rf $(BIN) *.ppm*  *.pdf

.PHONY: all clean cleanall pdf
