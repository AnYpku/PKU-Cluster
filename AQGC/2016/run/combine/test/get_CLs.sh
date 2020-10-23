operators_and_ranges="\
fM0,5165347
fM1,5165348
fM2,5165349
fM3,5165350
fM4,5165351
fM5,5165352
fM6,5165353
fM7,5165354
fT0,5165355
fT1,5165356
fT2,5165357
fT5,5165358
fT6,5165359
fT7,5165360
fT8,5165361
fT9,5165362
"
for operator_and_range in $operators_and_ranges
do
operator=`echo $operator_and_range | awk -F, '{print $1}'`
id=`echo $operator_and_range | awk -F, '{print $2}'`
echo $operator $id
python get_CLs.py $operator $id
done
