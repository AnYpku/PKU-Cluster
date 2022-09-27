import uproot
import numpy as np
import awkward as ak
import math as m
import matplotlib.pyplot as plt
import matplotlib as mpl
import mplhep as hep
import os
import numba as nb
import boost_histogram as bh
import yaml
import json
from coffea import hist as chist
from coffea.nanoevents.methods import vector

pi = 3.14159265

def Delta_phi(phi1,phi2):
    a = abs(phi1-phi2)
    return np.array(1*(a<=pi)*a+1*(a>pi)*(2*pi-a))

def Delta_eta(eta1,eta2):
    return np.array(abs(eta1-eta2))

def Delta_r(eta1,phi1,eta2,phi2):
    de = Delta_eta(eta1,eta2)
    dp = Delta_phi(phi1,phi2)
    return np.sqrt(de**2+dp**2)

@nb.jit(nopython=True)
def delta_phi(phi1,phi2):
    a = abs(phi1-phi2)
    return np.array(1*(a<=pi)*a+1*(a>pi)*(2*pi-a))

@nb.jit(nopython=True)
def delta_eta(eta1,eta2):
    return np.array(abs(eta1-eta2))

@nb.jit(nopython=True)
def delta_r(eta1,phi1,eta2,phi2):
    de = delta_eta(eta1,eta2)
    dp = delta_phi(phi1,phi2)
    return np.sqrt(de**2+dp**2)

@nb.jit(nopython=True)
def is_clean_with_collection(pat1, pat2_col, cone_size):
    if len(pat2_col)==0:
        return True
    for pat in pat2_col:
        if not delta_r(pat1.eta, pat1.phi, pat.eta, pat.phi) > cone_size:
            return False
    return True

@nb.jit(nopython=True)
def get_jets_drclean(jets,leptons,cone_size):
    jets_drclean = []
    for i,jets_per_event in enumerate(jets):
        jets_drclean_temp = []
        for jet in jets_per_event:
            jets_drclean_temp.append(is_clean_with_collection(jet, leptons[i], cone_size))
        jets_drclean.append(jets_drclean_temp[:])
    return jets_drclean

@nb.jit(nopython=True)
def gj_filter(masks,run_array,lumi_array):
    mask_out = np.zeros_like(run_array)
    assert len(run_array)==len(lumi_array)
    for iev in nb.prange(len(run_array)):
        run = np.uint32(run_array[iev])
        lumi = np.uint32(lumi_array[iev])
        if run in masks:
            lumimask = masks[run]
            ind = np.searchsorted(lumimask, lumi)
#             print(iev, lumimask, lumi, ind, np.mod(ind, 2))
            if np.mod(ind, 2) == 1:
                mask_out[iev] = 1
    return mask_out

ak.behavior.update(vector.behavior)
Mz = 91.2
M_muon = 0
M_electron = 0

gj_file_2016 = open("/data/pubfs/tyyang99/jupyter_files/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.json",'r',encoding='utf8')
gj_file_2017 = open("/data/pubfs/tyyang99/jupyter_files/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.json",'r',encoding='utf8')
gj_file_2018 = open("/data/pubfs/tyyang99/jupyter_files/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.json",'r',encoding='utf8')

gj_dict_2016 = json.load(gj_file_2016)
gj_dict_2017 = json.load(gj_file_2017)
gj_dict_2018 = json.load(gj_file_2018)

from numba.core import types
from numba.typed import Dict

masks_2016 = Dict.empty(key_type=types.uint32, value_type=types.uint32[:])
for run, lumilist in gj_dict_2016.items():
    mask = np.array(lumilist, dtype=np.uint32).flatten()
    mask[::2] -= 1
    masks_2016[np.uint32(run)] = mask
    
masks_2017 = Dict.empty(key_type=types.uint32, value_type=types.uint32[:])
for run, lumilist in gj_dict_2017.items():
    mask = np.array(lumilist, dtype=np.uint32).flatten()
    mask[::2] -= 1
    masks_2017[np.uint32(run)] = mask
    
masks_2018 = Dict.empty(key_type=types.uint32, value_type=types.uint32[:])
for run, lumilist in gj_dict_2018.items():
    mask = np.array(lumilist, dtype=np.uint32).flatten()
    mask[::2] -= 1
    masks_2018[np.uint32(run)] = mask

import argparse

parser = argparse.ArgumentParser(description='manual to this script')
parser.add_argument('-y', '--year', help='which year to run: 2016, 2017, 2018', default='2018')
parser.add_argument('-t', '--type', help='which type: data, mc', choices=('data', 'mc'), default='data')
parser.add_argument('-l', '--lepton', help='which type: muon, electron', choices=('muon', 'electron'), default='electron')
parser.add_argument('-n', '--number', help='id of the rootfile, used for the name of output file')
parser.add_argument('-f', '--file', help='dir of the file')
parser.add_argument('-o', '--output_dir', help='output abs directory')
args = parser.parse_args()

