#!/bin/bash

root -b -q runfit.C
root -b -q fitfraction.C
cd ../../ElectronEndcap/ZAfit
root -b -q runfit.C
root -b -q fitfraction.C

