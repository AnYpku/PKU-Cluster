//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 19 02:43:36 2021 by ROOT version 6.12/07
// from TChain Events/
//////////////////////////////////////////////////////////

#ifndef chain_WWg_h
#define chain_WWg_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "roccor/RoccoR.cc"
using namespace std;

// Header file for the classes stored in the TTree if any.

class chain_WWg {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          luminosityBlock;
   ULong64_t       event;
   Float_t         btagWeight_CSVV2;
   Float_t         btagWeight_DeepCSVB;
   UInt_t          nCorrT1METJet;
   Float_t         CorrT1METJet_area[28];   //[nCorrT1METJet]
   Float_t         CorrT1METJet_eta[28];   //[nCorrT1METJet]
   Float_t         CorrT1METJet_muonSubtrFactor[28];   //[nCorrT1METJet]
   Float_t         CorrT1METJet_phi[28];   //[nCorrT1METJet]
   Float_t         CorrT1METJet_rawPt[28];   //[nCorrT1METJet]
   Float_t         DeepMETResolutionTune_phi;
   Float_t         DeepMETResolutionTune_pt;
   Float_t         DeepMETResponseTune_phi;
   Float_t         DeepMETResponseTune_pt;
   UInt_t          nElectron;
   Float_t         Electron_dEscaleDown[10];   //[nElectron]
   Float_t         Electron_dEscaleUp[10];   //[nElectron]
   Float_t         Electron_dEsigmaDown[10];   //[nElectron]
   Float_t         Electron_dEsigmaUp[10];   //[nElectron]
   Float_t         Electron_deltaEtaSC[10];   //[nElectron]
   Float_t         Electron_dr03EcalRecHitSumEt[10];   //[nElectron]
   Float_t         Electron_dr03HcalDepth1TowerSumEt[10];   //[nElectron]
   Float_t         Electron_dr03TkSumPt[10];   //[nElectron]
   Float_t         Electron_dr03TkSumPtHEEP[10];   //[nElectron]
   Float_t         Electron_dxy[10];   //[nElectron]
   Float_t         Electron_dxyErr[10];   //[nElectron]
   Float_t         Electron_dz[10];   //[nElectron]
   Float_t         Electron_dzErr[10];   //[nElectron]
   Float_t         Electron_eCorr[10];   //[nElectron]
   Float_t         Electron_eInvMinusPInv[10];   //[nElectron]
   Float_t         Electron_energyErr[10];   //[nElectron]
   Float_t         Electron_eta[10];   //[nElectron]
   Float_t         Electron_hoe[10];   //[nElectron]
   Float_t         Electron_ip3d[10];   //[nElectron]
   Float_t         Electron_jetPtRelv2[10];   //[nElectron]
   Float_t         Electron_jetRelIso[10];   //[nElectron]
   Float_t         Electron_mass[10];   //[nElectron]
   Float_t         Electron_miniPFRelIso_all[10];   //[nElectron]
   Float_t         Electron_miniPFRelIso_chg[10];   //[nElectron]
   Float_t         Electron_mvaFall17V2Iso[10];   //[nElectron]
   Float_t         Electron_mvaFall17V2noIso[10];   //[nElectron]
   Float_t         Electron_pfRelIso03_all[10];   //[nElectron]
   Float_t         Electron_pfRelIso03_chg[10];   //[nElectron]
   Float_t         Electron_phi[10];   //[nElectron]
   Float_t         Electron_pt[10];   //[nElectron]
   Float_t         Electron_r9[10];   //[nElectron]
   Float_t         Electron_scEtOverPt[10];   //[nElectron]
   Float_t         Electron_sieie[10];   //[nElectron]
   Float_t         Electron_sip3d[10];   //[nElectron]
   Float_t         Electron_mvaTTH[10];   //[nElectron]
   Int_t           Electron_charge[10];   //[nElectron]
   Int_t           Electron_cutBased[10];   //[nElectron]
   Int_t           Electron_jetIdx[10];   //[nElectron]
   Int_t           Electron_pdgId[10];   //[nElectron]
   Int_t           Electron_photonIdx[10];   //[nElectron]
   Int_t           Electron_tightCharge[10];   //[nElectron]
   Int_t           Electron_vidNestedWPBitmap[10];   //[nElectron]
   Int_t           Electron_vidNestedWPBitmapHEEP[10];   //[nElectron]
   Bool_t          Electron_convVeto[10];   //[nElectron]
   Bool_t          Electron_cutBased_HEEP[10];   //[nElectron]
   Bool_t          Electron_isPFcand[10];   //[nElectron]
   UChar_t         Electron_jetNDauCharged[10];   //[nElectron]
   UChar_t         Electron_lostHits[10];   //[nElectron]
   Bool_t          Electron_mvaFall17V2Iso_WP80[10];   //[nElectron]
   Bool_t          Electron_mvaFall17V2Iso_WP90[10];   //[nElectron]
   Bool_t          Electron_mvaFall17V2Iso_WPL[10];   //[nElectron]
   Bool_t          Electron_mvaFall17V2noIso_WP80[10];   //[nElectron]
   Bool_t          Electron_mvaFall17V2noIso_WP90[10];   //[nElectron]
   Bool_t          Electron_mvaFall17V2noIso_WPL[10];   //[nElectron]
   UChar_t         Electron_seedGain[10];   //[nElectron]
   UInt_t          nFatJet;
   Float_t         FatJet_area[7];   //[nFatJet]
   Float_t         FatJet_btagCSVV2[7];   //[nFatJet]
   Float_t         FatJet_btagDDBvLV2[7];   //[nFatJet]
   Float_t         FatJet_btagDDCvBV2[7];   //[nFatJet]
   Float_t         FatJet_btagDDCvLV2[7];   //[nFatJet]
   Float_t         FatJet_btagDeepB[7];   //[nFatJet]
   Float_t         FatJet_btagHbb[7];   //[nFatJet]
   Float_t         FatJet_deepTagMD_H4qvsQCD[7];   //[nFatJet]
   Float_t         FatJet_deepTagMD_HbbvsQCD[7];   //[nFatJet]
   Float_t         FatJet_deepTagMD_TvsQCD[7];   //[nFatJet]
   Float_t         FatJet_deepTagMD_WvsQCD[7];   //[nFatJet]
   Float_t         FatJet_deepTagMD_ZHbbvsQCD[7];   //[nFatJet]
   Float_t         FatJet_deepTagMD_ZHccvsQCD[7];   //[nFatJet]
   Float_t         FatJet_deepTagMD_ZbbvsQCD[7];   //[nFatJet]
   Float_t         FatJet_deepTagMD_ZvsQCD[7];   //[nFatJet]
   Float_t         FatJet_deepTagMD_bbvsLight[7];   //[nFatJet]
   Float_t         FatJet_deepTagMD_ccvsLight[7];   //[nFatJet]
   Float_t         FatJet_deepTag_H[7];   //[nFatJet]
   Float_t         FatJet_deepTag_QCD[7];   //[nFatJet]
   Float_t         FatJet_deepTag_QCDothers[7];   //[nFatJet]
   Float_t         FatJet_deepTag_TvsQCD[7];   //[nFatJet]
   Float_t         FatJet_deepTag_WvsQCD[7];   //[nFatJet]
   Float_t         FatJet_deepTag_ZvsQCD[7];   //[nFatJet]
   Float_t         FatJet_eta[7];   //[nFatJet]
   Float_t         FatJet_mass[7];   //[nFatJet]
   Float_t         FatJet_msoftdrop[7];   //[nFatJet]
   Float_t         FatJet_n2b1[7];   //[nFatJet]
   Float_t         FatJet_n3b1[7];   //[nFatJet]
   Float_t         FatJet_particleNetMD_QCD[7];   //[nFatJet]
   Float_t         FatJet_particleNetMD_Xbb[7];   //[nFatJet]
   Float_t         FatJet_particleNetMD_Xcc[7];   //[nFatJet]
   Float_t         FatJet_particleNetMD_Xqq[7];   //[nFatJet]
   Float_t         FatJet_particleNet_H4qvsQCD[7];   //[nFatJet]
   Float_t         FatJet_particleNet_HbbvsQCD[7];   //[nFatJet]
   Float_t         FatJet_particleNet_HccvsQCD[7];   //[nFatJet]
   Float_t         FatJet_particleNet_QCD[7];   //[nFatJet]
   Float_t         FatJet_particleNet_TvsQCD[7];   //[nFatJet]
   Float_t         FatJet_particleNet_WvsQCD[7];   //[nFatJet]
   Float_t         FatJet_particleNet_ZvsQCD[7];   //[nFatJet]
   Float_t         FatJet_particleNet_mass[7];   //[nFatJet]
   Float_t         FatJet_phi[7];   //[nFatJet]
   Float_t         FatJet_pt[7];   //[nFatJet]
   Float_t         FatJet_rawFactor[7];   //[nFatJet]
   Float_t         FatJet_tau1[7];   //[nFatJet]
   Float_t         FatJet_tau2[7];   //[nFatJet]
   Float_t         FatJet_tau3[7];   //[nFatJet]
   Float_t         FatJet_tau4[7];   //[nFatJet]
   Float_t         FatJet_lsf3[7];   //[nFatJet]
   Int_t           FatJet_jetId[7];   //[nFatJet]
   Int_t           FatJet_subJetIdx1[7];   //[nFatJet]
   Int_t           FatJet_subJetIdx2[7];   //[nFatJet]
   Int_t           FatJet_electronIdx3SJ[7];   //[nFatJet]
   Int_t           FatJet_muonIdx3SJ[7];   //[nFatJet]
   UChar_t         FatJet_nConstituents[7];   //[nFatJet]
   UInt_t          nFsrPhoton;
   Float_t         FsrPhoton_dROverEt2[4];   //[nFsrPhoton]
   Float_t         FsrPhoton_eta[4];   //[nFsrPhoton]
   Float_t         FsrPhoton_phi[4];   //[nFsrPhoton]
   Float_t         FsrPhoton_pt[4];   //[nFsrPhoton]
   Float_t         FsrPhoton_relIso03[4];   //[nFsrPhoton]
   Int_t           FsrPhoton_muonIdx[4];   //[nFsrPhoton]
   UInt_t          nGenJetAK8;
   Float_t         GenJetAK8_eta[10];   //[nGenJetAK8]
   Float_t         GenJetAK8_mass[10];   //[nGenJetAK8]
   Float_t         GenJetAK8_phi[10];   //[nGenJetAK8]
   Float_t         GenJetAK8_pt[10];   //[nGenJetAK8]
   UInt_t          nGenJet;
   Float_t         GenJet_eta[27];   //[nGenJet]
   Float_t         GenJet_mass[27];   //[nGenJet]
   Float_t         GenJet_phi[27];   //[nGenJet]
   Float_t         GenJet_pt[27];   //[nGenJet]
   UInt_t          nGenPart;
   Float_t         GenPart_eta[190];   //[nGenPart]
   Float_t         GenPart_mass[190];   //[nGenPart]
   Float_t         GenPart_phi[190];   //[nGenPart]
   Float_t         GenPart_pt[190];   //[nGenPart]
   Int_t           GenPart_genPartIdxMother[190];   //[nGenPart]
   Int_t           GenPart_pdgId[190];   //[nGenPart]
   Int_t           GenPart_status[190];   //[nGenPart]
   Int_t           GenPart_statusFlags[190];   //[nGenPart]
   Float_t         Generator_binvar;
   Float_t         Generator_scalePDF;
   Float_t         Generator_weight;
   Float_t         Generator_x1;
   Float_t         Generator_x2;
   Float_t         Generator_xpdf1;
   Float_t         Generator_xpdf2;
   Int_t           Generator_id1;
   Int_t           Generator_id2;
   Float_t         GenVtx_x;
   Float_t         GenVtx_y;
   Float_t         GenVtx_z;
   Float_t         genWeight;
   Float_t         LHEWeight_originalXWGTUP;
   UInt_t          nLHEPdfWeight;
   Float_t         LHEPdfWeight[103];   //[nLHEPdfWeight]
   UInt_t          nLHEReweightingWeight;
   Float_t         LHEReweightingWeight[1];   //[nLHEReweightingWeight]
   UInt_t          nLHEScaleWeight;
   Float_t         LHEScaleWeight[9];   //[nLHEScaleWeight]
   UInt_t          nPSWeight;
   Float_t         PSWeight[4];   //[nPSWeight]
   UInt_t          nIsoTrack;
   UInt_t          nJet;
   Float_t         Jet_area[28];   //[nJet]
   Float_t         Jet_btagCSVV2[28];   //[nJet]
   Float_t         Jet_btagDeepB[28];   //[nJet]
   Float_t         Jet_btagDeepCvB[28];   //[nJet]
   Float_t         Jet_btagDeepCvL[28];   //[nJet]
   Float_t         Jet_btagDeepFlavB[28];   //[nJet]
   Float_t         Jet_btagDeepFlavCvB[28];   //[nJet]
   Float_t         Jet_btagDeepFlavCvL[28];   //[nJet]
   Float_t         Jet_btagDeepFlavQG[28];   //[nJet]
   Float_t         Jet_chEmEF[28];   //[nJet]
   Float_t         Jet_chFPV0EF[28];   //[nJet]
   Float_t         Jet_chHEF[28];   //[nJet]
   Float_t         Jet_eta[28];   //[nJet]
   Float_t         Jet_hfsigmaEtaEta[28];   //[nJet]
   Float_t         Jet_hfsigmaPhiPhi[28];   //[nJet]
   Float_t         Jet_mass[28];   //[nJet]
   Float_t         Jet_muEF[28];   //[nJet]
   Float_t         Jet_muonSubtrFactor[28];   //[nJet]
   Float_t         Jet_neEmEF[28];   //[nJet]
   Float_t         Jet_neHEF[28];   //[nJet]
   Float_t         Jet_phi[28];   //[nJet]
   Float_t         Jet_pt[28];   //[nJet]
   Float_t         Jet_puIdDisc[28];   //[nJet]
   Float_t         Jet_qgl[28];   //[nJet]
   Float_t         Jet_rawFactor[28];   //[nJet]
   Float_t         Jet_bRegCorr[28];   //[nJet]
   Float_t         Jet_bRegRes[28];   //[nJet]
   Float_t         Jet_cRegCorr[28];   //[nJet]
   Float_t         Jet_cRegRes[28];   //[nJet]
   Int_t           Jet_electronIdx1[28];   //[nJet]
   Int_t           Jet_electronIdx2[28];   //[nJet]
   Int_t           Jet_hfadjacentEtaStripsSize[28];   //[nJet]
   Int_t           Jet_hfcentralEtaStripSize[28];   //[nJet]
   Int_t           Jet_jetId[28];   //[nJet]
   Int_t           Jet_muonIdx1[28];   //[nJet]
   Int_t           Jet_muonIdx2[28];   //[nJet]
   Int_t           Jet_nElectrons[28];   //[nJet]
   Int_t           Jet_nMuons[28];   //[nJet]
   Int_t           Jet_puId[28];   //[nJet]
   UChar_t         Jet_nConstituents[28];   //[nJet]
   Float_t         L1PreFiringWeight_Dn;
   Float_t         L1PreFiringWeight_ECAL_Dn;
   Float_t         L1PreFiringWeight_ECAL_Nom;
   Float_t         L1PreFiringWeight_ECAL_Up;
   Float_t         L1PreFiringWeight_Muon_Nom;
   Float_t         L1PreFiringWeight_Muon_StatDn;
   Float_t         L1PreFiringWeight_Muon_StatUp;
   Float_t         L1PreFiringWeight_Muon_SystDn;
   Float_t         L1PreFiringWeight_Muon_SystUp;
   Float_t         L1PreFiringWeight_Nom;
   Float_t         L1PreFiringWeight_Up;
   Float_t         GenMET_phi;
   Float_t         GenMET_pt;
   Float_t         MET_MetUnclustEnUpDeltaX;
   Float_t         MET_MetUnclustEnUpDeltaY;
   Float_t         MET_covXX;
   Float_t         MET_covXY;
   Float_t         MET_covYY;
   Float_t         MET_phi;
   Float_t         MET_pt;
   Float_t         MET_significance;
   Float_t         MET_sumEt;
   Float_t         MET_sumPtUnclustered;
   UInt_t          nMuon;
   Float_t         Muon_dxy[16];   //[nMuon]
   Float_t         Muon_dxyErr[16];   //[nMuon]
   Float_t         Muon_dxybs[16];   //[nMuon]
   Float_t         Muon_dz[16];   //[nMuon]
   Float_t         Muon_dzErr[16];   //[nMuon]
   Float_t         Muon_eta[16];   //[nMuon]
   Float_t         Muon_ip3d[16];   //[nMuon]
   Float_t         Muon_jetPtRelv2[16];   //[nMuon]
   Float_t         Muon_jetRelIso[16];   //[nMuon]
   Float_t         Muon_mass[16];   //[nMuon]
   Float_t         Muon_miniPFRelIso_all[16];   //[nMuon]
   Float_t         Muon_miniPFRelIso_chg[16];   //[nMuon]
   Float_t         Muon_pfRelIso03_all[16];   //[nMuon]
   Float_t         Muon_pfRelIso03_chg[16];   //[nMuon]
   Float_t         Muon_pfRelIso04_all[16];   //[nMuon]
   Float_t         Muon_phi[16];   //[nMuon]
   Float_t         Muon_pt[16];   //[nMuon]
   Float_t         Muon_ptErr[16];   //[nMuon]
   Float_t         Muon_segmentComp[16];   //[nMuon]
   Float_t         Muon_sip3d[16];   //[nMuon]
   Float_t         Muon_softMva[16];   //[nMuon]
   Float_t         Muon_tkRelIso[16];   //[nMuon]
   Float_t         Muon_tunepRelPt[16];   //[nMuon]
   Float_t         Muon_mvaLowPt[16];   //[nMuon]
   Float_t         Muon_mvaTTH[16];   //[nMuon]
   Int_t           Muon_charge[16];   //[nMuon]
   Int_t           Muon_jetIdx[16];   //[nMuon]
   Int_t           Muon_nStations[16];   //[nMuon]
   Int_t           Muon_nTrackerLayers[16];   //[nMuon]
   Int_t           Muon_pdgId[16];   //[nMuon]
   Int_t           Muon_tightCharge[16];   //[nMuon]
   Int_t           Muon_fsrPhotonIdx[16];   //[nMuon]
   UChar_t         Muon_highPtId[16];   //[nMuon]
   Bool_t          Muon_highPurity[16];   //[nMuon]
   Bool_t          Muon_inTimeMuon[16];   //[nMuon]
   Bool_t          Muon_isGlobal[16];   //[nMuon]
   Bool_t          Muon_isPFcand[16];   //[nMuon]
   Bool_t          Muon_isStandalone[16];   //[nMuon]
   Bool_t          Muon_isTracker[16];   //[nMuon]
   UChar_t         Muon_jetNDauCharged[16];   //[nMuon]
   Bool_t          Muon_looseId[16];   //[nMuon]
   Bool_t          Muon_mediumId[16];   //[nMuon]
   Bool_t          Muon_mediumPromptId[16];   //[nMuon]
   UChar_t         Muon_miniIsoId[16];   //[nMuon]
   UChar_t         Muon_multiIsoId[16];   //[nMuon]
   UChar_t         Muon_mvaId[16];   //[nMuon]
   UChar_t         Muon_mvaLowPtId[16];   //[nMuon]
   UChar_t         Muon_pfIsoId[16];   //[nMuon]
   UChar_t         Muon_puppiIsoId[16];   //[nMuon]
   Bool_t          Muon_softId[16];   //[nMuon]
   Bool_t          Muon_softMvaId[16];   //[nMuon]
   Bool_t          Muon_tightId[16];   //[nMuon]
   UChar_t         Muon_tkIsoId[16];   //[nMuon]
   Bool_t          Muon_triggerIdLoose[16];   //[nMuon]
   UInt_t          nPhoton;
   Float_t         Photon_dEscaleDown[14];   //[nPhoton]
   Float_t         Photon_dEscaleUp[14];   //[nPhoton]
   Float_t         Photon_dEsigmaDown[14];   //[nPhoton]
   Float_t         Photon_dEsigmaUp[14];   //[nPhoton]
   Float_t         Photon_eCorr[14];   //[nPhoton]
   Float_t         Photon_energyErr[14];   //[nPhoton]
   Float_t         Photon_eta[14];   //[nPhoton]
   Float_t         Photon_hoe[14];   //[nPhoton]
   Float_t         Photon_mass[14];   //[nPhoton]
   Float_t         Photon_mvaID[14];   //[nPhoton]
   Float_t         Photon_mvaID_Fall17V1p1[14];   //[nPhoton]
   Float_t         Photon_pfRelIso03_all[14];   //[nPhoton]
   Float_t         Photon_pfRelIso03_chg[14];   //[nPhoton]
   Float_t         Photon_phi[14];   //[nPhoton]
   Float_t         Photon_pt[14];   //[nPhoton]
   Float_t         Photon_r9[14];   //[nPhoton]
   Float_t         Photon_sieie[14];   //[nPhoton]
   Int_t           Photon_charge[14];   //[nPhoton]
   Int_t           Photon_cutBased[14];   //[nPhoton]
   Int_t           Photon_cutBased_Fall17V1Bitmap[14];   //[nPhoton]
   Int_t           Photon_electronIdx[14];   //[nPhoton]
   Int_t           Photon_jetIdx[14];   //[nPhoton]
   Int_t           Photon_pdgId[14];   //[nPhoton]
   Int_t           Photon_vidNestedWPBitmap[14];   //[nPhoton]
   Bool_t          Photon_electronVeto[14];   //[nPhoton]
   Bool_t          Photon_isScEtaEB[14];   //[nPhoton]
   Bool_t          Photon_isScEtaEE[14];   //[nPhoton]
   Bool_t          Photon_mvaID_WP80[14];   //[nPhoton]
   Bool_t          Photon_mvaID_WP90[14];   //[nPhoton]
   Bool_t          Photon_pixelSeed[14];   //[nPhoton]
   UChar_t         Photon_seedGain[14];   //[nPhoton]
   Float_t         Pileup_nTrueInt;
   Float_t         Pileup_pudensity;
   Float_t         Pileup_gpudensity;
   Int_t           Pileup_nPU;
   Int_t           Pileup_sumEOOT;
   Int_t           Pileup_sumLOOT;
   Float_t         PuppiMET_phi;
   Float_t         PuppiMET_phiJERDown;
   Float_t         PuppiMET_phiJERUp;
   Float_t         PuppiMET_phiJESDown;
   Float_t         PuppiMET_phiJESUp;
   Float_t         PuppiMET_phiUnclusteredDown;
   Float_t         PuppiMET_phiUnclusteredUp;
   Float_t         PuppiMET_pt;
   Float_t         PuppiMET_ptJERDown;
   Float_t         PuppiMET_ptJERUp;
   Float_t         PuppiMET_ptJESDown;
   Float_t         PuppiMET_ptJESUp;
   Float_t         PuppiMET_ptUnclusteredDown;
   Float_t         PuppiMET_ptUnclusteredUp;
   Float_t         PuppiMET_sumEt;
   Float_t         RawMET_phi;
   Float_t         RawMET_pt;
   Float_t         RawMET_sumEt;
   Float_t         RawPuppiMET_phi;
   Float_t         RawPuppiMET_pt;
   Float_t         RawPuppiMET_sumEt;
   Float_t         fixedGridRhoFastjetAll;
   Float_t         fixedGridRhoFastjetCentral;
   Float_t         fixedGridRhoFastjetCentralCalo;
   Float_t         fixedGridRhoFastjetCentralChargedPileUp;
   Float_t         fixedGridRhoFastjetCentralNeutral;
   UInt_t          nGenDressedLepton;
   Float_t         GenDressedLepton_eta[5];   //[nGenDressedLepton]
   Float_t         GenDressedLepton_mass[5];   //[nGenDressedLepton]
   Float_t         GenDressedLepton_phi[5];   //[nGenDressedLepton]
   Float_t         GenDressedLepton_pt[5];   //[nGenDressedLepton]
   Int_t           GenDressedLepton_pdgId[5];   //[nGenDressedLepton]
   Bool_t          GenDressedLepton_hasTauAnc[5];   //[nGenDressedLepton]
   UInt_t          nGenIsolatedPhoton;
   Float_t         GenIsolatedPhoton_eta[4];   //[nGenIsolatedPhoton]
   Float_t         GenIsolatedPhoton_mass[4];   //[nGenIsolatedPhoton]
   Float_t         GenIsolatedPhoton_phi[4];   //[nGenIsolatedPhoton]
   Float_t         GenIsolatedPhoton_pt[4];   //[nGenIsolatedPhoton]
   Float_t         TkMET_phi;
   Float_t         TkMET_pt;
   Float_t         TkMET_sumEt;
   UInt_t          nTrigObj;
   Float_t         TrigObj_pt[50];   //[nTrigObj]
   Float_t         TrigObj_eta[50];   //[nTrigObj]
   Float_t         TrigObj_phi[50];   //[nTrigObj]
   Float_t         TrigObj_l1pt[50];   //[nTrigObj]
   Float_t         TrigObj_l1pt_2[50];   //[nTrigObj]
   Float_t         TrigObj_l2pt[50];   //[nTrigObj]
   Int_t           TrigObj_id[50];   //[nTrigObj]
   Int_t           TrigObj_l1iso[50];   //[nTrigObj]
   Int_t           TrigObj_l1charge[50];   //[nTrigObj]
   Int_t           TrigObj_filterBits[50];   //[nTrigObj]
   Int_t           genTtbarId;
   UInt_t          nOtherPV;
   Float_t         OtherPV_z[3];   //[nOtherPV]
   Float_t         PV_ndof;
   Float_t         PV_x;
   Float_t         PV_y;
   Float_t         PV_z;
   Float_t         PV_chi2;
   Float_t         PV_score;
   Int_t           PV_npvs;
   Int_t           PV_npvsGood;
   UInt_t          nSV;
   Float_t         SV_dlen[19];   //[nSV]
   Float_t         SV_dlenSig[19];   //[nSV]
   Float_t         SV_dxy[19];   //[nSV]
   Float_t         SV_dxySig[19];   //[nSV]
   Float_t         SV_pAngle[19];   //[nSV]
   Int_t           SV_charge[19];   //[nSV]
   Int_t           Electron_genPartIdx[10];   //[nElectron]
   UChar_t         Electron_genPartFlav[10];   //[nElectron]
   Int_t           FatJet_genJetAK8Idx[7];   //[nFatJet]
   Int_t           FatJet_hadronFlavour[7];   //[nFatJet]
   UChar_t         FatJet_nBHadrons[7];   //[nFatJet]
   UChar_t         FatJet_nCHadrons[7];   //[nFatJet]
   Int_t           GenJetAK8_partonFlavour[10];   //[nGenJetAK8]
   UChar_t         GenJetAK8_hadronFlavour[10];   //[nGenJetAK8]
   Int_t           GenJet_partonFlavour[27];   //[nGenJet]
   UChar_t         GenJet_hadronFlavour[27];   //[nGenJet]
   Float_t         GenVtx_t0;
   Int_t           Jet_genJetIdx[28];   //[nJet]
   Int_t           Jet_hadronFlavour[28];   //[nJet]
   Int_t           Jet_partonFlavour[28];   //[nJet]
   Int_t           Muon_genPartIdx[16];   //[nMuon]
   UChar_t         Muon_genPartFlav[16];   //[nMuon]
   Int_t           Photon_genPartIdx[14];   //[nPhoton]
   UChar_t         Photon_genPartFlav[14];   //[nPhoton]
   Float_t         MET_fiducialGenPhi;
   Float_t         MET_fiducialGenPt;
   UChar_t         Electron_cleanmask[10];   //[nElectron]
   UChar_t         Jet_cleanmask[28];   //[nJet]
   UChar_t         Muon_cleanmask[16];   //[nMuon]
   UChar_t         Photon_cleanmask[14];   //[nPhoton]
   Float_t         SV_chi2[19];   //[nSV]
   Float_t         SV_eta[19];   //[nSV]
   Float_t         SV_mass[19];   //[nSV]
   Float_t         SV_ndof[19];   //[nSV]
   Float_t         SV_phi[19];   //[nSV]
   Float_t         SV_pt[19];   //[nSV]
   Float_t         SV_x[19];   //[nSV]
   Float_t         SV_y[19];   //[nSV]
   Float_t         SV_z[19];   //[nSV]
   UChar_t         SV_ntracks[19];   //[nSV]
   Bool_t          Flag_HBHENoiseFilter;
   Bool_t          Flag_HBHENoiseIsoFilter;
   Bool_t          Flag_CSCTightHaloFilter;
   Bool_t          Flag_CSCTightHaloTrkMuUnvetoFilter;
   Bool_t          Flag_CSCTightHalo2015Filter;
   Bool_t          Flag_globalTightHalo2016Filter;
   Bool_t          Flag_globalSuperTightHalo2016Filter;
   Bool_t          Flag_HcalStripHaloFilter;
   Bool_t          Flag_hcalLaserEventFilter;
   Bool_t          Flag_EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          Flag_EcalDeadCellBoundaryEnergyFilter;
   Bool_t          Flag_ecalBadCalibFilter;
   Bool_t          Flag_goodVertices;
   Bool_t          Flag_eeBadScFilter;
   Bool_t          Flag_ecalLaserCorrFilter;
   Bool_t          Flag_trkPOGFilters;
   Bool_t          Flag_chargedHadronTrackResolutionFilter;
   Bool_t          Flag_muonBadTrackFilter;
   Bool_t          Flag_BadChargedCandidateFilter;
   Bool_t          Flag_BadPFMuonFilter;
   Bool_t          Flag_BadPFMuonDzFilter;
   Bool_t          Flag_hfNoisyHitsFilter;
   Bool_t          Flag_BadChargedCandidateSummer16Filter;
   Bool_t          Flag_BadPFMuonSummer16Filter;
   Bool_t          Flag_trkPOG_manystripclus53X;
   Bool_t          Flag_trkPOG_toomanystripclus53X;
   Bool_t          Flag_trkPOG_logErrorTooManyClusters;
   Bool_t          Flag_METFilters;
   Bool_t          HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL;
   Bool_t          HLT_DoubleEle25_CaloIdL_MW;
   Bool_t          HLT_DoubleEle27_CaloIdL_MW;
   Bool_t          HLT_DoubleEle33_CaloIdL_MW;
   Bool_t          HLT_DoubleEle24_eta2p1_WPTight_Gsf;
   Bool_t          HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350;
   Bool_t          HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350;
   Bool_t          HLT_Ele27_Ele37_CaloIdL_MW;
   Bool_t          HLT_Mu27_Ele37_CaloIdL_MW;
   Bool_t          HLT_DoublePhoton33_CaloIdL;
   Bool_t          HLT_DoublePhoton70;
   Bool_t          HLT_DoublePhoton85;
   Bool_t          HLT_Ele20_WPTight_Gsf;
   Bool_t          HLT_Ele15_WPLoose_Gsf;
   Bool_t          HLT_Ele17_WPLoose_Gsf;
   Bool_t          HLT_Ele20_WPLoose_Gsf;
   Bool_t          HLT_Ele20_eta2p1_WPLoose_Gsf;
   Bool_t          HLT_Ele27_WPTight_Gsf;
   Bool_t          HLT_Ele28_WPTight_Gsf;
   Bool_t          HLT_Ele30_WPTight_Gsf;
   Bool_t          HLT_Ele32_WPTight_Gsf;
   Bool_t          HLT_Ele35_WPTight_Gsf;
   Bool_t          HLT_Ele35_WPTight_Gsf_L1EGMT;
   Bool_t          HLT_Ele38_WPTight_Gsf;
   Bool_t          HLT_Ele40_WPTight_Gsf;
   Bool_t          HLT_Ele32_WPTight_Gsf_L1DoubleEG;
   Bool_t          HLT_IsoMu20;
   Bool_t          HLT_IsoMu24;
   Bool_t          HLT_IsoTkMu24;
   Bool_t          HLT_IsoMu24_eta2p1;
   Bool_t          HLT_IsoMu27;
   Bool_t          HLT_IsoMu30;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
   Bool_t          HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
   Bool_t          HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;
   Bool_t          HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
   Bool_t          HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8;
   Bool_t          HLT_Mu25_TkMu0_Onia;
   Bool_t          HLT_Mu20_TkMu0_Phi;
   Bool_t          HLT_Mu25_TkMu0_Phi;
   Bool_t          HLT_Mu12;
   Bool_t          HLT_Mu15;
   Bool_t          HLT_Mu20;
   Bool_t          HLT_Mu27;
   Bool_t          HLT_Mu50;
   Bool_t          HLT_Mu55;
   Bool_t          HLT_TkMu100;
   Bool_t          HLT_PFMET110_PFMHT110_IDTight;
   Bool_t          HLT_PFMET120_PFMHT120_IDTight;
   Bool_t          HLT_PFMET130_PFMHT130_IDTight;
   Bool_t          HLT_PFMET140_PFMHT140_IDTight;
   Bool_t          HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1;
   Bool_t          HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1;
   Bool_t          HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1;
   Bool_t          HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1;
   Bool_t          HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1;
   Bool_t          HLT_PFMET120_PFMHT120_IDTight_PFHT60;
   Bool_t          HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60;
   Bool_t          HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60;
   Bool_t          HLT_PFMETTypeOne110_PFMHT110_IDTight;
   Bool_t          HLT_PFMETTypeOne120_PFMHT120_IDTight;
   Bool_t          HLT_PFMETTypeOne130_PFMHT130_IDTight;
   Bool_t          HLT_PFMETTypeOne140_PFMHT140_IDTight;
   Bool_t          HLT_PFMETNoMu110_PFMHTNoMu110_IDTight;
   Bool_t          HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;
   Bool_t          HLT_PFMETNoMu130_PFMHTNoMu130_IDTight;
   Bool_t          HLT_PFMETNoMu140_PFMHTNoMu140_IDTight;
   Bool_t          HLT_PFMET200_NotCleaned;
   Bool_t          HLT_PFMET200_HBHECleaned;
   Bool_t          HLT_PFMET250_HBHECleaned;
   Bool_t          HLT_PFMET300_HBHECleaned;
   Bool_t          HLT_PFMET200_HBHE_BeamHaloCleaned;
   Bool_t          HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned;
   Bool_t          HLT_MET105_IsoTrk50;
   Bool_t          HLT_MET120_IsoTrk50;
   Bool_t          HLT_SingleJet30_Mu12_SinglePFJet40;
   Bool_t          HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71;
   Bool_t          HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71;
   Bool_t          HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71;
   Bool_t          HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71;
   Bool_t          HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71;
   Bool_t          HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71;
   Bool_t          HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71;
   Bool_t          HLT_Mu8_TrkIsoVVL;
   Bool_t          HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ;
   Bool_t          HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
   Bool_t          HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ;
   Bool_t          HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu17_TrkIsoVVL;
   Bool_t          HLT_Mu19_TrkIsoVVL;
   Bool_t          HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu12_DoublePhoton20;
   Bool_t          HLT_IsoMu24_TwoProngs35;
   Bool_t          HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned;
   Bool_t          HLT_Ele28_eta2p1_WPTight_Gsf_HT150;
   Bool_t          HLT_Ele28_HighEta_SC20_Mass55;
   Bool_t          HLT_DoubleMu20_7_Mass0to30_Photon23;
   Bool_t          HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5;
   Bool_t          HLT_Ele15_IsoVVVL_PFHT450_PFMET50;
   Bool_t          HLT_Ele15_IsoVVVL_PFHT450;
   Bool_t          HLT_Ele50_IsoVVVL_PFHT450;
   Bool_t          HLT_Ele15_IsoVVVL_PFHT600;
   Bool_t          HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60;
   Bool_t          HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60;
   Bool_t          HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60;
   Bool_t          HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5;
   Bool_t          HLT_Mu15_IsoVVVL_PFHT450_PFMET50;
   Bool_t          HLT_Mu15_IsoVVVL_PFHT450;
   Bool_t          HLT_Mu50_IsoVVVL_PFHT450;
   Bool_t          HLT_Mu15_IsoVVVL_PFHT600;
   Bool_t          HLT_DoubleIsoMu20_eta2p1;
   Bool_t          HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx;
   Bool_t          HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx;
   Bool_t          HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx;
   Bool_t          HLT_Mu8;
   Bool_t          HLT_Mu17;
   Bool_t          HLT_Mu19;
   Bool_t          HLT_Mu17_Photon30_IsoCaloId;
   Bool_t          HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30;
   Bool_t          HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30;
   Bool_t          HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30;
   Bool_t          HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30;
   Bool_t          HLT_Ele8_CaloIdM_TrackIdM_PFJet30;
   Bool_t          HLT_Ele17_CaloIdM_TrackIdM_PFJet30;
   Bool_t          HLT_Ele23_CaloIdM_TrackIdM_PFJet30;
   Bool_t          HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165;
   Bool_t          HLT_Ele115_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_Ele135_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_Ele145_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_Ele200_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_Ele250_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_Ele300_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_ECALHT800;
   Bool_t          HLT_Random;
   Bool_t          HLT_SinglePhoton10_Eta3p1ForPPRef;
   Bool_t          HLT_SinglePhoton20_Eta3p1ForPPRef;
   Bool_t          HLT_SinglePhoton30_Eta3p1ForPPRef;
   Bool_t          HLT_EcalCalibration;
   Bool_t          HLT_IsoTrackHB;
   Bool_t          HLT_IsoTrackHE;
   Bool_t          HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr;
   Bool_t          HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
   Bool_t          HLT_IsoMu27_MET90;
   Bool_t          HLT_PFMET100_PFMHT100_IDTight_PFHT60;
   Bool_t          HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60;
   Bool_t          HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60;
   Bool_t          HLT_Mu18_Mu9_SameSign;
   Bool_t          HLT_Mu18_Mu9_SameSign_DZ;
   Bool_t          HLT_Mu18_Mu9;
   Bool_t          HLT_Mu18_Mu9_DZ;
   Bool_t          HLT_Mu20_Mu10_SameSign;
   Bool_t          HLT_Mu20_Mu10_SameSign_DZ;
   Bool_t          HLT_Mu20_Mu10;
   Bool_t          HLT_Mu20_Mu10_DZ;
   Bool_t          HLT_Mu23_Mu12_SameSign;
   Bool_t          HLT_Mu23_Mu12_SameSign_DZ;
   Bool_t          HLT_Mu23_Mu12;
   Bool_t          HLT_Mu23_Mu12_DZ;
   Bool_t          HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05;
   Bool_t          HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi;
   Bool_t          HLT_TrkMu6NoFiltersNoVtx;
   Bool_t          HLT_TrkMu16NoFiltersNoVtx;
   Bool_t          HLT_DoubleTrkMu_16_6_NoFiltersNoVtx;
   Bool_t          HLTriggerFinalPath;
   Bool_t          L1simulation_step;
   Float_t         lumi;
   Char_t          pass_selection;
   Int_t           photon_selection;
   Int_t           channel;
   Int_t           lep1_pid;
   Int_t           lep2_pid;
   Float_t         lep1pt;
   Float_t         lep2pt;
   Float_t         lep1eta;
   Float_t         lep2eta;
   Float_t         lep1phi;
   Float_t         lep2phi;
   Float_t         drll;
   Int_t           lep1_charge;
   Int_t           lep2_charge;
   Int_t           lep1_isprompt;
   Int_t           lep2_isprompt;
   Int_t           lep1_is_tight;
   Int_t           lep2_is_tight;
   Int_t           n_loose_mu;
   Int_t           n_loose_ele;
   Int_t           n_leptons;
   Int_t           n_photon;
   Float_t         photonet;
   Float_t         photoneta;
   Float_t         photonphi;
   Float_t         photonchiso;
   Float_t         drl1a;
   Float_t         drl2a;
   Int_t           photon_isprompt;
   Int_t           photon_gen_matching;
   Float_t         mll;
   Float_t         mllg;
   Float_t         ptll;
   Float_t         mt;
   Float_t         puppimt;
   Float_t         met;
   Float_t         metup;
   Float_t         puppimet;
   Float_t         puppimetphi;
   Float_t         rawmet;
   Float_t         rawmetphi;
   Float_t         metphi;
   Float_t         gen_weight;
   Int_t           npu;
   Float_t         ntruepu;
   Int_t           MET_pass;
   Int_t           npvs;
   Int_t           n_bjets_loose_deepcsv;
   Int_t           n_bjets_loose_deepFlavB;
   Int_t           n_bjets20_loose_deepcsv;
   Int_t           n_bjets20_loose_deepFlavB;
   Int_t           n_bjets_medium_deepcsv;
   Int_t           n_bjets_medium_deepFlavB;
   Int_t           n_bjets20_medium_deepcsv;
   Int_t           n_bjets20_medium_deepFlavB;
   Int_t           njets50;
   Int_t           njets40;
   Int_t           njets30;
   Int_t           njets20;
   Int_t           njets50_pc;
   Int_t           njets40_pc;
   Int_t           njets30_pc;
   Int_t           njets20_pc;
   Int_t           n_bjets_loose_deepcsv_pc;
   Int_t           n_bjets_loose_deepFlavB_pc;
   Int_t           n_bjets20_loose_deepcsv_pc;
   Int_t           n_bjets20_loose_deepFlavB_pc;
   Int_t           n_bjets_medium_deepcsv_pc;
   Int_t           n_bjets_medium_deepFlavB_pc;
   Int_t           n_bjets20_medium_deepcsv_pc;
   Int_t           n_bjets20_medium_deepFlavB_pc;
   Float_t         Jet_pt_raw[28];   //[nJet]
   Float_t         Jet_pt_nom[28];   //[nJet]
   Float_t         Jet_mass_raw[28];   //[nJet]
   Float_t         Jet_mass_nom[28];   //[nJet]
   Float_t         Jet_corr_JEC[28];   //[nJet]
   Float_t         Jet_corr_JER[28];   //[nJet]
   Float_t         MET_T1_pt;
   Float_t         MET_T1_phi;
   Float_t         MET_T1Smear_pt;
   Float_t         MET_T1Smear_phi;
   Float_t         Jet_pt_jer0Up[28];   //[nJet]
   Float_t         Jet_mass_jer0Up[28];   //[nJet]
   Float_t         MET_T1_pt_jer0Up;
   Float_t         MET_T1_phi_jer0Up;
   Float_t         MET_T1Smear_pt_jer0Up;
   Float_t         MET_T1Smear_phi_jer0Up;
   Float_t         Jet_pt_jer1Up[28];   //[nJet]
   Float_t         Jet_mass_jer1Up[28];   //[nJet]
   Float_t         MET_T1_pt_jer1Up;
   Float_t         MET_T1_phi_jer1Up;
   Float_t         MET_T1Smear_pt_jer1Up;
   Float_t         MET_T1Smear_phi_jer1Up;
   Float_t         Jet_pt_jer2Up[28];   //[nJet]
   Float_t         Jet_mass_jer2Up[28];   //[nJet]
   Float_t         MET_T1_pt_jer2Up;
   Float_t         MET_T1_phi_jer2Up;
   Float_t         MET_T1Smear_pt_jer2Up;
   Float_t         MET_T1Smear_phi_jer2Up;
   Float_t         Jet_pt_jer3Up[28];   //[nJet]
   Float_t         Jet_mass_jer3Up[28];   //[nJet]
   Float_t         MET_T1_pt_jer3Up;
   Float_t         MET_T1_phi_jer3Up;
   Float_t         MET_T1Smear_pt_jer3Up;
   Float_t         MET_T1Smear_phi_jer3Up;
   Float_t         Jet_pt_jer4Up[28];   //[nJet]
   Float_t         Jet_mass_jer4Up[28];   //[nJet]
   Float_t         MET_T1_pt_jer4Up;
   Float_t         MET_T1_phi_jer4Up;
   Float_t         MET_T1Smear_pt_jer4Up;
   Float_t         MET_T1Smear_phi_jer4Up;
   Float_t         Jet_pt_jer5Up[28];   //[nJet]
   Float_t         Jet_mass_jer5Up[28];   //[nJet]
   Float_t         MET_T1_pt_jer5Up;
   Float_t         MET_T1_phi_jer5Up;
   Float_t         MET_T1Smear_pt_jer5Up;
   Float_t         MET_T1Smear_phi_jer5Up;
   Float_t         Jet_pt_jesTotalUp[28];   //[nJet]
   Float_t         Jet_mass_jesTotalUp[28];   //[nJet]
   Float_t         MET_T1_pt_jesTotalUp;
   Float_t         MET_T1_phi_jesTotalUp;
   Float_t         MET_T1Smear_pt_jesTotalUp;
   Float_t         MET_T1Smear_phi_jesTotalUp;
   Float_t         Jet_pt_jesHEMIssueUp[28];   //[nJet]
   Float_t         Jet_mass_jesHEMIssueUp[28];   //[nJet]
   Float_t         MET_T1_pt_jesHEMIssueUp;
   Float_t         MET_T1_phi_jesHEMIssueUp;
   Float_t         MET_T1Smear_pt_jesHEMIssueUp;
   Float_t         MET_T1Smear_phi_jesHEMIssueUp;
   Float_t         MET_T1_pt_unclustEnUp;
   Float_t         MET_T1_phi_unclustEnUp;
   Float_t         MET_T1Smear_pt_unclustEnUp;
   Float_t         MET_T1Smear_phi_unclustEnUp;
   Float_t         Jet_pt_jer0Down[28];   //[nJet]
   Float_t         Jet_mass_jer0Down[28];   //[nJet]
   Float_t         MET_T1_pt_jer0Down;
   Float_t         MET_T1_phi_jer0Down;
   Float_t         MET_T1Smear_pt_jer0Down;
   Float_t         MET_T1Smear_phi_jer0Down;
   Float_t         Jet_pt_jer1Down[28];   //[nJet]
   Float_t         Jet_mass_jer1Down[28];   //[nJet]
   Float_t         MET_T1_pt_jer1Down;
   Float_t         MET_T1_phi_jer1Down;
   Float_t         MET_T1Smear_pt_jer1Down;
   Float_t         MET_T1Smear_phi_jer1Down;
   Float_t         Jet_pt_jer2Down[28];   //[nJet]
   Float_t         Jet_mass_jer2Down[28];   //[nJet]
   Float_t         MET_T1_pt_jer2Down;
   Float_t         MET_T1_phi_jer2Down;
   Float_t         MET_T1Smear_pt_jer2Down;
   Float_t         MET_T1Smear_phi_jer2Down;
   Float_t         Jet_pt_jer3Down[28];   //[nJet]
   Float_t         Jet_mass_jer3Down[28];   //[nJet]
   Float_t         MET_T1_pt_jer3Down;
   Float_t         MET_T1_phi_jer3Down;
   Float_t         MET_T1Smear_pt_jer3Down;
   Float_t         MET_T1Smear_phi_jer3Down;
   Float_t         Jet_pt_jer4Down[28];   //[nJet]
   Float_t         Jet_mass_jer4Down[28];   //[nJet]
   Float_t         MET_T1_pt_jer4Down;
   Float_t         MET_T1_phi_jer4Down;
   Float_t         MET_T1Smear_pt_jer4Down;
   Float_t         MET_T1Smear_phi_jer4Down;
   Float_t         Jet_pt_jer5Down[28];   //[nJet]
   Float_t         Jet_mass_jer5Down[28];   //[nJet]
   Float_t         MET_T1_pt_jer5Down;
   Float_t         MET_T1_phi_jer5Down;
   Float_t         MET_T1Smear_pt_jer5Down;
   Float_t         MET_T1Smear_phi_jer5Down;
   Float_t         Jet_pt_jesTotalDown[28];   //[nJet]
   Float_t         Jet_mass_jesTotalDown[28];   //[nJet]
   Float_t         MET_T1_pt_jesTotalDown;
   Float_t         MET_T1_phi_jesTotalDown;
   Float_t         MET_T1Smear_pt_jesTotalDown;
   Float_t         MET_T1Smear_phi_jesTotalDown;
   Float_t         Jet_pt_jesHEMIssueDown[28];   //[nJet]
   Float_t         Jet_mass_jesHEMIssueDown[28];   //[nJet]
   Float_t         MET_T1_pt_jesHEMIssueDown;
   Float_t         MET_T1_phi_jesHEMIssueDown;
   Float_t         MET_T1Smear_pt_jesHEMIssueDown;
   Float_t         MET_T1Smear_phi_jesHEMIssueDown;
   Float_t         MET_T1_pt_unclustEnDown;
   Float_t         MET_T1_phi_unclustEnDown;
   Float_t         MET_T1Smear_pt_unclustEnDown;
   Float_t         MET_T1Smear_phi_unclustEnDown;
   Float_t         puWeight;
   Float_t         puWeightUp;
   Float_t         puWeightDown;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_luminosityBlock;   //!
   TBranch        *b_event;   //!
   TBranch        *b_btagWeight_CSVV2;   //!
   TBranch        *b_btagWeight_DeepCSVB;   //!
   TBranch        *b_nCorrT1METJet;   //!
   TBranch        *b_CorrT1METJet_area;   //!
   TBranch        *b_CorrT1METJet_eta;   //!
   TBranch        *b_CorrT1METJet_muonSubtrFactor;   //!
   TBranch        *b_CorrT1METJet_phi;   //!
   TBranch        *b_CorrT1METJet_rawPt;   //!
   TBranch        *b_DeepMETResolutionTune_phi;   //!
   TBranch        *b_DeepMETResolutionTune_pt;   //!
   TBranch        *b_DeepMETResponseTune_phi;   //!
   TBranch        *b_DeepMETResponseTune_pt;   //!
   TBranch        *b_nElectron;   //!
   TBranch        *b_Electron_dEscaleDown;   //!
   TBranch        *b_Electron_dEscaleUp;   //!
   TBranch        *b_Electron_dEsigmaDown;   //!
   TBranch        *b_Electron_dEsigmaUp;   //!
   TBranch        *b_Electron_deltaEtaSC;   //!
   TBranch        *b_Electron_dr03EcalRecHitSumEt;   //!
   TBranch        *b_Electron_dr03HcalDepth1TowerSumEt;   //!
   TBranch        *b_Electron_dr03TkSumPt;   //!
   TBranch        *b_Electron_dr03TkSumPtHEEP;   //!
   TBranch        *b_Electron_dxy;   //!
   TBranch        *b_Electron_dxyErr;   //!
   TBranch        *b_Electron_dz;   //!
   TBranch        *b_Electron_dzErr;   //!
   TBranch        *b_Electron_eCorr;   //!
   TBranch        *b_Electron_eInvMinusPInv;   //!
   TBranch        *b_Electron_energyErr;   //!
   TBranch        *b_Electron_eta;   //!
   TBranch        *b_Electron_hoe;   //!
   TBranch        *b_Electron_ip3d;   //!
   TBranch        *b_Electron_jetPtRelv2;   //!
   TBranch        *b_Electron_jetRelIso;   //!
   TBranch        *b_Electron_mass;   //!
   TBranch        *b_Electron_miniPFRelIso_all;   //!
   TBranch        *b_Electron_miniPFRelIso_chg;   //!
   TBranch        *b_Electron_mvaFall17V2Iso;   //!
   TBranch        *b_Electron_mvaFall17V2noIso;   //!
   TBranch        *b_Electron_pfRelIso03_all;   //!
   TBranch        *b_Electron_pfRelIso03_chg;   //!
   TBranch        *b_Electron_phi;   //!
   TBranch        *b_Electron_pt;   //!
   TBranch        *b_Electron_r9;   //!
   TBranch        *b_Electron_scEtOverPt;   //!
   TBranch        *b_Electron_sieie;   //!
   TBranch        *b_Electron_sip3d;   //!
   TBranch        *b_Electron_mvaTTH;   //!
   TBranch        *b_Electron_charge;   //!
   TBranch        *b_Electron_cutBased;   //!
   TBranch        *b_Electron_jetIdx;   //!
   TBranch        *b_Electron_pdgId;   //!
   TBranch        *b_Electron_photonIdx;   //!
   TBranch        *b_Electron_tightCharge;   //!
   TBranch        *b_Electron_vidNestedWPBitmap;   //!
   TBranch        *b_Electron_vidNestedWPBitmapHEEP;   //!
   TBranch        *b_Electron_convVeto;   //!
   TBranch        *b_Electron_cutBased_HEEP;   //!
   TBranch        *b_Electron_isPFcand;   //!
   TBranch        *b_Electron_jetNDauCharged;   //!
   TBranch        *b_Electron_lostHits;   //!
   TBranch        *b_Electron_mvaFall17V2Iso_WP80;   //!
   TBranch        *b_Electron_mvaFall17V2Iso_WP90;   //!
   TBranch        *b_Electron_mvaFall17V2Iso_WPL;   //!
   TBranch        *b_Electron_mvaFall17V2noIso_WP80;   //!
   TBranch        *b_Electron_mvaFall17V2noIso_WP90;   //!
   TBranch        *b_Electron_mvaFall17V2noIso_WPL;   //!
   TBranch        *b_Electron_seedGain;   //!
   TBranch        *b_nFatJet;   //!
   TBranch        *b_FatJet_area;   //!
   TBranch        *b_FatJet_btagCSVV2;   //!
   TBranch        *b_FatJet_btagDDBvLV2;   //!
   TBranch        *b_FatJet_btagDDCvBV2;   //!
   TBranch        *b_FatJet_btagDDCvLV2;   //!
   TBranch        *b_FatJet_btagDeepB;   //!
   TBranch        *b_FatJet_btagHbb;   //!
   TBranch        *b_FatJet_deepTagMD_H4qvsQCD;   //!
   TBranch        *b_FatJet_deepTagMD_HbbvsQCD;   //!
   TBranch        *b_FatJet_deepTagMD_TvsQCD;   //!
   TBranch        *b_FatJet_deepTagMD_WvsQCD;   //!
   TBranch        *b_FatJet_deepTagMD_ZHbbvsQCD;   //!
   TBranch        *b_FatJet_deepTagMD_ZHccvsQCD;   //!
   TBranch        *b_FatJet_deepTagMD_ZbbvsQCD;   //!
   TBranch        *b_FatJet_deepTagMD_ZvsQCD;   //!
   TBranch        *b_FatJet_deepTagMD_bbvsLight;   //!
   TBranch        *b_FatJet_deepTagMD_ccvsLight;   //!
   TBranch        *b_FatJet_deepTag_H;   //!
   TBranch        *b_FatJet_deepTag_QCD;   //!
   TBranch        *b_FatJet_deepTag_QCDothers;   //!
   TBranch        *b_FatJet_deepTag_TvsQCD;   //!
   TBranch        *b_FatJet_deepTag_WvsQCD;   //!
   TBranch        *b_FatJet_deepTag_ZvsQCD;   //!
   TBranch        *b_FatJet_eta;   //!
   TBranch        *b_FatJet_mass;   //!
   TBranch        *b_FatJet_msoftdrop;   //!
   TBranch        *b_FatJet_n2b1;   //!
   TBranch        *b_FatJet_n3b1;   //!
   TBranch        *b_FatJet_particleNetMD_QCD;   //!
   TBranch        *b_FatJet_particleNetMD_Xbb;   //!
   TBranch        *b_FatJet_particleNetMD_Xcc;   //!
   TBranch        *b_FatJet_particleNetMD_Xqq;   //!
   TBranch        *b_FatJet_particleNet_H4qvsQCD;   //!
   TBranch        *b_FatJet_particleNet_HbbvsQCD;   //!
   TBranch        *b_FatJet_particleNet_HccvsQCD;   //!
   TBranch        *b_FatJet_particleNet_QCD;   //!
   TBranch        *b_FatJet_particleNet_TvsQCD;   //!
   TBranch        *b_FatJet_particleNet_WvsQCD;   //!
   TBranch        *b_FatJet_particleNet_ZvsQCD;   //!
   TBranch        *b_FatJet_particleNet_mass;   //!
   TBranch        *b_FatJet_phi;   //!
   TBranch        *b_FatJet_pt;   //!
   TBranch        *b_FatJet_rawFactor;   //!
   TBranch        *b_FatJet_tau1;   //!
   TBranch        *b_FatJet_tau2;   //!
   TBranch        *b_FatJet_tau3;   //!
   TBranch        *b_FatJet_tau4;   //!
   TBranch        *b_FatJet_lsf3;   //!
   TBranch        *b_FatJet_jetId;   //!
   TBranch        *b_FatJet_subJetIdx1;   //!
   TBranch        *b_FatJet_subJetIdx2;   //!
   TBranch        *b_FatJet_electronIdx3SJ;   //!
   TBranch        *b_FatJet_muonIdx3SJ;   //!
   TBranch        *b_FatJet_nConstituents;   //!
   TBranch        *b_nFsrPhoton;   //!
   TBranch        *b_FsrPhoton_dROverEt2;   //!
   TBranch        *b_FsrPhoton_eta;   //!
   TBranch        *b_FsrPhoton_phi;   //!
   TBranch        *b_FsrPhoton_pt;   //!
   TBranch        *b_FsrPhoton_relIso03;   //!
   TBranch        *b_FsrPhoton_muonIdx;   //!
   TBranch        *b_nGenJetAK8;   //!
   TBranch        *b_GenJetAK8_eta;   //!
   TBranch        *b_GenJetAK8_mass;   //!
   TBranch        *b_GenJetAK8_phi;   //!
   TBranch        *b_GenJetAK8_pt;   //!
   TBranch        *b_nGenJet;   //!
   TBranch        *b_GenJet_eta;   //!
   TBranch        *b_GenJet_mass;   //!
   TBranch        *b_GenJet_phi;   //!
   TBranch        *b_GenJet_pt;   //!
   TBranch        *b_nGenPart;   //!
   TBranch        *b_GenPart_eta;   //!
   TBranch        *b_GenPart_mass;   //!
   TBranch        *b_GenPart_phi;   //!
   TBranch        *b_GenPart_pt;   //!
   TBranch        *b_GenPart_genPartIdxMother;   //!
   TBranch        *b_GenPart_pdgId;   //!
   TBranch        *b_GenPart_status;   //!
   TBranch        *b_GenPart_statusFlags;   //!
   TBranch        *b_Generator_binvar;   //!
   TBranch        *b_Generator_scalePDF;   //!
   TBranch        *b_Generator_weight;   //!
   TBranch        *b_Generator_x1;   //!
   TBranch        *b_Generator_x2;   //!
   TBranch        *b_Generator_xpdf1;   //!
   TBranch        *b_Generator_xpdf2;   //!
   TBranch        *b_Generator_id1;   //!
   TBranch        *b_Generator_id2;   //!
   TBranch        *b_GenVtx_x;   //!
   TBranch        *b_GenVtx_y;   //!
   TBranch        *b_GenVtx_z;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_LHEWeight_originalXWGTUP;   //!
   TBranch        *b_nLHEPdfWeight;   //!
   TBranch        *b_LHEPdfWeight;   //!
   TBranch        *b_nLHEReweightingWeight;   //!
   TBranch        *b_LHEReweightingWeight;   //!
   TBranch        *b_nLHEScaleWeight;   //!
   TBranch        *b_LHEScaleWeight;   //!
   TBranch        *b_nPSWeight;   //!
   TBranch        *b_PSWeight;   //!
   TBranch        *b_nIsoTrack;   //!
   TBranch        *b_nJet;   //!
   TBranch        *b_Jet_area;   //!
   TBranch        *b_Jet_btagCSVV2;   //!
   TBranch        *b_Jet_btagDeepB;   //!
   TBranch        *b_Jet_btagDeepCvB;   //!
   TBranch        *b_Jet_btagDeepCvL;   //!
   TBranch        *b_Jet_btagDeepFlavB;   //!
   TBranch        *b_Jet_btagDeepFlavCvB;   //!
   TBranch        *b_Jet_btagDeepFlavCvL;   //!
   TBranch        *b_Jet_btagDeepFlavQG;   //!
   TBranch        *b_Jet_chEmEF;   //!
   TBranch        *b_Jet_chFPV0EF;   //!
   TBranch        *b_Jet_chHEF;   //!
   TBranch        *b_Jet_eta;   //!
   TBranch        *b_Jet_hfsigmaEtaEta;   //!
   TBranch        *b_Jet_hfsigmaPhiPhi;   //!
   TBranch        *b_Jet_mass;   //!
   TBranch        *b_Jet_muEF;   //!
   TBranch        *b_Jet_muonSubtrFactor;   //!
   TBranch        *b_Jet_neEmEF;   //!
   TBranch        *b_Jet_neHEF;   //!
   TBranch        *b_Jet_phi;   //!
   TBranch        *b_Jet_pt;   //!
   TBranch        *b_Jet_puIdDisc;   //!
   TBranch        *b_Jet_qgl;   //!
   TBranch        *b_Jet_rawFactor;   //!
   TBranch        *b_Jet_bRegCorr;   //!
   TBranch        *b_Jet_bRegRes;   //!
   TBranch        *b_Jet_cRegCorr;   //!
   TBranch        *b_Jet_cRegRes;   //!
   TBranch        *b_Jet_electronIdx1;   //!
   TBranch        *b_Jet_electronIdx2;   //!
   TBranch        *b_Jet_hfadjacentEtaStripsSize;   //!
   TBranch        *b_Jet_hfcentralEtaStripSize;   //!
   TBranch        *b_Jet_jetId;   //!
   TBranch        *b_Jet_muonIdx1;   //!
   TBranch        *b_Jet_muonIdx2;   //!
   TBranch        *b_Jet_nElectrons;   //!
   TBranch        *b_Jet_nMuons;   //!
   TBranch        *b_Jet_puId;   //!
   TBranch        *b_Jet_nConstituents;   //!
   TBranch        *b_L1PreFiringWeight_Dn;   //!
   TBranch        *b_L1PreFiringWeight_ECAL_Dn;   //!
   TBranch        *b_L1PreFiringWeight_ECAL_Nom;   //!
   TBranch        *b_L1PreFiringWeight_ECAL_Up;   //!
   TBranch        *b_L1PreFiringWeight_Muon_Nom;   //!
   TBranch        *b_L1PreFiringWeight_Muon_StatDn;   //!
   TBranch        *b_L1PreFiringWeight_Muon_StatUp;   //!
   TBranch        *b_L1PreFiringWeight_Muon_SystDn;   //!
   TBranch        *b_L1PreFiringWeight_Muon_SystUp;   //!
   TBranch        *b_L1PreFiringWeight_Nom;   //!
   TBranch        *b_L1PreFiringWeight_Up;   //!
   TBranch        *b_GenMET_phi;   //!
   TBranch        *b_GenMET_pt;   //!
   TBranch        *b_MET_MetUnclustEnUpDeltaX;   //!
   TBranch        *b_MET_MetUnclustEnUpDeltaY;   //!
   TBranch        *b_MET_covXX;   //!
   TBranch        *b_MET_covXY;   //!
   TBranch        *b_MET_covYY;   //!
   TBranch        *b_MET_phi;   //!
   TBranch        *b_MET_pt;   //!
   TBranch        *b_MET_significance;   //!
   TBranch        *b_MET_sumEt;   //!
   TBranch        *b_MET_sumPtUnclustered;   //!
   TBranch        *b_nMuon;   //!
   TBranch        *b_Muon_dxy;   //!
   TBranch        *b_Muon_dxyErr;   //!
   TBranch        *b_Muon_dxybs;   //!
   TBranch        *b_Muon_dz;   //!
   TBranch        *b_Muon_dzErr;   //!
   TBranch        *b_Muon_eta;   //!
   TBranch        *b_Muon_ip3d;   //!
   TBranch        *b_Muon_jetPtRelv2;   //!
   TBranch        *b_Muon_jetRelIso;   //!
   TBranch        *b_Muon_mass;   //!
   TBranch        *b_Muon_miniPFRelIso_all;   //!
   TBranch        *b_Muon_miniPFRelIso_chg;   //!
   TBranch        *b_Muon_pfRelIso03_all;   //!
   TBranch        *b_Muon_pfRelIso03_chg;   //!
   TBranch        *b_Muon_pfRelIso04_all;   //!
   TBranch        *b_Muon_phi;   //!
   TBranch        *b_Muon_pt;   //!
   TBranch        *b_Muon_ptErr;   //!
   TBranch        *b_Muon_segmentComp;   //!
   TBranch        *b_Muon_sip3d;   //!
   TBranch        *b_Muon_softMva;   //!
   TBranch        *b_Muon_tkRelIso;   //!
   TBranch        *b_Muon_tunepRelPt;   //!
   TBranch        *b_Muon_mvaLowPt;   //!
   TBranch        *b_Muon_mvaTTH;   //!
   TBranch        *b_Muon_charge;   //!
   TBranch        *b_Muon_jetIdx;   //!
   TBranch        *b_Muon_nStations;   //!
   TBranch        *b_Muon_nTrackerLayers;   //!
   TBranch        *b_Muon_pdgId;   //!
   TBranch        *b_Muon_tightCharge;   //!
   TBranch        *b_Muon_fsrPhotonIdx;   //!
   TBranch        *b_Muon_highPtId;   //!
   TBranch        *b_Muon_highPurity;   //!
   TBranch        *b_Muon_inTimeMuon;   //!
   TBranch        *b_Muon_isGlobal;   //!
   TBranch        *b_Muon_isPFcand;   //!
   TBranch        *b_Muon_isStandalone;   //!
   TBranch        *b_Muon_isTracker;   //!
   TBranch        *b_Muon_jetNDauCharged;   //!
   TBranch        *b_Muon_looseId;   //!
   TBranch        *b_Muon_mediumId;   //!
   TBranch        *b_Muon_mediumPromptId;   //!
   TBranch        *b_Muon_miniIsoId;   //!
   TBranch        *b_Muon_multiIsoId;   //!
   TBranch        *b_Muon_mvaId;   //!
   TBranch        *b_Muon_mvaLowPtId;   //!
   TBranch        *b_Muon_pfIsoId;   //!
   TBranch        *b_Muon_puppiIsoId;   //!
   TBranch        *b_Muon_softId;   //!
   TBranch        *b_Muon_softMvaId;   //!
   TBranch        *b_Muon_tightId;   //!
   TBranch        *b_Muon_tkIsoId;   //!
   TBranch        *b_Muon_triggerIdLoose;   //!
   TBranch        *b_nPhoton;   //!
   TBranch        *b_Photon_dEscaleDown;   //!
   TBranch        *b_Photon_dEscaleUp;   //!
   TBranch        *b_Photon_dEsigmaDown;   //!
   TBranch        *b_Photon_dEsigmaUp;   //!
   TBranch        *b_Photon_eCorr;   //!
   TBranch        *b_Photon_energyErr;   //!
   TBranch        *b_Photon_eta;   //!
   TBranch        *b_Photon_hoe;   //!
   TBranch        *b_Photon_mass;   //!
   TBranch        *b_Photon_mvaID;   //!
   TBranch        *b_Photon_mvaID_Fall17V1p1;   //!
   TBranch        *b_Photon_pfRelIso03_all;   //!
   TBranch        *b_Photon_pfRelIso03_chg;   //!
   TBranch        *b_Photon_phi;   //!
   TBranch        *b_Photon_pt;   //!
   TBranch        *b_Photon_r9;   //!
   TBranch        *b_Photon_sieie;   //!
   TBranch        *b_Photon_charge;   //!
   TBranch        *b_Photon_cutBased;   //!
   TBranch        *b_Photon_cutBased_Fall17V1Bitmap;   //!
   TBranch        *b_Photon_electronIdx;   //!
   TBranch        *b_Photon_jetIdx;   //!
   TBranch        *b_Photon_pdgId;   //!
   TBranch        *b_Photon_vidNestedWPBitmap;   //!
   TBranch        *b_Photon_electronVeto;   //!
   TBranch        *b_Photon_isScEtaEB;   //!
   TBranch        *b_Photon_isScEtaEE;   //!
   TBranch        *b_Photon_mvaID_WP80;   //!
   TBranch        *b_Photon_mvaID_WP90;   //!
   TBranch        *b_Photon_pixelSeed;   //!
   TBranch        *b_Photon_seedGain;   //!
   TBranch        *b_Pileup_nTrueInt;   //!
   TBranch        *b_Pileup_pudensity;   //!
   TBranch        *b_Pileup_gpudensity;   //!
   TBranch        *b_Pileup_nPU;   //!
   TBranch        *b_Pileup_sumEOOT;   //!
   TBranch        *b_Pileup_sumLOOT;   //!
   TBranch        *b_PuppiMET_phi;   //!
   TBranch        *b_PuppiMET_phiJERDown;   //!
   TBranch        *b_PuppiMET_phiJERUp;   //!
   TBranch        *b_PuppiMET_phiJESDown;   //!
   TBranch        *b_PuppiMET_phiJESUp;   //!
   TBranch        *b_PuppiMET_phiUnclusteredDown;   //!
   TBranch        *b_PuppiMET_phiUnclusteredUp;   //!
   TBranch        *b_PuppiMET_pt;   //!
   TBranch        *b_PuppiMET_ptJERDown;   //!
   TBranch        *b_PuppiMET_ptJERUp;   //!
   TBranch        *b_PuppiMET_ptJESDown;   //!
   TBranch        *b_PuppiMET_ptJESUp;   //!
   TBranch        *b_PuppiMET_ptUnclusteredDown;   //!
   TBranch        *b_PuppiMET_ptUnclusteredUp;   //!
   TBranch        *b_PuppiMET_sumEt;   //!
   TBranch        *b_RawMET_phi;   //!
   TBranch        *b_RawMET_pt;   //!
   TBranch        *b_RawMET_sumEt;   //!
   TBranch        *b_RawPuppiMET_phi;   //!
   TBranch        *b_RawPuppiMET_pt;   //!
   TBranch        *b_RawPuppiMET_sumEt;   //!
   TBranch        *b_fixedGridRhoFastjetAll;   //!
   TBranch        *b_fixedGridRhoFastjetCentral;   //!
   TBranch        *b_fixedGridRhoFastjetCentralCalo;   //!
   TBranch        *b_fixedGridRhoFastjetCentralChargedPileUp;   //!
   TBranch        *b_fixedGridRhoFastjetCentralNeutral;   //!
   TBranch        *b_nGenDressedLepton;   //!
   TBranch        *b_GenDressedLepton_eta;   //!
   TBranch        *b_GenDressedLepton_mass;   //!
   TBranch        *b_GenDressedLepton_phi;   //!
   TBranch        *b_GenDressedLepton_pt;   //!
   TBranch        *b_GenDressedLepton_pdgId;   //!
   TBranch        *b_GenDressedLepton_hasTauAnc;   //!
   TBranch        *b_nGenIsolatedPhoton;   //!
   TBranch        *b_GenIsolatedPhoton_eta;   //!
   TBranch        *b_GenIsolatedPhoton_mass;   //!
   TBranch        *b_GenIsolatedPhoton_phi;   //!
   TBranch        *b_GenIsolatedPhoton_pt;   //!
   TBranch        *b_TkMET_phi;   //!
   TBranch        *b_TkMET_pt;   //!
   TBranch        *b_TkMET_sumEt;   //!
   TBranch        *b_nTrigObj;   //!
   TBranch        *b_TrigObj_pt;   //!
   TBranch        *b_TrigObj_eta;   //!
   TBranch        *b_TrigObj_phi;   //!
   TBranch        *b_TrigObj_l1pt;   //!
   TBranch        *b_TrigObj_l1pt_2;   //!
   TBranch        *b_TrigObj_l2pt;   //!
   TBranch        *b_TrigObj_id;   //!
   TBranch        *b_TrigObj_l1iso;   //!
   TBranch        *b_TrigObj_l1charge;   //!
   TBranch        *b_TrigObj_filterBits;   //!
   TBranch        *b_genTtbarId;   //!
   TBranch        *b_nOtherPV;   //!
   TBranch        *b_OtherPV_z;   //!
   TBranch        *b_PV_ndof;   //!
   TBranch        *b_PV_x;   //!
   TBranch        *b_PV_y;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_PV_chi2;   //!
   TBranch        *b_PV_score;   //!
   TBranch        *b_PV_npvs;   //!
   TBranch        *b_PV_npvsGood;   //!
   TBranch        *b_nSV;   //!
   TBranch        *b_SV_dlen;   //!
   TBranch        *b_SV_dlenSig;   //!
   TBranch        *b_SV_dxy;   //!
   TBranch        *b_SV_dxySig;   //!
   TBranch        *b_SV_pAngle;   //!
   TBranch        *b_SV_charge;   //!
   TBranch        *b_Electron_genPartIdx;   //!
   TBranch        *b_Electron_genPartFlav;   //!
   TBranch        *b_FatJet_genJetAK8Idx;   //!
   TBranch        *b_FatJet_hadronFlavour;   //!
   TBranch        *b_FatJet_nBHadrons;   //!
   TBranch        *b_FatJet_nCHadrons;   //!
   TBranch        *b_GenJetAK8_partonFlavour;   //!
   TBranch        *b_GenJetAK8_hadronFlavour;   //!
   TBranch        *b_GenJet_partonFlavour;   //!
   TBranch        *b_GenJet_hadronFlavour;   //!
   TBranch        *b_GenVtx_t0;   //!
   TBranch        *b_Jet_genJetIdx;   //!
   TBranch        *b_Jet_hadronFlavour;   //!
   TBranch        *b_Jet_partonFlavour;   //!
   TBranch        *b_Muon_genPartIdx;   //!
   TBranch        *b_Muon_genPartFlav;   //!
   TBranch        *b_Photon_genPartIdx;   //!
   TBranch        *b_Photon_genPartFlav;   //!
   TBranch        *b_MET_fiducialGenPhi;   //!
   TBranch        *b_MET_fiducialGenPt;   //!
   TBranch        *b_Electron_cleanmask;   //!
   TBranch        *b_Jet_cleanmask;   //!
   TBranch        *b_Muon_cleanmask;   //!
   TBranch        *b_Photon_cleanmask;   //!
   TBranch        *b_SV_chi2;   //!
   TBranch        *b_SV_eta;   //!
   TBranch        *b_SV_mass;   //!
   TBranch        *b_SV_ndof;   //!
   TBranch        *b_SV_phi;   //!
   TBranch        *b_SV_pt;   //!
   TBranch        *b_SV_x;   //!
   TBranch        *b_SV_y;   //!
   TBranch        *b_SV_z;   //!
   TBranch        *b_SV_ntracks;   //!
   TBranch        *b_Flag_HBHENoiseFilter;   //!
   TBranch        *b_Flag_HBHENoiseIsoFilter;   //!
   TBranch        *b_Flag_CSCTightHaloFilter;   //!
   TBranch        *b_Flag_CSCTightHaloTrkMuUnvetoFilter;   //!
   TBranch        *b_Flag_CSCTightHalo2015Filter;   //!
   TBranch        *b_Flag_globalTightHalo2016Filter;   //!
   TBranch        *b_Flag_globalSuperTightHalo2016Filter;   //!
   TBranch        *b_Flag_HcalStripHaloFilter;   //!
   TBranch        *b_Flag_hcalLaserEventFilter;   //!
   TBranch        *b_Flag_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_Flag_EcalDeadCellBoundaryEnergyFilter;   //!
   TBranch        *b_Flag_ecalBadCalibFilter;   //!
   TBranch        *b_Flag_goodVertices;   //!
   TBranch        *b_Flag_eeBadScFilter;   //!
   TBranch        *b_Flag_ecalLaserCorrFilter;   //!
   TBranch        *b_Flag_trkPOGFilters;   //!
   TBranch        *b_Flag_chargedHadronTrackResolutionFilter;   //!
   TBranch        *b_Flag_muonBadTrackFilter;   //!
   TBranch        *b_Flag_BadChargedCandidateFilter;   //!
   TBranch        *b_Flag_BadPFMuonFilter;   //!
   TBranch        *b_Flag_BadPFMuonDzFilter;   //!
   TBranch        *b_Flag_hfNoisyHitsFilter;   //!
   TBranch        *b_Flag_BadChargedCandidateSummer16Filter;   //!
   TBranch        *b_Flag_BadPFMuonSummer16Filter;   //!
   TBranch        *b_Flag_trkPOG_manystripclus53X;   //!
   TBranch        *b_Flag_trkPOG_toomanystripclus53X;   //!
   TBranch        *b_Flag_trkPOG_logErrorTooManyClusters;   //!
   TBranch        *b_Flag_METFilters;   //!
   TBranch        *b_HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL;   //!
   TBranch        *b_HLT_DoubleEle25_CaloIdL_MW;   //!
   TBranch        *b_HLT_DoubleEle27_CaloIdL_MW;   //!
   TBranch        *b_HLT_DoubleEle33_CaloIdL_MW;   //!
   TBranch        *b_HLT_DoubleEle24_eta2p1_WPTight_Gsf;   //!
   TBranch        *b_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350;   //!
   TBranch        *b_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350;   //!
   TBranch        *b_HLT_Ele27_Ele37_CaloIdL_MW;   //!
   TBranch        *b_HLT_Mu27_Ele37_CaloIdL_MW;   //!
   TBranch        *b_HLT_DoublePhoton33_CaloIdL;   //!
   TBranch        *b_HLT_DoublePhoton70;   //!
   TBranch        *b_HLT_DoublePhoton85;   //!
   TBranch        *b_HLT_Ele20_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele15_WPLoose_Gsf;   //!
   TBranch        *b_HLT_Ele17_WPLoose_Gsf;   //!
   TBranch        *b_HLT_Ele20_WPLoose_Gsf;   //!
   TBranch        *b_HLT_Ele20_eta2p1_WPLoose_Gsf;   //!
   TBranch        *b_HLT_Ele27_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele28_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele30_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele32_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele35_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele35_WPTight_Gsf_L1EGMT;   //!
   TBranch        *b_HLT_Ele38_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele40_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele32_WPTight_Gsf_L1DoubleEG;   //!
   TBranch        *b_HLT_IsoMu20;   //!
   TBranch        *b_HLT_IsoMu24;   //!
   TBranch        *b_HLT_IsoTkMu24;   //!
   TBranch        *b_HLT_IsoMu24_eta2p1;   //!
   TBranch        *b_HLT_IsoMu27;   //!
   TBranch        *b_HLT_IsoMu30;   //!
   TBranch        *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;   //!
   TBranch        *b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL;   //!
   TBranch        *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;   //!
   TBranch        *b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ;   //!
   TBranch        *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;   //!
   TBranch        *b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8;   //!
   TBranch        *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;   //!
   TBranch        *b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8;   //!
   TBranch        *b_HLT_Mu25_TkMu0_Onia;   //!
   TBranch        *b_HLT_Mu20_TkMu0_Phi;   //!
   TBranch        *b_HLT_Mu25_TkMu0_Phi;   //!
   TBranch        *b_HLT_Mu12;   //!
   TBranch        *b_HLT_Mu15;   //!
   TBranch        *b_HLT_Mu20;   //!
   TBranch        *b_HLT_Mu27;   //!
   TBranch        *b_HLT_Mu50;   //!
   TBranch        *b_HLT_Mu55;   //!
   TBranch        *b_HLT_TkMu100;   //!
   TBranch        *b_HLT_PFMET110_PFMHT110_IDTight;   //!
   TBranch        *b_HLT_PFMET120_PFMHT120_IDTight;   //!
   TBranch        *b_HLT_PFMET130_PFMHT130_IDTight;   //!
   TBranch        *b_HLT_PFMET140_PFMHT140_IDTight;   //!
   TBranch        *b_HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1;   //!
   TBranch        *b_HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1;   //!
   TBranch        *b_HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1;   //!
   TBranch        *b_HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1;   //!
   TBranch        *b_HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1;   //!
   TBranch        *b_HLT_PFMET120_PFMHT120_IDTight_PFHT60;   //!
   TBranch        *b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60;   //!
   TBranch        *b_HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60;   //!
   TBranch        *b_HLT_PFMETTypeOne110_PFMHT110_IDTight;   //!
   TBranch        *b_HLT_PFMETTypeOne120_PFMHT120_IDTight;   //!
   TBranch        *b_HLT_PFMETTypeOne130_PFMHT130_IDTight;   //!
   TBranch        *b_HLT_PFMETTypeOne140_PFMHT140_IDTight;   //!
   TBranch        *b_HLT_PFMETNoMu110_PFMHTNoMu110_IDTight;   //!
   TBranch        *b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;   //!
   TBranch        *b_HLT_PFMETNoMu130_PFMHTNoMu130_IDTight;   //!
   TBranch        *b_HLT_PFMETNoMu140_PFMHTNoMu140_IDTight;   //!
   TBranch        *b_HLT_PFMET200_NotCleaned;   //!
   TBranch        *b_HLT_PFMET200_HBHECleaned;   //!
   TBranch        *b_HLT_PFMET250_HBHECleaned;   //!
   TBranch        *b_HLT_PFMET300_HBHECleaned;   //!
   TBranch        *b_HLT_PFMET200_HBHE_BeamHaloCleaned;   //!
   TBranch        *b_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned;   //!
   TBranch        *b_HLT_MET105_IsoTrk50;   //!
   TBranch        *b_HLT_MET120_IsoTrk50;   //!
   TBranch        *b_HLT_SingleJet30_Mu12_SinglePFJet40;   //!
   TBranch        *b_HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71;   //!
   TBranch        *b_HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71;   //!
   TBranch        *b_HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71;   //!
   TBranch        *b_HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71;   //!
   TBranch        *b_HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71;   //!
   TBranch        *b_HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71;   //!
   TBranch        *b_HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71;   //!
   TBranch        *b_HLT_Mu8_TrkIsoVVL;   //!
   TBranch        *b_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ;   //!
   TBranch        *b_HLT_Mu8_DiEle12_CaloIdL_TrackIdL;   //!
   TBranch        *b_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ;   //!
   TBranch        *b_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350;   //!
   TBranch        *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30;   //!
   TBranch        *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30;   //!
   TBranch        *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5;   //!
   TBranch        *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5;   //!
   TBranch        *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_HLT_Mu17_TrkIsoVVL;   //!
   TBranch        *b_HLT_Mu19_TrkIsoVVL;   //!
   TBranch        *b_HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL; //!
   TBranch        *b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b_HLT_Mu12_DoublePhoton20;   //!
   TBranch        *b_HLT_IsoMu24_TwoProngs35;   //!
   TBranch        *b_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned;   //!
   TBranch        *b_HLT_Ele28_eta2p1_WPTight_Gsf_HT150;   //!
   TBranch        *b_HLT_Ele28_HighEta_SC20_Mass55;   //!
   TBranch        *b_HLT_DoubleMu20_7_Mass0to30_Photon23;   //!
   TBranch        *b_HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5;   //!
   TBranch        *b_HLT_Ele15_IsoVVVL_PFHT450_PFMET50;   //!
   TBranch        *b_HLT_Ele15_IsoVVVL_PFHT450;   //!
   TBranch        *b_HLT_Ele50_IsoVVVL_PFHT450;   //!
   TBranch        *b_HLT_Ele15_IsoVVVL_PFHT600;   //!
   TBranch        *b_HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60;   //!
   TBranch        *b_HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60;   //!
   TBranch        *b_HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60;   //!
   TBranch        *b_HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5;   //!
   TBranch        *b_HLT_Mu15_IsoVVVL_PFHT450_PFMET50;   //!
   TBranch        *b_HLT_Mu15_IsoVVVL_PFHT450;   //!
   TBranch        *b_HLT_Mu50_IsoVVVL_PFHT450;   //!
   TBranch        *b_HLT_Mu15_IsoVVVL_PFHT600;   //!
   TBranch        *b_HLT_DoubleIsoMu20_eta2p1;   //!
   TBranch        *b_HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx;   //!
   TBranch        *b_HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx;   //!
   TBranch        *b_HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx;   //!
   TBranch        *b_HLT_Mu8;   //!
   TBranch        *b_HLT_Mu17;   //!
   TBranch        *b_HLT_Mu19;   //!
   TBranch        *b_HLT_Mu17_Photon30_IsoCaloId;   //!
   TBranch        *b_HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30;   //!
   TBranch        *b_HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30;   //!
   TBranch        *b_HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30;   //!
   TBranch        *b_HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30;   //!
   TBranch        *b_HLT_Ele8_CaloIdM_TrackIdM_PFJet30;   //!
   TBranch        *b_HLT_Ele17_CaloIdM_TrackIdM_PFJet30;   //!
   TBranch        *b_HLT_Ele23_CaloIdM_TrackIdM_PFJet30;   //!
   TBranch        *b_HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165;   //!
   TBranch        *b_HLT_Ele115_CaloIdVT_GsfTrkIdT;   //!
   TBranch        *b_HLT_Ele135_CaloIdVT_GsfTrkIdT;   //!
   TBranch        *b_HLT_Ele145_CaloIdVT_GsfTrkIdT;   //!
   TBranch        *b_HLT_Ele200_CaloIdVT_GsfTrkIdT;   //!
   TBranch        *b_HLT_Ele250_CaloIdVT_GsfTrkIdT;   //!
   TBranch        *b_HLT_Ele300_CaloIdVT_GsfTrkIdT;   //!
   TBranch        *b_HLT_ECALHT800;   //!
   TBranch        *b_HLT_Random;   //!
   TBranch        *b_HLT_SinglePhoton10_Eta3p1ForPPRef;   //!
   TBranch        *b_HLT_SinglePhoton20_Eta3p1ForPPRef;   //!
   TBranch        *b_HLT_SinglePhoton30_Eta3p1ForPPRef;   //!
   TBranch        *b_HLT_EcalCalibration;   //!
   TBranch        *b_HLT_IsoTrackHB;   //!
   TBranch        *b_HLT_IsoTrackHE;   //!
   TBranch        *b_HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr;   //!
   TBranch        *b_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;   //!
   TBranch        *b_HLT_IsoMu27_MET90;   //!
   TBranch        *b_HLT_PFMET100_PFMHT100_IDTight_PFHT60;   //!
   TBranch        *b_HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60;   //!
   TBranch        *b_HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60;   //!
   TBranch        *b_HLT_Mu18_Mu9_SameSign;   //!
   TBranch        *b_HLT_Mu18_Mu9_SameSign_DZ;   //!
   TBranch        *b_HLT_Mu18_Mu9;   //!
   TBranch        *b_HLT_Mu18_Mu9_DZ;   //!
   TBranch        *b_HLT_Mu20_Mu10_SameSign;   //!
   TBranch        *b_HLT_Mu20_Mu10_SameSign_DZ;   //!
   TBranch        *b_HLT_Mu20_Mu10;   //!
   TBranch        *b_HLT_Mu20_Mu10_DZ;   //!
   TBranch        *b_HLT_Mu23_Mu12_SameSign;   //!
   TBranch        *b_HLT_Mu23_Mu12_SameSign_DZ;   //!
   TBranch        *b_HLT_Mu23_Mu12;   //!
   TBranch        *b_HLT_Mu23_Mu12_DZ;   //!
   TBranch        *b_HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05;   //!
   TBranch        *b_HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi;   //!
   TBranch        *b_HLT_TrkMu6NoFiltersNoVtx;   //!
   TBranch        *b_HLT_TrkMu16NoFiltersNoVtx;   //!
   TBranch        *b_HLT_DoubleTrkMu_16_6_NoFiltersNoVtx;   //!
   TBranch        *b_HLTriggerFinalPath;   //!
   TBranch        *b_L1simulation_step;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_pass_selection;   //!
   TBranch        *b_photon_selection;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_lep1_pid;   //!
   TBranch        *b_lep2_pid;   //!
   TBranch        *b_lep1pt;   //!
   TBranch        *b_lep2pt;   //!
   TBranch        *b_lep1eta;   //!
   TBranch        *b_lep2eta;   //!
   TBranch        *b_lep1phi;   //!
   TBranch        *b_lep2phi;   //!
   TBranch        *b_drll;   //!
   TBranch        *b_lep1_charge;   //!
   TBranch        *b_lep2_charge;   //!
   TBranch        *b_lep1_isprompt;   //!
   TBranch        *b_lep2_isprompt;   //!
   TBranch        *b_lep1_is_tight;   //!
   TBranch        *b_lep2_is_tight;   //!
   TBranch        *b_n_loose_mu;   //!
   TBranch        *b_n_loose_ele;   //!
   TBranch        *b_n_leptons;   //!
   TBranch        *b_n_photon;   //!
   TBranch        *b_photonet;   //!
   TBranch        *b_photoneta;   //!
   TBranch        *b_photonphi;   //!
   TBranch        *b_photonchiso;   //!
   TBranch        *b_drl1a;   //!
   TBranch        *b_drl2a;   //!
   TBranch        *b_photon_isprompt;   //!
   TBranch        *b_photon_gen_matching;   //!
   TBranch        *b_mll;   //!
   TBranch        *b_mllg;   //!
   TBranch        *b_ptll;   //!
   TBranch        *b_mt;   //!
   TBranch        *b_puppimt;   //!
   TBranch        *b_met;   //!
   TBranch        *b_metup;   //!
   TBranch        *b_puppimet;   //!
   TBranch        *b_puppimetphi;   //!
   TBranch        *b_rawmet;   //!
   TBranch        *b_rawmetphi;   //!
   TBranch        *b_metphi;   //!
   TBranch        *b_gen_weight;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_ntruepu;   //!
   TBranch        *b_MET_pass;   //!
   TBranch        *b_npvs;   //!
   TBranch        *b_n_bjets_loose_deepcsv;   //!
   TBranch        *b_n_bjets_loose_deepFlavB;   //!
   TBranch        *b_n_bjets20_loose_deepcsv;   //!
   TBranch        *b_n_bjets20_loose_deepFlavB;   //!
   TBranch        *b_n_bjets_medium_deepcsv;   //!
   TBranch        *b_n_bjets_medium_deepFlavB;   //!
   TBranch        *b_n_bjets20_medium_deepcsv;   //!
   TBranch        *b_n_bjets20_medium_deepFlavB;   //!
   TBranch        *b_njets50;   //!
   TBranch        *b_njets40;   //!
   TBranch        *b_njets30;   //!
   TBranch        *b_njets20;   //!
   TBranch        *b_njets50_pc;   //!
   TBranch        *b_njets40_pc;   //!
   TBranch        *b_njets30_pc;   //!
   TBranch        *b_njets20_pc;   //!
   TBranch        *b_n_bjets_loose_deepcsv_pc;   //!
   TBranch        *b_n_bjets_loose_deepFlavB_pc;   //!
   TBranch        *b_n_bjets20_loose_deepcsv_pc;   //!
   TBranch        *b_n_bjets20_loose_deepFlavB_pc;   //!
   TBranch        *b_n_bjets_medium_deepcsv_pc;   //!
   TBranch        *b_n_bjets_medium_deepFlavB_pc;   //!
   TBranch        *b_n_bjets20_medium_deepcsv_pc;   //!
   TBranch        *b_n_bjets20_medium_deepFlavB_pc;   //!
   TBranch        *b_Jet_pt_raw;   //!
   TBranch        *b_Jet_pt_nom;   //!
   TBranch        *b_Jet_mass_raw;   //!
   TBranch        *b_Jet_mass_nom;   //!
   TBranch        *b_Jet_corr_JEC;   //!
   TBranch        *b_Jet_corr_JER;   //!
   TBranch        *b_MET_T1_pt;   //!
   TBranch        *b_MET_T1_phi;   //!
   TBranch        *b_MET_T1Smear_pt;   //!
   TBranch        *b_MET_T1Smear_phi;   //!
   TBranch        *b_Jet_pt_jer0Up;   //!
   TBranch        *b_Jet_mass_jer0Up;   //!
   TBranch        *b_MET_T1_pt_jer0Up;   //!
   TBranch        *b_MET_T1_phi_jer0Up;   //!
   TBranch        *b_MET_T1Smear_pt_jer0Up;   //!
   TBranch        *b_MET_T1Smear_phi_jer0Up;   //!
   TBranch        *b_Jet_pt_jer1Up;   //!
   TBranch        *b_Jet_mass_jer1Up;   //!
   TBranch        *b_MET_T1_pt_jer1Up;   //!
   TBranch        *b_MET_T1_phi_jer1Up;   //!
   TBranch        *b_MET_T1Smear_pt_jer1Up;   //!
   TBranch        *b_MET_T1Smear_phi_jer1Up;   //!
   TBranch        *b_Jet_pt_jer2Up;   //!
   TBranch        *b_Jet_mass_jer2Up;   //!
   TBranch        *b_MET_T1_pt_jer2Up;   //!
   TBranch        *b_MET_T1_phi_jer2Up;   //!
   TBranch        *b_MET_T1Smear_pt_jer2Up;   //!
   TBranch        *b_MET_T1Smear_phi_jer2Up;   //!
   TBranch        *b_Jet_pt_jer3Up;   //!
   TBranch        *b_Jet_mass_jer3Up;   //!
   TBranch        *b_MET_T1_pt_jer3Up;   //!
   TBranch        *b_MET_T1_phi_jer3Up;   //!
   TBranch        *b_MET_T1Smear_pt_jer3Up;   //!
   TBranch        *b_MET_T1Smear_phi_jer3Up;   //!
   TBranch        *b_Jet_pt_jer4Up;   //!
   TBranch        *b_Jet_mass_jer4Up;   //!
   TBranch        *b_MET_T1_pt_jer4Up;   //!
   TBranch        *b_MET_T1_phi_jer4Up;   //!
   TBranch        *b_MET_T1Smear_pt_jer4Up;   //!
   TBranch        *b_MET_T1Smear_phi_jer4Up;   //!
   TBranch        *b_Jet_pt_jer5Up;   //!
   TBranch        *b_Jet_mass_jer5Up;   //!
   TBranch        *b_MET_T1_pt_jer5Up;   //!
   TBranch        *b_MET_T1_phi_jer5Up;   //!
   TBranch        *b_MET_T1Smear_pt_jer5Up;   //!
   TBranch        *b_MET_T1Smear_phi_jer5Up;   //!
   TBranch        *b_Jet_pt_jesTotalUp;   //!
   TBranch        *b_Jet_mass_jesTotalUp;   //!
   TBranch        *b_MET_T1_pt_jesTotalUp;   //!
   TBranch        *b_MET_T1_phi_jesTotalUp;   //!
   TBranch        *b_MET_T1Smear_pt_jesTotalUp;   //!
   TBranch        *b_MET_T1Smear_phi_jesTotalUp;   //!
   TBranch        *b_Jet_pt_jesHEMIssueUp;   //!
   TBranch        *b_Jet_mass_jesHEMIssueUp;   //!
   TBranch        *b_MET_T1_pt_jesHEMIssueUp;   //!
   TBranch        *b_MET_T1_phi_jesHEMIssueUp;   //!
   TBranch        *b_MET_T1Smear_pt_jesHEMIssueUp;   //!
   TBranch        *b_MET_T1Smear_phi_jesHEMIssueUp;   //!
   TBranch        *b_MET_T1_pt_unclustEnUp;   //!
   TBranch        *b_MET_T1_phi_unclustEnUp;   //!
   TBranch        *b_MET_T1Smear_pt_unclustEnUp;   //!
   TBranch        *b_MET_T1Smear_phi_unclustEnUp;   //!
   TBranch        *b_Jet_pt_jer0Down;   //!
   TBranch        *b_Jet_mass_jer0Down;   //!
   TBranch        *b_MET_T1_pt_jer0Down;   //!
   TBranch        *b_MET_T1_phi_jer0Down;   //!
   TBranch        *b_MET_T1Smear_pt_jer0Down;   //!
   TBranch        *b_MET_T1Smear_phi_jer0Down;   //!
   TBranch        *b_Jet_pt_jer1Down;   //!
   TBranch        *b_Jet_mass_jer1Down;   //!
   TBranch        *b_MET_T1_pt_jer1Down;   //!
   TBranch        *b_MET_T1_phi_jer1Down;   //!
   TBranch        *b_MET_T1Smear_pt_jer1Down;   //!
   TBranch        *b_MET_T1Smear_phi_jer1Down;   //!
   TBranch        *b_Jet_pt_jer2Down;   //!
   TBranch        *b_Jet_mass_jer2Down;   //!
   TBranch        *b_MET_T1_pt_jer2Down;   //!
   TBranch        *b_MET_T1_phi_jer2Down;   //!
   TBranch        *b_MET_T1Smear_pt_jer2Down;   //!
   TBranch        *b_MET_T1Smear_phi_jer2Down;   //!
   TBranch        *b_Jet_pt_jer3Down;   //!
   TBranch        *b_Jet_mass_jer3Down;   //!
   TBranch        *b_MET_T1_pt_jer3Down;   //!
   TBranch        *b_MET_T1_phi_jer3Down;   //!
   TBranch        *b_MET_T1Smear_pt_jer3Down;   //!
   TBranch        *b_MET_T1Smear_phi_jer3Down;   //!
   TBranch        *b_Jet_pt_jer4Down;   //!
   TBranch        *b_Jet_mass_jer4Down;   //!
   TBranch        *b_MET_T1_pt_jer4Down;   //!
   TBranch        *b_MET_T1_phi_jer4Down;   //!
   TBranch        *b_MET_T1Smear_pt_jer4Down;   //!
   TBranch        *b_MET_T1Smear_phi_jer4Down;   //!
   TBranch        *b_Jet_pt_jer5Down;   //!
   TBranch        *b_Jet_mass_jer5Down;   //!
   TBranch        *b_MET_T1_pt_jer5Down;   //!
   TBranch        *b_MET_T1_phi_jer5Down;   //!
   TBranch        *b_MET_T1Smear_pt_jer5Down;   //!
   TBranch        *b_MET_T1Smear_phi_jer5Down;   //!
   TBranch        *b_Jet_pt_jesTotalDown;   //!
   TBranch        *b_Jet_mass_jesTotalDown;   //!
   TBranch        *b_MET_T1_pt_jesTotalDown;   //!
   TBranch        *b_MET_T1_phi_jesTotalDown;   //!
   TBranch        *b_MET_T1Smear_pt_jesTotalDown;   //!
   TBranch        *b_MET_T1Smear_phi_jesTotalDown;   //!
   TBranch        *b_Jet_pt_jesHEMIssueDown;   //!
   TBranch        *b_Jet_mass_jesHEMIssueDown;   //!
   TBranch        *b_MET_T1_pt_jesHEMIssueDown;   //!
   TBranch        *b_MET_T1_phi_jesHEMIssueDown;   //!
   TBranch        *b_MET_T1Smear_pt_jesHEMIssueDown;   //!
   TBranch        *b_MET_T1Smear_phi_jesHEMIssueDown;   //!
   TBranch        *b_MET_T1_pt_unclustEnDown;   //!
   TBranch        *b_MET_T1_phi_unclustEnDown;   //!
   TBranch        *b_MET_T1Smear_pt_unclustEnDown;   //!
   TBranch        *b_MET_T1Smear_phi_unclustEnDown;   //!
   TBranch        *b_puWeight;   //!
   TBranch        *b_puWeightUp;   //!
   TBranch        *b_puWeightDown;   //!

