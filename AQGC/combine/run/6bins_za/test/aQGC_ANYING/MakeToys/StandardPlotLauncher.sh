qsub -P P_atlas -m e -M delgove@lal.in2p3.fr -l ct=24:00:00 -l sps=1,vmem=3G,fsize=28G -N Toy_Script_0 -o ../Log_Toy///Toys/Log_Toy_Script_0.OU -e ../Log_Toy///Toys/Log_Toy_Script_0.ER Script_0
