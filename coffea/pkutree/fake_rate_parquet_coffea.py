from cmath import log
import uproot as up
import awkward as ak
import coffea
from coffea.nanoevents import NanoEventsFactory, NanoAODSchema, BaseSchema, TreeMakerSchema
from coffea import processor
from coffea.nanoevents.methods import candidate
from coffea import lookup_tools
from coffea.lookup_tools import extractor
from coffea.jetmet_tools import FactorizedJetCorrector, JetCorrectionUncertainty
from coffea.jetmet_tools import JECStack, CorrectedJetsFactory, CorrectedMETFactory
from coffea.btag_tools.btagscalefactor import BTagScaleFactor
ak.behavior.update(candidate.behavior)
from template.temp_class import ntuplize
import numpy as np
import argparse
import os
from utils import common_helper as com
from utils import analyze_helper as ana
from coffea import hist as chist

import argparse

parser = argparse.ArgumentParser(description='manual to this script')
parser.add_argument('-y', '--year', help='which year to run: 2016, 2017, 2018', default='2018')
parser.add_argument('-t', '--type', help='which type: data, mc', choices=('data', 'mc'), default='data')
parser.add_argument('-l', '--lepton', help='which type: muon, electron', choices=('muon', 'electron'), default='electron')
parser.add_argument('-n', '--number', help='id of the rootfile, used for the name of output file')
parser.add_argument('-f', '--file', help='dir of the file')
parser.add_argument('-o', '--output_dir', help='output abs directory')
args = parser.parse_args()

print(args.number)
print(args.year)
print(args.type)
print(args.file)

filename = args.file

if args.type=='data':
    isdata=True
elif args.type=='mc':
    isdata=False
else:
    pass

events = NanoEventsFactory.from_root(filename, schemaclass=NanoAODSchema).events()
if isdata==True:
    events['nevents'] = len(events)
else:
    events['nevents'] = np.sum(events.Generator.weight)
print('ntotal: %d'%len(events.run))

year = args.year
if isdata==True:
    lumi_mask = ana.get_lumi_mask(events, year)
    events = events[lumi_mask]
muons = events.Muon
electrons = events.Electron
taus = events.Tau
jets = events.Jet
MET = events.MET
puppimet = events.PuppiMET

events['nmuons'] = np.sum(ak.ones_like(muons.pt),axis=1)
events['nelectrons'] = np.sum(ak.ones_like(electrons.pt),axis=1)
events['njets'] = np.sum(ak.ones_like(jets.pt),axis=1)
events['nleps'] = events.nmuons+events.nelectrons

muons['pt_orig'] = muons.pt
muons['pt'],muons['pt_roccor_up'],muons['pt_roccor_down'] = ana.apply_rochester_correction(muons,data=isdata,year=year)
# electrons['corrected_pt'] = electrons.pt

#muon definition
loose_muon_ip = (abs(muons.dz)<0.1) & (((muons.pt<20) & (abs(muons.dxy)<0.01)) | ((muons.pt>20) & (abs(muons.dxy)<0.02)))
veto_muon_sel = (muons.pt>10) & (abs(muons.eta)<2.4)
loose_muon_sel = loose_muon_ip & (abs(muons.eta)<2.4) & muons.tightId & (muons.pfRelIso04_all<0.4)
tight_muon_sel = loose_muon_sel & (muons.pfRelIso04_all<0.15)

if isdata==True:
    pass
else:
    muons['is_real'] = (~np.isnan(ak.fill_none(muons.matched_gen.pt, np.nan)))*1

muons['isveto'] = veto_muon_sel
muons['isloose'] = loose_muon_sel
muons['istight'] = tight_muon_sel
muons['istightcharge'] = (muons.tightCharge>1)
muons['iselectron'] = ak.zeros_like(muons.pt)
muons['ismuon'] = ak.ones_like(muons.pt)
events['nveto_muons'] = np.sum(veto_muon_sel,axis=1)
events['nloose_muons'] = np.sum(loose_muon_sel,axis=1)
events['ntight_muons'] = np.sum(tight_muon_sel,axis=1)

veto_muons = muons[muons.isveto]
good_muons = muons[muons.isloose]

#election definition: the same as latino
loose_elec_barrel = (abs(electrons.eta + electrons.deltaEtaSC) <= 1.479) & (abs(electrons.dz) < 0.1) & (abs(electrons.dxy) < 0.05)
loose_elec_endcap = (abs(electrons.eta + electrons.deltaEtaSC) > 1.479) & (abs(electrons.dz) < 0.2) & (abs(electrons.dxy) < 0.1) & (electrons.sieie < 0.03) & (electrons.eInvMinusPInv < 0.014)