   TString m_dataset;
   chain_WWg(TTree *tree=0,TString dataset="");
   virtual ~chain_WWg();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString name,double nevents,TString year,bool flag);
   virtual float    get_rochester_scale(bool isdata, float charge_temp, float pt, float eta, float phi, int nl, float r1);
   virtual Float_t  delta_R(Float_t eta1, Float_t phi1, Float_t eta2, Float_t phi2);
   virtual int      get_index(float lep1pt);
   virtual void     Init();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     endJob();

   RoccoR rc;
 private:
     TTree *ExTree;
     TFile *fout;
     float scalef;
     float ele_id_scale,ele_reco_scale,muon_id_scale,muon_iso_scale,photon_id_scale,photon_veto_scale;
     float ele_id_scale_Up,ele_reco_scale_Up,muon_id_scale_Up,muon_iso_scale_Up,photon_id_scale_Up,photon_veto_scale_Up;
     float ele_id_scale_Down,ele_reco_scale_Down,muon_id_scale_Down,muon_iso_scale_Down,photon_id_scale_Down,photon_veto_scale_Down;
     float btag_weight_medium,btag_weight_medium_up,btag_weight_medium_down;
     float btag_weight_loose,btag_weight_loose_up,btag_weight_loose_down;
     float muon1_rochester;
     float phiVlep,yVlep;
     Bool_t HLT_ee,HLT_mm,HLT_emu;
};

