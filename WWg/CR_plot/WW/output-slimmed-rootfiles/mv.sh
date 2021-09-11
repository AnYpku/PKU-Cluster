#!/bin/bash

for file in `cat file`
do
name=`echo $file | awk -F. '{print $1}'`
#echo "$name"
fname=${name}18.root
mv $file $fname

done
