#! /bin/bash

sleep 826
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/fake_rate_parquet.py -n $2 -y 2018 -f $1 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/parquet_mc_electron_fake_rate/DYJetsToLL_M-50/10 -l electron
echo "job done!"