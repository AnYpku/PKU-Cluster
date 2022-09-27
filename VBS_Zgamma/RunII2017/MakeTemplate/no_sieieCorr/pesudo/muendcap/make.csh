#!/bin/bash
g++ -o run `root-config --cflags --glibs` createroot.c
g++ -o build `root-config --cflags --glibs` buildtemplate.C

