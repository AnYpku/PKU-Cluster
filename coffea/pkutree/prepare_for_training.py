from cmath import log
import uproot as up
import awkward as ak
import coffea
from coffea.nanoevents import NanoEventsFactory, NanoAODSchema, BaseSchema, TreeMakerSchema
from coffea.nanoevents.methods import candidate
ak.behavior.update(candidate.behavior)
from template.temp_class import ntuplize
import numpy as np
import argparse
import os
from utils import common_helper as com
from utils import analyze_helper as ana
from coffea import hist as chist
import yaml

import numba as nb

@nb.jit(nopython=True)
def set_elec_fr_weight(pt,eta):
    if 10<pt<=20:
        if 0<abs(eta)<=1:
            return 0.401
        elif 1<abs(eta)<=1.5:
            return 0.353
        elif 1.5<abs(eta)<=2.0:
            return 0.203
        elif 2.0<abs(eta):
            return 0.260
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    elif 20<pt<=25:
        if 0<abs(eta)<=1:
            return 0.351
        elif 1<abs(eta)<=1.5:
            return 0.391
        elif 1.5<abs(eta)<=2.0:
            return 0.194
        elif 2.0<abs(eta):
            return 0.304
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    elif 25<pt<=30:
        if 0<abs(eta)<=1:
            return 0.387
        elif 1<abs(eta)<=1.5:
            return 0.349
        elif 1.5<abs(eta)<=2.0:
            return 0.214
        elif 2.0<abs(eta):
            return 0.266
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    elif 30<pt<=35:
        if 0<abs(eta)<=1:
            return 0.369
        elif 1<abs(eta)<=1.5:
            return 0.347
        elif 1.5<abs(eta)<=2.0:
            return 0.204
        elif 2.0<abs(eta):
            return 0.247
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    elif pt>35:
        if 0<abs(eta)<=1:
            return 0.394
        elif 1<abs(eta)<=1.5:
            return 0.373
        elif 1.5<abs(eta)<=2.0:
            return 0.228
        elif 2.0<abs(eta):
            return 0.257
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    else:
        print("Sth wrong with the electron pt cut!")
        return -1

@nb.jit(nopython=True)    
def set_mu_fr_weight(pt,eta):
    if 10<pt<=20:
        if 0<abs(eta)<=1:
            return 0.329
        elif 1<abs(eta)<=1.5:
            return 0.375
        elif 1.5<abs(eta)<=2.0:
            return 0.415
        elif 2.0<abs(eta):
            return 0.468
        else:
            print("Sth wrong with the muon eta cut!")
            return -1
    elif 20<pt<=25:
        if 0<abs(eta)<=1:
            return 0.288
        elif 1<abs(eta)<=1.5:
            return 0.345
        elif 1.5<abs(eta)<=2.0:
            return 0.418
        elif 2.0<abs(eta):
            return 0.458
        else:
            print("Sth wrong with the muon eta cut!")
            return -1
    elif 25<pt<=30:
        if 0<abs(eta)<=1:
            return 0.280
        elif 1<abs(eta)<=1.5:
            return 0.346
        elif 1.5<abs(eta)<=2.0:
            return 0.413
        elif 2.0<abs(eta):
            return 0.477
        else:
            print("Sth wrong with the muon eta cut!")
            return -1
    elif 30<pt<=35:
        if 0<abs(eta)<=1:
            return 0.293
        elif 1<abs(eta)<=1.5:
            return 0.353
        elif 1.5<abs(eta)<=2.0:
            return 0.406
        elif 2.0<abs(eta):
            return 0.515
        else:
            print("Sth wrong with the muon eta cut!")
            return -1
    elif pt>35:
        if 0<abs(eta)<=1:
            return 0.310
        elif 1<abs(eta)<=1.5:
            return 0.338
        elif 1.5<abs(eta)<=2.0:
            return 0.427
        elif 2.0<abs(eta):
            return 0.517
        else:
            print("Sth wrong with the muon eta cut!")
            return -1
    else:
        print("Sth wrong with the muon pt cut!")
        return -1

