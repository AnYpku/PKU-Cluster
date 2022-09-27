#! /bin/bash

sleep 759
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/prepare_for_training.py -y 2018 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_for_training_data_parquet -p EGamma_Run2018C -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_data_ssww_parquet/EGamma_Run2018C -e no
echo "job done!"