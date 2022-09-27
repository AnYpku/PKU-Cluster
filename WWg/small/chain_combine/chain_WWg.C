#define chain_WWg_cxx
#include "chain_WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "TLorentzVector.h"
using namespace std;
void chain_WWg::Loop(TString name)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   Bool_t BSL=0,LEP=0,PHOTON=0,missET=0;
   int tot=0;double pfmet,pfmetphi,puppimet,puppimetphi,phiVlep;
   TLorentzVector Zp4, photonp4, jet1p4, jet2p4,lep1p4,lep2p4;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      bool isdata=0,isMC=0;
      if(name.Contains("Muon")==0 && name.Contains("Ele")==0 && name.Contains("MET")==0 && name.Contains("EGamma")==0 ) isMC=1;
      else isdata=1;

      if(isdata) scalef=1;

      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;

      LEP = channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 /*&& lep1_charge*lep2_charge<0*/ && drll>0.5 && lep1pt>15 && lep2pt>15 && fabs(lep1eta) < 2.4 && fabs(lep2eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20;
      PHOTON = n_photon>0 && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5 && fabs(photoneta)>1.566 ) ) && drl1a>0.5 && drl2a>0.5;

      if( !( LEP ) )
	      continue;

      lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
      lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.000511);
      phiVlep=(lep1p4+lep2p4).Phi();
      photonp4.SetPtEtaPhiM(photonet, photoneta, photonphi,0);

      if( name.Contains("Muon")||name.Contains("Ele") ){
	      pfmet=MET_T1_pt;pfmetphi=MET_T1_phi;
      }
      else{
	      pfmet=MET_T1Smear_pt;pfmetphi=MET_T1Smear_phi;
      }
      puppimet=PuppiMET_pt;puppimetphi=PuppiMET_phi;

      mT_pf=sqrt(2*(ptll*pfmet*(1-cos(phiVlep-pfmetphi) ) ) );
      mT_puppi=sqrt(2*(ptll*puppimet*(1-cos(phiVlep-puppimetphi) ) ) );

      if(lep1pt>lep2pt){
	      mT2_pf=sqrt(2*(lep2pt*pfmet*(1-cos(lep2phi-pfmetphi) ) ) );
	      mT2_puppi=sqrt(2*(lep2pt*puppimet*(1-cos(lep2phi-puppimetphi) ) ) );
	      ml1g=(lep1p4+photonp4).M();
	      ml2g=(lep2p4+photonp4).M();
      }
      else{
	      mT2_pf=sqrt(2*(lep1pt*pfmet*(1-cos(lep1phi-pfmetphi) ) ) );
	      mT2_puppi=sqrt(2*(lep1pt*puppimet*(1-cos(lep1phi-puppimetphi) ) ) );
	      ml1g=(lep2p4+photonp4).M();
	      ml2g=(lep1p4+photonp4).M();
      } 

      ExTree->Fill();
      tot++;
      // if (Cut(ientry) < 0) continue;
   }
   cout<<nentries<<" "<<tot<<endl;
}