@nb.jit(nopython=True)
def non_prompt_weight(pt1_array,eta1_array,pt2_array,eta2_array,iselectron1_array,iselectron2_array,istight1_array,istight2_array):
    w_array = []
    for i in range(len(pt1_array)):
        pt1 = pt1_array[i]
        eta1 = eta1_array[i]
        pt2 = pt2_array[i]
        eta2 = eta2_array[i]
        iselectron1 = iselectron1_array[i]
        iselectron2 = iselectron2_array[i]
        istight1 = istight1_array[i]
        istight2 = istight2_array[i]
        if iselectron1 == True:
            w1 = set_elec_fr_weight(pt1,eta1)
        else:
            w1 = set_mu_fr_weight(pt1,eta1)
        if iselectron2 == True:
            w2 = set_elec_fr_weight(pt2,eta2)
        else:
            w2 = set_mu_fr_weight(pt2,eta2)
#         w = (1-istight1)*w1/(1-w1) + (1-istight2)*w2/(1-w2) - (1-istight1)*(1-istight2)*w1/(1-w1)*w2/(1-w2)
        if istight1+istight2==1:
            w = (1-istight1)*w1/(1-w1) + (1-istight2)*w2/(1-w2)
        elif istight1+istight2==0:
            w = -w1/(1-w1)*w2/(1-w2)
        else:
            w = 0
        w_array.append(w)
    return w_array

@nb.jit(nopython=True)
def Data_set_elec_chargeflip_weight(pt,eta):
    if 20<=pt<=40:
        if 0<abs(eta)<=1:
            return 0.000463
        elif 1<abs(eta)<=1.5:
            return 0.000466
        elif 1.5<abs(eta)<=2.0:
            return 0.000934
        elif 2.0<abs(eta):
            return 0.001295
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    elif 40<pt<=60:
        if 0<abs(eta)<=1:
            return 0.000187
        elif 1<abs(eta)<=1.5:
            return 0.000550
        elif 1.5<abs(eta)<=2.0:
            return 0.001159
        elif 2.0<abs(eta):
            return 0.001883
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    elif 60<pt<=80:
        if 0<abs(eta)<=1:
            return 0.000195
        elif 1<abs(eta)<=1.5:
            return 0.000594
        elif 1.5<abs(eta)<=2.0:
            return 0.001548
        elif 2.0<abs(eta):
            return 0.002406
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    elif pt>80:
        if 0<abs(eta)<=1:
            return 0.000250
        elif 1<abs(eta)<=1.5:
            return 0.001006
        elif 1.5<abs(eta)<=2.0:
            return 0.001807
        elif 2.0<abs(eta):
            return 0.003609
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    else:
        print("Sth wrong with the electron pt cut!")
        return -1
    
@nb.jit(nopython=True)
def MC_set_elec_chargeflip_weight(pt,eta):
    if 20<=pt<=40:
        if 0<abs(eta)<=1:
            return 0.000177
        elif 1<abs(eta)<=1.5:
            return 0.000162
        elif 1.5<abs(eta)<=2.0:
            return 0.000266
        elif 2.0<abs(eta):
            return 0.000283
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    elif 40<pt<=60:
        if 0<abs(eta)<=1:
            return 0.000087
        elif 1<abs(eta)<=1.5:
            return 0.000145
        elif 1.5<abs(eta)<=2.0:
            return 0.000283
        elif 2.0<abs(eta):
            return 0.000409
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    elif 60<pt<=80:
        if 0<abs(eta)<=1:
            return 0.000385
        elif 1<abs(eta)<=1.5:
            return 0.000468
        elif 1.5<abs(eta)<=2.0:
            return 0.000567
        elif 2.0<abs(eta):
            return 0.000779
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    elif pt>80:
        if 0<abs(eta)<=1:
            return 0.000772
        elif 1<abs(eta)<=1.5:
            return 0.000775
        elif 1.5<abs(eta)<=2.0:
            return 0.000904
        elif 2.0<abs(eta):
            return 0.001328
        else:
            print("Sth wrong with the electron eta cut!")
            return -1
    else:
        print("Sth wrong with the electron pt cut!")
        return -1

