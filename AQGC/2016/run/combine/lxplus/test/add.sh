operators_and_ranges="\
fM0,-30,30
fM1,-60,60
fM2,-15,15
fM3,-25,25
fM4,-25,25
fM5,-40,40
fM6,-60,60
fM7,-90,90
fT0,-1,1
fT1,-1.5,1.5
fT2,-3,3
fT5,-1.2,1.2
fT6,-3,3
fT7,-4,4
fT8,-0.6,0.6
fT9,-1.8,1.8
"
for operator_and_range in $operators_and_ranges
do
 operator=`echo $operator_and_range | awk -F, '{print $1}'`
 echo $operator
 mkdir $operator
 cp *$operator* $operator
 line1="should_transfer_files = YES"
 line2="transfer_input_files =/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/run/combine/test/wpwp_${operator}_scaling_refined.root"
# sed -i "s/\.Test/\.TEST\_$operator/g" condor_condor-$operator.sh
# sed -i '3 d' condor_condor-$operator.sub
# sed -i "2 i$line1" condor_condor-$operator.sub
# sed -i "3 i$line2" condor_condor-$operator.sub
done
