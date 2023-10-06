#!/bin/bash
cd ..
make
cd build/
for((i=32;i<20000;i=i*2)); do
	echo "test con $i righe"
	head -$i input.txt > inputtest.txt
	rm output.log
	./final_program -overlap_list
	python3 pversio.py
	python3 testmatch_list.py
done