@nb.jit(nopython=True)
def charge_flip_weight(pt1_array,eta1_array,pt2_array,eta2_array,iselectron1_array,iselectron2_array,isdata):
    w_array = []
    if isdata==True:
        for i in range(len(pt1_array)):
            pt1 = pt1_array[i]
            eta1 = eta1_array[i]
            pt2 = pt2_array[i]
            eta2 = eta2_array[i]
            iselectron1 = iselectron1_array[i]
            iselectron2 = iselectron2_array[i]
            w1 = Data_set_elec_chargeflip_weight(pt1,eta1)
            w2 = Data_set_elec_chargeflip_weight(pt2,eta2)
            w = (1*iselectron1)*w1 + (1*iselectron2)*w2
            w_array.append(w)
    else:
        for i in range(len(pt1_array)):
            pt1 = pt1_array[i]
            eta1 = eta1_array[i]
            pt2 = pt2_array[i]
            eta2 = eta2_array[i]
            iselectron1 = iselectron1_array[i]
            iselectron2 = iselectron2_array[i]
            w1 = MC_set_elec_chargeflip_weight(pt1,eta1)
            w2 = MC_set_elec_chargeflip_weight(pt2,eta2)
            w = (1*iselectron1)*w1 + (1*iselectron2)*w2
            w_array.append(w)
    return w_array

def list_concatenate(list1,list2):
    new_list = []
    for a in list1:
        new_list.append(a)
    for b in list2:
        new_list.append(b)
    return new_list


import argparse

parser = argparse.ArgumentParser(description='manual to this script')
parser.add_argument('-y', '--year', help='which year to run: 2016, 2017, 2018', default='2018')
parser.add_argument('-t', '--type', help='which type: data, mc', choices=('data', 'mc'), default='data')
# parser.add_argument('-n', '--number', help='id of the rootfile, used for the name of output file')
parser.add_argument('-p', '--process', help='name of the process')
parser.add_argument('-d', '--directory', help='directory of the process', default='')
parser.add_argument('-o', '--output_dir', help='output abs directory')
parser.add_argument('-e', '--ext', help='whether process have ext samples', choices=('yes', 'no'), default='no')
args = parser.parse_args()

if args.type=='data':
    isdata=True
elif args.type=='mc':
    isdata=False
else:
    pass

if isdata==True:
    with open(f"/data/pubfs/tyyang99/jupyter_files/data_2018_nanov7.yaml", 'r') as f:
        mc_yaml = yaml.load(f, Loader=yaml.FullLoader)
else:
    with open(f"/data/pubfs/tyyang99/jupyter_files/changexs_datasets.yaml", 'r') as f:
        mc_yaml = yaml.load(f, Loader=yaml.FullLoader)
        
process = args.process
year = args.year
if year=='2018':
    Lumi = 60.0*1e+03

SR_2e_sel = []
SR_2mu_sel = []
SR_1e1mu_sel = []

SR_nonprompt_2e_sel = []
SR_nonprompt_2mu_sel = []
SR_nonprompt_1e1mu_sel = []

SR_os_2e_sel = []
SR_os_2mu_sel = []
SR_os_1e1mu_sel = []

SR_leptons = []
SR_jets = []
SR_MET = []
SR_weight = []

SR_nonprompt_leptons = []
SR_nonprompt_jets = []
SR_nonprompt_MET = []
SR_nonprompt_weight = []

SR_os_leptons = []
SR_os_jets = []
SR_os_MET = []
SR_os_weight = []


if process.endswith('_ext'):
    pass
