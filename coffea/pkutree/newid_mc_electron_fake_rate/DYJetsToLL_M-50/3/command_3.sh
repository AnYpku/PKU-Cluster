#! /bin/bash

sleep 763
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/fake_rate_newid.py -n $2 -y 2018 -f $1 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/newid_mc_electron_fake_rate/DYJetsToLL_M-50/3 -l electron
echo "job done!"