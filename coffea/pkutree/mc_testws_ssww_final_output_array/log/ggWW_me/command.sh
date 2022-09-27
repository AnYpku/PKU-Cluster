#! /bin/bash

sleep 501
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/mc_testws_ssww_final_output_array -p ggWW_me -d /data/pubfs/tyyang99/jupyter_files/pkutree/mc_ssww_parquet/ggWW_me -e no
echo "job done!"