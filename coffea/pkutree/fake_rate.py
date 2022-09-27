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
    'eInvMinusPInv':events['Electron_eInvMinusPInv'].array(),
    'dr03TkSumPt':events['Electron_dr03TkSumPt'].array(),
    'dr03EcalRecHitSumEt':events['Electron_dr03EcalRecHitSumEt'].array(),
    'dr03HcalDepth1TowerSumEt':events['Electron_dr03HcalDepth1TowerSumEt'].array(),
    'sieie':events['Electron_sieie'].array(),
    'mvaFall17V2Iso_WPL':events['Electron_mvaFall17V2Iso_WPL'].array(),
    'mvaFall17V2Iso_WP90':events['Electron_mvaFall17V2Iso_WP90'].array(),
    'mvaFall17V2Iso_WP80':events['Electron_mvaFall17V2Iso_WP80'].array(),
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

HLT_IsoMu27 = events['HLT_IsoMu27'].array()
HLT_Mu8_TrkIsoVVL = events['HLT_Mu8_TrkIsoVVL'].array()
HLT_Mu17_TrkIsoVVL = events['HLT_Mu17_TrkIsoVVL'].array()
HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30 = events['HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30'].array()
HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 = events['HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30'].array()

run_array = ak.to_numpy(events['run'].array())
lumi_array = ak.to_numpy(events['luminosityBlock'].array())

MET_pt = events['MET_pt'].array()
MET_phi = events['MET_phi'].array()
PuppiMET_pt = events['PuppiMET_pt'].array()
PuppiMET_phi = events['PuppiMET_phi'].array()

loose_muon_ip = (abs(muons.dz)<0.1) & (((muons.pt<20) & (abs(muons.dxy)<0.01)) | ((muons.pt>20) & (abs(muons.dxy)<0.02)))
veto_muon_sel = muons.looseId & (muons.pt>10) & (abs(muons.eta)<2.4)
loose_muon_sel = loose_muon_ip & (muons.pt>10) & (abs(muons.eta)<2.4) & muons.tightId & (muons.pfRelIso04_all<0.4)

veto_muons = muons[veto_muon_sel]
loose_muons = muons[loose_muon_sel]

nveto_muons = np.sum(veto_muon_sel,axis=1)
nloose_muons = np.sum(loose_muon_sel,axis=1)

loose_elec_barrel = (abs(electrons.eta + electrons.deltaEtaSC) < 1.479) & (abs(electrons.dz) < 0.1) & (abs(electrons.dxy) < 0.05)
Combined_Isolation_Barrel = (electrons.dr03TkSumPt+(1*((electrons.dr03EcalRecHitSumEt-1)>0)*(electrons.dr03EcalRecHitSumEt-1)+0*((electrons.dr03EcalRecHitSumEt-1)<=0))+electrons.dr03HcalDepth1TowerSumEt)/electrons.pt
loose_elec_endcap = (abs(electrons.eta + electrons.deltaEtaSC) > 1.479) & (abs(electrons.dz) < 0.2) & (abs(electrons.dxy) < 0.1) & (electrons.sieie < 0.03) & (electrons.eInvMinusPInv < 0.014)
Combined_Isolation_Endcap = (electrons.dr03TkSumPt+electrons.dr03EcalRecHitSumEt+electrons.dr03HcalDepth1TowerSumEt)/electrons.pt

Isolation_Barrel_sel = loose_elec_barrel & (Combined_Isolation_Barrel<0.0571)
Isolation_Endcap_sel = loose_elec_endcap & (Combined_Isolation_Endcap<0.05880)
combined_iso_sel = Isolation_Barrel_sel | Isolation_Endcap_sel

loose_elec_sel_pdgmva = (loose_elec_barrel | loose_elec_endcap) & (electrons.pt > 10) & (abs(electrons.eta+electrons.deltaEtaSC) < 2.5) & (electrons.cutBased >= 3)
# loose_elec_sel_drmu = get_jets_drclean(electrons,loose_muons,0.4)
# loose_elec_sel_drmu = ak.Array(loose_elec_sel_drmu)
# loose_elec_sel = loose_elec_sel_pdgmva & loose_elec_sel_drmu
loose_elec_sel = loose_elec_sel_pdgmva
veto_elec_sel = (loose_elec_barrel | loose_elec_endcap) & (electrons.pt > 10) & (abs(electrons.eta+electrons.deltaEtaSC) < 2.5) & electrons.mvaFall17V2Iso_WPL
tight_elec_sel = loose_elec_sel & electrons.mvaFall17V2Iso_WP90 & combined_iso_sel

