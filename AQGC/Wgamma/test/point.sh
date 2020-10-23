operators_and_ranges="\
fM0,-10,10,0.2
fM1,-15,15,0.3
fM2,-5,5,0.1
fM3,-8,8,0.2
fM4,-8,8,0.2
fM5,-12,12,0.3
fM6,-20,20,0.4
fM7,-25,25,0.5
fT0,-1,1,0.05
fT1,-1.5,1.5,0.05
fT2,-2,2,0.05
fT5,-1.2,1.2,0.03
fT6,-1,1,0.05
fT7,-2,2,0.05
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
point_tmp=`echo | awk "{print $step+$j*$step}"`
point=`echo | awk "{print 0-$point_tmp}"`
 echo "$num $operator $point"
 echo "$point" >> list_point_${operator}.txt
done
done