nanoAOD_rootfiles = args.file+':Events'
events = uproot.open(nanoAOD_rootfiles)

ptbins=np.array([10,20,25,30,35,45])
etabins=np.array([0,1.0,1.5,2.0,2.5])
highest_pt_bin_center=(ptbins[len(ptbins)-1]+ptbins[len(ptbins)-2])/2

electrons = ak.zip({
    'pt':     events['Electron_pt'].array(),
    'eta':    events['Electron_eta'].array(),
    'phi':    events['Electron_phi'].array(),
    'mass':   events['Electron_mass'].array(), 
    'charge': events['Electron_charge'].array(), 
    'pdgid':     events['Electron_pdgId'].array(),
    'tightcharge': events['Electron_tightCharge'].array(),
    'deltaEtaSC':events['Electron_deltaEtaSC'].array(),
    'dz':events['Electron_dz'].array(),
    'dxy':events['Electron_dxy'].array(),
    'cutBased':events['Electron_cutBased_Fall17_V1'].array(),
    'convVeto':events['Electron_convVeto'].array(),
    'eInvMinusPInv':events['Electron_eInvMinusPInv'].array(),
    'dr03TkSumPt':events['Electron_dr03TkSumPt'].array(),
    'dr03EcalRecHitSumEt':events['Electron_dr03EcalRecHitSumEt'].array(),
    'dr03HcalDepth1TowerSumEt':events['Electron_dr03HcalDepth1TowerSumEt'].array(),
    'sieie':events['Electron_sieie'].array(),
    'mvaFall17V1Iso_WPL':events['Electron_mvaFall17V1Iso_WPL'].array(),
    'mvaFall17V1Iso_WP90':events['Electron_mvaFall17V1Iso_WP90'].array(),
    'mvaFall17V1Iso_WP80':events['Electron_mvaFall17V1Iso_WP80'].array(),
    'pfRelIso03_all':events['Electron_pfRelIso03_all'].array()
#                 'mvaFall17V2Iso_WP70':events['Electron_mvaFall17V2Iso_WP70'].array(),
 }, with_name="PtEtaPhiMLorentzVector")
muons = ak.zip({
    'pt':     events['Muon_pt'].array(),
    'eta':    events['Muon_eta'].array(),
    'phi':    events['Muon_phi'].array(),
    'mass':   events['Muon_mass'].array(), 
    'charge': events['Muon_charge'].array(), 
    'pdgid':     events['Muon_pdgId'].array(),
    'looseId':events['Muon_looseId'].array(),
    'tightId':events['Muon_tightId'].array(),
    'tightcharge': events['Muon_tightCharge'].array(),
    'pfRelIso04_all':events['Muon_pfRelIso04_all'].array(),
    'dz':events['Muon_dz'].array(),
    'dxy':events['Muon_dxy'].array()
 }, with_name="PtEtaPhiMLorentzVector")
jets = ak.zip({
    'pt':     events['Jet_pt'].array(),
    'eta':    events['Jet_eta'].array(),
    'phi':    events['Jet_phi'].array(),
    'mass':   events['Jet_mass'].array(), 
    'btag':   events['Jet_btagDeepFlavB'].array(),
    'jetId':     events['Jet_jetId'].array()
 }, with_name="PtEtaPhiMLorentzVector")

HLT_list = ['Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
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
        'Photon200',
        'Mu8_TrkIsoVVL',
        'Mu17_TrkIsoVVL',
        'Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30',
        'Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30']


run_array = ak.to_numpy(events['run'].array())
lumi_array = ak.to_numpy(events['luminosityBlock'].array())

MET_pt = events['MET_pt'].array()
MET_phi = events['MET_phi'].array()
PuppiMET_pt = events['PuppiMET_pt'].array()
PuppiMET_phi = events['PuppiMET_phi'].array()

loose_muon_ip = (abs(muons.dz)<0.1) & (((muons.pt<20) & (abs(muons.dxy)<0.01)) | ((muons.pt>20) & (abs(muons.dxy)<0.02)))
veto_muon_sel = (muons.pt>10) & (abs(muons.eta)<2.4)
loose_muon_sel = loose_muon_ip & (abs(muons.eta)<2.4) & muons.tightId & (muons.pfRelIso04_all<0.4)
tight_muon_sel = loose_muon_sel & (muons.pfRelIso04_all<0.15)

veto_muons = muons[veto_muon_sel]
loose_muons = muons[loose_muon_sel]

