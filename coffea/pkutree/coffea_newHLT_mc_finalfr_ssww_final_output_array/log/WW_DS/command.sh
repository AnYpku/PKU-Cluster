#! /bin/bash

sleep 716
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newHLT_mc_finalfr_ssww_final_output_array -p WW_DS -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_mc_ssww_parquet/WW_DS -e no
echo "job done!"