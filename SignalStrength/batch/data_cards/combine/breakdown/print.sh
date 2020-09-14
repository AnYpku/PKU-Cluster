#!/bin/bash
vars="\
full_RunII
full18_test
full16_test
full17_test
"
for var in $vars
do
    python extract.py $var
done

