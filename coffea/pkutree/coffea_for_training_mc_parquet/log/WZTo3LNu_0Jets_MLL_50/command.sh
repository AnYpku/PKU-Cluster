#! /bin/bash

sleep 751
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/prepare_for_training.py -y 2018 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_for_training_mc_parquet -p WZTo3LNu_0Jets_MLL_50 -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_mc_ssww_parquet/WZTo3LNu_0Jets_MLL_50 -e no
echo "job done!"