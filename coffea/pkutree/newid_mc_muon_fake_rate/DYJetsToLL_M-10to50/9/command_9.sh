#! /bin/bash

sleep 617
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/fake_rate_newid.py -n $2 -y 2018 -f $1 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/newid_mc_muon_fake_rate/DYJetsToLL_M-10to50/9 -l muon
echo "job done!"