#! /bin/bash

sleep 547
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_mc_testfr3_ssww_final_output_array -p ggWW_et -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_mc_ssww_parquet/ggWW_et -e no
echo "job done!"