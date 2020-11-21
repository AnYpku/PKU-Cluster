
operators_and_ranges="\
fM0,-20,20
fM1,-35,35
fM2,-10,10
fM3,-20,20
fM4,-15,15
fM5,-25,25
fM6,-35,35
fM7,-50,50
fT0,-1,1
fT1,-1.5,1.5
fT2,-3,3
fT5,-1.0,1.0
fT6,-3,3
fT7,-3,3
fT8,-0.5,0.5
fT9,-1.5,1.5
"
for operator_and_range in $operators_and_ranges
do

   operator=`echo $operator_and_range | awk -F, '{print $1}'`
   lower=`echo $operator_and_range | awk -F, '{print $2}'`
   upper=`echo $operator_and_range | awk -F, '{print $3}'`
   band=`echo | awk "{print $upper*2}"`
#   echo "$operator,$band" 
   if [[ "$band" -gt 10 ]]; then
       num=$band
#       echo "$operator,$band,$num" 
   else 
       num=`echo | awk "{print $band*10}"`
#       echo "$operator,$band,$num" 
  fi
   for (( j=1 ; j<$num ; j++))
   do
      m=`echo | awk "{print $upper*2}"`
      n=`echo | awk "{print $upper/$num}"`
      i=`echo | awk "{print $lower+$j*$n}"`
      k=`echo | awk "{print $upper-$j*$n}"`
      echo "$operator,$upper,$num,$k" 
      combine os_mll_fM0.root -M HybridNew --LHCmode LHC-feldman-cousins --clsAcc 0 --singlePoint  param=${k} --saveHybridResult >> result_feldman_${operator}.txt
      echo "$operator, $k" >> result_feldman_${operator}.txt
      echo '#################################' >> result_feldman_${operator}.txt
      mv higgsCombineTest.HybridNew.mH120.root higgsCombineTest.HybridNew.mH120_${operator}_${k}.root

   done
done
