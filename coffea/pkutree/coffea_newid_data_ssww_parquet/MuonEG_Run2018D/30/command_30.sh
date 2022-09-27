#! /bin/bash

sleep 616
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/ssww.py -n $2 -y 2018 -f $1 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_data_ssww_parquet/MuonEG_Run2018D/30
echo "job done!"