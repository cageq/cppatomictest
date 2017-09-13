#!/bin/bash
for i in `seq 1 100`;
do
	echo  "spsc : "
#	./queue >> run.log 
#	./stlqueue >> run.log 
#	./follyqueue >> run.log 
count=500000

	./queue   $count 
	./stlqueue  $count
	./follyqueue  $count
	./spscqueue  $count
	./boostqueue  $count
done
