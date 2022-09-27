#! /bin/bash

sleep 1769
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/fake_rate_parquet.py -n $2 -y 2018 -f $1 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/parquet_data_muon_fake_rate/136 -l muon
echo "job done!"