#define small_cxx
#include "small.h"
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
using namespace std;
void small::Loop(TString name)
{
//   In a ROOT session, you can do:
//      Root > .L small.C
//      Root > small t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   TH2D* h_up[30];
   TH2D* h_down[30];
   Double_t mjj_bins[4]={500, 800, 1200,2000};
   Double_t detajj_bins[4]={2.5,4.5,6,6.5};
   TH2D*h=new TH2D("h","hist",3,mjj_bins,3,detajj_bins);
   h->Sumw2();
   for(int i=0;i<30;i++){
      h_up[i]=new TH2D(Form("hist_up_%i",i),"hist",3,mjj_bins,3,detajj_bins);
      h_down[i]=new TH2D(Form("hist_down_%i",i),"hist",3,mjj_bins,3,detajj_bins);
       h_up[i]->Sumw2();
       h_down[i]->Sumw2();
   }
   Bool_t JET_up;
   Bool_t JET_down;
   Bool_t JET;
   TFile*file=new TFile("hist_"+name,"RECREATE");
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
//   for (Long64_t jentry=0; jentry<1000;jentry++){
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      setValue();
      // if (Cut(ientry) < 0) continue;
      scalef = 1000.*47.46/(np-nm)*theWeight/fabs(theWeight);
      if(jentry%10000==0) cout<<"scalef "<<scalef<<endl;
      TLorentzVector photonp4;
      photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
      TLorentzVector vp4;
//      if(  !(fabs(photoneta)<1.4442 && Mva>100) )
//         continue;
      vp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
      for(int i=0;i<jet1pt_unc_up->size();i++){
                      TLorentzVector j1p4_up,j1p4_down;
                      j1p4_up.SetPtEtaPhiE( jet1pt_unc_up->at(i), jet1eta_unc_up->at(i), jet1phi_unc_up->at(i), jet1e_unc_up->at(i));
                      j1p4_down.SetPtEtaPhiE(jet1pt_unc_down->at(i), jet1eta_unc_down->at(i), jet1phi_unc_down->at(i), jet1e_unc_down->at(i));
                      TLorentzVector j2p4_up,j2p4_down;
                      j2p4_up.SetPtEtaPhiE(  jet2pt_unc_up->at(i), jet2eta_unc_up->at(i), jet2phi_unc_up->at(i), jet2e_unc_up->at(i));
                      j2p4_down.SetPtEtaPhiE(jet2pt_unc_down->at(i), jet2eta_unc_down->at(i), jet2phi_unc_down->at(i), jet2e_unc_down->at(i));
                      zepp_up[i]=fabs((vp4+photonp4).Rapidity() - (j1p4_up.Rapidity() + j2p4_up.Rapidity())/ 2.0);
                      zepp_down[i]=fabs((vp4+photonp4).Rapidity() - (j1p4_down.Rapidity() + j2p4_down.Rapidity())/ 2.0);
                      delta_phi_up[i]=fabs((vp4+photonp4).Phi()-(j1p4_up+j2p4_up).Phi());
                      delta_phi_down[i]=fabs((vp4+photonp4).Phi()-(j1p4_down+j2p4_down).Phi());
//                      cout<<"zepp_up "<<zepp_up[i]<<" "<<"zepp_down "<<zepp_down[i]<<endl;
//                      cout<<"delta_phi_down "<< delta_phi_down[i]<<"delta_phi_up "<<delta_phi_up[i]<<endl;
      }
//      cout<<"fill zepp end"<<endl;
      TLorentzVector Zp4,jet1p4, jet2p4;
      Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
      photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
      jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
      jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
      delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
      for(int i=0;i<jet1pt_unc_up->size();i++){
          JET_up=jet1pt_unc_up->at(i)>30 && jet2pt_unc_up->at(i)>30 && fabs(jet1eta_unc_up->at(i))<4.7 && fabs(jet2eta_unc_up->at(i))<4.7 && drj1a_up->at(i)>0.5 && drj1l1_up->at(i)>0.5 && drj1l2_up->at(i)>0.5 && drj2l1_up->at(i)>0.5 && drj2l2_up->at(i)>0.5 && drjj_up->at(i)>0.5 && detajj_up->at(i)>2.5 && Mjj_up->at(i)>500 && zepp_up[i]<2.4 && delta_phi_up[i]>1.9 && Mva>100;
          JET_down=jet1pt_unc_down->at(i)>30 && jet2pt_unc_down->at(i)>30 && fabs(jet1eta_unc_down->at(i))<4.7 && fabs(jet2eta_unc_down->at(i))<4.7 && drj1a_down->at(i)>0.5 && drj1l1_down->at(i)>0.5 && drj1l2_down->at(i)>0.5 && drj2l1_down->at(i)>0.5 && drj2l2_down->at(i)>0.5 && drjj_down->at(i)>0.5 && detajj_down->at(i)>2.5 && Mjj_down->at(i)>500 && zepp_down[i]<2.4 && delta_phi_down[i]>1.9 && Mva>100; 
          if(Mjj_up->at(i)>2000) Mjj_up->at(i)=1999;   if(Mjj_down->at(i)>2000) Mjj_down->at(i)=1999;
          if(detajj_up->at(i)>6.5) detajj_up->at(i)=6.1;   if(detajj_down->at(i)>6.5) detajj_down->at(i)=6.1;
//          if(jentry%100==0)cout<<"Fill histograms"<<endl;
          if(JET_up){
               h_up[i]->Fill(Mjj_up->at(i),detajj_up->at(i),scalef);
	  }
          if(JET_down){
               h_down[i]->Fill(Mjj_down->at(i),detajj_down->at(i),scalef);
	  }
      }   
      JET=jet1pt>30 && jet2pt>30 && fabs(jet1eta)<4.7 && fabs(jet2eta)<4.7&&Mjj>500&&deltaeta>2.5 && drj1a>0.5 && drj1l>0.5 && drj2l>0.5 && drj1l2>0.5 && drj2l2>0.5 && zepp<2.4 && delta_phi>1.9 && Mva>100;
      if(Mjj>2000) Mjj=1999;
      if(deltaeta>6.5) deltaeta=6.1;
      if(JET) {h->Fill(Mjj,deltaeta,scalef);}
//      if(jentry%10000==0)cout<<"finish the vector loop"<<endl;

      zepp_up.clear();         zepp_down.clear();
      delta_phi_up.clear();    delta_phi_down.clear();
   }
  cout<<"end the big loop"<<endl; 
  file->cd();
  for(int i=0;i<30;i++){
	  h_up[i]->Write();
  }
  for(int i=0;i<30;i++){
	  h_down[i]->Write();
  }
  h->Write();
  file->Close();
}
void small::setValue(){
        for(int i=0;i<jet1pt_unc_up->size();i++){
                zepp_up.push_back(-10);         zepp_down.push_back(-10);
                delta_phi_up.push_back(-10);    delta_phi_down.push_back(-10);
        }
}
