#!/bin/bash
g++ -o build `root-config --cflags --glibs` buildtemplate.C
g++ -o buildt `root-config --cflags --glibs` build.C

