operators_and_ranges="\
fM0,-10,10,0.05
fM1,-15,15,0.05
fM2,-5,5,0.05
fM3,-8,8,0.05
fM4,-8,8,0.05
fM5,-12,12,0.05
fM6,-20,20,0.05
fM7,-25,25,0.05
fT0,-1,1,0.005
fT1,-1.5,1.5,0.005
fT2,-2,2,0.005
fT5,-1.2,1.2,0.005
fT6,-1,1,0.005
fT7,-2,2,0.005
"
for operator_and_range in $operators_and_ranges
do
operator=`echo $operator_and_range | awk -F, '{print $1}'`
lower=`echo $operator_and_range | awk -F, '{print $2}'`
upper=`echo $operator_and_range | awk -F, '{print $3}'`
step=`echo $operator_and_range | awk -F, '{print $4}'`
echo "$operator,$upper,$step"
num=`echo | awk "{print $upper/$step}"`
for (( j=0; j<$num ; j++))
do
point=`echo | awk "{print $step+$j*$step}"`

 echo "$num $operator $point"
 echo "$point" >> list_point_${operator}.txt
done
done

