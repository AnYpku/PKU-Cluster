#!/bin/bash


combineCards.py Mjj_bin_* >&all.txt
text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO verbose  --PO map=.*/.*genbin1:r_1[1.,-10.,10.] --PO map=.*/.*genbin2:r_2[1.,-10.,10.] --PO map=.*/.*genbin3:r_3[1.,-10.,10.]  all.txt -o fullmodel.root
combine -M MultiDimFit fullmodel.root --saveFitResult