loose_elec_sel_pdgmva = (loose_elec_barrel | loose_elec_endcap) & (abs(electrons.eta+electrons.deltaEtaSC) < 2.5) & (electrons.cutBased_Fall17_V1 >= 3) & (electrons.convVeto == 1)
elec_sel_drmu = ana.is_clean(electrons,good_muons,0.4)
loose_elec_sel = loose_elec_sel_pdgmva & elec_sel_drmu

tight_elec_barrel = loose_elec_barrel
tight_elec_endcap = (abs(electrons.eta + electrons.deltaEtaSC) > 1.479) & (abs(electrons.dz) < 0.2) & (abs(electrons.dxy) < 0.1)
tight_elec_sel = (tight_elec_barrel | tight_elec_endcap) & (abs(electrons.eta+electrons.deltaEtaSC) < 2.5) & electrons.mvaFall17V1Iso_WP90 & (electrons.convVeto == 1) & (electrons.pfRelIso03_all < 0.06) & elec_sel_drmu

veto_elec_sel = (electrons.cutBased_Fall17_V1 >= 1)

electrons['isveto'] = veto_elec_sel
electrons['isloose'] = loose_elec_sel
electrons['istight'] = tight_elec_sel
electrons['istightcharge'] = (electrons.tightCharge>1)
electrons['iselectron'] = ak.ones_like(electrons.pt)
electrons['ismuon'] = ak.zeros_like(electrons.pt)
events['nveto_electrons'] = np.sum(veto_elec_sel,axis=1)
events['nloose_electrons'] = np.sum(loose_elec_sel,axis=1)
events['ntight_electrons'] = np.sum(tight_elec_sel,axis=1)

veto_electrons = electrons[electrons.isveto]
good_electrons = electrons[electrons.isloose]

jets_drclean_elec = ana.is_clean(jets,electrons[electrons.isloose],0.4)
jets_drclean_mu = ana.is_clean(jets,muons[muons.isloose],0.4)
jets_drclean = jets_drclean_elec & jets_drclean_mu
good_jets_sel = (jets_drclean) & (jets.pt > 30) & (abs(jets.eta)<4.7) & (jets.jetId>>1 & 1)
good_jets_sel = good_jets_sel==1
jets['isgood'] = good_jets_sel
good_jets = jets[good_jets_sel]
good_jets['pt_orig'] = good_jets.pt
good_jets['mass_orig'] = good_jets.mass

#####   JEC   #####
if isdata==True:
    pass
else:
    good_jets['is_real'] = (~np.isnan(ak.fill_none(good_jets.matched_gen.pt, np.nan)))*1
    good_jets["pt_raw"] = (1 - good_jets.rawFactor)*good_jets.pt
    good_jets["mass_raw"] = (1 - good_jets.rawFactor)*good_jets.mass
    good_jets["pt_gen"] = ak.values_astype(ak.fill_none(good_jets.matched_gen.pt, 0), np.float32)
    good_jets["rho"] = ak.broadcast_arrays(events.fixedGridRhoFastjetAll, good_jets.pt)[0]
    corrected_jets = ana.apply_jet_corrections(year).build(good_jets, lazy_cache=events.caches[0])
    jesr_unc = [i for i in corrected_jets.fields if i.startswith("JES") or i.startswith("JER")]
    good_jets["pt"] = corrected_jets.pt
    good_jets["mass"] = corrected_jets.mass
    for ibr in jesr_unc:
        good_jets[f"pt_{ibr}_up"] = corrected_jets[ibr].up.pt
        good_jets[f"pt_{ibr}_down"] = corrected_jets[ibr].down.pt
        good_jets[f"mass_{ibr}_up"] = corrected_jets[ibr].up.mass
        good_jets[f"mass_{ibr}_down"] = corrected_jets[ibr].down.mass
    # ordered by new pt: high -> low
    index = ak.argsort(good_jets.pt, ascending=False)
    good_jets = good_jets[index]

#####   btag   #####
if isdata==True:
    pass
else:
    flav = good_jets.hadronFlavour
    abseta = np.abs(good_jets.eta)
    pt = good_jets.pt
    good_jets['btagSF'], good_jets['btagSF_up'], good_jets['btagSF_down']  = ana.get_btagsf(flav, abseta, pt, year)
events['ngood_jets'] = np.sum(good_jets_sel,axis=1)

