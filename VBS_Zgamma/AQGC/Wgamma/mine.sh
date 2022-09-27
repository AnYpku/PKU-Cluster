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
#text2workspace.py -m 125 all.txt -o os_mll_${operator}.root -P HiggsAnalysis.CombinedLimit.OneParameterPhysicsModel:my_1d_model --PO range_param=[${lower},${upper}] --PO scaling_filename=./wpwp_${operator}_scaling_refined.root

#mkdir $operator
cd $operator
cp ../os_mll_${operator}.root  ./
cp ../wpwp_${operator}_scaling_refined.root ./
cp ../condor_condor-fM0.sub ./
cp ../condor_condor-fM0.sh ./
cp ../list_point_${operator}.txt ./
#mkdir log
#mkdir out
#mkdir err
sed -i "s/fM0/${operator}/g" condor_condor-fM0.sub
sed -i "s/fM0/${operator}/g" condor_condor-fM0.sh
mv condor_condor-fM0.sub condor_condor-${operator}.sub
mv condor_condor-fM0.sh condor_condor-${operator}.sh
cd -
done

