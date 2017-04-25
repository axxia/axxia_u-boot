#!/bin/bash

rm -f *.c *.trace
./convert.py --input=../trace --architecture=5600
#./convert.py --input=../trace --architecture=2500

