#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "TLorentzVector.h"
using namespace std;
void WWg::Loop(TString name)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   Bool_t HLT_mm=0,HLT_ee=0,HLT_emu=0;
   Bool_t BSL=0,LEP=0,PHOTON=0,missET=0;
   int tot=0;double met_tmp,metphi_tmp,phiVlep;
   TLorentzVector Zp4, photonp4, jet1p4, jet2p4,lep1p4,lep2p4;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      HLT_mm = (HLT_IsoMu24) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
      HLT_ee = (HLT_Ele32_WPTight_Gsf) || (HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
      HLT_emu = (HLT_Ele32_WPTight_Gsf) || (HLT_IsoMu24) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL); 
      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;
      BSL = (n_loose_ele+n_loose_mu)==2 && (HLT_mm || HLT_ee || HLT_emu);
      LEP = channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20;
      PHOTON = n_photon>0 && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5 && fabs(photoneta)>1.566 ) ) && drl1a>0.5 && drl2a>0.5;

      if( !( LEP && PHOTON  ) )
	      continue;

      lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
      lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.000511);
      phiVlep=(lep1p4+lep2p4).Phi();
      photonp4.SetPtEtaPhiM(photonet, photoneta, photonphi,0);

      if(name.Contains("Muon")||name.Contains("plj")||name.Contains("fake")){ met_tmp=PuppiMET_T1_pt;metphi_tmp=PuppiMET_T1_phi;}
      else{ met_tmp=PuppiMET_T1Smear_pt;metphi_tmp=PuppiMET_T1Smear_phi;}
      mT=sqrt(2*(ptll*met_tmp*(1-cos(phiVlep-metphi_tmp) ) ) );
      if(lep1pt>lep2pt){
	      mT2=sqrt(2*(lep2pt*met_tmp*(1-cos(lep2phi-metphi_tmp) ) ) );
              ml1g=(lep1p4+photonp4).M();
              ml2g=(lep2p4+photonp4).M();
      }
      else{
	      mT2=sqrt(2*(lep1pt*met_tmp*(1-cos(lep1phi-metphi_tmp) ) ) );
              ml1g=(lep2p4+photonp4).M();
              ml2g=(lep1p4+photonp4).M();
      } 
      ExTree->Fill();
      tot++;
      // if (Cut(ientry) < 0) continue;
   }
   cout<<nentries<<" "<<tot<<endl;
}