veto_electrons = electrons[veto_elec_sel]
loose_electrons = electrons[loose_elec_sel]
tight_electrons = electrons[tight_elec_sel]

nveto_electrons = np.sum(veto_elec_sel,axis=1)
nloose_electrons = np.sum(loose_elec_sel,axis=1)
ntight_electrons = np.sum(tight_elec_sel,axis=1)

nother_electrons = np.sum(loose_elec_sel==False,axis=1)

jets_drclean_electron = get_jets_drclean(jets,loose_electrons,0.4)
jets_drclean_muon = get_jets_drclean(jets,loose_muons,0.4)
jets_drclean = ak.Array(jets_drclean_electron) & ak.Array(jets_drclean_muon)
good_jets_sel = (jets_drclean) & (jets.pt > 30) & (abs(jets.eta)<4.7) & (jets.jetId>>1 & 1)
good_jets_sel = (good_jets_sel==1)
good_jets = jets[good_jets_sel]

ngood_jets = np.sum(good_jets_sel, axis=1)

if args.type=='data':
    gj_judge = gj_filter(masks_2018,run_array,lumi_array)
    gj_judge = (ak.from_numpy(gj_judge)==1)
else:
    gj_judge = (ak.ones_like(nveto_electrons)==1)
    
if args.lepton=='muon':
    muon_filter = (nloose_muons == 1) & (nveto_muons == 1) & (nveto_electrons == 0) & gj_judge & (ngood_jets == 1)
    fm_muons = loose_muons[muon_filter]
    fm_good_jets = good_jets[muon_filter]
    selected_jet_pt = fm_good_jets.pt
    selected_jet_phi = fm_good_jets.phi
    selected_jet_eta = fm_good_jets.eta

    loose_muon_pt = fm_muons.pt

    dr_lepton_lj = Delta_r(selected_jet_eta, selected_jet_phi, fm_muons.eta, fm_muons.phi)
    dr_pt_filter = (dr_lepton_lj > 1)

    abs_lepton_eta = abs(fm_muons.eta)

    puppimt = np.sqrt(2*fm_muons.pt*PuppiMET_pt[muon_filter]*(1 - np.cos(PuppiMET_phi[muon_filter] - fm_muons.phi)))
    mt = np.sqrt(2*fm_muons.pt*MET_pt[muon_filter]*(1 - np.cos(MET_phi[muon_filter] - fm_muons.phi)))

    puppimt_filter = (PuppiMET_pt[muon_filter] < 30) & (puppimt < 20)
    mt_filter = (MET_pt[muon_filter] < 30) & (mt < 20)
    HLT_filter = ((loose_muon_pt < 20) & HLT_Mu8_TrkIsoVVL[muon_filter]) | ((loose_muon_pt > 20) & HLT_Mu17_TrkIsoVVL[muon_filter])

    # all_muon_filter = dr_pt_filter & puppimt_filter & HLT_filter
    all_muon_filter = dr_pt_filter & mt_filter & HLT_filter

    muons_aftersel = fm_muons[all_muon_filter[:,0]]
    pass_filter = muons_aftersel.pfRelIso04_all < 0.15
    muons_aftersel_pass = muons_aftersel[pass_filter[:,0]]

    cropped_muons_pt = 1*(muons_aftersel.pt<highest_pt_bin_center)*muons_aftersel.pt + (1-1*(muons_aftersel.pt<highest_pt_bin_center))*ak.ones_like(muons_aftersel.pt)*highest_pt_bin_center
    
    n_loose = len(muons_aftersel)
    n_tight = len(muons_aftersel_pass)
    print("number of fakable muons: %d"%(n_loose))
    print("number of tight muons: %d"%(n_tight))
    
    x_array = abs(muons_aftersel.eta[:,0])
    y_array = cropped_muons_pt[:,0]
    if args.type=='mc':
        gen_weight_array = events['Generator_weight'].array()[muon_filter][all_muon_filter[:,0]]

    x_pass_array = abs(muons_aftersel_pass.eta[:,0])
    y_pass_array = cropped_muons_pt[:,0][pass_filter[:,0]]
    if args.type=='mc':
        gen_weight_pass_array = events['Generator_weight'].array()[muon_filter][all_muon_filter[:,0]][pass_filter[:,0]]
