#! /bin/bash

sleep 846
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_DeepCSVbtag_newHLT_mc_MET_ssww_final_output_array -p ttHToNonbb -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_mc_ssww_parquet/ttHToNonbb -e no
echo "job done!"