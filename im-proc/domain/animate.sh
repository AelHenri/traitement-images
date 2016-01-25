#!/bin/bash

mkdir tmp
for i in `seq 1 32`;
do
	s=$(($i*16))
	name=""
	if [ $i -lt 10 ]
		then
		name="a00$i.ppm"
	else
		name="a0$i.ppm"
	fi
		./scroll $s 0 ../data/earth.ppm tmp/$name
		./sphere tmp/$name tmp/$name
	done

	convert -loop 6 tmp/* animated.gif

	rm -rf tmp