#! /bin/bash
operators_and_ranges="\
fM0,20,0.5
fM1,40,1
fM2,15,0.5
fM3,20,0.5
fM4,20,0.5
fM5,25,0.5
fM6,40,1
fM7,60,1
fT0,1.0,0.05
fT1,2,0.05
fT2,2.0,0.05
fT5,1.0,0.05
fT6,2.0,0.05
fT7,3.0,0.05
fT8,1,0.05
fT9,2,0.05
"
for operator_and_range in $operators_and_ranges
do

operator=`echo $operator_and_range | awk -F, '{print $1}'`
upper=`echo $operator_and_range | awk -F, '{print $2}'`
step=`echo $operator_and_range | awk -F, '{print $3}'`
echo "$operator,$upper,$step"
num=`echo | awk "{print $upper/$step}"`
for (( j=0; j<$num ; j++))
do
point=`echo | awk "{print $step+$j*$step}"`

 echo "$num $operator $point"
 echo "$point" >> list_point_${operator}.txt
done

done
