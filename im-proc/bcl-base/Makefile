ROOT=../bcl

CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -I$(ROOT)/include
LDFLAGS= -L$(ROOT)/lib -lbcl 

BIN=print-ppm\
	test1\
	extract-subimage\
	extract-channel\
	gray2color\
	color2mean\
	normalize


all: $(BIN)

print-ppm: print-ppm.o
	$(CC) print-ppm.o $(LDFLAGS) -o print-ppm

test1: test1.o 
	$(CC) test1.o $(LDFLAGS) -o test1

print-ppm.o: print-ppm.c

test1.o: test1.c 

test: test-ppm

test-ppm: all
	./print-ppm 0 255 255 200 300 > a.ppm; pvisu a.ppm ; read
	./print-ppm 255 0 255 200 300 > a.ppm; pvisu a.ppm ; read
	rm -rf a.ppm
	killall pvisu
	
	
extract-subimage: extract-subimage.o
	$(CC) extract-subimage.o $(LDFLAGS) -o extract-subimage

extract-subimage.o: extract-subimage.c



extract-channel: extract-channel.o
	$(CC) extract-channel.o $(LDFLAGS) -o extract-channel

extract-channel.o: extract-channel.c



gray2color: gray2color.o
	$(CC) gray2color.o $(LDFLAGS) -o gray2color

gray2color.o: gray2color.c



color2mean: color2mean.o
	$(CC) color2mean.o $(LDFLAGS) -o color2mean

color2mean.o: color2mean.c

normalize: normalize.o
	$(CC) normalize.o $(LDFLAGS) -o normalize

normalize.o: normalize.c


clean:
	rm -f *.o 

cleanall: clean
	rm -rf $(BIN) *.ppm

.PHONY :
	clean all


