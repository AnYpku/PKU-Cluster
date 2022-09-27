#! /bin/bash

sleep 818
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/data_ssww_final_output_array -p MuonEG_Run2018C -d /data/pubfs/tyyang99/jupyter_files/pkutree/data_ssww_parquet/MuonEG_Run2018C -e no
echo "job done!"