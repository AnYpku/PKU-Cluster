#!/bin/bash
g++ -o run `root-config --cflags --glibs` runxx.C
g++ -o run1 `root-config --cflags --glibs` runxx1.C
