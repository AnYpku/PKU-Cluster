#!/bin/bash
ls *.root > tmp
for file in `cat tmp`
do
    name1=`echo "$file" | awk -Fewk '{print $1}'` 
    name2=`echo "$file" | awk -Fewk '{print $2}'`
    echo "$name1"
    echo "$name2"
    mv $file ${name1}.root

done
