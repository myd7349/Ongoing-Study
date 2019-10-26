#!/bin/bash

for src in *.c
do
	echo ---------- $src ----------
	echo ----- O0 -----
	gcc -O0 $src
	ls -l a.out
	size a.out
	echo ----- O2 -----
	gcc -O2 $src
	ls -l a.out
	size a.out
done