#####   MET   ####
MET['pt_orig'] = MET.pt
MET['phi_orig'] = MET.phi
MET['pt_roccor'], MET['phi_roccor'] = ana.corrected_polar_met(MET.pt,MET.phi,good_muons.pt,good_muons.phi,good_muons.pt_orig)
# consider the jer corr, please note: for jets, the pt_raw is the pt_orig, think about it
if isdata==True:
    pass
else:
    # the jer is applied after considering roccorr on Muon
    MET['pt'], MET['phi'] = ana.corrected_polar_met(MET['pt_roccor'],MET['phi_roccor'],good_jets["pt"],good_jets["phi"],good_jets["pt_orig"])
    # uncertainties
    MET['pt_roccor_up'], MET['phi_roccor_up'] = ana.corrected_polar_met(MET.pt,MET.phi,good_muons.pt_roccor_up,good_muons.phi,good_muons.pt)
    MET['pt_roccor_down'], MET['phi_roccor_down'] = ana.corrected_polar_met(MET.pt,MET.phi,good_muons.pt_roccor_down,good_muons.phi,good_muons.pt)
    MET['pt_UnclusteredEnergy_up'], MET['phi_UnclusteredEnergy_up'] = ana.corrected_polar_met(
        MET['pt'],
        MET['phi'],
        good_jets["pt"],
        good_jets["phi"],
        good_jets["pt"],
        (
            True,
            MET.MetUnclustEnUpDeltaX,
            MET.MetUnclustEnUpDeltaY,
        ),
    )
    MET['pt_UnclusteredEnergy_down'], MET['phi_UnclusteredEnergy_down'] = ana.corrected_polar_met(
        MET['pt'],
        MET['phi'],
        good_jets["pt"],
        good_jets["phi"],
        good_jets["pt"],
        (
            False,
            MET.MetUnclustEnUpDeltaX,
            MET.MetUnclustEnUpDeltaY,
        ),
    )
    for ibr in jesr_unc:
        MET[f"pt_{ibr}_up"], MET[f"phi_{ibr}_up"] = ana.corrected_polar_met(MET['pt'],MET['phi'],good_jets[f"pt_{ibr}_up"],good_jets["phi"],good_jets["pt"])
        MET[f"pt_{ibr}_down"], MET[f"phi_{ibr}_down"] = ana.corrected_polar_met(MET['pt'],MET['phi'],good_jets[f"pt_{ibr}_down"],good_jets["phi"],good_jets["pt"])
if args.lepton=='muon':   
    nleps_sel = (events.nloose_muons==1) & (events.nloose_electrons==0)
    nveto_leps_sel = (events.nveto_muons==1) & (events.nveto_electrons==0)
elif args.lepton=='electron':
    nleps_sel = (events.nloose_muons==0) & (events.nloose_electrons==1)
    nveto_leps_sel = (events.nveto_muons==0) & (events.nveto_electrons==1)
njets_sel = events.ngood_jets==1
total_sel = nleps_sel & njets_sel & nveto_leps_sel & ak.fill_none(events.run!=None, False)

events = events[total_sel]
if args.lepton=='muon':  
    sel_lepton = good_muons[total_sel]
elif args.lepton=='electron':
    sel_lepton = good_electrons[total_sel]
sel_good_jets = good_jets[total_sel]
MET = MET[total_sel]
puppimet = puppimet[total_sel]
npassed = len(events.run)

print('npassed: %d'%npassed)

lepton_bool_list = ['is_real','isloose','istight','istightcharge','iselectron','ismuon']
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


if npassed > 0:
    eve_dict = {}
    for ibr in sel_lepton.fields:
        if ibr in lepton_bool_list:
            eve_dict[f'Lepton_{ibr}'] = sel_lepton[ibr]*1
        else:
            eve_dict[f'Lepton_{ibr}'] = sel_lepton[ibr]
    for ibr in sel_good_jets.fields:
        if not ibr in ['muonIdxG','electronIdxG']:
            eve_dict[f'Jet_{ibr}'] = sel_good_jets[ibr]
    eve_dict['MET_pt'] = MET.pt
    eve_dict['MET_phi'] = MET.phi
    eve_dict['PuppiMET_pt'] = puppimet.pt
    eve_dict['PuppiMET_phi'] = puppimet.phi
    if args.type=='mc':
        eve_dict['Generator_weight'] = events.Generator.weight
    eve_dict['lepton_istight'] = sel_lepton.istight*1
    
    for ihlt in HLT_list:
        try:
            eve_dict[f"HLT_{ihlt}"] = events.HLT[ihlt]*1
        except:
            pass
        
    eve_ak = ak.Array(eve_dict)
    ak.to_parquet(eve_ak,f'{args.output_dir}/events.parquet')