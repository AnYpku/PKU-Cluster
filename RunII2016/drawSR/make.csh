#!/bin/bash
g++ -o execute_name `root-config --cflags --glibs` loopPlot.C
./execute_name
