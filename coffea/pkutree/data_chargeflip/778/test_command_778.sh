#! /bin/bash

source /home/pku/tyyang99/.bashrc
python /data/pubfs/tyyang99/jupyter_files/pkutree/charge_flip.py -n $2 -y 2018 -f $1 -t data -o /data/pubfs/tyyang99/jupyter_files/pkutree/temp_command/778
echo "job done!"