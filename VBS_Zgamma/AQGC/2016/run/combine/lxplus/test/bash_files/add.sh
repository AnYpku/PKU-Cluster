operators_and_ranges="\
fM0
fM1
fM2
fM3
fM4
fM5
fM6
fM7
fT0
fT1
fT2
fT5
fT6
fT7
fT8
fT9
"
for operator in $operators_and_ranges
do
 sed -i "/.TEST/s/${operator}.TEST/g" condor_condor-$operator.sh
done
