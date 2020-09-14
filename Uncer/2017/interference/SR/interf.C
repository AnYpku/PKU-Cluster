#define interf_cxx
#include "interf.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "unroll.C"
#define Pi 3.141592654 
using namespace std;

void interf::Loop(TH2D* th2,TString name)
{
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   TFile *file = new TFile("2d_"+name+".root","RECREATE");
   Long64_t nentries = fChain->GetEntriesFast();
   Double_t mjj_bins[4]={500, 800, 1200, 2000};
   Double_t deltaeta_bins[4]={2.5, 4.5,  6, 6.5};
   double drll,drjj,actualWeight=0;
   Bool_t JET=false;
   th2 = new TH2D(name,"Mjj vs deltaeta",3, mjj_bins, 3, deltaeta_bins);
   th2->Sumw2();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	   // if (Cut(ientry) < 0) continue;
                if (fabs(philep1-philep2)>Pi) drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(2*Pi-fabs(philep1-philep2))*(2*Pi-fabs(philep1-philep2)));
                else drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(fabs(philep1-philep2))*(fabs(philep1-philep2)));
	   if (fabs(jet1phi-jet2phi)>Pi) 
		   drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
	   else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));

	   JET = ( (!(fabs(jet2eta)<3.14 && fabs(jet2eta)>2.65) && !(fabs(jet1eta)<3.14 && fabs(jet1eta)>2.65) &&  jet1pt<50 && jet2pt<50 && jet1pt>30 && jet2pt>30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) || (jet1pt>50 && jet2pt>50 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) ) && jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 500 && drla > 0.7 && drla2 > 0.7 && drj1a > 0.5 && drj2a > 0.5 && drjj> 0.5 && drj1l > 0.5 && drj2l > 0.5 && drj1l2 > 0.5 && drj2l2 > 0.5 && deltaetajj>2.5&&Mva>100;
           if(  !( ( drla>0.7 && drla2>0.7 && lep == 13 && (HLT_Mu1>0||HLT_Mu2 > 0) && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet > 20.&&( (fabs(photoneta) < 1.4442) || (fabs(photoneta)>1.566&&fabs(photoneta)<2.5)) )||
                 ((drla>0.7 && drla2>0.7 && lep == 11 &&  ( HLT_Ele1 > 0|| HLT_Ele2 > 0) && ptlep1 > 25. && ptlep2 > 25. && fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0 && massVlep > 70. && massVlep < 110. && photonet > 20. &&( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) ) )) ))
		   continue;
           if(Mjj > 2000) Mjj = 1999; if(deltaetajj > 6.5) deltaetajj = 6.1;

	   if(lep==13) actualWeight = scalef*pileupWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale;
	   if(lep==11) actualWeight = scalef*pileupWeight*ele1_id_scale*ele2_id_scale*photon_id_scale;
           cout<<actualWeight<<endl;
	   if(JET &&Mjj>500&& Mjj<2000 && deltaetajj<6.5){ 
		   th2->Fill(Mjj, deltaetajj, actualWeight);
	   }
                
   }
   TString hname=name+"_hist";
   TH1D*h1=unroll(th2, mjj_bins, deltaeta_bins, 3,3,hname);
   file->cd();
   h1->Write();
   th2->Write();
   file->Close();
   cout<<"finish the loop"<<endl;
}
