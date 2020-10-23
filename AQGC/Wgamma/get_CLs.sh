operators_and_ranges="\
fM0,5174469
fM1,5174470
fM2,5174471
fM3,5174472
fM4,5174473
fM5,5174474
fM6,5174475
fM7,5174476
fT0,5174477
fT1,5174478
fT2,5174479
fT5,5174480
fT6,5174481
fT7,5174482
"
for operator_and_range in $operators_and_ranges
do
operator=`echo $operator_and_range | awk -F, '{print $1}'`
id=`echo $operator_and_range | awk -F, '{print $2}'`
echo $operator $id
python get_CLs.py $operator $id
done
