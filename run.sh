#!/bin/bash
for i in `seq 1 100`;
do
#	./queue >> run.log 
#	./stlqueue >> run.log 
#	./follyqueue >> run.log 
count=500000

	./bin/queue   $count   
	./bin/stlqueue  $count
	./bin/follyqueue  $count
	./bin/spscqueue  $count
	./bin/boostqueue  $count
done
