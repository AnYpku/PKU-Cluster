#! /bin/bash

sleep 92
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/fake_rate_parquet_coffea.py -n $2 -y 2018 -f $1 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_parquet_mc_electron_fake_rate/DYJetsToLL_M-50/4 -l electron
echo "job done!"