#define jesrUncer_cxx
#include "jesrUncer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#define Pi 3.141592654 
using namespace std;
void jesrUncer::Loop(TH2D* th2[3])
{
//   In a ROOT session, you can do:
//      root> .L jesrUncer.C
//      root> jesrUncer t
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
   Double_t Mjj_JEC[3],Mjj_JER[3],deltaetajj_JEC[3],deltaetajj_JER[3],scalef;
   Double_t drjj, drjj_new,drjj_JEC_up,drjj_JEC_down,drll;
   Bool_t JET=0,JET_up=0,JET_down=0,JET_JEC[3]={0},JET_new=0;
   Double_t mjj_bins[4]={500, 800, 1200, 2000};
   Double_t deltaetajj_bins[4]={2.5, 4.5,  6, 6.5};
   mjj_JEC_down = new TH1D("h_down","mjj_JEC_down",9,0,9);
   mjj_JEC_up = new TH1D("h_up","mjj_JEC_up",9,0,9);
   for(int i=0;i<3;i++){
	   th2[i] = new TH2D(Form("th2_%d",i),"Mjj vs deltaetajj",3, mjj_bins, 3, deltaetajj_bins);
	   th2[i]->Sumw2();
   }

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
	   JET = jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 150 && drla > 0.7 && drla2 > 0.7 && drj1a > 0.5 && drj2a > 0.5 && drjj> 0.5 && drj1l > 0.5 && drj2l > 0.5 && drj1l2 > 0.5 && drj2l2 > 0.5;
	   if(  !( drla>0.7 && drla>0.7 && lep == 13 && HLT_Mu2 > 0 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet > 20.&& fabs(photoneta) < 1.4442) )
		   continue;
           if(Mjj_new > 2000) Mjj_new = 1999; if(deltaetajj_new > 6.5) deltaetajj_new = 6.1;

	   for(int i=0;i<3;i++){
		   if(JET && Mjj<2000 && deltaetajj<6.5){ 
			   th2[i]->Fill(Mjj, deltaetajj, scalef);
		   }
	   }
	   if(JET==1) {
		   if(Mjj>=500&&Mjj<800&&deltaetajj>=2.5&&deltaetajj<4.5) mjj_JEC_down->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		   if(Mjj>=800&&Mjj<1200&&deltaetajj>=2.5&&deltaetajj<4.5) mjj_JEC_down->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		   if(Mjj>=1200&&deltaetajj>=2.5&&deltaetajj<4.5) mjj_JEC_down->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
		   if(Mjj>=500&&Mjj<800&&deltaetajj>=4.5&&deltaetajj<6) mjj_JEC_down->Fill(3.5,scalef);//3~4 4.5~6 500~800 
		   if(Mjj>=800&&Mjj<1200&&deltaetajj>=4.5&&deltaetajj<6) mjj_JEC_down->Fill(4.5,scalef);//4~5 4.5~6 800~1200
		   if(Mjj>=1200&&deltaetajj>=4.5&&deltaetajj<6) mjj_JEC_down->Fill(5.5,scalef);
		   if(Mjj>=500&&Mjj<800&&deltaetajj>=6) mjj_JEC_down->Fill(6.5,scalef);
		   if(Mjj>=800&&Mjj<1200&&deltaetajj>=6) mjj_JEC_down->Fill(7.5,scalef);
		   if(Mjj>=1200&&deltaetajj>=6) mjj_JEC_down->Fill(8.5,scalef);
	   }
                
   }
   cout<<"OK"<<endl;
}
void jesrUncer::makefile(){
	TFile *file = new TFile("2d_jec.root","RECREATE");
        TH2D* h2[3];
	Loop(h2);
	cout<<"OK"<<endl;
	file->cd();
	h2[0]->Write();
	h2[1]->Write();
        h2[2]->Write();
	cout<<"OK"<<endl;
        mjj_JEC_down->Write();
        mjj_JEC_up->Write();
	cout<<"OK"<<endl;
        file->Close();
}