#endif

#ifdef chain_WWg_cxx
chain_WWg::chain_WWg(TTree *tree,TString dataset) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("Events",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("Events","");
      chain->Add("cutlep-outTTGJets18.root/Events");
      chain->Add("cutlep-outVV18.root/Events");
      tree = chain;
#endif // SINGLE_TREE

   }
   m_dataset=dataset;
   Init(tree);
}

chain_WWg::~chain_WWg()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t chain_WWg::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t chain_WWg::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void chain_WWg::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fout = new TFile("/home/pku/anying/cms/rootfiles/"+m_dataset, "RECREATE");
   ExTree = fChain->CloneTree(0);
   ExTree->Branch("scalef",&scalef,"scalef/F");
   ExTree->Branch("muon1_rochester",&muon1_rochester,"muon1_rochester/F");
   ExTree->Branch("phiVlep",&phiVlep,"phiVlep/F");
   ExTree->Branch("yVlep",&yVlep,"yVlep/F");
   ExTree->Branch("ele_id_scale",&ele_id_scale,"ele_id_scale/F");
   ExTree->Branch("ele_id_scale_Up",&ele_id_scale_Up,"ele_id_scale_Up/F");
   ExTree->Branch("ele_id_scale_Down",&ele_id_scale_Down,"ele_id_scale_Down/F");
   ExTree->Branch("ele_reco_scale",&ele_reco_scale,"ele_reco_scale/F");
   ExTree->Branch("ele_reco_scale_Up",&ele_reco_scale_Up,"ele_reco_scale_Up/F");
   ExTree->Branch("ele_reco_scale_Down",&ele_reco_scale_Down,"ele_reco_scale_Down/F");
   ExTree->Branch("muon_id_scale",&muon_id_scale,"muon_id_scale/F");
   ExTree->Branch("muon_id_scale_Up",&muon_id_scale_Up,"muon_id_scale_Up/F");
   ExTree->Branch("muon_id_scale_Down",&muon_id_scale_Down,"muon_id_scale_Down/F");
   ExTree->Branch("muon_iso_scale",&muon_iso_scale,"muon_iso_scale/F");
   ExTree->Branch("muon_iso_scale_Up",&muon_iso_scale_Up,"muon_iso_scale_Up/F");
   ExTree->Branch("muon_iso_scale_Down",&muon_iso_scale_Down,"muon_iso_scale_Down/F");
   ExTree->Branch("photon_id_scale",&photon_id_scale,"photon_id_scale/F");
   ExTree->Branch("photon_id_scale_Up",&photon_id_scale_Up,"photon_id_scale_Up/F");
   ExTree->Branch("photon_id_scale_Down",&photon_id_scale_Down,"photon_id_scale_Down/F");
   ExTree->Branch("photon_veto_scale",&photon_veto_scale,"photon_veto_scale/F");
   ExTree->Branch("photon_veto_scale_Up",&photon_veto_scale_Up,"photon_veto_scale_Up/F");
   ExTree->Branch("photon_veto_scale_Down",&photon_veto_scale_Down,"photon_veto_scale_Down/F");
   ExTree->Branch("btag_weight_medium",&btag_weight_medium,"btag_weight_medium/F");
   ExTree->Branch("btag_weight_medium_up",&btag_weight_medium_up,"btag_weight_medium_up/F");
   ExTree->Branch("btag_weight_medium_down",&btag_weight_medium_down,"btag_weight_medium_down/F");
   ExTree->Branch("btag_weight_loose",&btag_weight_loose,"btag_weight_loose/F");
   ExTree->Branch("btag_weight_loose_up",&btag_weight_loose_up,"btag_weight_loose_up/F");
   ExTree->Branch("btag_weight_loose_down",&btag_weight_loose_down,"btag_weight_loose_down/F");
   ExTree->Branch("HLT_ee",&HLT_ee,"HLT_ee/B");
   ExTree->Branch("HLT_mm",&HLT_mm,"HLT_mm/B");
   ExTree->Branch("HLT_emu",&HLT_emu,"HLT_emu/B");

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("luminosityBlock", &luminosityBlock, &b_luminosityBlock);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("btagWeight_CSVV2", &btagWeight_CSVV2, &b_btagWeight_CSVV2);
   fChain->SetBranchAddress("btagWeight_DeepCSVB", &btagWeight_DeepCSVB, &b_btagWeight_DeepCSVB);
   fChain->SetBranchAddress("nCorrT1METJet", &nCorrT1METJet, &b_nCorrT1METJet);
   fChain->SetBranchAddress("CorrT1METJet_area", CorrT1METJet_area, &b_CorrT1METJet_area);
   fChain->SetBranchAddress("CorrT1METJet_eta", CorrT1METJet_eta, &b_CorrT1METJet_eta);
   fChain->SetBranchAddress("CorrT1METJet_muonSubtrFactor", CorrT1METJet_muonSubtrFactor, &b_CorrT1METJet_muonSubtrFactor);
   fChain->SetBranchAddress("CorrT1METJet_phi", CorrT1METJet_phi, &b_CorrT1METJet_phi);
   fChain->SetBranchAddress("CorrT1METJet_rawPt", CorrT1METJet_rawPt, &b_CorrT1METJet_rawPt);
   fChain->SetBranchAddress("DeepMETResolutionTune_phi", &DeepMETResolutionTune_phi, &b_DeepMETResolutionTune_phi);
   fChain->SetBranchAddress("DeepMETResolutionTune_pt", &DeepMETResolutionTune_pt, &b_DeepMETResolutionTune_pt);
   fChain->SetBranchAddress("DeepMETResponseTune_phi", &DeepMETResponseTune_phi, &b_DeepMETResponseTune_phi);
   fChain->SetBranchAddress("DeepMETResponseTune_pt", &DeepMETResponseTune_pt, &b_DeepMETResponseTune_pt);
   fChain->SetBranchAddress("nElectron", &nElectron, &b_nElectron);
   fChain->SetBranchAddress("Electron_dEscaleDown", Electron_dEscaleDown, &b_Electron_dEscaleDown);
   fChain->SetBranchAddress("Electron_dEscaleUp", Electron_dEscaleUp, &b_Electron_dEscaleUp);
   fChain->SetBranchAddress("Electron_dEsigmaDown", Electron_dEsigmaDown, &b_Electron_dEsigmaDown);
   fChain->SetBranchAddress("Electron_dEsigmaUp", Electron_dEsigmaUp, &b_Electron_dEsigmaUp);
   fChain->SetBranchAddress("Electron_deltaEtaSC", Electron_deltaEtaSC, &b_Electron_deltaEtaSC);
   fChain->SetBranchAddress("Electron_dr03EcalRecHitSumEt", Electron_dr03EcalRecHitSumEt, &b_Electron_dr03EcalRecHitSumEt);
   fChain->SetBranchAddress("Electron_dr03HcalDepth1TowerSumEt", Electron_dr03HcalDepth1TowerSumEt, &b_Electron_dr03HcalDepth1TowerSumEt);
   fChain->SetBranchAddress("Electron_dr03TkSumPt", Electron_dr03TkSumPt, &b_Electron_dr03TkSumPt);
   fChain->SetBranchAddress("Electron_dr03TkSumPtHEEP", Electron_dr03TkSumPtHEEP, &b_Electron_dr03TkSumPtHEEP);
   fChain->SetBranchAddress("Electron_dxy", Electron_dxy, &b_Electron_dxy);
   fChain->SetBranchAddress("Electron_dxyErr", Electron_dxyErr, &b_Electron_dxyErr);
   fChain->SetBranchAddress("Electron_dz", Electron_dz, &b_Electron_dz);
   fChain->SetBranchAddress("Electron_dzErr", Electron_dzErr, &b_Electron_dzErr);
   fChain->SetBranchAddress("Electron_eCorr", Electron_eCorr, &b_Electron_eCorr);
   fChain->SetBranchAddress("Electron_eInvMinusPInv", Electron_eInvMinusPInv, &b_Electron_eInvMinusPInv);
   fChain->SetBranchAddress("Electron_energyErr", Electron_energyErr, &b_Electron_energyErr);
   fChain->SetBranchAddress("Electron_eta", Electron_eta, &b_Electron_eta);
   fChain->SetBranchAddress("Electron_hoe", Electron_hoe, &b_Electron_hoe);
   fChain->SetBranchAddress("Electron_ip3d", Electron_ip3d, &b_Electron_ip3d);
   fChain->SetBranchAddress("Electron_jetPtRelv2", Electron_jetPtRelv2, &b_Electron_jetPtRelv2);
   fChain->SetBranchAddress("Electron_jetRelIso", Electron_jetRelIso, &b_Electron_jetRelIso);
   fChain->SetBranchAddress("Electron_mass", Electron_mass, &b_Electron_mass);
   fChain->SetBranchAddress("Electron_miniPFRelIso_all", Electron_miniPFRelIso_all, &b_Electron_miniPFRelIso_all);
   fChain->SetBranchAddress("Electron_miniPFRelIso_chg", Electron_miniPFRelIso_chg, &b_Electron_miniPFRelIso_chg);
   fChain->SetBranchAddress("Electron_mvaFall17V2Iso", Electron_mvaFall17V2Iso, &b_Electron_mvaFall17V2Iso);
   fChain->SetBranchAddress("Electron_mvaFall17V2noIso", Electron_mvaFall17V2noIso, &b_Electron_mvaFall17V2noIso);
   fChain->SetBranchAddress("Electron_pfRelIso03_all", Electron_pfRelIso03_all, &b_Electron_pfRelIso03_all);
   fChain->SetBranchAddress("Electron_pfRelIso03_chg", Electron_pfRelIso03_chg, &b_Electron_pfRelIso03_chg);
   fChain->SetBranchAddress("Electron_phi", Electron_phi, &b_Electron_phi);
   fChain->SetBranchAddress("Electron_pt", Electron_pt, &b_Electron_pt);
   fChain->SetBranchAddress("Electron_r9", Electron_r9, &b_Electron_r9);
   fChain->SetBranchAddress("Electron_scEtOverPt", Electron_scEtOverPt, &b_Electron_scEtOverPt);
   fChain->SetBranchAddress("Electron_sieie", Electron_sieie, &b_Electron_sieie);
   fChain->SetBranchAddress("Electron_sip3d", Electron_sip3d, &b_Electron_sip3d);
   fChain->SetBranchAddress("Electron_mvaTTH", Electron_mvaTTH, &b_Electron_mvaTTH);
   fChain->SetBranchAddress("Electron_charge", Electron_charge, &b_Electron_charge);
   fChain->SetBranchAddress("Electron_cutBased", Electron_cutBased, &b_Electron_cutBased);
   fChain->SetBranchAddress("Electron_jetIdx", Electron_jetIdx, &b_Electron_jetIdx);
   fChain->SetBranchAddress("Electron_pdgId", Electron_pdgId, &b_Electron_pdgId);
   fChain->SetBranchAddress("Electron_photonIdx", Electron_photonIdx, &b_Electron_photonIdx);
   fChain->SetBranchAddress("Electron_tightCharge", Electron_tightCharge, &b_Electron_tightCharge);
   fChain->SetBranchAddress("Electron_vidNestedWPBitmap", Electron_vidNestedWPBitmap, &b_Electron_vidNestedWPBitmap);
   fChain->SetBranchAddress("Electron_vidNestedWPBitmapHEEP", Electron_vidNestedWPBitmapHEEP, &b_Electron_vidNestedWPBitmapHEEP);
   fChain->SetBranchAddress("Electron_convVeto", Electron_convVeto, &b_Electron_convVeto);
   fChain->SetBranchAddress("Electron_cutBased_HEEP", Electron_cutBased_HEEP, &b_Electron_cutBased_HEEP);
   fChain->SetBranchAddress("Electron_isPFcand", Electron_isPFcand, &b_Electron_isPFcand);
   fChain->SetBranchAddress("Electron_jetNDauCharged", Electron_jetNDauCharged, &b_Electron_jetNDauCharged);
   fChain->SetBranchAddress("Electron_lostHits", Electron_lostHits, &b_Electron_lostHits);
   fChain->SetBranchAddress("Electron_mvaFall17V2Iso_WP80", Electron_mvaFall17V2Iso_WP80, &b_Electron_mvaFall17V2Iso_WP80);
   fChain->SetBranchAddress("Electron_mvaFall17V2Iso_WP90", Electron_mvaFall17V2Iso_WP90, &b_Electron_mvaFall17V2Iso_WP90);
   fChain->SetBranchAddress("Electron_mvaFall17V2Iso_WPL", Electron_mvaFall17V2Iso_WPL, &b_Electron_mvaFall17V2Iso_WPL);
   fChain->SetBranchAddress("Electron_mvaFall17V2noIso_WP80", Electron_mvaFall17V2noIso_WP80, &b_Electron_mvaFall17V2noIso_WP80);
   fChain->SetBranchAddress("Electron_mvaFall17V2noIso_WP90", Electron_mvaFall17V2noIso_WP90, &b_Electron_mvaFall17V2noIso_WP90);
   fChain->SetBranchAddress("Electron_mvaFall17V2noIso_WPL", Electron_mvaFall17V2noIso_WPL, &b_Electron_mvaFall17V2noIso_WPL);
   fChain->SetBranchAddress("Electron_seedGain", Electron_seedGain, &b_Electron_seedGain);
   fChain->SetBranchAddress("nFatJet", &nFatJet, &b_nFatJet);
   fChain->SetBranchAddress("FatJet_area", FatJet_area, &b_FatJet_area);
   fChain->SetBranchAddress("FatJet_btagCSVV2", FatJet_btagCSVV2, &b_FatJet_btagCSVV2);
   fChain->SetBranchAddress("FatJet_btagDDBvLV2", FatJet_btagDDBvLV2, &b_FatJet_btagDDBvLV2);
   fChain->SetBranchAddress("FatJet_btagDDCvBV2", FatJet_btagDDCvBV2, &b_FatJet_btagDDCvBV2);
   fChain->SetBranchAddress("FatJet_btagDDCvLV2", FatJet_btagDDCvLV2, &b_FatJet_btagDDCvLV2);
   fChain->SetBranchAddress("FatJet_btagDeepB", FatJet_btagDeepB, &b_FatJet_btagDeepB);
   fChain->SetBranchAddress("FatJet_btagHbb", FatJet_btagHbb, &b_FatJet_btagHbb);
   fChain->SetBranchAddress("FatJet_deepTagMD_H4qvsQCD", FatJet_deepTagMD_H4qvsQCD, &b_FatJet_deepTagMD_H4qvsQCD);
   fChain->SetBranchAddress("FatJet_deepTagMD_HbbvsQCD", FatJet_deepTagMD_HbbvsQCD, &b_FatJet_deepTagMD_HbbvsQCD);
   fChain->SetBranchAddress("FatJet_deepTagMD_TvsQCD", FatJet_deepTagMD_TvsQCD, &b_FatJet_deepTagMD_TvsQCD);
   fChain->SetBranchAddress("FatJet_deepTagMD_WvsQCD", FatJet_deepTagMD_WvsQCD, &b_FatJet_deepTagMD_WvsQCD);
   fChain->SetBranchAddress("FatJet_deepTagMD_ZHbbvsQCD", FatJet_deepTagMD_ZHbbvsQCD, &b_FatJet_deepTagMD_ZHbbvsQCD);
   fChain->SetBranchAddress("FatJet_deepTagMD_ZHccvsQCD", FatJet_deepTagMD_ZHccvsQCD, &b_FatJet_deepTagMD_ZHccvsQCD);
   fChain->SetBranchAddress("FatJet_deepTagMD_ZbbvsQCD", FatJet_deepTagMD_ZbbvsQCD, &b_FatJet_deepTagMD_ZbbvsQCD);
   fChain->SetBranchAddress("FatJet_deepTagMD_ZvsQCD", FatJet_deepTagMD_ZvsQCD, &b_FatJet_deepTagMD_ZvsQCD);
   fChain->SetBranchAddress("FatJet_deepTagMD_bbvsLight", FatJet_deepTagMD_bbvsLight, &b_FatJet_deepTagMD_bbvsLight);
   fChain->SetBranchAddress("FatJet_deepTagMD_ccvsLight", FatJet_deepTagMD_ccvsLight, &b_FatJet_deepTagMD_ccvsLight);
   fChain->SetBranchAddress("FatJet_deepTag_H", FatJet_deepTag_H, &b_FatJet_deepTag_H);
   fChain->SetBranchAddress("FatJet_deepTag_QCD", FatJet_deepTag_QCD, &b_FatJet_deepTag_QCD);
   fChain->SetBranchAddress("FatJet_deepTag_QCDothers", FatJet_deepTag_QCDothers, &b_FatJet_deepTag_QCDothers);
   fChain->SetBranchAddress("FatJet_deepTag_TvsQCD", FatJet_deepTag_TvsQCD, &b_FatJet_deepTag_TvsQCD);
   fChain->SetBranchAddress("FatJet_deepTag_WvsQCD", FatJet_deepTag_WvsQCD, &b_FatJet_deepTag_WvsQCD);
   fChain->SetBranchAddress("FatJet_deepTag_ZvsQCD", FatJet_deepTag_ZvsQCD, &b_FatJet_deepTag_ZvsQCD);
   fChain->SetBranchAddress("FatJet_eta", FatJet_eta, &b_FatJet_eta);
   fChain->SetBranchAddress("FatJet_mass", FatJet_mass, &b_FatJet_mass);
   fChain->SetBranchAddress("FatJet_msoftdrop", FatJet_msoftdrop, &b_FatJet_msoftdrop);
   fChain->SetBranchAddress("FatJet_n2b1", FatJet_n2b1, &b_FatJet_n2b1);
   fChain->SetBranchAddress("FatJet_n3b1", FatJet_n3b1, &b_FatJet_n3b1);
   fChain->SetBranchAddress("FatJet_particleNetMD_QCD", FatJet_particleNetMD_QCD, &b_FatJet_particleNetMD_QCD);
   fChain->SetBranchAddress("FatJet_particleNetMD_Xbb", FatJet_particleNetMD_Xbb, &b_FatJet_particleNetMD_Xbb);
   fChain->SetBranchAddress("FatJet_particleNetMD_Xcc", FatJet_particleNetMD_Xcc, &b_FatJet_particleNetMD_Xcc);
   fChain->SetBranchAddress("FatJet_particleNetMD_Xqq", FatJet_particleNetMD_Xqq, &b_FatJet_particleNetMD_Xqq);
   fChain->SetBranchAddress("FatJet_particleNet_H4qvsQCD", FatJet_particleNet_H4qvsQCD, &b_FatJet_particleNet_H4qvsQCD);
   fChain->SetBranchAddress("FatJet_particleNet_HbbvsQCD", FatJet_particleNet_HbbvsQCD, &b_FatJet_particleNet_HbbvsQCD);
   fChain->SetBranchAddress("FatJet_particleNet_HccvsQCD", FatJet_particleNet_HccvsQCD, &b_FatJet_particleNet_HccvsQCD);
   fChain->SetBranchAddress("FatJet_particleNet_QCD", FatJet_particleNet_QCD, &b_FatJet_particleNet_QCD);
   fChain->SetBranchAddress("FatJet_particleNet_TvsQCD", FatJet_particleNet_TvsQCD, &b_FatJet_particleNet_TvsQCD);
   fChain->SetBranchAddress("FatJet_particleNet_WvsQCD", FatJet_particleNet_WvsQCD, &b_FatJet_particleNet_WvsQCD);
   fChain->SetBranchAddress("FatJet_particleNet_ZvsQCD", FatJet_particleNet_ZvsQCD, &b_FatJet_particleNet_ZvsQCD);
   fChain->SetBranchAddress("FatJet_particleNet_mass", FatJet_particleNet_mass, &b_FatJet_particleNet_mass);
   fChain->SetBranchAddress("FatJet_phi", FatJet_phi, &b_FatJet_phi);
   fChain->SetBranchAddress("FatJet_pt", FatJet_pt, &b_FatJet_pt);
   fChain->SetBranchAddress("FatJet_rawFactor", FatJet_rawFactor, &b_FatJet_rawFactor);
   fChain->SetBranchAddress("FatJet_tau1", FatJet_tau1, &b_FatJet_tau1);
   fChain->SetBranchAddress("FatJet_tau2", FatJet_tau2, &b_FatJet_tau2);
   fChain->SetBranchAddress("FatJet_tau3", FatJet_tau3, &b_FatJet_tau3);
   fChain->SetBranchAddress("FatJet_tau4", FatJet_tau4, &b_FatJet_tau4);
   fChain->SetBranchAddress("FatJet_lsf3", FatJet_lsf3, &b_FatJet_lsf3);
   fChain->SetBranchAddress("FatJet_jetId", FatJet_jetId, &b_FatJet_jetId);
   fChain->SetBranchAddress("FatJet_subJetIdx1", FatJet_subJetIdx1, &b_FatJet_subJetIdx1);
   fChain->SetBranchAddress("FatJet_subJetIdx2", FatJet_subJetIdx2, &b_FatJet_subJetIdx2);
   fChain->SetBranchAddress("FatJet_electronIdx3SJ", FatJet_electronIdx3SJ, &b_FatJet_electronIdx3SJ);
   fChain->SetBranchAddress("FatJet_muonIdx3SJ", FatJet_muonIdx3SJ, &b_FatJet_muonIdx3SJ);
   fChain->SetBranchAddress("FatJet_nConstituents", FatJet_nConstituents, &b_FatJet_nConstituents);
   fChain->SetBranchAddress("nFsrPhoton", &nFsrPhoton, &b_nFsrPhoton);
   fChain->SetBranchAddress("FsrPhoton_dROverEt2", FsrPhoton_dROverEt2, &b_FsrPhoton_dROverEt2);
   fChain->SetBranchAddress("FsrPhoton_eta", FsrPhoton_eta, &b_FsrPhoton_eta);
   fChain->SetBranchAddress("FsrPhoton_phi", FsrPhoton_phi, &b_FsrPhoton_phi);
   fChain->SetBranchAddress("FsrPhoton_pt", FsrPhoton_pt, &b_FsrPhoton_pt);
   fChain->SetBranchAddress("FsrPhoton_relIso03", FsrPhoton_relIso03, &b_FsrPhoton_relIso03);
   fChain->SetBranchAddress("FsrPhoton_muonIdx", FsrPhoton_muonIdx, &b_FsrPhoton_muonIdx);
   fChain->SetBranchAddress("nGenJetAK8", &nGenJetAK8, &b_nGenJetAK8);
   fChain->SetBranchAddress("GenJetAK8_eta", GenJetAK8_eta, &b_GenJetAK8_eta);
   fChain->SetBranchAddress("GenJetAK8_mass", GenJetAK8_mass, &b_GenJetAK8_mass);
   fChain->SetBranchAddress("GenJetAK8_phi", GenJetAK8_phi, &b_GenJetAK8_phi);
   fChain->SetBranchAddress("GenJetAK8_pt", GenJetAK8_pt, &b_GenJetAK8_pt);
   fChain->SetBranchAddress("nGenJet", &nGenJet, &b_nGenJet);
   fChain->SetBranchAddress("GenJet_eta", GenJet_eta, &b_GenJet_eta);
   fChain->SetBranchAddress("GenJet_mass", GenJet_mass, &b_GenJet_mass);
   fChain->SetBranchAddress("GenJet_phi", GenJet_phi, &b_GenJet_phi);
   fChain->SetBranchAddress("GenJet_pt", GenJet_pt, &b_GenJet_pt);
   fChain->SetBranchAddress("nGenPart", &nGenPart, &b_nGenPart);
   fChain->SetBranchAddress("GenPart_eta", GenPart_eta, &b_GenPart_eta);
   fChain->SetBranchAddress("GenPart_mass", GenPart_mass, &b_GenPart_mass);
   fChain->SetBranchAddress("GenPart_phi", GenPart_phi, &b_GenPart_phi);
   fChain->SetBranchAddress("GenPart_pt", GenPart_pt, &b_GenPart_pt);
   fChain->SetBranchAddress("GenPart_genPartIdxMother", GenPart_genPartIdxMother, &b_GenPart_genPartIdxMother);
   fChain->SetBranchAddress("GenPart_pdgId", GenPart_pdgId, &b_GenPart_pdgId);
   fChain->SetBranchAddress("GenPart_status", GenPart_status, &b_GenPart_status);
   fChain->SetBranchAddress("GenPart_statusFlags", GenPart_statusFlags, &b_GenPart_statusFlags);
   fChain->SetBranchAddress("Generator_binvar", &Generator_binvar, &b_Generator_binvar);
   fChain->SetBranchAddress("Generator_scalePDF", &Generator_scalePDF, &b_Generator_scalePDF);
   fChain->SetBranchAddress("Generator_weight", &Generator_weight, &b_Generator_weight);
   fChain->SetBranchAddress("Generator_x1", &Generator_x1, &b_Generator_x1);
   fChain->SetBranchAddress("Generator_x2", &Generator_x2, &b_Generator_x2);
   fChain->SetBranchAddress("Generator_xpdf1", &Generator_xpdf1, &b_Generator_xpdf1);
   fChain->SetBranchAddress("Generator_xpdf2", &Generator_xpdf2, &b_Generator_xpdf2);
   fChain->SetBranchAddress("Generator_id1", &Generator_id1, &b_Generator_id1);
   fChain->SetBranchAddress("Generator_id2", &Generator_id2, &b_Generator_id2);
   fChain->SetBranchAddress("GenVtx_x", &GenVtx_x, &b_GenVtx_x);
   fChain->SetBranchAddress("GenVtx_y", &GenVtx_y, &b_GenVtx_y);
   fChain->SetBranchAddress("GenVtx_z", &GenVtx_z, &b_GenVtx_z);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("LHEWeight_originalXWGTUP", &LHEWeight_originalXWGTUP, &b_LHEWeight_originalXWGTUP);
   fChain->SetBranchAddress("nLHEPdfWeight", &nLHEPdfWeight, &b_nLHEPdfWeight);
   fChain->SetBranchAddress("LHEPdfWeight", LHEPdfWeight, &b_LHEPdfWeight);
   fChain->SetBranchAddress("nLHEReweightingWeight", &nLHEReweightingWeight, &b_nLHEReweightingWeight);
   fChain->SetBranchAddress("LHEReweightingWeight", &LHEReweightingWeight, &b_LHEReweightingWeight);
   fChain->SetBranchAddress("nLHEScaleWeight", &nLHEScaleWeight, &b_nLHEScaleWeight);
   fChain->SetBranchAddress("LHEScaleWeight", LHEScaleWeight, &b_LHEScaleWeight);
   fChain->SetBranchAddress("nPSWeight", &nPSWeight, &b_nPSWeight);
   fChain->SetBranchAddress("PSWeight", PSWeight, &b_PSWeight);
   fChain->SetBranchAddress("nIsoTrack", &nIsoTrack, &b_nIsoTrack);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("Jet_area", Jet_area, &b_Jet_area);
   fChain->SetBranchAddress("Jet_btagCSVV2", Jet_btagCSVV2, &b_Jet_btagCSVV2);
   fChain->SetBranchAddress("Jet_btagDeepB", Jet_btagDeepB, &b_Jet_btagDeepB);
   fChain->SetBranchAddress("Jet_btagDeepCvB", Jet_btagDeepCvB, &b_Jet_btagDeepCvB);
   fChain->SetBranchAddress("Jet_btagDeepCvL", Jet_btagDeepCvL, &b_Jet_btagDeepCvL);
   fChain->SetBranchAddress("Jet_btagDeepFlavB", Jet_btagDeepFlavB, &b_Jet_btagDeepFlavB);
   fChain->SetBranchAddress("Jet_btagDeepFlavCvB", Jet_btagDeepFlavCvB, &b_Jet_btagDeepFlavCvB);
   fChain->SetBranchAddress("Jet_btagDeepFlavCvL", Jet_btagDeepFlavCvL, &b_Jet_btagDeepFlavCvL);
   fChain->SetBranchAddress("Jet_btagDeepFlavQG", Jet_btagDeepFlavQG, &b_Jet_btagDeepFlavQG);
   fChain->SetBranchAddress("Jet_chEmEF", Jet_chEmEF, &b_Jet_chEmEF);
   fChain->SetBranchAddress("Jet_chFPV0EF", Jet_chFPV0EF, &b_Jet_chFPV0EF);
   fChain->SetBranchAddress("Jet_chHEF", Jet_chHEF, &b_Jet_chHEF);
   fChain->SetBranchAddress("Jet_eta", Jet_eta, &b_Jet_eta);
   fChain->SetBranchAddress("Jet_hfsigmaEtaEta", Jet_hfsigmaEtaEta, &b_Jet_hfsigmaEtaEta);
   fChain->SetBranchAddress("Jet_hfsigmaPhiPhi", Jet_hfsigmaPhiPhi, &b_Jet_hfsigmaPhiPhi);
   fChain->SetBranchAddress("Jet_mass", Jet_mass, &b_Jet_mass);
   fChain->SetBranchAddress("Jet_muEF", Jet_muEF, &b_Jet_muEF);
   fChain->SetBranchAddress("Jet_muonSubtrFactor", Jet_muonSubtrFactor, &b_Jet_muonSubtrFactor);
   fChain->SetBranchAddress("Jet_neEmEF", Jet_neEmEF, &b_Jet_neEmEF);
   fChain->SetBranchAddress("Jet_neHEF", Jet_neHEF, &b_Jet_neHEF);
   fChain->SetBranchAddress("Jet_phi", Jet_phi, &b_Jet_phi);
   fChain->SetBranchAddress("Jet_pt", Jet_pt, &b_Jet_pt);
   fChain->SetBranchAddress("Jet_puIdDisc", Jet_puIdDisc, &b_Jet_puIdDisc);
   fChain->SetBranchAddress("Jet_qgl", Jet_qgl, &b_Jet_qgl);
   fChain->SetBranchAddress("Jet_rawFactor", Jet_rawFactor, &b_Jet_rawFactor);
   fChain->SetBranchAddress("Jet_bRegCorr", Jet_bRegCorr, &b_Jet_bRegCorr);
   fChain->SetBranchAddress("Jet_bRegRes", Jet_bRegRes, &b_Jet_bRegRes);
   fChain->SetBranchAddress("Jet_cRegCorr", Jet_cRegCorr, &b_Jet_cRegCorr);
   fChain->SetBranchAddress("Jet_cRegRes", Jet_cRegRes, &b_Jet_cRegRes);
   fChain->SetBranchAddress("Jet_electronIdx1", Jet_electronIdx1, &b_Jet_electronIdx1);
   fChain->SetBranchAddress("Jet_electronIdx2", Jet_electronIdx2, &b_Jet_electronIdx2);
   fChain->SetBranchAddress("Jet_hfadjacentEtaStripsSize", Jet_hfadjacentEtaStripsSize, &b_Jet_hfadjacentEtaStripsSize);
   fChain->SetBranchAddress("Jet_hfcentralEtaStripSize", Jet_hfcentralEtaStripSize, &b_Jet_hfcentralEtaStripSize);
   fChain->SetBranchAddress("Jet_jetId", Jet_jetId, &b_Jet_jetId);
   fChain->SetBranchAddress("Jet_muonIdx1", Jet_muonIdx1, &b_Jet_muonIdx1);
   fChain->SetBranchAddress("Jet_muonIdx2", Jet_muonIdx2, &b_Jet_muonIdx2);
   fChain->SetBranchAddress("Jet_nElectrons", Jet_nElectrons, &b_Jet_nElectrons);
   fChain->SetBranchAddress("Jet_nMuons", Jet_nMuons, &b_Jet_nMuons);
   fChain->SetBranchAddress("Jet_puId", Jet_puId, &b_Jet_puId);
   fChain->SetBranchAddress("Jet_nConstituents", Jet_nConstituents, &b_Jet_nConstituents);
   fChain->SetBranchAddress("L1PreFiringWeight_Dn", &L1PreFiringWeight_Dn, &b_L1PreFiringWeight_Dn);
   fChain->SetBranchAddress("L1PreFiringWeight_ECAL_Dn", &L1PreFiringWeight_ECAL_Dn, &b_L1PreFiringWeight_ECAL_Dn);
   fChain->SetBranchAddress("L1PreFiringWeight_ECAL_Nom", &L1PreFiringWeight_ECAL_Nom, &b_L1PreFiringWeight_ECAL_Nom);
   fChain->SetBranchAddress("L1PreFiringWeight_ECAL_Up", &L1PreFiringWeight_ECAL_Up, &b_L1PreFiringWeight_ECAL_Up);
   fChain->SetBranchAddress("L1PreFiringWeight_Muon_Nom", &L1PreFiringWeight_Muon_Nom, &b_L1PreFiringWeight_Muon_Nom);
   fChain->SetBranchAddress("L1PreFiringWeight_Muon_StatDn", &L1PreFiringWeight_Muon_StatDn, &b_L1PreFiringWeight_Muon_StatDn);
   fChain->SetBranchAddress("L1PreFiringWeight_Muon_StatUp", &L1PreFiringWeight_Muon_StatUp, &b_L1PreFiringWeight_Muon_StatUp);
   fChain->SetBranchAddress("L1PreFiringWeight_Muon_SystDn", &L1PreFiringWeight_Muon_SystDn, &b_L1PreFiringWeight_Muon_SystDn);
   fChain->SetBranchAddress("L1PreFiringWeight_Muon_SystUp", &L1PreFiringWeight_Muon_SystUp, &b_L1PreFiringWeight_Muon_SystUp);
   fChain->SetBranchAddress("L1PreFiringWeight_Nom", &L1PreFiringWeight_Nom, &b_L1PreFiringWeight_Nom);
   fChain->SetBranchAddress("L1PreFiringWeight_Up", &L1PreFiringWeight_Up, &b_L1PreFiringWeight_Up);
   fChain->SetBranchAddress("GenMET_phi", &GenMET_phi, &b_GenMET_phi);
   fChain->SetBranchAddress("GenMET_pt", &GenMET_pt, &b_GenMET_pt);
   fChain->SetBranchAddress("MET_MetUnclustEnUpDeltaX", &MET_MetUnclustEnUpDeltaX, &b_MET_MetUnclustEnUpDeltaX);
   fChain->SetBranchAddress("MET_MetUnclustEnUpDeltaY", &MET_MetUnclustEnUpDeltaY, &b_MET_MetUnclustEnUpDeltaY);
   fChain->SetBranchAddress("MET_covXX", &MET_covXX, &b_MET_covXX);
   fChain->SetBranchAddress("MET_covXY", &MET_covXY, &b_MET_covXY);
   fChain->SetBranchAddress("MET_covYY", &MET_covYY, &b_MET_covYY);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("MET_pt", &MET_pt, &b_MET_pt);
   fChain->SetBranchAddress("MET_significance", &MET_significance, &b_MET_significance);
   fChain->SetBranchAddress("MET_sumEt", &MET_sumEt, &b_MET_sumEt);
   fChain->SetBranchAddress("MET_sumPtUnclustered", &MET_sumPtUnclustered, &b_MET_sumPtUnclustered);
   fChain->SetBranchAddress("nMuon", &nMuon, &b_nMuon);
   fChain->SetBranchAddress("Muon_dxy", Muon_dxy, &b_Muon_dxy);
   fChain->SetBranchAddress("Muon_dxyErr", Muon_dxyErr, &b_Muon_dxyErr);
   fChain->SetBranchAddress("Muon_dxybs", Muon_dxybs, &b_Muon_dxybs);
   fChain->SetBranchAddress("Muon_dz", Muon_dz, &b_Muon_dz);
   fChain->SetBranchAddress("Muon_dzErr", Muon_dzErr, &b_Muon_dzErr);
   fChain->SetBranchAddress("Muon_eta", Muon_eta, &b_Muon_eta);
   fChain->SetBranchAddress("Muon_ip3d", Muon_ip3d, &b_Muon_ip3d);
   fChain->SetBranchAddress("Muon_jetPtRelv2", Muon_jetPtRelv2, &b_Muon_jetPtRelv2);
   fChain->SetBranchAddress("Muon_jetRelIso", Muon_jetRelIso, &b_Muon_jetRelIso);
   fChain->SetBranchAddress("Muon_mass", Muon_mass, &b_Muon_mass);
   fChain->SetBranchAddress("Muon_miniPFRelIso_all", Muon_miniPFRelIso_all, &b_Muon_miniPFRelIso_all);
   fChain->SetBranchAddress("Muon_miniPFRelIso_chg", Muon_miniPFRelIso_chg, &b_Muon_miniPFRelIso_chg);
   fChain->SetBranchAddress("Muon_pfRelIso03_all", Muon_pfRelIso03_all, &b_Muon_pfRelIso03_all);
   fChain->SetBranchAddress("Muon_pfRelIso03_chg", Muon_pfRelIso03_chg, &b_Muon_pfRelIso03_chg);
   fChain->SetBranchAddress("Muon_pfRelIso04_all", Muon_pfRelIso04_all, &b_Muon_pfRelIso04_all);
   fChain->SetBranchAddress("Muon_phi", Muon_phi, &b_Muon_phi);
   fChain->SetBranchAddress("Muon_pt", Muon_pt, &b_Muon_pt);
   fChain->SetBranchAddress("Muon_ptErr", Muon_ptErr, &b_Muon_ptErr);
   fChain->SetBranchAddress("Muon_segmentComp", Muon_segmentComp, &b_Muon_segmentComp);
   fChain->SetBranchAddress("Muon_sip3d", Muon_sip3d, &b_Muon_sip3d);
   fChain->SetBranchAddress("Muon_softMva", Muon_softMva, &b_Muon_softMva);
   fChain->SetBranchAddress("Muon_tkRelIso", Muon_tkRelIso, &b_Muon_tkRelIso);
   fChain->SetBranchAddress("Muon_tunepRelPt", Muon_tunepRelPt, &b_Muon_tunepRelPt);
   fChain->SetBranchAddress("Muon_mvaLowPt", Muon_mvaLowPt, &b_Muon_mvaLowPt);
   fChain->SetBranchAddress("Muon_mvaTTH", Muon_mvaTTH, &b_Muon_mvaTTH);
   fChain->SetBranchAddress("Muon_charge", Muon_charge, &b_Muon_charge);
   fChain->SetBranchAddress("Muon_jetIdx", Muon_jetIdx, &b_Muon_jetIdx);
   fChain->SetBranchAddress("Muon_nStations", Muon_nStations, &b_Muon_nStations);
   fChain->SetBranchAddress("Muon_nTrackerLayers", Muon_nTrackerLayers, &b_Muon_nTrackerLayers);
   fChain->SetBranchAddress("Muon_pdgId", Muon_pdgId, &b_Muon_pdgId);
   fChain->SetBranchAddress("Muon_tightCharge", Muon_tightCharge, &b_Muon_tightCharge);
   fChain->SetBranchAddress("Muon_fsrPhotonIdx", Muon_fsrPhotonIdx, &b_Muon_fsrPhotonIdx);
   fChain->SetBranchAddress("Muon_highPtId", Muon_highPtId, &b_Muon_highPtId);
   fChain->SetBranchAddress("Muon_highPurity", Muon_highPurity, &b_Muon_highPurity);
   fChain->SetBranchAddress("Muon_inTimeMuon", Muon_inTimeMuon, &b_Muon_inTimeMuon);
   fChain->SetBranchAddress("Muon_isGlobal", Muon_isGlobal, &b_Muon_isGlobal);
   fChain->SetBranchAddress("Muon_isPFcand", Muon_isPFcand, &b_Muon_isPFcand);
   fChain->SetBranchAddress("Muon_isStandalone", Muon_isStandalone, &b_Muon_isStandalone);
   fChain->SetBranchAddress("Muon_isTracker", Muon_isTracker, &b_Muon_isTracker);
   fChain->SetBranchAddress("Muon_jetNDauCharged", Muon_jetNDauCharged, &b_Muon_jetNDauCharged);
   fChain->SetBranchAddress("Muon_looseId", Muon_looseId, &b_Muon_looseId);
   fChain->SetBranchAddress("Muon_mediumId", Muon_mediumId, &b_Muon_mediumId);
   fChain->SetBranchAddress("Muon_mediumPromptId", Muon_mediumPromptId, &b_Muon_mediumPromptId);
   fChain->SetBranchAddress("Muon_miniIsoId", Muon_miniIsoId, &b_Muon_miniIsoId);
   fChain->SetBranchAddress("Muon_multiIsoId", Muon_multiIsoId, &b_Muon_multiIsoId);
   fChain->SetBranchAddress("Muon_mvaId", Muon_mvaId, &b_Muon_mvaId);
   fChain->SetBranchAddress("Muon_mvaLowPtId", Muon_mvaLowPtId, &b_Muon_mvaLowPtId);
   fChain->SetBranchAddress("Muon_pfIsoId", Muon_pfIsoId, &b_Muon_pfIsoId);
   fChain->SetBranchAddress("Muon_puppiIsoId", Muon_puppiIsoId, &b_Muon_puppiIsoId);
   fChain->SetBranchAddress("Muon_softId", Muon_softId, &b_Muon_softId);
   fChain->SetBranchAddress("Muon_softMvaId", Muon_softMvaId, &b_Muon_softMvaId);
   fChain->SetBranchAddress("Muon_tightId", Muon_tightId, &b_Muon_tightId);
   fChain->SetBranchAddress("Muon_tkIsoId", Muon_tkIsoId, &b_Muon_tkIsoId);
   fChain->SetBranchAddress("Muon_triggerIdLoose", Muon_triggerIdLoose, &b_Muon_triggerIdLoose);
   fChain->SetBranchAddress("nPhoton", &nPhoton, &b_nPhoton);
   fChain->SetBranchAddress("Photon_dEscaleDown", Photon_dEscaleDown, &b_Photon_dEscaleDown);
   fChain->SetBranchAddress("Photon_dEscaleUp", Photon_dEscaleUp, &b_Photon_dEscaleUp);
   fChain->SetBranchAddress("Photon_dEsigmaDown", Photon_dEsigmaDown, &b_Photon_dEsigmaDown);
   fChain->SetBranchAddress("Photon_dEsigmaUp", Photon_dEsigmaUp, &b_Photon_dEsigmaUp);
   fChain->SetBranchAddress("Photon_eCorr", Photon_eCorr, &b_Photon_eCorr);
   fChain->SetBranchAddress("Photon_energyErr", Photon_energyErr, &b_Photon_energyErr);
   fChain->SetBranchAddress("Photon_eta", Photon_eta, &b_Photon_eta);
   fChain->SetBranchAddress("Photon_hoe", Photon_hoe, &b_Photon_hoe);
   fChain->SetBranchAddress("Photon_mass", Photon_mass, &b_Photon_mass);
   fChain->SetBranchAddress("Photon_mvaID", Photon_mvaID, &b_Photon_mvaID);
   fChain->SetBranchAddress("Photon_mvaID_Fall17V1p1", Photon_mvaID_Fall17V1p1, &b_Photon_mvaID_Fall17V1p1);
   fChain->SetBranchAddress("Photon_pfRelIso03_all", Photon_pfRelIso03_all, &b_Photon_pfRelIso03_all);
   fChain->SetBranchAddress("Photon_pfRelIso03_chg", Photon_pfRelIso03_chg, &b_Photon_pfRelIso03_chg);
   fChain->SetBranchAddress("Photon_phi", Photon_phi, &b_Photon_phi);
   fChain->SetBranchAddress("Photon_pt", Photon_pt, &b_Photon_pt);
   fChain->SetBranchAddress("Photon_r9", Photon_r9, &b_Photon_r9);
   fChain->SetBranchAddress("Photon_sieie", Photon_sieie, &b_Photon_sieie);
   fChain->SetBranchAddress("Photon_charge", Photon_charge, &b_Photon_charge);
   fChain->SetBranchAddress("Photon_cutBased", Photon_cutBased, &b_Photon_cutBased);
   fChain->SetBranchAddress("Photon_cutBased_Fall17V1Bitmap", Photon_cutBased_Fall17V1Bitmap, &b_Photon_cutBased_Fall17V1Bitmap);
   fChain->SetBranchAddress("Photon_electronIdx", Photon_electronIdx, &b_Photon_electronIdx);
   fChain->SetBranchAddress("Photon_jetIdx", Photon_jetIdx, &b_Photon_jetIdx);
   fChain->SetBranchAddress("Photon_pdgId", Photon_pdgId, &b_Photon_pdgId);
   fChain->SetBranchAddress("Photon_vidNestedWPBitmap", Photon_vidNestedWPBitmap, &b_Photon_vidNestedWPBitmap);
   fChain->SetBranchAddress("Photon_electronVeto", Photon_electronVeto, &b_Photon_electronVeto);
   fChain->SetBranchAddress("Photon_isScEtaEB", Photon_isScEtaEB, &b_Photon_isScEtaEB);
   fChain->SetBranchAddress("Photon_isScEtaEE", Photon_isScEtaEE, &b_Photon_isScEtaEE);
   fChain->SetBranchAddress("Photon_mvaID_WP80", Photon_mvaID_WP80, &b_Photon_mvaID_WP80);
   fChain->SetBranchAddress("Photon_mvaID_WP90", Photon_mvaID_WP90, &b_Photon_mvaID_WP90);
   fChain->SetBranchAddress("Photon_pixelSeed", Photon_pixelSeed, &b_Photon_pixelSeed);
   fChain->SetBranchAddress("Photon_seedGain", Photon_seedGain, &b_Photon_seedGain);
   fChain->SetBranchAddress("Pileup_nTrueInt", &Pileup_nTrueInt, &b_Pileup_nTrueInt);
   fChain->SetBranchAddress("Pileup_pudensity", &Pileup_pudensity, &b_Pileup_pudensity);
   fChain->SetBranchAddress("Pileup_gpudensity", &Pileup_gpudensity, &b_Pileup_gpudensity);
   fChain->SetBranchAddress("Pileup_nPU", &Pileup_nPU, &b_Pileup_nPU);
   fChain->SetBranchAddress("Pileup_sumEOOT", &Pileup_sumEOOT, &b_Pileup_sumEOOT);
   fChain->SetBranchAddress("Pileup_sumLOOT", &Pileup_sumLOOT, &b_Pileup_sumLOOT);
   fChain->SetBranchAddress("PuppiMET_phi", &PuppiMET_phi, &b_PuppiMET_phi);
   fChain->SetBranchAddress("PuppiMET_phiJERDown", &PuppiMET_phiJERDown, &b_PuppiMET_phiJERDown);
   fChain->SetBranchAddress("PuppiMET_phiJERUp", &PuppiMET_phiJERUp, &b_PuppiMET_phiJERUp);
   fChain->SetBranchAddress("PuppiMET_phiJESDown", &PuppiMET_phiJESDown, &b_PuppiMET_phiJESDown);
   fChain->SetBranchAddress("PuppiMET_phiJESUp", &PuppiMET_phiJESUp, &b_PuppiMET_phiJESUp);
   fChain->SetBranchAddress("PuppiMET_phiUnclusteredDown", &PuppiMET_phiUnclusteredDown, &b_PuppiMET_phiUnclusteredDown);
   fChain->SetBranchAddress("PuppiMET_phiUnclusteredUp", &PuppiMET_phiUnclusteredUp, &b_PuppiMET_phiUnclusteredUp);
   fChain->SetBranchAddress("PuppiMET_pt", &PuppiMET_pt, &b_PuppiMET_pt);
   fChain->SetBranchAddress("PuppiMET_ptJERDown", &PuppiMET_ptJERDown, &b_PuppiMET_ptJERDown);
   fChain->SetBranchAddress("PuppiMET_ptJERUp", &PuppiMET_ptJERUp, &b_PuppiMET_ptJERUp);
   fChain->SetBranchAddress("PuppiMET_ptJESDown", &PuppiMET_ptJESDown, &b_PuppiMET_ptJESDown);
   fChain->SetBranchAddress("PuppiMET_ptJESUp", &PuppiMET_ptJESUp, &b_PuppiMET_ptJESUp);
   fChain->SetBranchAddress("PuppiMET_ptUnclusteredDown", &PuppiMET_ptUnclusteredDown, &b_PuppiMET_ptUnclusteredDown);
   fChain->SetBranchAddress("PuppiMET_ptUnclusteredUp", &PuppiMET_ptUnclusteredUp, &b_PuppiMET_ptUnclusteredUp);
   fChain->SetBranchAddress("PuppiMET_sumEt", &PuppiMET_sumEt, &b_PuppiMET_sumEt);
   fChain->SetBranchAddress("RawMET_phi", &RawMET_phi, &b_RawMET_phi);
   fChain->SetBranchAddress("RawMET_pt", &RawMET_pt, &b_RawMET_pt);
   fChain->SetBranchAddress("RawMET_sumEt", &RawMET_sumEt, &b_RawMET_sumEt);
   fChain->SetBranchAddress("RawPuppiMET_phi", &RawPuppiMET_phi, &b_RawPuppiMET_phi);
   fChain->SetBranchAddress("RawPuppiMET_pt", &RawPuppiMET_pt, &b_RawPuppiMET_pt);
   fChain->SetBranchAddress("RawPuppiMET_sumEt", &RawPuppiMET_sumEt, &b_RawPuppiMET_sumEt);
   fChain->SetBranchAddress("fixedGridRhoFastjetAll", &fixedGridRhoFastjetAll, &b_fixedGridRhoFastjetAll);
   fChain->SetBranchAddress("fixedGridRhoFastjetCentral", &fixedGridRhoFastjetCentral, &b_fixedGridRhoFastjetCentral);
   fChain->SetBranchAddress("fixedGridRhoFastjetCentralCalo", &fixedGridRhoFastjetCentralCalo, &b_fixedGridRhoFastjetCentralCalo);
   fChain->SetBranchAddress("fixedGridRhoFastjetCentralChargedPileUp", &fixedGridRhoFastjetCentralChargedPileUp, &b_fixedGridRhoFastjetCentralChargedPileUp);
   fChain->SetBranchAddress("fixedGridRhoFastjetCentralNeutral", &fixedGridRhoFastjetCentralNeutral, &b_fixedGridRhoFastjetCentralNeutral);
   fChain->SetBranchAddress("nGenDressedLepton", &nGenDressedLepton, &b_nGenDressedLepton);
   fChain->SetBranchAddress("GenDressedLepton_eta", GenDressedLepton_eta, &b_GenDressedLepton_eta);
   fChain->SetBranchAddress("GenDressedLepton_mass", GenDressedLepton_mass, &b_GenDressedLepton_mass);
   fChain->SetBranchAddress("GenDressedLepton_phi", GenDressedLepton_phi, &b_GenDressedLepton_phi);
   fChain->SetBranchAddress("GenDressedLepton_pt", GenDressedLepton_pt, &b_GenDressedLepton_pt);
   fChain->SetBranchAddress("GenDressedLepton_pdgId", GenDressedLepton_pdgId, &b_GenDressedLepton_pdgId);
   fChain->SetBranchAddress("GenDressedLepton_hasTauAnc", GenDressedLepton_hasTauAnc, &b_GenDressedLepton_hasTauAnc);
   fChain->SetBranchAddress("nGenIsolatedPhoton", &nGenIsolatedPhoton, &b_nGenIsolatedPhoton);
   fChain->SetBranchAddress("GenIsolatedPhoton_eta", GenIsolatedPhoton_eta, &b_GenIsolatedPhoton_eta);
   fChain->SetBranchAddress("GenIsolatedPhoton_mass", GenIsolatedPhoton_mass, &b_GenIsolatedPhoton_mass);
   fChain->SetBranchAddress("GenIsolatedPhoton_phi", GenIsolatedPhoton_phi, &b_GenIsolatedPhoton_phi);
   fChain->SetBranchAddress("GenIsolatedPhoton_pt", GenIsolatedPhoton_pt, &b_GenIsolatedPhoton_pt);
   fChain->SetBranchAddress("TkMET_phi", &TkMET_phi, &b_TkMET_phi);
   fChain->SetBranchAddress("TkMET_pt", &TkMET_pt, &b_TkMET_pt);
   fChain->SetBranchAddress("TkMET_sumEt", &TkMET_sumEt, &b_TkMET_sumEt);
   fChain->SetBranchAddress("nTrigObj", &nTrigObj, &b_nTrigObj);
   fChain->SetBranchAddress("TrigObj_pt", TrigObj_pt, &b_TrigObj_pt);
   fChain->SetBranchAddress("TrigObj_eta", TrigObj_eta, &b_TrigObj_eta);
   fChain->SetBranchAddress("TrigObj_phi", TrigObj_phi, &b_TrigObj_phi);
   fChain->SetBranchAddress("TrigObj_l1pt", TrigObj_l1pt, &b_TrigObj_l1pt);
   fChain->SetBranchAddress("TrigObj_l1pt_2", TrigObj_l1pt_2, &b_TrigObj_l1pt_2);
   fChain->SetBranchAddress("TrigObj_l2pt", TrigObj_l2pt, &b_TrigObj_l2pt);
   fChain->SetBranchAddress("TrigObj_id", TrigObj_id, &b_TrigObj_id);
   fChain->SetBranchAddress("TrigObj_l1iso", TrigObj_l1iso, &b_TrigObj_l1iso);
   fChain->SetBranchAddress("TrigObj_l1charge", TrigObj_l1charge, &b_TrigObj_l1charge);
   fChain->SetBranchAddress("TrigObj_filterBits", TrigObj_filterBits, &b_TrigObj_filterBits);
   fChain->SetBranchAddress("genTtbarId", &genTtbarId, &b_genTtbarId);
   fChain->SetBranchAddress("nOtherPV", &nOtherPV, &b_nOtherPV);
   fChain->SetBranchAddress("OtherPV_z", OtherPV_z, &b_OtherPV_z);
   fChain->SetBranchAddress("PV_ndof", &PV_ndof, &b_PV_ndof);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("PV_chi2", &PV_chi2, &b_PV_chi2);
   fChain->SetBranchAddress("PV_score", &PV_score, &b_PV_score);
   fChain->SetBranchAddress("PV_npvs", &PV_npvs, &b_PV_npvs);
   fChain->SetBranchAddress("PV_npvsGood", &PV_npvsGood, &b_PV_npvsGood);
   fChain->SetBranchAddress("nSV", &nSV, &b_nSV);
   fChain->SetBranchAddress("SV_dlen", SV_dlen, &b_SV_dlen);
   fChain->SetBranchAddress("SV_dlenSig", SV_dlenSig, &b_SV_dlenSig);
   fChain->SetBranchAddress("SV_dxy", SV_dxy, &b_SV_dxy);
   fChain->SetBranchAddress("SV_dxySig", SV_dxySig, &b_SV_dxySig);
   fChain->SetBranchAddress("SV_pAngle", SV_pAngle, &b_SV_pAngle);
   fChain->SetBranchAddress("SV_charge", SV_charge, &b_SV_charge);
   fChain->SetBranchAddress("Electron_genPartIdx", Electron_genPartIdx, &b_Electron_genPartIdx);
   fChain->SetBranchAddress("Electron_genPartFlav", Electron_genPartFlav, &b_Electron_genPartFlav);
   fChain->SetBranchAddress("FatJet_genJetAK8Idx", FatJet_genJetAK8Idx, &b_FatJet_genJetAK8Idx);
   fChain->SetBranchAddress("FatJet_hadronFlavour", FatJet_hadronFlavour, &b_FatJet_hadronFlavour);
   fChain->SetBranchAddress("FatJet_nBHadrons", FatJet_nBHadrons, &b_FatJet_nBHadrons);
   fChain->SetBranchAddress("FatJet_nCHadrons", FatJet_nCHadrons, &b_FatJet_nCHadrons);
   fChain->SetBranchAddress("GenJetAK8_partonFlavour", GenJetAK8_partonFlavour, &b_GenJetAK8_partonFlavour);
   fChain->SetBranchAddress("GenJetAK8_hadronFlavour", GenJetAK8_hadronFlavour, &b_GenJetAK8_hadronFlavour);
   fChain->SetBranchAddress("GenJet_partonFlavour", GenJet_partonFlavour, &b_GenJet_partonFlavour);
   fChain->SetBranchAddress("GenJet_hadronFlavour", GenJet_hadronFlavour, &b_GenJet_hadronFlavour);
   fChain->SetBranchAddress("GenVtx_t0", &GenVtx_t0, &b_GenVtx_t0);
   fChain->SetBranchAddress("Jet_genJetIdx", Jet_genJetIdx, &b_Jet_genJetIdx);
   fChain->SetBranchAddress("Jet_hadronFlavour", Jet_hadronFlavour, &b_Jet_hadronFlavour);
   fChain->SetBranchAddress("Jet_partonFlavour", Jet_partonFlavour, &b_Jet_partonFlavour);
   fChain->SetBranchAddress("Muon_genPartIdx", Muon_genPartIdx, &b_Muon_genPartIdx);
   fChain->SetBranchAddress("Muon_genPartFlav", Muon_genPartFlav, &b_Muon_genPartFlav);
   fChain->SetBranchAddress("Photon_genPartIdx", Photon_genPartIdx, &b_Photon_genPartIdx);
   fChain->SetBranchAddress("Photon_genPartFlav", Photon_genPartFlav, &b_Photon_genPartFlav);
   fChain->SetBranchAddress("MET_fiducialGenPhi", &MET_fiducialGenPhi, &b_MET_fiducialGenPhi);
   fChain->SetBranchAddress("MET_fiducialGenPt", &MET_fiducialGenPt, &b_MET_fiducialGenPt);
   fChain->SetBranchAddress("Electron_cleanmask", Electron_cleanmask, &b_Electron_cleanmask);
   fChain->SetBranchAddress("Jet_cleanmask", Jet_cleanmask, &b_Jet_cleanmask);
   fChain->SetBranchAddress("Muon_cleanmask", Muon_cleanmask, &b_Muon_cleanmask);
   fChain->SetBranchAddress("Photon_cleanmask", Photon_cleanmask, &b_Photon_cleanmask);
   fChain->SetBranchAddress("SV_chi2", SV_chi2, &b_SV_chi2);
   fChain->SetBranchAddress("SV_eta", SV_eta, &b_SV_eta);
   fChain->SetBranchAddress("SV_mass", SV_mass, &b_SV_mass);
   fChain->SetBranchAddress("SV_ndof", SV_ndof, &b_SV_ndof);
   fChain->SetBranchAddress("SV_phi", SV_phi, &b_SV_phi);
   fChain->SetBranchAddress("SV_pt", SV_pt, &b_SV_pt);
   fChain->SetBranchAddress("SV_x", SV_x, &b_SV_x);
   fChain->SetBranchAddress("SV_y", SV_y, &b_SV_y);
   fChain->SetBranchAddress("SV_z", SV_z, &b_SV_z);
   fChain->SetBranchAddress("SV_ntracks", SV_ntracks, &b_SV_ntracks);
   fChain->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter, &b_Flag_HBHENoiseFilter);
   fChain->SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter, &b_Flag_HBHENoiseIsoFilter);
   fChain->SetBranchAddress("Flag_CSCTightHaloFilter", &Flag_CSCTightHaloFilter, &b_Flag_CSCTightHaloFilter);
   fChain->SetBranchAddress("Flag_CSCTightHaloTrkMuUnvetoFilter", &Flag_CSCTightHaloTrkMuUnvetoFilter, &b_Flag_CSCTightHaloTrkMuUnvetoFilter);
   fChain->SetBranchAddress("Flag_CSCTightHalo2015Filter", &Flag_CSCTightHalo2015Filter, &b_Flag_CSCTightHalo2015Filter);
   fChain->SetBranchAddress("Flag_globalTightHalo2016Filter", &Flag_globalTightHalo2016Filter, &b_Flag_globalTightHalo2016Filter);
   fChain->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter, &b_Flag_globalSuperTightHalo2016Filter);
   fChain->SetBranchAddress("Flag_HcalStripHaloFilter", &Flag_HcalStripHaloFilter, &b_Flag_HcalStripHaloFilter);
   fChain->SetBranchAddress("Flag_hcalLaserEventFilter", &Flag_hcalLaserEventFilter, &b_Flag_hcalLaserEventFilter);
   fChain->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter, &b_Flag_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("Flag_EcalDeadCellBoundaryEnergyFilter", &Flag_EcalDeadCellBoundaryEnergyFilter, &b_Flag_EcalDeadCellBoundaryEnergyFilter);
   fChain->SetBranchAddress("Flag_ecalBadCalibFilter", &Flag_ecalBadCalibFilter, &b_Flag_ecalBadCalibFilter);
   fChain->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices, &b_Flag_goodVertices);
   fChain->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter, &b_Flag_eeBadScFilter);
   fChain->SetBranchAddress("Flag_ecalLaserCorrFilter", &Flag_ecalLaserCorrFilter, &b_Flag_ecalLaserCorrFilter);
   fChain->SetBranchAddress("Flag_trkPOGFilters", &Flag_trkPOGFilters, &b_Flag_trkPOGFilters);
   fChain->SetBranchAddress("Flag_chargedHadronTrackResolutionFilter", &Flag_chargedHadronTrackResolutionFilter, &b_Flag_chargedHadronTrackResolutionFilter);
   fChain->SetBranchAddress("Flag_muonBadTrackFilter", &Flag_muonBadTrackFilter, &b_Flag_muonBadTrackFilter);
   fChain->SetBranchAddress("Flag_BadChargedCandidateFilter", &Flag_BadChargedCandidateFilter, &b_Flag_BadChargedCandidateFilter);
   fChain->SetBranchAddress("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter, &b_Flag_BadPFMuonFilter);
   fChain->SetBranchAddress("Flag_BadPFMuonDzFilter", &Flag_BadPFMuonDzFilter, &b_Flag_BadPFMuonDzFilter);
   fChain->SetBranchAddress("Flag_hfNoisyHitsFilter", &Flag_hfNoisyHitsFilter, &b_Flag_hfNoisyHitsFilter);
   fChain->SetBranchAddress("Flag_BadChargedCandidateSummer16Filter", &Flag_BadChargedCandidateSummer16Filter, &b_Flag_BadChargedCandidateSummer16Filter);
   fChain->SetBranchAddress("Flag_BadPFMuonSummer16Filter", &Flag_BadPFMuonSummer16Filter, &b_Flag_BadPFMuonSummer16Filter);
   fChain->SetBranchAddress("Flag_trkPOG_manystripclus53X", &Flag_trkPOG_manystripclus53X, &b_Flag_trkPOG_manystripclus53X);
   fChain->SetBranchAddress("Flag_trkPOG_toomanystripclus53X", &Flag_trkPOG_toomanystripclus53X, &b_Flag_trkPOG_toomanystripclus53X);
   fChain->SetBranchAddress("Flag_trkPOG_logErrorTooManyClusters", &Flag_trkPOG_logErrorTooManyClusters, &b_Flag_trkPOG_logErrorTooManyClusters);
   fChain->SetBranchAddress("Flag_METFilters", &Flag_METFilters, &b_Flag_METFilters);
   fChain->SetBranchAddress("HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL", &HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL, &b_HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL);
   fChain->SetBranchAddress("HLT_DoubleEle25_CaloIdL_MW", &HLT_DoubleEle25_CaloIdL_MW, &b_HLT_DoubleEle25_CaloIdL_MW);
   fChain->SetBranchAddress("HLT_DoubleEle27_CaloIdL_MW", &HLT_DoubleEle27_CaloIdL_MW, &b_HLT_DoubleEle27_CaloIdL_MW);
   fChain->SetBranchAddress("HLT_DoubleEle33_CaloIdL_MW", &HLT_DoubleEle33_CaloIdL_MW, &b_HLT_DoubleEle33_CaloIdL_MW);
   fChain->SetBranchAddress("HLT_DoubleEle24_eta2p1_WPTight_Gsf", &HLT_DoubleEle24_eta2p1_WPTight_Gsf, &b_HLT_DoubleEle24_eta2p1_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350", &HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350, &b_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350);
   fChain->SetBranchAddress("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350", &HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350, &b_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350);
   fChain->SetBranchAddress("HLT_Ele27_Ele37_CaloIdL_MW", &HLT_Ele27_Ele37_CaloIdL_MW, &b_HLT_Ele27_Ele37_CaloIdL_MW);
   fChain->SetBranchAddress("HLT_Mu27_Ele37_CaloIdL_MW", &HLT_Mu27_Ele37_CaloIdL_MW, &b_HLT_Mu27_Ele37_CaloIdL_MW);
   fChain->SetBranchAddress("HLT_DoublePhoton33_CaloIdL", &HLT_DoublePhoton33_CaloIdL, &b_HLT_DoublePhoton33_CaloIdL);
   fChain->SetBranchAddress("HLT_DoublePhoton70", &HLT_DoublePhoton70, &b_HLT_DoublePhoton70);
   fChain->SetBranchAddress("HLT_DoublePhoton85", &HLT_DoublePhoton85, &b_HLT_DoublePhoton85);
   fChain->SetBranchAddress("HLT_Ele20_WPTight_Gsf", &HLT_Ele20_WPTight_Gsf, &b_HLT_Ele20_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele15_WPLoose_Gsf", &HLT_Ele15_WPLoose_Gsf, &b_HLT_Ele15_WPLoose_Gsf);
   fChain->SetBranchAddress("HLT_Ele17_WPLoose_Gsf", &HLT_Ele17_WPLoose_Gsf, &b_HLT_Ele17_WPLoose_Gsf);
   fChain->SetBranchAddress("HLT_Ele20_WPLoose_Gsf", &HLT_Ele20_WPLoose_Gsf, &b_HLT_Ele20_WPLoose_Gsf);
   fChain->SetBranchAddress("HLT_Ele20_eta2p1_WPLoose_Gsf", &HLT_Ele20_eta2p1_WPLoose_Gsf, &b_HLT_Ele20_eta2p1_WPLoose_Gsf);
   fChain->SetBranchAddress("HLT_Ele27_WPTight_Gsf", &HLT_Ele27_WPTight_Gsf, &b_HLT_Ele27_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele28_WPTight_Gsf", &HLT_Ele28_WPTight_Gsf, &b_HLT_Ele28_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele30_WPTight_Gsf", &HLT_Ele30_WPTight_Gsf, &b_HLT_Ele30_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf, &b_HLT_Ele32_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele35_WPTight_Gsf", &HLT_Ele35_WPTight_Gsf, &b_HLT_Ele35_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele35_WPTight_Gsf_L1EGMT", &HLT_Ele35_WPTight_Gsf_L1EGMT, &b_HLT_Ele35_WPTight_Gsf_L1EGMT);
   fChain->SetBranchAddress("HLT_Ele38_WPTight_Gsf", &HLT_Ele38_WPTight_Gsf, &b_HLT_Ele38_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele40_WPTight_Gsf", &HLT_Ele40_WPTight_Gsf, &b_HLT_Ele40_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG", &HLT_Ele32_WPTight_Gsf_L1DoubleEG, &b_HLT_Ele32_WPTight_Gsf_L1DoubleEG);
   fChain->SetBranchAddress("HLT_IsoMu20", &HLT_IsoMu20, &b_HLT_IsoMu20);
   fChain->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24, &b_HLT_IsoMu24);
   fChain->SetBranchAddress("HLT_IsoTkMu24", &HLT_IsoTkMu24, &b_HLT_IsoTkMu24);
   fChain->SetBranchAddress("HLT_IsoMu24_eta2p1", &HLT_IsoMu24_eta2p1, &b_HLT_IsoMu24_eta2p1);
   fChain->SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27, &b_HLT_IsoMu27);
   fChain->SetBranchAddress("HLT_IsoMu30", &HLT_IsoMu30, &b_HLT_IsoMu30);
   fChain->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL, &b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
   fChain->SetBranchAddress("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL", &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL, &b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL);
   fChain->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ, &b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
   fChain->SetBranchAddress("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ", &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ, &b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ);
   fChain->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8, &b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
   fChain->SetBranchAddress("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8", &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8, &b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8);
   fChain->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8, &b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
   fChain->SetBranchAddress("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8, &b_HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8);
   fChain->SetBranchAddress("HLT_Mu25_TkMu0_Onia", &HLT_Mu25_TkMu0_Onia, &b_HLT_Mu25_TkMu0_Onia);
   fChain->SetBranchAddress("HLT_Mu20_TkMu0_Phi", &HLT_Mu20_TkMu0_Phi, &b_HLT_Mu20_TkMu0_Phi);
   fChain->SetBranchAddress("HLT_Mu25_TkMu0_Phi", &HLT_Mu25_TkMu0_Phi, &b_HLT_Mu25_TkMu0_Phi);
   fChain->SetBranchAddress("HLT_Mu12", &HLT_Mu12, &b_HLT_Mu12);
   fChain->SetBranchAddress("HLT_Mu15", &HLT_Mu15, &b_HLT_Mu15);
   fChain->SetBranchAddress("HLT_Mu20", &HLT_Mu20, &b_HLT_Mu20);
   fChain->SetBranchAddress("HLT_Mu27", &HLT_Mu27, &b_HLT_Mu27);
   fChain->SetBranchAddress("HLT_Mu50", &HLT_Mu50, &b_HLT_Mu50);
   fChain->SetBranchAddress("HLT_Mu55", &HLT_Mu55, &b_HLT_Mu55);
   fChain->SetBranchAddress("HLT_TkMu100", &HLT_TkMu100, &b_HLT_TkMu100);
   fChain->SetBranchAddress("HLT_PFMET110_PFMHT110_IDTight", &HLT_PFMET110_PFMHT110_IDTight, &b_HLT_PFMET110_PFMHT110_IDTight);
   fChain->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight", &HLT_PFMET120_PFMHT120_IDTight, &b_HLT_PFMET120_PFMHT120_IDTight);
   fChain->SetBranchAddress("HLT_PFMET130_PFMHT130_IDTight", &HLT_PFMET130_PFMHT130_IDTight, &b_HLT_PFMET130_PFMHT130_IDTight);
   fChain->SetBranchAddress("HLT_PFMET140_PFMHT140_IDTight", &HLT_PFMET140_PFMHT140_IDTight, &b_HLT_PFMET140_PFMHT140_IDTight);
   fChain->SetBranchAddress("HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1", &HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1, &b_HLT_PFMET100_PFMHT100_IDTight_CaloBTagDeepCSV_3p1);
   fChain->SetBranchAddress("HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1", &HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1, &b_HLT_PFMET110_PFMHT110_IDTight_CaloBTagDeepCSV_3p1);
   fChain->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1", &HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1, &b_HLT_PFMET120_PFMHT120_IDTight_CaloBTagDeepCSV_3p1);
   fChain->SetBranchAddress("HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1", &HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1, &b_HLT_PFMET130_PFMHT130_IDTight_CaloBTagDeepCSV_3p1);
   fChain->SetBranchAddress("HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1", &HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1, &b_HLT_PFMET140_PFMHT140_IDTight_CaloBTagDeepCSV_3p1);
   fChain->SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight_PFHT60", &HLT_PFMET120_PFMHT120_IDTight_PFHT60, &b_HLT_PFMET120_PFMHT120_IDTight_PFHT60);
   fChain->SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60, &b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60);
   fChain->SetBranchAddress("HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60", &HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60, &b_HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60);
   fChain->SetBranchAddress("HLT_PFMETTypeOne110_PFMHT110_IDTight", &HLT_PFMETTypeOne110_PFMHT110_IDTight, &b_HLT_PFMETTypeOne110_PFMHT110_IDTight);
   fChain->SetBranchAddress("HLT_PFMETTypeOne120_PFMHT120_IDTight", &HLT_PFMETTypeOne120_PFMHT120_IDTight, &b_HLT_PFMETTypeOne120_PFMHT120_IDTight);
   fChain->SetBranchAddress("HLT_PFMETTypeOne130_PFMHT130_IDTight", &HLT_PFMETTypeOne130_PFMHT130_IDTight, &b_HLT_PFMETTypeOne130_PFMHT130_IDTight);
   fChain->SetBranchAddress("HLT_PFMETTypeOne140_PFMHT140_IDTight", &HLT_PFMETTypeOne140_PFMHT140_IDTight, &b_HLT_PFMETTypeOne140_PFMHT140_IDTight);
   fChain->SetBranchAddress("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight", &HLT_PFMETNoMu110_PFMHTNoMu110_IDTight, &b_HLT_PFMETNoMu110_PFMHTNoMu110_IDTight);
   fChain->SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight, &b_HLT_PFMETNoMu120_PFMHTNoMu120_IDTight);
   fChain->SetBranchAddress("HLT_PFMETNoMu130_PFMHTNoMu130_IDTight", &HLT_PFMETNoMu130_PFMHTNoMu130_IDTight, &b_HLT_PFMETNoMu130_PFMHTNoMu130_IDTight);
   fChain->SetBranchAddress("HLT_PFMETNoMu140_PFMHTNoMu140_IDTight", &HLT_PFMETNoMu140_PFMHTNoMu140_IDTight, &b_HLT_PFMETNoMu140_PFMHTNoMu140_IDTight);
   fChain->SetBranchAddress("HLT_PFMET200_NotCleaned", &HLT_PFMET200_NotCleaned, &b_HLT_PFMET200_NotCleaned);
   fChain->SetBranchAddress("HLT_PFMET200_HBHECleaned", &HLT_PFMET200_HBHECleaned, &b_HLT_PFMET200_HBHECleaned);
   fChain->SetBranchAddress("HLT_PFMET250_HBHECleaned", &HLT_PFMET250_HBHECleaned, &b_HLT_PFMET250_HBHECleaned);
   fChain->SetBranchAddress("HLT_PFMET300_HBHECleaned", &HLT_PFMET300_HBHECleaned, &b_HLT_PFMET300_HBHECleaned);
   fChain->SetBranchAddress("HLT_PFMET200_HBHE_BeamHaloCleaned", &HLT_PFMET200_HBHE_BeamHaloCleaned, &b_HLT_PFMET200_HBHE_BeamHaloCleaned);
   fChain->SetBranchAddress("HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned", &HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned, &b_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned);
   fChain->SetBranchAddress("HLT_MET105_IsoTrk50", &HLT_MET105_IsoTrk50, &b_HLT_MET105_IsoTrk50);
   fChain->SetBranchAddress("HLT_MET120_IsoTrk50", &HLT_MET120_IsoTrk50, &b_HLT_MET120_IsoTrk50);
   fChain->SetBranchAddress("HLT_SingleJet30_Mu12_SinglePFJet40", &HLT_SingleJet30_Mu12_SinglePFJet40, &b_HLT_SingleJet30_Mu12_SinglePFJet40);
   fChain->SetBranchAddress("HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71", &HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71, &b_HLT_Mu12_DoublePFJets40_CaloBTagDeepCSV_p71);
   fChain->SetBranchAddress("HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71", &HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71, &b_HLT_Mu12_DoublePFJets100_CaloBTagDeepCSV_p71);
   fChain->SetBranchAddress("HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71", &HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71, &b_HLT_Mu12_DoublePFJets200_CaloBTagDeepCSV_p71);
   fChain->SetBranchAddress("HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71", &HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71, &b_HLT_Mu12_DoublePFJets350_CaloBTagDeepCSV_p71);
   fChain->SetBranchAddress("HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71", &HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71, &b_HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagDeepCSV_p71);
   fChain->SetBranchAddress("HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71", &HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71, &b_HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagDeepCSV_p71);
   fChain->SetBranchAddress("HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71", &HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71, &b_HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagDeepCSV_p71);
   fChain->SetBranchAddress("HLT_Mu8_TrkIsoVVL", &HLT_Mu8_TrkIsoVVL, &b_HLT_Mu8_TrkIsoVVL);
   fChain->SetBranchAddress("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ", &HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ, &b_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ);
   fChain->SetBranchAddress("HLT_Mu8_DiEle12_CaloIdL_TrackIdL", &HLT_Mu8_DiEle12_CaloIdL_TrackIdL, &b_HLT_Mu8_DiEle12_CaloIdL_TrackIdL);
   fChain->SetBranchAddress("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ", &HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ, &b_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ);
   fChain->SetBranchAddress("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350", &HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350, &b_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350);
   fChain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, &b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30, &b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30);
   fChain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30, &b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30);
   fChain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5, &b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_PFDiJet30_PFBtagDeepCSV_1p5);
   fChain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5, &b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_CaloDiJet30_CaloBtagDeepCSV_1p5);
   fChain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, &b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("HLT_Mu17_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL, &b_HLT_Mu17_TrkIsoVVL);
   fChain->SetBranchAddress("HLT_Mu19_TrkIsoVVL", &HLT_Mu19_TrkIsoVVL, &b_HLT_Mu19_TrkIsoVVL);
   fChain->SetBranchAddress("HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL", &HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL, &b_HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, &b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL, &b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, &b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL, &b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL, &b_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, &b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, &b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("HLT_Mu12_DoublePhoton20", &HLT_Mu12_DoublePhoton20, &b_HLT_Mu12_DoublePhoton20);
   fChain->SetBranchAddress("HLT_IsoMu24_TwoProngs35", &HLT_IsoMu24_TwoProngs35, &b_HLT_IsoMu24_TwoProngs35);
   fChain->SetBranchAddress("HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned", &HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned, &b_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned);
   fChain->SetBranchAddress("HLT_Ele28_eta2p1_WPTight_Gsf_HT150", &HLT_Ele28_eta2p1_WPTight_Gsf_HT150, &b_HLT_Ele28_eta2p1_WPTight_Gsf_HT150);
   fChain->SetBranchAddress("HLT_Ele28_HighEta_SC20_Mass55", &HLT_Ele28_HighEta_SC20_Mass55, &b_HLT_Ele28_HighEta_SC20_Mass55);
   fChain->SetBranchAddress("HLT_DoubleMu20_7_Mass0to30_Photon23", &HLT_DoubleMu20_7_Mass0to30_Photon23, &b_HLT_DoubleMu20_7_Mass0to30_Photon23);
   fChain->SetBranchAddress("HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5", &HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5, &b_HLT_Ele15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5);
   fChain->SetBranchAddress("HLT_Ele15_IsoVVVL_PFHT450_PFMET50", &HLT_Ele15_IsoVVVL_PFHT450_PFMET50, &b_HLT_Ele15_IsoVVVL_PFHT450_PFMET50);
   fChain->SetBranchAddress("HLT_Ele15_IsoVVVL_PFHT450", &HLT_Ele15_IsoVVVL_PFHT450, &b_HLT_Ele15_IsoVVVL_PFHT450);
   fChain->SetBranchAddress("HLT_Ele50_IsoVVVL_PFHT450", &HLT_Ele50_IsoVVVL_PFHT450, &b_HLT_Ele50_IsoVVVL_PFHT450);
   fChain->SetBranchAddress("HLT_Ele15_IsoVVVL_PFHT600", &HLT_Ele15_IsoVVVL_PFHT600, &b_HLT_Ele15_IsoVVVL_PFHT600);
   fChain->SetBranchAddress("HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60", &HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60, &b_HLT_Mu4_TrkIsoVVL_DiPFJet90_40_DEta3p5_MJJ750_HTT300_PFMETNoMu60);
   fChain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60", &HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60, &b_HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60);
   fChain->SetBranchAddress("HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60", &HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60, &b_HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60);
   fChain->SetBranchAddress("HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5", &HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5, &b_HLT_Mu15_IsoVVVL_PFHT450_CaloBTagDeepCSV_4p5);
   fChain->SetBranchAddress("HLT_Mu15_IsoVVVL_PFHT450_PFMET50", &HLT_Mu15_IsoVVVL_PFHT450_PFMET50, &b_HLT_Mu15_IsoVVVL_PFHT450_PFMET50);
   fChain->SetBranchAddress("HLT_Mu15_IsoVVVL_PFHT450", &HLT_Mu15_IsoVVVL_PFHT450, &b_HLT_Mu15_IsoVVVL_PFHT450);
   fChain->SetBranchAddress("HLT_Mu50_IsoVVVL_PFHT450", &HLT_Mu50_IsoVVVL_PFHT450, &b_HLT_Mu50_IsoVVVL_PFHT450);
   fChain->SetBranchAddress("HLT_Mu15_IsoVVVL_PFHT600", &HLT_Mu15_IsoVVVL_PFHT600, &b_HLT_Mu15_IsoVVVL_PFHT600);
   fChain->SetBranchAddress("HLT_DoubleIsoMu20_eta2p1", &HLT_DoubleIsoMu20_eta2p1, &b_HLT_DoubleIsoMu20_eta2p1);
   fChain->SetBranchAddress("HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx", &HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx, &b_HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx);
   fChain->SetBranchAddress("HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx", &HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx, &b_HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx);
   fChain->SetBranchAddress("HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx", &HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx, &b_HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx);
   fChain->SetBranchAddress("HLT_Mu8", &HLT_Mu8, &b_HLT_Mu8);
   fChain->SetBranchAddress("HLT_Mu17", &HLT_Mu17, &b_HLT_Mu17);
   fChain->SetBranchAddress("HLT_Mu19", &HLT_Mu19, &b_HLT_Mu19);
   fChain->SetBranchAddress("HLT_Mu17_Photon30_IsoCaloId", &HLT_Mu17_Photon30_IsoCaloId, &b_HLT_Mu17_Photon30_IsoCaloId);
   fChain->SetBranchAddress("HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30", &HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30, &b_HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30);
   fChain->SetBranchAddress("HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30", &HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30, &b_HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30);
   fChain->SetBranchAddress("HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30", &HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30, &b_HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30);
   fChain->SetBranchAddress("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30", &HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30, &b_HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30);
   fChain->SetBranchAddress("HLT_Ele8_CaloIdM_TrackIdM_PFJet30", &HLT_Ele8_CaloIdM_TrackIdM_PFJet30, &b_HLT_Ele8_CaloIdM_TrackIdM_PFJet30);
   fChain->SetBranchAddress("HLT_Ele17_CaloIdM_TrackIdM_PFJet30", &HLT_Ele17_CaloIdM_TrackIdM_PFJet30, &b_HLT_Ele17_CaloIdM_TrackIdM_PFJet30);
   fChain->SetBranchAddress("HLT_Ele23_CaloIdM_TrackIdM_PFJet30", &HLT_Ele23_CaloIdM_TrackIdM_PFJet30, &b_HLT_Ele23_CaloIdM_TrackIdM_PFJet30);
   fChain->SetBranchAddress("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165", &HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165, &b_HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165);
   fChain->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT", &HLT_Ele115_CaloIdVT_GsfTrkIdT, &b_HLT_Ele115_CaloIdVT_GsfTrkIdT);
   fChain->SetBranchAddress("HLT_Ele135_CaloIdVT_GsfTrkIdT", &HLT_Ele135_CaloIdVT_GsfTrkIdT, &b_HLT_Ele135_CaloIdVT_GsfTrkIdT);
   fChain->SetBranchAddress("HLT_Ele145_CaloIdVT_GsfTrkIdT", &HLT_Ele145_CaloIdVT_GsfTrkIdT, &b_HLT_Ele145_CaloIdVT_GsfTrkIdT);
   fChain->SetBranchAddress("HLT_Ele200_CaloIdVT_GsfTrkIdT", &HLT_Ele200_CaloIdVT_GsfTrkIdT, &b_HLT_Ele200_CaloIdVT_GsfTrkIdT);
   fChain->SetBranchAddress("HLT_Ele250_CaloIdVT_GsfTrkIdT", &HLT_Ele250_CaloIdVT_GsfTrkIdT, &b_HLT_Ele250_CaloIdVT_GsfTrkIdT);
   fChain->SetBranchAddress("HLT_Ele300_CaloIdVT_GsfTrkIdT", &HLT_Ele300_CaloIdVT_GsfTrkIdT, &b_HLT_Ele300_CaloIdVT_GsfTrkIdT);
   fChain->SetBranchAddress("HLT_ECALHT800", &HLT_ECALHT800, &b_HLT_ECALHT800);
   fChain->SetBranchAddress("HLT_Random", &HLT_Random, &b_HLT_Random);
   fChain->SetBranchAddress("HLT_SinglePhoton10_Eta3p1ForPPRef", &HLT_SinglePhoton10_Eta3p1ForPPRef, &b_HLT_SinglePhoton10_Eta3p1ForPPRef);
   fChain->SetBranchAddress("HLT_SinglePhoton20_Eta3p1ForPPRef", &HLT_SinglePhoton20_Eta3p1ForPPRef, &b_HLT_SinglePhoton20_Eta3p1ForPPRef);
   fChain->SetBranchAddress("HLT_SinglePhoton30_Eta3p1ForPPRef", &HLT_SinglePhoton30_Eta3p1ForPPRef, &b_HLT_SinglePhoton30_Eta3p1ForPPRef);
   fChain->SetBranchAddress("HLT_EcalCalibration", &HLT_EcalCalibration, &b_HLT_EcalCalibration);
   fChain->SetBranchAddress("HLT_IsoTrackHB", &HLT_IsoTrackHB, &b_HLT_IsoTrackHB);
   fChain->SetBranchAddress("HLT_IsoTrackHE", &HLT_IsoTrackHE, &b_HLT_IsoTrackHE);
   fChain->SetBranchAddress("HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr", &HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr, &b_HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr);
   fChain->SetBranchAddress("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL", &HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL, &b_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL);
   fChain->SetBranchAddress("HLT_IsoMu27_MET90", &HLT_IsoMu27_MET90, &b_HLT_IsoMu27_MET90);
   fChain->SetBranchAddress("HLT_PFMET100_PFMHT100_IDTight_PFHT60", &HLT_PFMET100_PFMHT100_IDTight_PFHT60, &b_HLT_PFMET100_PFMHT100_IDTight_PFHT60);
   fChain->SetBranchAddress("HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60", &HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60, &b_HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60);
   fChain->SetBranchAddress("HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60", &HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60, &b_HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60);
   fChain->SetBranchAddress("HLT_Mu18_Mu9_SameSign", &HLT_Mu18_Mu9_SameSign, &b_HLT_Mu18_Mu9_SameSign);
   fChain->SetBranchAddress("HLT_Mu18_Mu9_SameSign_DZ", &HLT_Mu18_Mu9_SameSign_DZ, &b_HLT_Mu18_Mu9_SameSign_DZ);
   fChain->SetBranchAddress("HLT_Mu18_Mu9", &HLT_Mu18_Mu9, &b_HLT_Mu18_Mu9);
   fChain->SetBranchAddress("HLT_Mu18_Mu9_DZ", &HLT_Mu18_Mu9_DZ, &b_HLT_Mu18_Mu9_DZ);
   fChain->SetBranchAddress("HLT_Mu20_Mu10_SameSign", &HLT_Mu20_Mu10_SameSign, &b_HLT_Mu20_Mu10_SameSign);
   fChain->SetBranchAddress("HLT_Mu20_Mu10_SameSign_DZ", &HLT_Mu20_Mu10_SameSign_DZ, &b_HLT_Mu20_Mu10_SameSign_DZ);
   fChain->SetBranchAddress("HLT_Mu20_Mu10", &HLT_Mu20_Mu10, &b_HLT_Mu20_Mu10);
   fChain->SetBranchAddress("HLT_Mu20_Mu10_DZ", &HLT_Mu20_Mu10_DZ, &b_HLT_Mu20_Mu10_DZ);
   fChain->SetBranchAddress("HLT_Mu23_Mu12_SameSign", &HLT_Mu23_Mu12_SameSign, &b_HLT_Mu23_Mu12_SameSign);
   fChain->SetBranchAddress("HLT_Mu23_Mu12_SameSign_DZ", &HLT_Mu23_Mu12_SameSign_DZ, &b_HLT_Mu23_Mu12_SameSign_DZ);
   fChain->SetBranchAddress("HLT_Mu23_Mu12", &HLT_Mu23_Mu12, &b_HLT_Mu23_Mu12);
   fChain->SetBranchAddress("HLT_Mu23_Mu12_DZ", &HLT_Mu23_Mu12_DZ, &b_HLT_Mu23_Mu12_DZ);
   fChain->SetBranchAddress("HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05", &HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05, &b_HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi1p05);
   fChain->SetBranchAddress("HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi", &HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi, &b_HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi);
   fChain->SetBranchAddress("HLT_TrkMu6NoFiltersNoVtx", &HLT_TrkMu6NoFiltersNoVtx, &b_HLT_TrkMu6NoFiltersNoVtx);
   fChain->SetBranchAddress("HLT_TrkMu16NoFiltersNoVtx", &HLT_TrkMu16NoFiltersNoVtx, &b_HLT_TrkMu16NoFiltersNoVtx);
   fChain->SetBranchAddress("HLT_DoubleTrkMu_16_6_NoFiltersNoVtx", &HLT_DoubleTrkMu_16_6_NoFiltersNoVtx, &b_HLT_DoubleTrkMu_16_6_NoFiltersNoVtx);
   fChain->SetBranchAddress("HLTriggerFinalPath", &HLTriggerFinalPath, &b_HLTriggerFinalPath);
   fChain->SetBranchAddress("L1simulation_step", &L1simulation_step, &b_L1simulation_step);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("pass_selection", &pass_selection, &b_pass_selection);
   fChain->SetBranchAddress("photon_selection", &photon_selection, &b_photon_selection);
   fChain->SetBranchAddress("channel", &channel, &b_channel);
   fChain->SetBranchAddress("lep1_pid", &lep1_pid, &b_lep1_pid);
   fChain->SetBranchAddress("lep2_pid", &lep2_pid, &b_lep2_pid);
   fChain->SetBranchAddress("lep1pt", &lep1pt, &b_lep1pt);
   fChain->SetBranchAddress("lep2pt", &lep2pt, &b_lep2pt);
   fChain->SetBranchAddress("lep1eta", &lep1eta, &b_lep1eta);
   fChain->SetBranchAddress("lep2eta", &lep2eta, &b_lep2eta);
   fChain->SetBranchAddress("lep1phi", &lep1phi, &b_lep1phi);
   fChain->SetBranchAddress("lep2phi", &lep2phi, &b_lep2phi);
   fChain->SetBranchAddress("drll", &drll, &b_drll);
   fChain->SetBranchAddress("lep1_charge", &lep1_charge, &b_lep1_charge);
   fChain->SetBranchAddress("lep2_charge", &lep2_charge, &b_lep2_charge);
   fChain->SetBranchAddress("lep1_isprompt", &lep1_isprompt, &b_lep1_isprompt);
   fChain->SetBranchAddress("lep2_isprompt", &lep2_isprompt, &b_lep2_isprompt);
   fChain->SetBranchAddress("lep1_is_tight", &lep1_is_tight, &b_lep1_is_tight);
   fChain->SetBranchAddress("lep2_is_tight", &lep2_is_tight, &b_lep2_is_tight);
   fChain->SetBranchAddress("n_loose_mu", &n_loose_mu, &b_n_loose_mu);
   fChain->SetBranchAddress("n_loose_ele", &n_loose_ele, &b_n_loose_ele);
   fChain->SetBranchAddress("n_leptons", &n_leptons, &b_n_leptons);
   fChain->SetBranchAddress("n_photon", &n_photon, &b_n_photon);
   fChain->SetBranchAddress("photonet", &photonet, &b_photonet);
   fChain->SetBranchAddress("photoneta", &photoneta, &b_photoneta);
   fChain->SetBranchAddress("photonphi", &photonphi, &b_photonphi);
   fChain->SetBranchAddress("photonchiso", &photonchiso, &b_photonchiso);
   fChain->SetBranchAddress("drl1a", &drl1a, &b_drl1a);
   fChain->SetBranchAddress("drl2a", &drl2a, &b_drl2a);
   fChain->SetBranchAddress("photon_isprompt", &photon_isprompt, &b_photon_isprompt);
   fChain->SetBranchAddress("photon_gen_matching", &photon_gen_matching, &b_photon_gen_matching);
   fChain->SetBranchAddress("mll", &mll, &b_mll);
   fChain->SetBranchAddress("mllg", &mllg, &b_mllg);
   fChain->SetBranchAddress("ptll", &ptll, &b_ptll);
   fChain->SetBranchAddress("mt", &mt, &b_mt);
   fChain->SetBranchAddress("puppimt", &puppimt, &b_puppimt);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("metup", &metup, &b_metup);
   fChain->SetBranchAddress("puppimet", &puppimet, &b_puppimet);
   fChain->SetBranchAddress("puppimetphi", &puppimetphi, &b_puppimetphi);
   fChain->SetBranchAddress("rawmet", &rawmet, &b_rawmet);
   fChain->SetBranchAddress("rawmetphi", &rawmetphi, &b_rawmetphi);
   fChain->SetBranchAddress("metphi", &metphi, &b_metphi);
   fChain->SetBranchAddress("gen_weight", &gen_weight, &b_gen_weight);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("ntruepu", &ntruepu, &b_ntruepu);
   fChain->SetBranchAddress("MET_pass", &MET_pass, &b_MET_pass);
   fChain->SetBranchAddress("npvs", &npvs, &b_npvs);
   fChain->SetBranchAddress("n_bjets_loose_deepcsv", &n_bjets_loose_deepcsv, &b_n_bjets_loose_deepcsv);
   fChain->SetBranchAddress("n_bjets_loose_deepFlavB", &n_bjets_loose_deepFlavB, &b_n_bjets_loose_deepFlavB);
   fChain->SetBranchAddress("n_bjets20_loose_deepcsv", &n_bjets20_loose_deepcsv, &b_n_bjets20_loose_deepcsv);
   fChain->SetBranchAddress("n_bjets20_loose_deepFlavB", &n_bjets20_loose_deepFlavB, &b_n_bjets20_loose_deepFlavB);
   fChain->SetBranchAddress("n_bjets_medium_deepcsv", &n_bjets_medium_deepcsv, &b_n_bjets_medium_deepcsv);
   fChain->SetBranchAddress("n_bjets_medium_deepFlavB", &n_bjets_medium_deepFlavB, &b_n_bjets_medium_deepFlavB);
   fChain->SetBranchAddress("n_bjets20_medium_deepcsv", &n_bjets20_medium_deepcsv, &b_n_bjets20_medium_deepcsv);
   fChain->SetBranchAddress("n_bjets20_medium_deepFlavB", &n_bjets20_medium_deepFlavB, &b_n_bjets20_medium_deepFlavB);
   fChain->SetBranchAddress("njets50", &njets50, &b_njets50);
   fChain->SetBranchAddress("njets40", &njets40, &b_njets40);
   fChain->SetBranchAddress("njets30", &njets30, &b_njets30);
   fChain->SetBranchAddress("njets20", &njets20, &b_njets20);
   fChain->SetBranchAddress("njets50_pc", &njets50_pc, &b_njets50_pc);
   fChain->SetBranchAddress("njets40_pc", &njets40_pc, &b_njets40_pc);
   fChain->SetBranchAddress("njets30_pc", &njets30_pc, &b_njets30_pc);
   fChain->SetBranchAddress("njets20_pc", &njets20_pc, &b_njets20_pc);
   fChain->SetBranchAddress("n_bjets_loose_deepcsv_pc", &n_bjets_loose_deepcsv_pc, &b_n_bjets_loose_deepcsv_pc);
   fChain->SetBranchAddress("n_bjets_loose_deepFlavB_pc", &n_bjets_loose_deepFlavB_pc, &b_n_bjets_loose_deepFlavB_pc);
   fChain->SetBranchAddress("n_bjets20_loose_deepcsv_pc", &n_bjets20_loose_deepcsv_pc, &b_n_bjets20_loose_deepcsv_pc);
   fChain->SetBranchAddress("n_bjets20_loose_deepFlavB_pc", &n_bjets20_loose_deepFlavB_pc, &b_n_bjets20_loose_deepFlavB_pc);
   fChain->SetBranchAddress("n_bjets_medium_deepcsv_pc", &n_bjets_medium_deepcsv_pc, &b_n_bjets_medium_deepcsv_pc);
   fChain->SetBranchAddress("n_bjets_medium_deepFlavB_pc", &n_bjets_medium_deepFlavB_pc, &b_n_bjets_medium_deepFlavB_pc);
   fChain->SetBranchAddress("n_bjets20_medium_deepcsv_pc", &n_bjets20_medium_deepcsv_pc, &b_n_bjets20_medium_deepcsv_pc);
   fChain->SetBranchAddress("n_bjets20_medium_deepFlavB_pc", &n_bjets20_medium_deepFlavB_pc, &b_n_bjets20_medium_deepFlavB_pc);
   fChain->SetBranchAddress("Jet_pt_raw", Jet_pt_raw, &b_Jet_pt_raw);
   fChain->SetBranchAddress("Jet_pt_nom", Jet_pt_nom, &b_Jet_pt_nom);
   fChain->SetBranchAddress("Jet_mass_raw", Jet_mass_raw, &b_Jet_mass_raw);
   fChain->SetBranchAddress("Jet_mass_nom", Jet_mass_nom, &b_Jet_mass_nom);
   fChain->SetBranchAddress("Jet_corr_JEC", Jet_corr_JEC, &b_Jet_corr_JEC);
   fChain->SetBranchAddress("Jet_corr_JER", Jet_corr_JER, &b_Jet_corr_JER);
   fChain->SetBranchAddress("MET_T1_pt", &MET_T1_pt, &b_MET_T1_pt);
   fChain->SetBranchAddress("MET_T1_phi", &MET_T1_phi, &b_MET_T1_phi);
   fChain->SetBranchAddress("MET_T1Smear_pt", &MET_T1Smear_pt, &b_MET_T1Smear_pt);
   fChain->SetBranchAddress("MET_T1Smear_phi", &MET_T1Smear_phi, &b_MET_T1Smear_phi);
   fChain->SetBranchAddress("Jet_pt_jer0Up", Jet_pt_jer0Up, &b_Jet_pt_jer0Up);
   fChain->SetBranchAddress("Jet_mass_jer0Up", Jet_mass_jer0Up, &b_Jet_mass_jer0Up);
   fChain->SetBranchAddress("MET_T1_pt_jer0Up", &MET_T1_pt_jer0Up, &b_MET_T1_pt_jer0Up);
   fChain->SetBranchAddress("MET_T1_phi_jer0Up", &MET_T1_phi_jer0Up, &b_MET_T1_phi_jer0Up);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer0Up", &MET_T1Smear_pt_jer0Up, &b_MET_T1Smear_pt_jer0Up);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer0Up", &MET_T1Smear_phi_jer0Up, &b_MET_T1Smear_phi_jer0Up);
   fChain->SetBranchAddress("Jet_pt_jer1Up", Jet_pt_jer1Up, &b_Jet_pt_jer1Up);
   fChain->SetBranchAddress("Jet_mass_jer1Up", Jet_mass_jer1Up, &b_Jet_mass_jer1Up);
   fChain->SetBranchAddress("MET_T1_pt_jer1Up", &MET_T1_pt_jer1Up, &b_MET_T1_pt_jer1Up);
   fChain->SetBranchAddress("MET_T1_phi_jer1Up", &MET_T1_phi_jer1Up, &b_MET_T1_phi_jer1Up);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer1Up", &MET_T1Smear_pt_jer1Up, &b_MET_T1Smear_pt_jer1Up);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer1Up", &MET_T1Smear_phi_jer1Up, &b_MET_T1Smear_phi_jer1Up);
   fChain->SetBranchAddress("Jet_pt_jer2Up", Jet_pt_jer2Up, &b_Jet_pt_jer2Up);
   fChain->SetBranchAddress("Jet_mass_jer2Up", Jet_mass_jer2Up, &b_Jet_mass_jer2Up);
   fChain->SetBranchAddress("MET_T1_pt_jer2Up", &MET_T1_pt_jer2Up, &b_MET_T1_pt_jer2Up);
   fChain->SetBranchAddress("MET_T1_phi_jer2Up", &MET_T1_phi_jer2Up, &b_MET_T1_phi_jer2Up);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer2Up", &MET_T1Smear_pt_jer2Up, &b_MET_T1Smear_pt_jer2Up);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer2Up", &MET_T1Smear_phi_jer2Up, &b_MET_T1Smear_phi_jer2Up);
   fChain->SetBranchAddress("Jet_pt_jer3Up", Jet_pt_jer3Up, &b_Jet_pt_jer3Up);
   fChain->SetBranchAddress("Jet_mass_jer3Up", Jet_mass_jer3Up, &b_Jet_mass_jer3Up);
   fChain->SetBranchAddress("MET_T1_pt_jer3Up", &MET_T1_pt_jer3Up, &b_MET_T1_pt_jer3Up);
   fChain->SetBranchAddress("MET_T1_phi_jer3Up", &MET_T1_phi_jer3Up, &b_MET_T1_phi_jer3Up);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer3Up", &MET_T1Smear_pt_jer3Up, &b_MET_T1Smear_pt_jer3Up);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer3Up", &MET_T1Smear_phi_jer3Up, &b_MET_T1Smear_phi_jer3Up);
   fChain->SetBranchAddress("Jet_pt_jer4Up", Jet_pt_jer4Up, &b_Jet_pt_jer4Up);
   fChain->SetBranchAddress("Jet_mass_jer4Up", Jet_mass_jer4Up, &b_Jet_mass_jer4Up);
   fChain->SetBranchAddress("MET_T1_pt_jer4Up", &MET_T1_pt_jer4Up, &b_MET_T1_pt_jer4Up);
   fChain->SetBranchAddress("MET_T1_phi_jer4Up", &MET_T1_phi_jer4Up, &b_MET_T1_phi_jer4Up);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer4Up", &MET_T1Smear_pt_jer4Up, &b_MET_T1Smear_pt_jer4Up);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer4Up", &MET_T1Smear_phi_jer4Up, &b_MET_T1Smear_phi_jer4Up);
   fChain->SetBranchAddress("Jet_pt_jer5Up", Jet_pt_jer5Up, &b_Jet_pt_jer5Up);
   fChain->SetBranchAddress("Jet_mass_jer5Up", Jet_mass_jer5Up, &b_Jet_mass_jer5Up);
   fChain->SetBranchAddress("MET_T1_pt_jer5Up", &MET_T1_pt_jer5Up, &b_MET_T1_pt_jer5Up);
   fChain->SetBranchAddress("MET_T1_phi_jer5Up", &MET_T1_phi_jer5Up, &b_MET_T1_phi_jer5Up);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer5Up", &MET_T1Smear_pt_jer5Up, &b_MET_T1Smear_pt_jer5Up);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer5Up", &MET_T1Smear_phi_jer5Up, &b_MET_T1Smear_phi_jer5Up);
   fChain->SetBranchAddress("Jet_pt_jesTotalUp", Jet_pt_jesTotalUp, &b_Jet_pt_jesTotalUp);
   fChain->SetBranchAddress("Jet_mass_jesTotalUp", Jet_mass_jesTotalUp, &b_Jet_mass_jesTotalUp);
   fChain->SetBranchAddress("MET_T1_pt_jesTotalUp", &MET_T1_pt_jesTotalUp, &b_MET_T1_pt_jesTotalUp);
   fChain->SetBranchAddress("MET_T1_phi_jesTotalUp", &MET_T1_phi_jesTotalUp, &b_MET_T1_phi_jesTotalUp);
   fChain->SetBranchAddress("MET_T1Smear_pt_jesTotalUp", &MET_T1Smear_pt_jesTotalUp, &b_MET_T1Smear_pt_jesTotalUp);
   fChain->SetBranchAddress("MET_T1Smear_phi_jesTotalUp", &MET_T1Smear_phi_jesTotalUp, &b_MET_T1Smear_phi_jesTotalUp);
   fChain->SetBranchAddress("Jet_pt_jesHEMIssueUp", Jet_pt_jesHEMIssueUp, &b_Jet_pt_jesHEMIssueUp);
   fChain->SetBranchAddress("Jet_mass_jesHEMIssueUp", Jet_mass_jesHEMIssueUp, &b_Jet_mass_jesHEMIssueUp);
   fChain->SetBranchAddress("MET_T1_pt_jesHEMIssueUp", &MET_T1_pt_jesHEMIssueUp, &b_MET_T1_pt_jesHEMIssueUp);
   fChain->SetBranchAddress("MET_T1_phi_jesHEMIssueUp", &MET_T1_phi_jesHEMIssueUp, &b_MET_T1_phi_jesHEMIssueUp);
   fChain->SetBranchAddress("MET_T1Smear_pt_jesHEMIssueUp", &MET_T1Smear_pt_jesHEMIssueUp, &b_MET_T1Smear_pt_jesHEMIssueUp);
   fChain->SetBranchAddress("MET_T1Smear_phi_jesHEMIssueUp", &MET_T1Smear_phi_jesHEMIssueUp, &b_MET_T1Smear_phi_jesHEMIssueUp);
   fChain->SetBranchAddress("MET_T1_pt_unclustEnUp", &MET_T1_pt_unclustEnUp, &b_MET_T1_pt_unclustEnUp);
   fChain->SetBranchAddress("MET_T1_phi_unclustEnUp", &MET_T1_phi_unclustEnUp, &b_MET_T1_phi_unclustEnUp);
   fChain->SetBranchAddress("MET_T1Smear_pt_unclustEnUp", &MET_T1Smear_pt_unclustEnUp, &b_MET_T1Smear_pt_unclustEnUp);
   fChain->SetBranchAddress("MET_T1Smear_phi_unclustEnUp", &MET_T1Smear_phi_unclustEnUp, &b_MET_T1Smear_phi_unclustEnUp);
   fChain->SetBranchAddress("Jet_pt_jer0Down", Jet_pt_jer0Down, &b_Jet_pt_jer0Down);
   fChain->SetBranchAddress("Jet_mass_jer0Down", Jet_mass_jer0Down, &b_Jet_mass_jer0Down);
   fChain->SetBranchAddress("MET_T1_pt_jer0Down", &MET_T1_pt_jer0Down, &b_MET_T1_pt_jer0Down);
   fChain->SetBranchAddress("MET_T1_phi_jer0Down", &MET_T1_phi_jer0Down, &b_MET_T1_phi_jer0Down);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer0Down", &MET_T1Smear_pt_jer0Down, &b_MET_T1Smear_pt_jer0Down);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer0Down", &MET_T1Smear_phi_jer0Down, &b_MET_T1Smear_phi_jer0Down);
   fChain->SetBranchAddress("Jet_pt_jer1Down", Jet_pt_jer1Down, &b_Jet_pt_jer1Down);
   fChain->SetBranchAddress("Jet_mass_jer1Down", Jet_mass_jer1Down, &b_Jet_mass_jer1Down);
   fChain->SetBranchAddress("MET_T1_pt_jer1Down", &MET_T1_pt_jer1Down, &b_MET_T1_pt_jer1Down);
   fChain->SetBranchAddress("MET_T1_phi_jer1Down", &MET_T1_phi_jer1Down, &b_MET_T1_phi_jer1Down);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer1Down", &MET_T1Smear_pt_jer1Down, &b_MET_T1Smear_pt_jer1Down);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer1Down", &MET_T1Smear_phi_jer1Down, &b_MET_T1Smear_phi_jer1Down);
   fChain->SetBranchAddress("Jet_pt_jer2Down", Jet_pt_jer2Down, &b_Jet_pt_jer2Down);
   fChain->SetBranchAddress("Jet_mass_jer2Down", Jet_mass_jer2Down, &b_Jet_mass_jer2Down);
   fChain->SetBranchAddress("MET_T1_pt_jer2Down", &MET_T1_pt_jer2Down, &b_MET_T1_pt_jer2Down);
   fChain->SetBranchAddress("MET_T1_phi_jer2Down", &MET_T1_phi_jer2Down, &b_MET_T1_phi_jer2Down);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer2Down", &MET_T1Smear_pt_jer2Down, &b_MET_T1Smear_pt_jer2Down);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer2Down", &MET_T1Smear_phi_jer2Down, &b_MET_T1Smear_phi_jer2Down);
   fChain->SetBranchAddress("Jet_pt_jer3Down", Jet_pt_jer3Down, &b_Jet_pt_jer3Down);
   fChain->SetBranchAddress("Jet_mass_jer3Down", Jet_mass_jer3Down, &b_Jet_mass_jer3Down);
   fChain->SetBranchAddress("MET_T1_pt_jer3Down", &MET_T1_pt_jer3Down, &b_MET_T1_pt_jer3Down);
   fChain->SetBranchAddress("MET_T1_phi_jer3Down", &MET_T1_phi_jer3Down, &b_MET_T1_phi_jer3Down);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer3Down", &MET_T1Smear_pt_jer3Down, &b_MET_T1Smear_pt_jer3Down);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer3Down", &MET_T1Smear_phi_jer3Down, &b_MET_T1Smear_phi_jer3Down);
   fChain->SetBranchAddress("Jet_pt_jer4Down", Jet_pt_jer4Down, &b_Jet_pt_jer4Down);
   fChain->SetBranchAddress("Jet_mass_jer4Down", Jet_mass_jer4Down, &b_Jet_mass_jer4Down);
   fChain->SetBranchAddress("MET_T1_pt_jer4Down", &MET_T1_pt_jer4Down, &b_MET_T1_pt_jer4Down);
   fChain->SetBranchAddress("MET_T1_phi_jer4Down", &MET_T1_phi_jer4Down, &b_MET_T1_phi_jer4Down);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer4Down", &MET_T1Smear_pt_jer4Down, &b_MET_T1Smear_pt_jer4Down);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer4Down", &MET_T1Smear_phi_jer4Down, &b_MET_T1Smear_phi_jer4Down);
   fChain->SetBranchAddress("Jet_pt_jer5Down", Jet_pt_jer5Down, &b_Jet_pt_jer5Down);
   fChain->SetBranchAddress("Jet_mass_jer5Down", Jet_mass_jer5Down, &b_Jet_mass_jer5Down);
   fChain->SetBranchAddress("MET_T1_pt_jer5Down", &MET_T1_pt_jer5Down, &b_MET_T1_pt_jer5Down);
   fChain->SetBranchAddress("MET_T1_phi_jer5Down", &MET_T1_phi_jer5Down, &b_MET_T1_phi_jer5Down);
   fChain->SetBranchAddress("MET_T1Smear_pt_jer5Down", &MET_T1Smear_pt_jer5Down, &b_MET_T1Smear_pt_jer5Down);
   fChain->SetBranchAddress("MET_T1Smear_phi_jer5Down", &MET_T1Smear_phi_jer5Down, &b_MET_T1Smear_phi_jer5Down);
   fChain->SetBranchAddress("Jet_pt_jesTotalDown", Jet_pt_jesTotalDown, &b_Jet_pt_jesTotalDown);
   fChain->SetBranchAddress("Jet_mass_jesTotalDown", Jet_mass_jesTotalDown, &b_Jet_mass_jesTotalDown);
   fChain->SetBranchAddress("MET_T1_pt_jesTotalDown", &MET_T1_pt_jesTotalDown, &b_MET_T1_pt_jesTotalDown);
   fChain->SetBranchAddress("MET_T1_phi_jesTotalDown", &MET_T1_phi_jesTotalDown, &b_MET_T1_phi_jesTotalDown);
   fChain->SetBranchAddress("MET_T1Smear_pt_jesTotalDown", &MET_T1Smear_pt_jesTotalDown, &b_MET_T1Smear_pt_jesTotalDown);
   fChain->SetBranchAddress("MET_T1Smear_phi_jesTotalDown", &MET_T1Smear_phi_jesTotalDown, &b_MET_T1Smear_phi_jesTotalDown);
   fChain->SetBranchAddress("Jet_pt_jesHEMIssueDown", Jet_pt_jesHEMIssueDown, &b_Jet_pt_jesHEMIssueDown);
   fChain->SetBranchAddress("Jet_mass_jesHEMIssueDown", Jet_mass_jesHEMIssueDown, &b_Jet_mass_jesHEMIssueDown);
   fChain->SetBranchAddress("MET_T1_pt_jesHEMIssueDown", &MET_T1_pt_jesHEMIssueDown, &b_MET_T1_pt_jesHEMIssueDown);
   fChain->SetBranchAddress("MET_T1_phi_jesHEMIssueDown", &MET_T1_phi_jesHEMIssueDown, &b_MET_T1_phi_jesHEMIssueDown);
   fChain->SetBranchAddress("MET_T1Smear_pt_jesHEMIssueDown", &MET_T1Smear_pt_jesHEMIssueDown, &b_MET_T1Smear_pt_jesHEMIssueDown);
   fChain->SetBranchAddress("MET_T1Smear_phi_jesHEMIssueDown", &MET_T1Smear_phi_jesHEMIssueDown, &b_MET_T1Smear_phi_jesHEMIssueDown);
   fChain->SetBranchAddress("MET_T1_pt_unclustEnDown", &MET_T1_pt_unclustEnDown, &b_MET_T1_pt_unclustEnDown);
   fChain->SetBranchAddress("MET_T1_phi_unclustEnDown", &MET_T1_phi_unclustEnDown, &b_MET_T1_phi_unclustEnDown);
   fChain->SetBranchAddress("MET_T1Smear_pt_unclustEnDown", &MET_T1Smear_pt_unclustEnDown, &b_MET_T1Smear_pt_unclustEnDown);
   fChain->SetBranchAddress("MET_T1Smear_phi_unclustEnDown", &MET_T1Smear_phi_unclustEnDown, &b_MET_T1Smear_phi_unclustEnDown);
   fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
   fChain->SetBranchAddress("puWeightUp", &puWeightUp, &b_puWeightUp);
   fChain->SetBranchAddress("puWeightDown", &puWeightDown, &b_puWeightDown);
   Notify();
}

Bool_t chain_WWg::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void chain_WWg::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
void chain_WWg::endJob() {
        fout->cd();
        ExTree->Write();
        fout->Write();
        fout->Close();
        delete fout;
}
Int_t chain_WWg::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef chain_WWg_cxx
