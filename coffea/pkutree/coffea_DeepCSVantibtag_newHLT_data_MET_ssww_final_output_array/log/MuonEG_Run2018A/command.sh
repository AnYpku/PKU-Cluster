#! /bin/bash

sleep 470
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_DeepCSVantibtag_newHLT_data_MET_ssww_final_output_array -p MuonEG_Run2018A -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_data_ssww_parquet/MuonEG_Run2018A -e no
echo "job done!"