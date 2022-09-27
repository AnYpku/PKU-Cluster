#! /bin/bash

sleep 92
source /home/pku/tyyang99/.bashrc
cd /data/pubfs/tyyang99/jupyter_files/pkutree
python /data/pubfs/tyyang99/jupyter_files/pkutree/charge_flip.py -n $2 -y 2018 -f $1 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/newid_data_chargeflip/346
echo "job done!"