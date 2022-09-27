#! /bin/bash

sleep 285
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/newid_mc_testws_ssww_final_output_array -p ggWW_te -d /data/pubfs/tyyang99/jupyter_files/pkutree/newid_mc_ssww_parquet/ggWW_te -e no
echo "job done!"