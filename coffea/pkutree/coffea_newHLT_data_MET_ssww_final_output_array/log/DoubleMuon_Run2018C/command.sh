#! /bin/bash

sleep 817
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newHLT_data_MET_ssww_final_output_array -p DoubleMuon_Run2018C -d /data/pubfs/tyyang99/jupyter_files/pkutree/coffea_newid_data_ssww_parquet/DoubleMuon_Run2018C -e no
echo "job done!"