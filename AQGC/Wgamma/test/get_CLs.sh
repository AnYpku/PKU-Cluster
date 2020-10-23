operators_and_ranges="\
fM0,5181701
fM1,5181702
fM2,5181703
fM3,5181704
fM4,5181705
fM5,5181706
fM6,5181707
fM7,5181708
fT0,5181709
fT1,5181710
fT2,5181711
fT5,5181712
fT6,5181713
fT7,5181714
"
for operator_and_range in $operators_and_ranges
do
operator=`echo $operator_and_range | awk -F, '{print $1}'`
id=`echo $operator_and_range | awk -F, '{print $2}'`
echo $operator $id
python get_CLs.py $operator $id
done
