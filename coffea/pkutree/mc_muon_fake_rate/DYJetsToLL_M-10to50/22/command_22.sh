#! /bin/bash

sleep 104
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/fake_rate.py -n $2 -y 2018 -f $1 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/mc_muon_fake_rate/DYJetsToLL_M-10to50/22 -l muon
echo "job done!"