else:
    print(process)
    if isdata==True:
        pass
    else:
        xs = mc_yaml[process]['xs']
    nevents = 0
    parquet_list = []
    
    process_dir = args.directory
    for num in os.listdir(process_dir):
        parquet_list.append(process_dir+'/%s/%s.parquet'%(num,num))
    
    if args.ext=='yes':
        process_ext_dir = args.directory + '_ext'
        for num in os.listdir(process_ext_dir):
            parquet_list.append(process_ext_dir+'/%s/%s.parquet'%(num,num))
    else:
        pass
    
    for n_par, parquet_file in enumerate(parquet_list):
        parquet_dir = parquet_file
        
        try:
            events = NanoEventsFactory.from_parquet(parquet_dir, schemaclass=NanoAODSchema).events()
            print(parquet_dir,'\t%d/%d'%(n_par+1,len(parquet_list)))
        except:
            continue
        nevents += events.nevents[0]

        muons = events.Muon
        electrons = events.Electron
        taus = events.Tau
        good_jets = events.Jet
        MET = events.MET
        puppimet = events.PuppiMET

        events['nloose_muons'] = np.sum(muons.isloose==1,axis=1)
        events['ntight_muons'] = np.sum(muons.istight==1,axis=1)

        events['nloose_electrons'] = np.sum(electrons.isloose==1,axis=1)
        events['ntight_electrons'] = np.sum(electrons.istight==1,axis=1)

        events['ngood_jets'] = ak.count(good_jets.pt,axis=1)
        
        good_tau_sel1 = (taus.pt > 20) & (abs(taus.eta) < 2.3) & ((taus.decayMode!=5) & (taus.decayMode!=6)) & (taus.idDeepTau2017v2p1VSjet>>2 & 1)
        good_tau_sel2 = (taus.idDeepTau2017v2p1VSe > 16) & (taus.idDeepTau2017v2p1VSjet > 16) & (taus.idDeepTau2017v2p1VSmu > 4)
        good_tau_sel3 = ana.is_clean(taus,muons,0.4) & ana.is_clean(taus,electrons,0.4)
        good_tau_sel = good_tau_sel1 & good_tau_sel2 & good_tau_sel3

        taus['isgood'] = good_tau_sel
        events['ngood_taus'] = np.sum(good_tau_sel,axis=1)
    
        #2lepton and multijets
        nleps_sel = events.nloose_muons+events.nloose_electrons==2
        nveto_leps_sel = events.nveto.muons+events.nveto.electrons==2
        njets_sel = events.ngood_jets>=2
        tau_veto_sel = events.ngood_taus==0
        _2lnj_sel = nleps_sel & nveto_leps_sel & njets_sel & tau_veto_sel
    
        #get selected objects
        sel_events = events[_2lnj_sel]
        sel_electrons = electrons[electrons.isloose==1][_2lnj_sel]
        sel_muons = muons[muons.isloose==1][_2lnj_sel]
        sel_leptons = ak.concatenate([sel_electrons,sel_muons],axis=1)
        sel_jets = good_jets[_2lnj_sel]
        sel_MET = MET[_2lnj_sel]

        #get 1e1mu, 2e, 2mu
        _2e_sel = (sel_events.nloose_electrons==2)
        _2m_sel = (sel_events.nloose_muons==2)
        _1e1mu_sel = (sel_events.nloose_electrons==1) & (sel_events.nloose_muons==1)

        #HLT for 1e1mu, 2e, 2mu
        HLT_all_list = ['Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                   'Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
                   'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
                   'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL',
                   'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                   'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
                   'Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8',
                   'Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8',
                   'Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8',
                   'Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8',
                   'Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
                   'Ele23_Ele12_CaloIdL_TrackIdL_IsoVL',
                   'DiEle27_WPTightCaloOnly_L1DoubleEG',
                   'DoubleEle33_CaloIdL_MW',
                   'DoubleEle25_CaloIdL_MW',
                   'DoubleEle27_CaloIdL_MW',
                   'DoublePhoton70',
                   'IsoMu24','IsoMu27','IsoMu30','Mu50',
                   'Ele115_CaloIdVT_GsfTrkIdT',
                   'Ele27_WPTight_Gsf',
                   'Ele28_WPTight_Gsf',
                   'Ele32_WPTight_Gsf',
                   'Ele35_WPTight_Gsf',
                   'Ele38_WPTight_Gsf',
                   'Ele40_WPTight_Gsf',
                   'Ele32_WPTight_Gsf_L1DoubleEG',
                   'Photon200']
        if isdata==False:
            HLT_list_pass = ['Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                        'Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
                        'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
                        'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL',
                        'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                        'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
                        'Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8',
                        'Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8',
                        'Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8',
                        'Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8',
                        'Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
                        'Ele23_Ele12_CaloIdL_TrackIdL_IsoVL',
                        'DiEle27_WPTightCaloOnly_L1DoubleEG',
                        'DoubleEle33_CaloIdL_MW',
                        'DoubleEle25_CaloIdL_MW',
                        'DoubleEle27_CaloIdL_MW',
                        'DoublePhoton70',
                        'IsoMu24','IsoMu27','IsoMu30','Mu50',
                        'Ele115_CaloIdVT_GsfTrkIdT',
                        'Ele27_WPTight_Gsf',
                        'Ele28_WPTight_Gsf',
                        'Ele32_WPTight_Gsf',
                        'Ele35_WPTight_Gsf',
                        'Ele38_WPTight_Gsf',
                        'Ele40_WPTight_Gsf',
                        'Ele32_WPTight_Gsf_L1DoubleEG',
                        'Photon200']
            HLT_list_fail = []
        else:
            if 'MuonEG' in process:
                HLT_list_pass = ['Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
                            'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL',
                            'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL'
                            ]
                HLT_list_fail = []
            elif 'DoubleMuon' in process:
                HLT_list_pass = ['Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8',
                            'Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8',
                            'Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8',
                            'Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8'
                            ]
                HLT_list_fail = ['Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
                            'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL',
                            'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL'
                            ]
            elif 'SingleMuon' in process:
                HLT_list_pass = ['IsoMu24','IsoMu27','IsoMu30','Mu50']
                HLT_list_fail = ['Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
                            'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL',
                            'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
                            'Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8',
                            'Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8',
                            'Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8',
                            'Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8'
                            ]
            elif 'EGamma' in process:
                HLT_list_pass = ['Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Ele23_Ele12_CaloIdL_TrackIdL_IsoVL',
                            'DiEle27_WPTightCaloOnly_L1DoubleEG',
                            'DoubleEle33_CaloIdL_MW',
                            'DoubleEle25_CaloIdL_MW',
                            'DoubleEle27_CaloIdL_MW',
                            'DoublePhoton70',
                            'Ele115_CaloIdVT_GsfTrkIdT',
                            'Ele27_WPTight_Gsf',
                            'Ele28_WPTight_Gsf',
                            'Ele32_WPTight_Gsf',
                            'Ele35_WPTight_Gsf',
                            'Ele38_WPTight_Gsf',
                            'Ele40_WPTight_Gsf',
                            'Ele32_WPTight_Gsf_L1DoubleEG',
                            'Photon200']
                HLT_list_fail = ['Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
                            'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL',
                            'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
                            'Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL',
                            'Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8',
                            'Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8',
                            'Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8',
                            'Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8',
                            'IsoMu24','IsoMu27','IsoMu30','Mu50'
                            ]
            else:
                HLT_list = []

        HLT_sel_pass = 0*ak.ones_like(sel_events.nloose_muons)==1
        HLT_sel_fail = 0*ak.ones_like(sel_events.nloose_muons)==1
        for field in HLT_list_pass:
            try:
                HLT_sel_pass = HLT_sel_pass | sel_events.HLT[field]
            except:
                pass
        for field in HLT_list_fail:
            try:
                HLT_sel_fail = HLT_sel_fail | sel_events.HLT[field]
            except:
                pass
        HLT_sel = HLT_sel_pass & (1-HLT_sel_fail)
        #get leading and subleading lepton and mll
        leading_lep_idx = ak.argmax(sel_leptons.pt,axis=1,keepdims=True)
        subleading_lep_idx = 1-leading_lep_idx
        sel_leptons_mll = (sel_leptons[:,0]+sel_leptons[:,1]).mass

        #lepton selection
        lep_pt_sel = (sel_leptons[leading_lep_idx].pt>25) & (sel_leptons[subleading_lep_idx].pt>20)
        lep_mll_sel = sel_leptons_mll>20
        lep_mllzz_sel = (_2e_sel & (abs(sel_leptons_mll-91.2)>15)) | ((1-_2e_sel)==1)
        lep_tc_sel = np.sum(sel_leptons.istightcharge,axis=1)==2
        MET_pt_sel = MET[_2lnj_sel].pt>30
