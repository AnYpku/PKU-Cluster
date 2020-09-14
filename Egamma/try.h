//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr 30 22:01:39 2019 by ROOT version 6.06/01
// from TTree hltGenTree/
// found on file: zToEE_M_50_120_102X_TrigNtup.root
//////////////////////////////////////////////////////////

#ifndef try_h
#define try_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class try : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> runnr = {fReader, "evt.runnr"};
   TTreeReaderValue<Int_t> lumiSec = {fReader, "evt.lumiSec"};
   TTreeReaderValue<Int_t> eventnr = {fReader, "evt.eventnr"};
   TTreeReaderValue<Int_t> bx = {fReader, "evt.bx"};
   TTreeReaderValue<Int_t> datasetCode = {fReader, "evt.datasetCode"};
   TTreeReaderValue<Int_t> nrTruePUInt = {fReader, "genPU.nrTruePUInt"};
   TTreeReaderValue<Int_t> nrPUInt = {fReader, "genPU.nrPUInt"};
   TTreeReaderValue<Int_t> nrPUIntPos = {fReader, "genPU.nrPUIntPos"};
   TTreeReaderValue<Int_t> nrPUIntNeg = {fReader, "genPU.nrPUIntNeg"};
   TTreeReaderValue<Float_t> weight = {fReader, "weight"};
   TTreeReaderValue<Float_t> genWeight = {fReader, "genWeight"};
   TTreeReaderValue<Float_t> puWeight = {fReader, "puWeight"};
   TTreeReaderValue<Float_t> truthDR = {fReader, "truthDR"};
   TTreeReaderValue<Float_t> nrgy = {fReader, "nrgy"};
   TTreeReaderValue<Float_t> clusNrgy = {fReader, "clusNrgy"};
   TTreeReaderValue<Float_t> gsfNrgy = {fReader, "gsfNrgy"};
   TTreeReaderValue<Float_t> preShowerNrgy = {fReader, "preShowerNrgy"};
   TTreeReaderValue<Float_t> et = {fReader, "et"};
   TTreeReaderValue<Float_t> clusEt = {fReader, "clusEt"};
   TTreeReaderValue<Float_t> eta = {fReader, "eta"};
   TTreeReaderValue<Float_t> phi = {fReader, "phi"};
   TTreeReaderValue<Float_t> detEta = {fReader, "detEta"};
   TTreeReaderValue<Float_t> detPhi = {fReader, "detPhi"};
   TTreeReaderValue<Float_t> z0 = {fReader, "z0"};
   TTreeReaderValue<Char_t> region = {fReader, "region"};
   TTreeReaderValue<Char_t> q = {fReader, "q"};
   TTreeReaderValue<Float_t> trkPt = {fReader, "trkPt"};
   TTreeReaderValue<Float_t> epIn = {fReader, "epIn"};
   TTreeReaderValue<Float_t> epOut = {fReader, "epOut"};
   TTreeReaderValue<Float_t> invEinvP = {fReader, "invEinvP"};
   TTreeReaderValue<Float_t> bremFrac = {fReader, "bremFrac"};
   TTreeReaderValue<Float_t> trkPInn = {fReader, "trkPInn"};
   TTreeReaderValue<Float_t> trkEtaInn = {fReader, "trkEtaInn"};
   TTreeReaderValue<Float_t> trkPhiInn = {fReader, "trkPhiInn"};
   TTreeReaderValue<Float_t> dEtaIn = {fReader, "dEtaIn"};
   TTreeReaderValue<Float_t> dEtaInSeed = {fReader, "dEtaInSeed"};
   TTreeReaderValue<Float_t> dPhiIn = {fReader, "dPhiIn"};
   TTreeReaderValue<Float_t> hadem = {fReader, "hadem"};
   TTreeReaderValue<Float_t> sigmaIEtaIEta = {fReader, "sigmaIEtaIEta"};
   TTreeReaderValue<Float_t> e1x5Over5x5 = {fReader, "e1x5Over5x5"};
   TTreeReaderValue<Float_t> e2x5Over5x5 = {fReader, "e2x5Over5x5"};
   TTreeReaderValue<Float_t> e5x5 = {fReader, "e5x5"};
   TTreeReaderValue<Float_t> isolEm = {fReader, "isolEm"};
   TTreeReaderValue<Float_t> isolHadDepth1 = {fReader, "isolHadDepth1"};
   TTreeReaderValue<Float_t> isolHadDepth2 = {fReader, "isolHadDepth2"};
   TTreeReaderValue<Float_t> isolPtTrks = {fReader, "isolPtTrks"};
   TTreeReaderValue<Float_t> dxy = {fReader, "dxy"};
   TTreeReaderValue<Float_t> nrMissHits = {fReader, "nrMissHits"};
   TTreeReaderValue<Float_t> r9 = {fReader, "r9"};
   TTreeReaderValue<Float_t> rhoCorr = {fReader, "rhoCorr"};
   TTreeReaderValue<Float_t> isolCharged = {fReader, "isolCharged"};
   TTreeReaderValue<Float_t> isolNeutral = {fReader, "isolNeutral"};
   TTreeReaderValue<Float_t> isolPhoton = {fReader, "isolPhoton"};
   TTreeReaderValue<Float_t> isolEcalClus = {fReader, "isolEcalClus"};
   TTreeReaderValue<Float_t> isolHcalClus = {fReader, "isolHcalClus"};
   TTreeReaderValue<Float_t> hademDepth1BC = {fReader, "hademDepth1BC"};
   TTreeReaderValue<Float_t> hademDepth2BC = {fReader, "hademDepth2BC"};
   TTreeReaderValue<Char_t> nrSatIn5x5 = {fReader, "nrSatIn5x5"};
   TTreeReaderValue<Bool_t> passCutPreSel = {fReader, "passCutPreSel"};
   TTreeReaderValue<Bool_t> passPFPreSel = {fReader, "passPFPreSel"};
   TTreeReaderValue<Bool_t> hasTrk = {fReader, "hasTrk"};
   TTreeReaderValue<Bool_t> isEcalDriven = {fReader, "isEcalDriven"};
   TTreeReaderValue<Bool_t> isTrackerDriven = {fReader, "isTrackerDriven"};
   TTreeReaderValue<Int_t> cutCode = {fReader, "cutCode"};
   TTreeReaderValue<Int_t> vidIds = {fReader, "vidIds"};
   TTreeReaderValue<Float_t> rawNrgy = {fReader, "rawNrgy"};
   TTreeReaderValue<Float_t> seedClusEt = {fReader, "seedClusEt"};
   TTreeReaderValue<Float_t> seedClusEta = {fReader, "seedClusEta"};
   TTreeReaderValue<Float_t> seedClusPhi = {fReader, "seedClusPhi"};
   TTreeReaderValue<Short_t> nrClus = {fReader, "nrClus"};
   TTreeReaderValue<Short_t> nrCrys = {fReader, "nrCrys"};
   TTreeReaderValue<Float_t> eMax = {fReader, "eMax"};
   TTreeReaderValue<Float_t> e3x3 = {fReader, "e3x3"};
   TTreeReaderValue<Short_t> eMaxPhi = {fReader, "eMaxPhi"};
   TTreeReaderValue<Short_t> eMaxEta = {fReader, "eMaxEta"};
   TTreeReaderValue<Short_t> eMaxTowerPhi = {fReader, "eMaxTowerPhi"};
   TTreeReaderValue<Short_t> eMaxTowerEta = {fReader, "eMaxTowerEta"};
   TTreeReaderValue<Short_t> e2ndPhi = {fReader, "e2ndPhi"};
   TTreeReaderValue<Short_t> e2ndEta = {fReader, "e2ndEta"};
   TTreeReaderValue<Short_t> e2ndTowerPhi = {fReader, "e2ndTowerPhi"};
   TTreeReaderValue<Short_t> e2ndTowerEta = {fReader, "e2ndTowerEta"};
   TTreeReaderValue<Char_t> seedRegion = {fReader, "seedRegion"};
   TTreeReaderValue<Char_t> nrGain6In5x5 = {fReader, "nrGain6In5x5"};
   TTreeReaderValue<Char_t> nrGain1In5x5 = {fReader, "nrGain1In5x5"};
   TTreeReaderValue<Float_t> towerHadEt = {fReader, "towerHadEt"};
   TTreeReaderValue<Float_t> towerEmEt = {fReader, "towerEmEt"};
   TTreeReaderValue<Float_t> towerHadD1Nrgy = {fReader, "towerHadD1Nrgy"};
   TTreeReaderValue<Float_t> towerHadD2Nrgy = {fReader, "towerHadD2Nrgy"};
   TTreeReaderValue<Float_t> nrgyAlt = {fReader, "nrgyAlt"};
   TTreeReaderValue<Float_t> gsfNrgyAlt = {fReader, "gsfNrgyAlt"};
   TTreeReaderValue<Float_t> phoNrgy = {fReader, "phoNrgy"};
   TTreeReaderValue<Float_t> phoNrgyAlt = {fReader, "phoNrgyAlt"};
   TTreeReaderValue<Int_t> gain6Map = {fReader, "gain6Map"};
   TTreeReaderValue<Int_t> gain1Map = {fReader, "gain1Map"};
   TTreeReaderValue<Float_t> isolPtTrksAlt = {fReader, "isolPtTrksAlt"};
   TTreeReaderValue<Float_t> mvaIsol = {fReader, "mvaIsol"};
   TTreeReaderValue<Float_t> mvaNonIsol = {fReader, "mvaNonIsol"};
   TTreeReaderValue<Float_t> eleTruthNrgy = {fReader, "eleTruthNrgy"};
   TTreeReaderValue<Float_t> eleTruthPhi = {fReader, "eleTruthPhi"};
   TTreeReaderValue<Float_t> eleTruthEta = {fReader, "eleTruthEta"};
   TTreeReaderValue<Float_t> eleTruthDetEta = {fReader, "eleTruthDetEta"};
   TTreeReaderValue<Float_t> eleTruthRegion = {fReader, "eleTruthRegion"};
   TTreeReaderValue<Float_t> eleTruthEt = {fReader, "eleTruthEt"};
   TTreeReaderValue<Float_t> eleTruthZ = {fReader, "eleTruthZ"};
   TTreeReaderValue<Float_t> eleTruthY = {fReader, "eleTruthY"};
   TTreeReaderValue<Float_t> eleTruthX = {fReader, "eleTruthX"};
   TTreeReaderValue<Int_t> pid = {fReader, "pid"};
   TTreeReaderArray<Int_t> eleTrigs = {fReader, "eleTrigs"};
   TTreeReaderArray<Int_t> evtTrigs = {fReader, "evtTrigs"};
   TTreeReaderValue<Float_t> nrgy = {fReader, "hlt.nrgy"};
   TTreeReaderValue<Float_t> et = {fReader, "hlt.et"};
   TTreeReaderValue<Float_t> eta = {fReader, "hlt.eta"};
   TTreeReaderValue<Float_t> phi = {fReader, "hlt.phi"};
   TTreeReaderValue<Float_t> pt = {fReader, "hlt.pt"};
   TTreeReaderValue<Float_t> et = {fReader, "egHLT.et"};
   TTreeReaderValue<Float_t> nrgy = {fReader, "egHLT.nrgy"};
   TTreeReaderValue<Float_t> eta = {fReader, "egHLT.eta"};
   TTreeReaderValue<Float_t> phi = {fReader, "egHLT.phi"};
   TTreeReaderValue<Float_t> hadem = {fReader, "egHLT.hadem"};
   TTreeReaderValue<Float_t> sigmaIEtaIEta = {fReader, "egHLT.sigmaIEtaIEta"};
   TTreeReaderValue<Float_t> dEtaIn = {fReader, "egHLT.dEtaIn"};
   TTreeReaderValue<Float_t> dPhiIn = {fReader, "egHLT.dPhiIn"};
   TTreeReaderValue<Float_t> nrMissHits = {fReader, "egHLT.nrMissHits"};
   TTreeReaderValue<Float_t> nrClus = {fReader, "egHLT.nrClus"};
   TTreeReaderValue<Float_t> seedClusEFrac = {fReader, "egHLT.seedClusEFrac"};
   TTreeReaderValue<Float_t> pmDPhi1 = {fReader, "egHLT.pmDPhi1"};
   TTreeReaderValue<Float_t> pmDPhi2 = {fReader, "egHLT.pmDPhi2"};
   TTreeReaderValue<Float_t> pmDPhi3 = {fReader, "egHLT.pmDPhi3"};
   TTreeReaderValue<Float_t> pmDPhi4 = {fReader, "egHLT.pmDPhi4"};
   TTreeReaderValue<Float_t> pmDPhi1Info = {fReader, "egHLT.pmDPhi1Info"};
   TTreeReaderValue<Float_t> pmDPhi2Info = {fReader, "egHLT.pmDPhi2Info"};
   TTreeReaderValue<Float_t> pmDPhi3Info = {fReader, "egHLT.pmDPhi3Info"};
   TTreeReaderValue<Float_t> pmDPhi4Info = {fReader, "egHLT.pmDPhi4Info"};
   TTreeReaderValue<Float_t> pmDRZ1 = {fReader, "egHLT.pmDRZ1"};
   TTreeReaderValue<Float_t> pmDRZ2 = {fReader, "egHLT.pmDRZ2"};
   TTreeReaderValue<Float_t> pmDRZ3 = {fReader, "egHLT.pmDRZ3"};
   TTreeReaderValue<Float_t> pmDRZ4 = {fReader, "egHLT.pmDRZ4"};
   TTreeReaderValue<Float_t> pmDRZ1Info = {fReader, "egHLT.pmDRZ1Info"};
   TTreeReaderValue<Float_t> pmDRZ2Info = {fReader, "egHLT.pmDRZ2Info"};
   TTreeReaderValue<Float_t> pmDRZ3Info = {fReader, "egHLT.pmDRZ3Info"};
   TTreeReaderValue<Float_t> pmDRZ4Info = {fReader, "egHLT.pmDRZ4Info"};
   TTreeReaderValue<Float_t> phiWidth = {fReader, "egHLT.phiWidth"};
   TTreeReaderValue<Float_t> etaWidth = {fReader, "egHLT.etaWidth"};
   TTreeReaderValue<Float_t> s2 = {fReader, "egHLT.s2"};
   TTreeReaderValue<Float_t> dPhi1BestS2 = {fReader, "egHLT.dPhi1BestS2"};
   TTreeReaderValue<Float_t> dPhi2BestS2 = {fReader, "egHLT.dPhi2BestS2"};
   TTreeReaderValue<Float_t> dPhi3BestS2 = {fReader, "egHLT.dPhi3BestS2"};
   TTreeReaderValue<Float_t> dRZ2BestS2 = {fReader, "egHLT.dRZ2BestS2"};
   TTreeReaderValue<Float_t> dRZ3BestS2 = {fReader, "egHLT.dRZ3BestS2"};
   TTreeReaderValue<Float_t> ecalIso = {fReader, "egHLT.ecalIso"};
   TTreeReaderValue<Float_t> hcalIso = {fReader, "egHLT.hcalIso"};
   TTreeReaderValue<Float_t> trkIso = {fReader, "egHLT.trkIso"};
   TTreeReaderValue<Float_t> trkChi2 = {fReader, "egHLT.trkChi2"};
   TTreeReaderValue<Float_t> invEOInvP = {fReader, "egHLT.invEOInvP"};
   TTreeReaderValue<Float_t> et = {fReader, "egHLTUS.et"};
   TTreeReaderValue<Float_t> nrgy = {fReader, "egHLTUS.nrgy"};
   TTreeReaderValue<Float_t> eta = {fReader, "egHLTUS.eta"};
   TTreeReaderValue<Float_t> phi = {fReader, "egHLTUS.phi"};
   TTreeReaderValue<Float_t> hadem = {fReader, "egHLTUS.hadem"};
   TTreeReaderValue<Float_t> sigmaIEtaIEta = {fReader, "egHLTUS.sigmaIEtaIEta"};
   TTreeReaderValue<Float_t> dEtaIn = {fReader, "egHLTUS.dEtaIn"};
   TTreeReaderValue<Float_t> dPhiIn = {fReader, "egHLTUS.dPhiIn"};
   TTreeReaderValue<Float_t> nrMissHits = {fReader, "egHLTUS.nrMissHits"};
   TTreeReaderValue<Float_t> nrClus = {fReader, "egHLTUS.nrClus"};
   TTreeReaderValue<Float_t> seedClusEFrac = {fReader, "egHLTUS.seedClusEFrac"};
   TTreeReaderValue<Float_t> pmDPhi1 = {fReader, "egHLTUS.pmDPhi1"};
   TTreeReaderValue<Float_t> pmDPhi2 = {fReader, "egHLTUS.pmDPhi2"};
   TTreeReaderValue<Float_t> pmDPhi3 = {fReader, "egHLTUS.pmDPhi3"};
   TTreeReaderValue<Float_t> pmDPhi4 = {fReader, "egHLTUS.pmDPhi4"};
   TTreeReaderValue<Float_t> pmDPhi1Info = {fReader, "egHLTUS.pmDPhi1Info"};
   TTreeReaderValue<Float_t> pmDPhi2Info = {fReader, "egHLTUS.pmDPhi2Info"};
   TTreeReaderValue<Float_t> pmDPhi3Info = {fReader, "egHLTUS.pmDPhi3Info"};
   TTreeReaderValue<Float_t> pmDPhi4Info = {fReader, "egHLTUS.pmDPhi4Info"};
   TTreeReaderValue<Float_t> pmDRZ1 = {fReader, "egHLTUS.pmDRZ1"};
   TTreeReaderValue<Float_t> pmDRZ2 = {fReader, "egHLTUS.pmDRZ2"};
   TTreeReaderValue<Float_t> pmDRZ3 = {fReader, "egHLTUS.pmDRZ3"};
   TTreeReaderValue<Float_t> pmDRZ4 = {fReader, "egHLTUS.pmDRZ4"};
   TTreeReaderValue<Float_t> pmDRZ1Info = {fReader, "egHLTUS.pmDRZ1Info"};
   TTreeReaderValue<Float_t> pmDRZ2Info = {fReader, "egHLTUS.pmDRZ2Info"};
   TTreeReaderValue<Float_t> pmDRZ3Info = {fReader, "egHLTUS.pmDRZ3Info"};
   TTreeReaderValue<Float_t> pmDRZ4Info = {fReader, "egHLTUS.pmDRZ4Info"};
   TTreeReaderValue<Float_t> phiWidth = {fReader, "egHLTUS.phiWidth"};
   TTreeReaderValue<Float_t> etaWidth = {fReader, "egHLTUS.etaWidth"};
   TTreeReaderValue<Float_t> s2 = {fReader, "egHLTUS.s2"};
   TTreeReaderValue<Float_t> dPhi1BestS2 = {fReader, "egHLTUS.dPhi1BestS2"};
   TTreeReaderValue<Float_t> dPhi2BestS2 = {fReader, "egHLTUS.dPhi2BestS2"};
   TTreeReaderValue<Float_t> dPhi3BestS2 = {fReader, "egHLTUS.dPhi3BestS2"};
   TTreeReaderValue<Float_t> dRZ2BestS2 = {fReader, "egHLTUS.dRZ2BestS2"};
   TTreeReaderValue<Float_t> dRZ3BestS2 = {fReader, "egHLTUS.dRZ3BestS2"};
   TTreeReaderValue<Float_t> ecalIso = {fReader, "egHLTUS.ecalIso"};
   TTreeReaderValue<Float_t> hcalIso = {fReader, "egHLTUS.hcalIso"};
   TTreeReaderValue<Float_t> trkIso = {fReader, "egHLTUS.trkIso"};
   TTreeReaderValue<Float_t> trkChi2 = {fReader, "egHLTUS.trkChi2"};
   TTreeReaderValue<Float_t> invEOInvP = {fReader, "egHLTUS.invEOInvP"};
   TTreeReaderValue<Float_t> rho = {fReader, "rho"};
   TTreeReaderValue<Float_t> rhoAlt = {fReader, "rhoAlt"};


   try(TTree * /*tree*/ =0) { }
   virtual ~try() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(try,0);

};

#endif

#ifdef try_cxx
void try::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t try::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef try_cxx
