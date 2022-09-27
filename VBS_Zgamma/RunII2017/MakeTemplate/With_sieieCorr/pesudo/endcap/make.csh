#!/bin/bash
g++ -o build `root-config --cflags --glibs` buildtemplate.C
#./build
#cd ../fit_endcap/
#root -l fitfraction.C 