#         MET_pt_sel = puppimet[_2lnj_sel].pt>30

        #jets variables definition
        leading_jet = sel_jets[ak.argsort(sel_jets.pt,axis=1,ascending=False)==0]
        subleading_jet = sel_jets[ak.argsort(sel_jets.pt,axis=1,ascending=False)==1]
        jet1_pt = leading_jet.pt
        jet1_eta = leading_jet.eta
        jet2_pt = subleading_jet.pt
        jet2_eta = subleading_jet.eta
        zf_2leps = abs(sel_leptons.eta-(jet1_eta+jet2_eta)[:,0]/2)/abs(jet1_eta-jet2_eta)[:,0]
        sel_jets_mjj = (leading_jet+subleading_jet).mass

        #jets selection
#         jet_btag_sel = np.sum(sel_jets.btagDeepFlavB>0.2783,axis=1)<1
        jet_btag_sel = np.sum(sel_jets.btagDeepB>0.4184,axis=1)<1
        jet_anti_btag_sel = (1-jet_btag_sel)==1
        jet_mjj_sel = (sel_jets_mjj>500)
        jet_deta_sel = abs(jet1_eta-jet2_eta)>2.5
        jet_pt_sel = (jet1_pt>50) & (jet2_pt>50)
        zf_sel = (zf_2leps[:,0] < 0.75) & (zf_2leps[:,1] < 0.75)

        #same-sign
        ss_sel = (abs(np.sum(sel_electrons.charge,axis=1)+np.sum(sel_muons.charge,axis=1))>0)
        os_sel = (abs(np.sum(sel_electrons.charge,axis=1)+np.sum(sel_muons.charge,axis=1))==0)
        # ss_2lnj_sel = nleps_sel & njets_sel & ss_sel
        # os_2lnj_sel = nleps_sel & njets_sel & os_sel

        #merge_selection_condition
        lep_merged_sel = lep_pt_sel & lep_mll_sel & lep_mllzz_sel & lep_tc_sel
        jet_merged_sel = jet_btag_sel & jet_mjj_sel & jet_deta_sel & jet_pt_sel
