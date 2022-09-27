#! /bin/bash

sleep 454
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/newid_data_testws_ssww_final_output_array -p DoubleMuon_Run2018D -d /data/pubfs/tyyang99/jupyter_files/pkutree/newid_data_ssww_parquet/DoubleMuon_Run2018D -e no
echo "job done!"