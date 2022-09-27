#! /bin/bash

sleep 594
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/prepare_for_training.py -y 2018 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_for_training_data_parquet -p MuonEG_Run2018D -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_data_ssww_parquet/MuonEG_Run2018D -e no
echo "job done!"