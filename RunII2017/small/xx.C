#define xx_cxx
#include "L1_weight.C"
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "ele_channel_scale.C"
//#include "muon_channel_scale.C"

using namespace std;
void xx::Loop(TString name)
{
//   In a ROOT session, you can do:
//      root> .L xx.C
//      root> xx t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
//   double photonet_;
//   TFile* ID_photon_file = TFile::Open("./ele_SFs/2017_PhotonsMedium.root");
//   TH2F* ID_photon=0;
//   ID_photon_file->GetObject("EGamma_SF2D", ID_photon);
//   cout<<"open the photon ID file: 2017_PhotonsMedium.root"<<endl;

   double lep1_phi_station2_tmp = 0;
   double lep2_phi_station2_tmp = 0;
   cut0=0,cut1=0;
   bool LEPele,LEPmu,JET,PHOTON,SignalRegion,DR;
//  nentries=1000;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      cut0++;//total events, cut0=t1->GetEntries()
      
      if(name.Contains("Muon")) scalef=1;
      if(name.Contains("Ele")) scalef=1;

      lep1_phi_station2_tmp = lep1_phi_station2;
      lep2_phi_station2_tmp = lep2_phi_station2;      
      if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
      if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
      l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);      
      if(drla==10) drla=-1;
      if(drla2==10) drla2=-1; 
      if(drj1a==10) drj1a=-1;
      if(drj2a==10) drj2a=-1;
      int p=0;
      for(int i=0;i<257;i++){
              weight[p]=pweight[i];
              p++;
      }
      double photon_veto_scale;
      if(fabs(photoneta)<1.4442) photon_veto_scale=0.9862;
      if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566) photon_veto_scale=0.9638;
      if(lep==11)
              scalef=scalef*pileupWeight*photon_id_scale*photon_veto_scale*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*prefWeight;
      if(lep==13)
              scalef=scalef*pileupWeight*photon_id_scale*photon_veto_scale*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon1_track_scale*muon2_track_scale*prefWeight;

      LEPele = lep==11 && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
      LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0||HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && ngoodmus>1;
      SignalRegion= Mjj>500 && deltaetajj>2.5;// && zepp<1.8;
      PHOTON= photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );
//      JET=jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && !(fabs(jet1eta)<3&&fabs(jet1eta)>2.7) && !(fabs(jet2eta)<3&&fabs(jet2eta)>2.7);
      JET= ( (!(fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65) && !(fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) &&  jet1pt<50 && jet2pt<50 && jet1pt>30 && jet2pt>30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) || (jet1pt>50 && jet2pt>50 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) ); 
      DR =drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5;
//      photonet_=photonet;
//      if(photonet>500)   photonet_=499;
//      if(photonet_>0)    photon_id_scale=get_photon_ID(photoneta,photonet_,ID_photon);
//      if(photonet>0) cout<<photonet<<" "<<photoneta<<" "<<get_photon_ID(photoneta,photonet,ID_photon)<<endl;
      if(jentry%1000000==0)   cout<<jentry<<"; "<<nentries<<"; cut1 = "<<cut1<<endl;
      if(  !( (LEPmu || LEPele) && PHOTON && JET /*&& DR && SignalRegion*/) )
	      continue;
      if(m_dataset.Contains("ZA_plj")){
	      if(isprompt!=1 ) continue;
      }
      cut1++;//how many events passing the selection 
      newtree->Fill(); //fill the brach when this entry pass the both selection
//                 cout<<"jentry = "<<jentry<<"; cut1 = "<<cut1<<endl;

    }
//   ID_photon_file->Close();
   cout<<cut0<<"; "<<cut1<<endl;
}
