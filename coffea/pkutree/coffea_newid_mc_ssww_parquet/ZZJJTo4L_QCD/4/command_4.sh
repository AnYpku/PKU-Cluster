#! /bin/bash

sleep 877
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/ssww.py -n $2 -y 2018 -f $1 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_mc_ssww_parquet/ZZJJTo4L_QCD/4
echo "job done!"