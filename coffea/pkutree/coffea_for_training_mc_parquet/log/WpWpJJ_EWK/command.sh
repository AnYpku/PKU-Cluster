#! /bin/bash

sleep 782
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/prepare_for_training.py -y 2018 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_for_training_mc_parquet -p WpWpJJ_EWK -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_mc_ssww_parquet/WpWpJJ_EWK -e no
echo "job done!"