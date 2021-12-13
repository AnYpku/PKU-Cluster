#define WWg_cxx
#include "genparticles.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;
void WWg::Loop(TString name)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
//   nentries=1000;

   Long64_t nbytes = 0, nb = 0;
   Bool_t BSL=0;
   Bool_t GenLEP=0,GenPHOTON=0,GenMET=0,GenJET=0;
   Bool_t LEP=0,PHOTON=0,MET=0,JET=0;
   int tot=0,nlep=0,nphoton=0;
   TLorentzVector Zp4, photonp4, lep1p4, lep2p4;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
           ResetValue();
	   Init();
           genparticles();

	   lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
	   lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.000511);
	   yVlep=(lep1p4+lep2p4).Eta();
	   phiVlep=(lep1p4+lep2p4).Phi();
	   ptVlep=(lep1p4+lep2p4).Pt();
	   mll=(lep1p4+lep2p4).M();
	   photonp4.SetPtEtaPhiM(photonet, photoneta, photonphi,0);
           Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, mll);
	   mllg=(Zp4+photonp4).M();

	   genmT=sqrt(2*(genptll*GenMET_pt*(1-cos(genphiVlep-GenMET_phi) ) ) );
	   mT=sqrt(2*(ptll*PuppiMET_T1Smear_pt*(1-cos(phiVlep-PuppiMET_T1Smear_phi) ) ) );

	   if(genlep1>genlep2)
		   genmT2=sqrt(2*(genlep2pt*GenMET_pt*(1-cos(genlep2phi-GenMET_phi) ) ) );
           else
                   genmT2=sqrt(2*(genlep2pt*GenMET_pt*(1-cos(genlep2phi-GenMET_phi) ) ) );

	   if(lep1pt>lep2pt)
		   mT2=sqrt(2*(lep2pt*PuppiMET_T1Smear_pt*(1-cos(lep2phi-PuppiMET_T1Smear_phi) ) ) );
	   else
		   mT2=sqrt(2*(lep1pt*PuppiMET_T1Smear_pt*(1-cos(lep1phi-PuppiMET_T1Smear_phi) ) ) );

	   HLT_emu1=HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
	   HLT_emu2=HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
	   HLT_emu3=HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
	   HLT_emu4=HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;

	   LEP = ( (HLT_emu1||HLT_emu2||HLT_emu3||HLT_emu4) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1_charge*lep2_charge<0 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_is_tight==1 && lep2_is_tight==1 && lep1_isprompt==1 && lep2_isprompt==1 && drll>0.5 );
	   PHOTON = ( n_photon>0  && photonet > 20. &&( (fabs(photoneta) < 1.4442) || ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 )) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && photon_isprompt==1 );
           MET = ( PuppiMET_T1Smear_pt > 20 && mT>50 && mT2>20 );
           JET = ( n_bjets_nom==0 && njets30<=1 );

           GenLEP = ( gen_channel==1 && fabs(genlep1)==13 && fabs(genlep2)==11 && gendrll>0.5 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta) < 2.4 && fabs(genlep1eta) < 2.5 && genptll>30 && genmll>20);
           GenPHOTON = ( genphotonet>20 && ( fabs(genphotoneta)<1.4442 || (fabs(genphotoneta)<2.5 && fabs(genphotoneta)>1.566 )) && gendrl1a>0.5 && gendrl2a>0.5 );
           GenMET = (GenMET_pt>20 && genmT>50 && genmT2>20) ;
           GenJET = (n_genbjets==0 && n_genjets30<=1);

           if( (GenLEP && GenPHOTON && GenMET && GenJET))
		   tot++;
	   ExTree->Fill();
   }
   cout<<nentries<<" Full Gen "<<tot<<endl;
}
void WWg::Init(){
	ele_id_scale=1;ele_id_scale_Up=1;ele_id_scale_Down=1;
	ele_reco_scale=1;ele_reco_scale_Up=1;ele_reco_scale_Down=1;
	muon_id_scale=1;muon_id_scale_Up=1;muon_id_scale_Down=1;
	muon_iso_scale=1;muon_iso_scale_Up=1;muon_iso_scale_Down=1;
	photon_id_scale=1;photon_id_scale_Up=1;photon_id_scale_Down=1;
	photon_veto_scale=1;photon_veto_scale_Up=1;photon_veto_scale_Down=1;
	HLT_emu1=0;HLT_emu2=0;HLT_emu3=0;HLT_emu4=0;
}
      
Float_t WWg::delta_R(Float_t eta1, Float_t phi1, Float_t eta2, Float_t phi2)
{
        Float_t dp = phi1-phi2;
        if(std::fabs(dp) > pi) dp = 2*pi - std::fabs(dp);
        Float_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
        return dr;
}
