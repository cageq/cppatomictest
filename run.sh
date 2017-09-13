#!/bin/bash
for i in `seq 1 100`;
do
	echo  "spsc : "
#	./queue >> run.log 
#	./stlqueue >> run.log 
#	./follyqueue >> run.log 

	./queue  1000000
	./stlqueue 1000000
	./follyqueue  1000000
	./boostqueue  1000000
done
