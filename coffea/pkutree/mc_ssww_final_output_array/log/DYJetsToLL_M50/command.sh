#! /bin/bash

sleep 634
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/mc_ssww_final_output_array -p DYJetsToLL_M50 -d /data/pubfs/tyyang99/jupyter_files/pkutree/mc_ssww_parquet/DYJetsToLL_M50 -e no
echo "job done!"