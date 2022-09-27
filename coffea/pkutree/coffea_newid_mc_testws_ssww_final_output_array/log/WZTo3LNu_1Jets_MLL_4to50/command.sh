#! /bin/bash

sleep 590
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_mc_testws_ssww_final_output_array -p WZTo3LNu_1Jets_MLL_4to50 -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_mc_ssww_parquet/WZTo3LNu_1Jets_MLL_4to50 -e no
echo "job done!"