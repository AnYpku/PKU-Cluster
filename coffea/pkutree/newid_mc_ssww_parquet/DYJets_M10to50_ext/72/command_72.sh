#! /bin/bash

sleep 1378
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/ssww.py -n $2 -y 2018 -f $1 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/newid_mc_ssww_parquet/DYJets_M10to50_ext/72
echo "job done!"