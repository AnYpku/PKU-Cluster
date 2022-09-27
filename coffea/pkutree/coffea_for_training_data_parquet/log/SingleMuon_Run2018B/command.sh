#! /bin/bash

sleep 842
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/prepare_for_training.py -y 2018 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_for_training_data_parquet -p SingleMuon_Run2018B -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_data_ssww_parquet/SingleMuon_Run2018B -e no
echo "job done!"