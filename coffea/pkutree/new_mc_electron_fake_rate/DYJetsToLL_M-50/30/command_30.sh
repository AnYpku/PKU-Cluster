#! /bin/bash

sleep 89
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/fake_rate.py -n $2 -y 2018 -f $1 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/new_mc_electron_fake_rate/WJets/DYJetsToLL_M-10to50/DYJetsToLL_M-50/30 -l electron
echo "job done!"