nveto_muons = np.sum(veto_muon_sel,axis=1)
nloose_muons = np.sum(loose_muon_sel,axis=1)

veto_elec_sel = (electrons.cutBased >= 1)

loose_elec_barrel = (abs(electrons.eta + electrons.deltaEtaSC) < 1.479) & (abs(electrons.dz) < 0.1) & (abs(electrons.dxy) < 0.05)
loose_elec_endcap = (abs(electrons.eta + electrons.deltaEtaSC) > 1.479) & (abs(electrons.dz) < 0.2) & (abs(electrons.dxy) < 0.1) & (electrons.sieie < 0.03) & (electrons.eInvMinusPInv < 0.014)

loose_elec_sel_pdgmva = (loose_elec_barrel | loose_elec_endcap) & (abs(electrons.eta+electrons.deltaEtaSC) < 2.5) & (electrons.cutBased >= 3) & (electrons.convVeto == 1)
loose_elec_sel = loose_elec_sel_pdgmva

tight_elec_barrel = loose_elec_barrel
tight_elec_endcap = (abs(electrons.eta + electrons.deltaEtaSC) > 1.479) & (abs(electrons.dz) < 0.2) & (abs(electrons.dxy) < 0.1)
tight_elec_sel = (tight_elec_barrel | tight_elec_endcap) & (abs(electrons.eta+electrons.deltaEtaSC) < 2.5) & electrons.mvaFall17V1Iso_WP90 & (electrons.convVeto == 1) & (electrons.pfRelIso03_all < 0.06)

veto_electrons = electrons[veto_elec_sel]
loose_electrons = electrons[loose_elec_sel]
tight_electrons = electrons[tight_elec_sel]

nveto_electrons = np.sum(ak.ones_like(electrons.pt),axis=1)
nloose_electrons = np.sum(loose_elec_sel,axis=1)
ntight_electrons = np.sum(tight_elec_sel,axis=1)

nother_electrons = np.sum(loose_elec_sel==False,axis=1)

jets_drclean_electron = get_jets_drclean(jets,loose_electrons,0.4)
jets_drclean_muon = get_jets_drclean(jets,loose_muons,0.4)
jets_drclean = ak.Array(jets_drclean_electron) & ak.Array(jets_drclean_muon)
good_jets_sel = (jets_drclean) & (jets.pt > 20) & (abs(jets.eta)<4.7) & (jets.jetId>>1 & 1)
good_jets_sel = (good_jets_sel==1)
good_jets = jets[good_jets_sel]

ngood_jets = np.sum(good_jets_sel, axis=1)

if args.type=='data':
    gj_judge = gj_filter(masks_2018,run_array,lumi_array)
    gj_judge = (ak.from_numpy(gj_judge)==1)
else:
    gj_judge = (ak.ones_like(nveto_electrons)==1)
    
if args.lepton=='muon':
    events_filter = (nloose_muons == 1) & (nveto_muons == 1) & (nveto_electrons == 0) & gj_judge & (ngood_jets == 1)
    sel_lepton = loose_muons[events_filter]
    sel_good_jets = good_jets[events_filter]
    lepton_tight_judge = 1*tight_muon_sel[loose_muon_sel][events_filter]
    
    
elif args.lepton=='electron':
    events_filter = (nloose_electrons == 1) & (nveto_electrons == 1) & (nveto_muons == 0) & gj_judge & (ngood_jets == 1)
    sel_lepton = loose_electrons[events_filter]
    sel_good_jets = good_jets[events_filter]
    lepton_tight_judge = 1*tight_elec_sel[loose_elec_sel][events_filter]

n_passed = len(sel_lepton)
print('n_total: %d'%len(nveto_electrons))
print('n_sel: %d'%n_passed)
if n_passed > 0:
    eve_dict = {}
    eve_dict['leptons'] = sel_lepton
    eve_dict['jets'] = sel_good_jets
    eve_dict['MET_pt'] = MET_pt[events_filter]
    eve_dict['MET_phi'] = MET_phi[events_filter]
    eve_dict['PuppiMET_pt'] = PuppiMET_pt[events_filter]
    eve_dict['PuppiMET_phi'] = PuppiMET_phi[events_filter]
    if args.type=='mc':
        eve_dict['Generator_Weight'] = events['Generator_Weight'].array()[events_filter]
    eve_dict['lepton_istight'] = lepton_tight_judge
    
    for ihlt in HLT_list:
        try:
            eve_dict[f"HLT_{ihlt}"] = events[f"HLT_{ihlt}"].array()[events_filter]*1
        except:
            pass
        
        
ak.to_parquet(eve_dict,f'{args.output_dir}/events.parquet')
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    