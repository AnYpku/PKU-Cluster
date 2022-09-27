for (( j=0 ; j<1000 ; j++))
do
 i=$(echo "${j}*0.3"|bc)

 echo $i>>result_feldman.txt
 combine os_mll_fM0.root -M HybridNew --LHCmode LHC-feldman-cousins --clsAcc 0 --singlePoint  param=${i} --saveHybridResult >> result_feldman.txt
 echo '#################################' >> result_feldman.txt
 
done
