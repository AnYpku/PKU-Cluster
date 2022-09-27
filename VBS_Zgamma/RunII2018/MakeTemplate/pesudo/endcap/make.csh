#!/bin/bash
g++ -o buildt `root-config --cflags --glibs` build.C
g++ -o build `root-config --cflags --glibs` buildtemplate.C

