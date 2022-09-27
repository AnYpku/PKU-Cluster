#! /bin/bash

sleep 111
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/ssww.py -n $2 -y 2018 -f $1 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_mc_ssww_parquet/TTZToLLNuNu_M_10/14
echo "job done!"