#         jet_merged_sel = jet_anti_btag_sel & jet_mjj_sel & jet_deta_sel & jet_pt_sel
        ss_all_merged_sel = lep_merged_sel & jet_merged_sel & MET_pt_sel & zf_sel & (HLT_sel==1) & ss_sel
        os_all_merged_sel = lep_merged_sel & jet_merged_sel & MET_pt_sel & zf_sel & (HLT_sel==1) & os_sel

        events_after_sel = sel_events[ss_all_merged_sel[:,0]]
        electrons_after_sel = sel_electrons[ss_all_merged_sel[:,0]]
        muons_after_sel = sel_muons[ss_all_merged_sel[:,0]]
        leptons_after_sel = sel_leptons[ss_all_merged_sel[:,0]]
        jets_after_sel = sel_jets[ss_all_merged_sel[:,0]]
        MET_after_sel = sel_MET[ss_all_merged_sel[:,0]]

        #tight leptons
        print(len(leptons_after_sel))
        tight_leps_sel = (ak.sum(leptons_after_sel.istight,axis=1)==2)
        tight_leptons = leptons_after_sel[tight_leps_sel]
        tight_leptons_jets = jets_after_sel[tight_leps_sel]
        tight_leptons_MET = MET_after_sel[tight_leps_sel]

        os_tight_leps_sel = (ak.sum(sel_leptons[os_all_merged_sel[:,0]].istight,axis=1)==2)
        os_tight_leptons = sel_leptons[os_all_merged_sel[:,0]][os_tight_leps_sel]
        os_tight_leptons_jets = sel_jets[os_all_merged_sel[:,0]][os_tight_leps_sel]
        os_tight_leptons_MET = sel_MET[os_all_merged_sel[:,0]][os_tight_leps_sel]

        not_both_tight_leptons = leptons_after_sel[tight_leps_sel==0]
        not_both_tight_leptons_jets = jets_after_sel[tight_leps_sel==0]
        not_both_tight_leptons_MET = MET_after_sel[tight_leps_sel==0]
        print(np.sum(tight_leps_sel))
        print(np.sum(os_tight_leps_sel))
        
        test_2e_sel = (sel_events.nloose_electrons==2)
        test_1e1mu_sel = (sel_events.nloose_electrons==1)
        test_2mu_sel = (sel_events.nloose_muons==2)

        os_tight_2e_sel = 1*(test_2e_sel[os_all_merged_sel[:,0]][os_tight_leps_sel])
        os_tight_2mu_sel = 1*(test_2mu_sel[os_all_merged_sel[:,0]][os_tight_leps_sel])
        os_tight_1e1mu_sel = 1*(test_1e1mu_sel[os_all_merged_sel[:,0]][os_tight_leps_sel])
        
        SR_os_2e_sel.append(os_tight_2e_sel)
        SR_os_2mu_sel.append(os_tight_2mu_sel)
        SR_os_1e1mu_sel.append(os_tight_1e1mu_sel)
        
        test_tight_2e_sel = 1*(test_2e_sel[ss_all_merged_sel[:,0]][tight_leps_sel])
        test_tight_2mu_sel = 1*(test_2mu_sel[ss_all_merged_sel[:,0]][tight_leps_sel])
        test_tight_1e1mu_sel = 1*(test_1e1mu_sel[ss_all_merged_sel[:,0]][tight_leps_sel])
        
        SR_2e_sel.append(test_tight_2e_sel)
        SR_2mu_sel.append(test_tight_2mu_sel)
        SR_1e1mu_sel.append(test_tight_1e1mu_sel)
        
        nonprompt_2e_sel = 1*(test_2e_sel[ss_all_merged_sel[:,0]][tight_leps_sel==0])
        nonprompt_2mu_sel = 1*(test_2mu_sel[ss_all_merged_sel[:,0]][tight_leps_sel==0])
        nonprompt_1e1mu_sel = 1*(test_1e1mu_sel[ss_all_merged_sel[:,0]][tight_leps_sel==0])
        
        SR_nonprompt_2e_sel.append(nonprompt_2e_sel)
        SR_nonprompt_2mu_sel.append(nonprompt_2mu_sel)
        SR_nonprompt_1e1mu_sel.append(nonprompt_1e1mu_sel)

        pt1 = not_both_tight_leptons.pt[:,0]
        eta1 = not_both_tight_leptons.eta[:,0]
        pt2 = not_both_tight_leptons.pt[:,1]
        eta2 = not_both_tight_leptons.eta[:,1]
        iselectron1 = not_both_tight_leptons.iselectron[:,0]
        iselectron2 = not_both_tight_leptons.iselectron[:,1]
        istight1 = not_both_tight_leptons.istight[:,0]
        istight2 = not_both_tight_leptons.istight[:,1]
        nonp_weight = non_prompt_weight(pt1, eta1, pt2, eta2, iselectron1, iselectron2, istight1, istight2)
        if isdata==False:
            nonp_weight = ak.Array(nonp_weight)*events_after_sel.Generator.weight[tight_leps_sel==0]
        else:
            nonp_weight = ak.Array(nonp_weight)

        cf_pt1 = os_tight_leptons.pt[:,0]
        cf_eta1 = os_tight_leptons.eta[:,0]
        cf_pt2 = os_tight_leptons.pt[:,1]
        cf_eta2 = os_tight_leptons.eta[:,1]
        cf_iselectron1 = os_tight_leptons.iselectron[:,0]
        cf_iselectron2 = os_tight_leptons.iselectron[:,1]
        cf_weight = charge_flip_weight(cf_pt1, cf_eta1, cf_pt2, cf_eta2, cf_iselectron1, cf_iselectron2, isdata)
        if isdata==False:
            cf_weight = ak.Array(cf_weight)*sel_events.Generator.weight[os_all_merged_sel[:,0]][os_tight_leps_sel]
        else:
            cf_weight = ak.Array(cf_weight)
            
        if isdata==False:
            sr_weight = events_after_sel.Generator.weight[tight_leps_sel]
        else:
            sr_weight = ak.ones_like(tight_leps_sel[tight_leps_sel])*1
        
        SR_leptons.append(tight_leptons)
        SR_jets.append(tight_leptons_jets)
        SR_MET.append(tight_leptons_MET)
        SR_weight.append(sr_weight)

        SR_nonprompt_leptons.append(not_both_tight_leptons)
        SR_nonprompt_jets.append(not_both_tight_leptons_jets)
        SR_nonprompt_MET.append(not_both_tight_leptons_MET)
        SR_nonprompt_weight.append(nonp_weight)

        SR_os_leptons.append(os_tight_leptons)
        SR_os_jets.append(os_tight_leptons_jets)
        SR_os_MET.append(os_tight_leptons_MET)
        SR_os_weight.append(cf_weight)
        
    if isdata==True:
        mc_weight = 1
    else:
        mc_weight = Lumi*xs/nevents
    ##########################################################################
    
    n_out = 0
    n_out_nonp = 0
    n_out_os = 0
    
    target_list = ['pt','eta','phi','mass','tightcharge','charge','is_real','isloose','istight','istightcharge','iselectron','ismuon']
    for i in range(len(SR_2e_sel)):
        ##########################################################################
        temp_SR_2e_sel = SR_2e_sel[i]
        temp_SR_2mu_sel = SR_2mu_sel[i]
        temp_SR_1e1mu_sel = SR_1e1mu_sel[i]
    
        temp_SR_leptons = SR_leptons[i]
        temp_SR_jets = SR_jets[i]
        temp_SR_MET = SR_MET[i]
        temp_SR_weight = mc_weight*SR_weight[i]
        ##########################################################################
        if len(temp_SR_weight)>0:
            eve_dict = {}

            eve_dict['Channel_2e'] = temp_SR_2e_sel*1
            eve_dict['Channel_2mu'] = temp_SR_2mu_sel*1
            eve_dict['Channel_1e1mu'] = temp_SR_1e1mu_sel*1

            eve_dict['Event_Weight'] = temp_SR_weight*1

            for ibr in temp_SR_leptons.fields:
                if ibr in target_list:
                    eve_dict[f'Lepton_{ibr}'] = temp_SR_leptons[ibr]
            for ibr in temp_SR_jets.fields:
                if ibr in target_list:
                    eve_dict[f'Jet_{ibr}'] = temp_SR_jets[ibr]
            for ibr in temp_SR_MET.fields:
                if ibr in target_list:
                    eve_dict[f'MET_{ibr}'] = temp_SR_MET[ibr]
            eve_ak = ak.Array(eve_dict)
            ak.to_parquet(eve_ak,f"{args.output_dir}/{process}/pass_SR_%d.parquet"%n_out)
            n_out += 1
        ##########################################################################
        temp_SR_nonprompt_2e_sel = SR_nonprompt_2e_sel[i]
        temp_SR_nonprompt_2mu_sel = SR_nonprompt_2mu_sel[i]
        temp_SR_nonprompt_1e1mu_sel = SR_nonprompt_1e1mu_sel[i]

        temp_SR_nonprompt_leptons = SR_nonprompt_leptons[i]
        temp_SR_nonprompt_jets = SR_nonprompt_jets[i]
        temp_SR_nonprompt_MET = SR_nonprompt_MET[i]
        temp_SR_nonprompt_weight = mc_weight*SR_nonprompt_weight[i]
        ##########################################################################
        if len(temp_SR_nonprompt_weight)>0:
            eve_nonp_dict = {}

            eve_nonp_dict['Channel_2e'] = temp_SR_nonprompt_2e_sel*1
            eve_nonp_dict['Channel_2mu'] = temp_SR_nonprompt_2mu_sel*1
            eve_nonp_dict['Channel_1e1mu'] = temp_SR_nonprompt_1e1mu_sel*1

            eve_nonp_dict['Event_Weight'] = temp_SR_nonprompt_weight*1

            for ibr in temp_SR_nonprompt_leptons.fields:
                if ibr in target_list:
                    eve_nonp_dict[f'Lepton_{ibr}'] = temp_SR_nonprompt_leptons[ibr]
            for ibr in temp_SR_nonprompt_jets.fields:
                if ibr in target_list:
                    eve_nonp_dict[f'Jet_{ibr}'] = temp_SR_nonprompt_jets[ibr]
            for ibr in temp_SR_nonprompt_MET.fields:
                if ibr in target_list:
                    eve_nonp_dict[f'MET_{ibr}'] = temp_SR_nonprompt_MET[ibr]
            eve_nonp_ak = ak.Array(eve_nonp_dict)
            ak.to_parquet(eve_nonp_ak,f"{args.output_dir}/{process}/pass_SR_nonp_%d.parquet"%n_out_nonp)
            n_out_nonp += 1
        ##########################################################################
        temp_SR_os_2e_sel = SR_os_2e_sel[i]
        temp_SR_os_2mu_sel = SR_os_2mu_sel[i]
        temp_SR_os_1e1mu_sel = SR_os_1e1mu_sel[i]

        temp_SR_os_leptons = SR_os_leptons[i]
        temp_SR_os_jets = SR_os_jets[i]
        temp_SR_os_MET = SR_os_MET[i]
        temp_SR_os_weight = mc_weight*SR_os_weight[i]
        ##########################################################################
        if len(temp_SR_os_weight)>0:
            eve_os_dict = {}

            eve_os_dict['Channel_2e'] = temp_SR_os_2e_sel*1
            eve_os_dict['Channel_2mu'] = temp_SR_os_2mu_sel*1
            eve_os_dict['Channel_1e1mu'] = temp_SR_os_1e1mu_sel*1

            eve_os_dict['Event_Weight'] = temp_SR_os_weight*1
    
            for ibr in temp_SR_os_leptons.fields:
                if ibr in target_list:
                    eve_os_dict[f'Lepton_{ibr}'] = temp_SR_os_leptons[ibr]
            for ibr in temp_SR_os_jets.fields:
                if ibr in target_list:
                    eve_os_dict[f'Jet_{ibr}'] = temp_SR_os_jets[ibr]
            for ibr in temp_SR_os_MET.fields:
                if ibr in target_list:
                    eve_os_dict[f'MET_{ibr}'] = temp_SR_os_MET[ibr]
            eve_os_ak = ak.Array(eve_os_dict)
            ak.to_parquet(eve_os_ak,f"{args.output_dir}/{process}/pass_SR_os_%d.parquet"%n_out_os)
            n_out_os += 1
        ##########################################################################
