#! /bin/bash

sleep 656
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/process_parquet.py -y 2018 -t mc -o /data/pubfs/tyyang99/jupyter_files/pkutree/mc_ssww_final_output_array -p ZZJJTo4L_EWK -d /data/pubfs/tyyang99/jupyter_files/pkutree/mc_ssww_parquet/ZZJJTo4L_EWK -e no
echo "job done!"