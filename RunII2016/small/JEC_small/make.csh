#!/bin/bash
g++ -o run `root-config --cflags --glibs` runxx.C
./run >> process_run.txt 	