elif args.lepton=='electron':
    electron_filter = (nloose_electrons == 1) & (nveto_electrons == 1) & (nveto_muons == 0) & gj_judge & (ngood_jets == 1)
    fe_electrons = loose_electrons[electron_filter]
    fe_jets = good_jets[electron_filter]
    selected_jet_pt = fe_jets.pt
    selected_jet_phi = fe_jets.phi
    selected_jet_eta = fe_jets.eta

    loose_electron_pt = fe_electrons.pt

    dr_lepton_lj = Delta_r(selected_jet_eta, selected_jet_phi, fe_electrons.eta, fe_electrons.phi)
    dr_pt_filter = (dr_lepton_lj > 1) & (selected_jet_pt > 35)

    abs_lepton_eta = abs(fe_electrons.eta)

    puppimt = np.sqrt(2*fe_electrons.pt*PuppiMET_pt[electron_filter]*(1 - np.cos(PuppiMET_phi[electron_filter] - fe_electrons.phi)))
    mt = np.sqrt(2*fe_electrons.pt*MET_pt[electron_filter]*(1 - np.cos(MET_phi[electron_filter] - fe_electrons.phi)))

    puppimt_filter = (PuppiMET_pt[electron_filter] < 30) & (puppimt < 20)
    mt_filter = (MET_pt[electron_filter] < 30) & (mt < 20)
    HLT_filter = ((loose_electron_pt < 25) & HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30[electron_filter]) | ((loose_electron_pt > 25) & HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30[electron_filter])

    # all_electron_filter = dr_pt_filter & puppimt_filter & HLT_filter
    all_electron_filter = dr_pt_filter & mt_filter & HLT_filter

    electrons_aftersel = fe_electrons[all_electron_filter[:,0]]
    pass_filter = (electrons_aftersel.mvaFall17V2Iso_WP90) & combined_iso_sel[loose_elec_sel][electron_filter][all_electron_filter[:,0]]
    electrons_aftersel_pass = electrons_aftersel[pass_filter[:,0]]

    cropped_electrons_pt = 1*(electrons_aftersel.pt<highest_pt_bin_center)*electrons_aftersel.pt + (1-1*(electrons_aftersel.pt<highest_pt_bin_center))*ak.ones_like(electrons_aftersel.pt)*highest_pt_bin_center
    
    n_loose = len(electrons_aftersel)
    n_tight = len(electrons_aftersel_pass)
    print("number of fakable electrons: %d"%(n_loose))
    print("number of tight electrons: %d"%(n_tight))
    
    x_array = abs(electrons_aftersel.eta[:,0])
    y_array = cropped_electrons_pt[:,0]
    if args.type=='mc':
        gen_weight_array = events['Generator_weight'].array()[electron_filter][all_electron_filter[:,0]]

    x_pass_array = abs(electrons_aftersel_pass.eta[:,0])
    y_pass_array = cropped_electrons_pt[:,0][pass_filter[:,0]]
    if args.type=='mc':
        gen_weight_pass_array = events['Generator_weight'].array()[electron_filter][all_electron_filter[:,0]][pass_filter[:,0]]
else:
    print('wrong lepton setting!')



ak.to_parquet(x_array,f'{args.output_dir}/x_array')
ak.to_parquet(y_array,f'{args.output_dir}/y_array')
ak.to_parquet(x_pass_array,f'{args.output_dir}/x_pass_array')
ak.to_parquet(y_pass_array,f'{args.output_dir}/y_pass_array')
if args.type=='mc':
    ak.to_parquet(gen_weight_array,f'{args.output_dir}/gen_weight_array')
    ak.to_parquet(gen_weight_pass_array,f'{args.output_dir}/gen_weight_pass_array')
































