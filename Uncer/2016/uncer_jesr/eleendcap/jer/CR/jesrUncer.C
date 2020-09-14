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
   Double_t Mjj_JEC[3],Mjj_JER[3],deltaeta_JEC[3],deltaeta_JER[3],actualWeight;
   Double_t drjj, drjj_new,drjj_JER_up,drjj_JER_down,drll;
   Bool_t JET=0,JET_up=0,JET_down=0,JET_JER[3]={0},JET_new=0,JET_JEC[3]={0};
   Double_t mjj_bins[2]={150,400};
   Double_t deltaeta_bins[2]={0, 6.5};
   mjj_JEC_down = new TH1D("h_down","mjj_JEC_down",1,0,1);
   mjj_JEC_up = new TH1D("h_up","mjj_JEC_up",1,0,1);
   mjj_JER_down = new TH1D("h_JER_down","mjj_JER_down",1,0,1);
   mjj_JER_up = new TH1D("h_JER_up","mjj_JER_up",1,0,1);
   for(int i=0;i<3;i++){
	   th2[i] = new TH2D(Form("th2_%d",i),"Mjj vs deltaeta",1, mjj_bins, 1, deltaeta_bins);
	   th2[i]->Sumw2();
   }

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	   scalef = 0.0003656;
	   // if (Cut(ientry) < 0) continue;
                if (fabs(philep1-philep2)>Pi) drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(2*Pi-fabs(philep1-philep2))*(2*Pi-fabs(philep1-philep2)));
                else drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(fabs(philep1-philep2))*(fabs(philep1-philep2)));
	   if (fabs(jet1phi-jet2phi)>Pi) 
		   drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
	   else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));
	   if (fabs(jet1phi_new-jet2phi_new)>Pi)
		   drjj_new = sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(2*Pi-fabs(jet1phi_new-jet2phi_new))*(2*Pi-fabs(jet1phi_new-jet2phi_new)));
	   else drjj_new = sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(fabs(jet1phi_new-jet2phi_new))*(fabs(jet1phi_new-jet2phi_new)));
	   if (fabs(jet1phi_JER_up-jet2phi_JER_up)>Pi) 
		   drjj_JER_up = sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(2*Pi-fabs(jet1phi_JER_up-jet2phi_JER_up))*(2*Pi-fabs(jet1phi_JER_up-jet2phi_JER_up)));
	   else drjj_JER_up = sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(fabs(jet1phi_JER_up-jet2phi_JER_up))*(fabs(jet1phi_JER_up-jet2phi_JER_up)));

	   if (fabs(jet1phi_JER_down-jet2phi_JER_down)>Pi) 
		   drjj_JER_down = sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(2*Pi-fabs(jet1phi_JER_down-jet2phi_JER_down))*(2*Pi-fabs(jet1phi_JER_down-jet2phi_JER_down)));
	   else drjj_JER_down = sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(fabs(jet1phi_JER_down-jet2phi_JER_down))*(fabs(jet1phi_JER_down-jet2phi_JER_down)));
	   JET = jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 150 && drla > 0.7 && drla2 > 0.7 && drj1a > 0.5 && drj2a > 0.5 && drjj> 0.5 && drj1l > 0.5 && drj2l > 0.5 && drj1l2 > 0.5 && drj2l2 > 0.5;
	   JET_new = jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && drjj_new> 0.5 && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5;
	   JET_down = jet1pt_JER_down> 30 && jet2pt_JER_down > 30 && fabs(jet1eta_JER_down)< 4.7 && fabs(jet2eta_JER_down)<4.7 && Mjj_JER_down > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && drjj_JER_down> 0.5 && drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5;
	   JET_up = jet1pt_JER_up> 30 && jet2pt_JER_up > 30 && fabs(jet1eta_JER_up)< 4.7 && fabs(jet2eta_JER_up)<4.7 && Mjj_JER_up > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && drjj_JER_up> 0.5 && drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5;

       if(  !( drla>0.7 && drla>0.7 && lep == 11 && ( HLT_Ele1 > 0|| HLT_Ele2 > 0) && ptlep1 > 25. &&     ptlep2 > 25. && fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0 && massVlep > 70. && massVlep < 110. && photonet > 20.&& (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) ) )
           continue;
           if(Mjj_new > 2000) Mjj_new = 1999; if(deltaeta_new > 6.5) deltaeta_new = 6.1;
           if(Mjj_JEC_up > 2000) Mjj_JEC_up = 1999;if(deltaeta_JEC_up > 6.5) deltaeta_JEC_up = 6.1;
           if(Mjj_JEC_down > 2000) Mjj_JEC_down = 1999;if(deltaeta_JEC_down > 6.5) deltaeta_JEC_down = 6.1;

           if(Mjj_JER_up > 2000) Mjj_JER_up = 1999;if(deltaeta_JER_up > 6.5) deltaeta_JER_up = 6.1;
           if(Mjj_JER_down > 2000) Mjj_JER_down = 1999;if(deltaeta_JER_down > 6.5) deltaeta_JER_down = 6.1;
	   Mjj_JEC[0] = Mjj_new;
//	   Mjj_JEC[0] = Mjj;deltaeta_JEC[0] = deltaeta;
	   Mjj_JEC[1]=Mjj_JEC_up;
	   Mjj_JEC[2]=Mjj_JEC_down;

	   Mjj_JER[0] = Mjj_new;
	   Mjj_JER[1]=Mjj_JER_up;
	   Mjj_JER[2]=Mjj_JER_down;

	   deltaeta_JEC[0] = deltaeta_new;
	   deltaeta_JEC[1]= deltaeta_JEC_up;
	   deltaeta_JEC[2]= deltaeta_JEC_down;

	   deltaeta_JER[0] = deltaeta_new;
	   deltaeta_JER[1]= deltaeta_JER_up;
	   deltaeta_JER[2]= deltaeta_JER_down;

           JET_JER[0]=JET_new;JET_JER[1]=JET_up;JET_JER[2]=JET_down;
	   actualWeight = scalef*lumiWeight* pileupWeight /* *muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*/;
//	   cout<<jentry<<"; "<<fChain->GetEntries()<<endl;
//	   cout<<"scalef = "<<scalef<<"; pileupWeight = "<<pileupWeight<<"; actualWeight = "<<actualWeight<<endl;
	   for(int i=0;i<3;i++){
		   if(JET_JER[i] && Mjj_JER[i]<400 && deltaeta_JER[i]<6.5){ 
			   th2[i]->Fill(Mjj_JER[i], deltaeta_JER[i], actualWeight);
		   }
//		   if(JET_JEC[i] && Mjj_JEC[i]>=2000 && deltaeta_JEC[i]<=6.5) 
//			   th2[i]->Fill(1999, deltaeta_JEC[i], actualWeight);
//		   if(JET_JEC[i] && Mjj_JEC[i]<2000 && deltaeta_JEC[i]>=6.5) 
//			   th2[i]->Fill(Mjj_JEC[i], 6.1, actualWeight);
//		   if(JET_JEC[i] && Mjj_JEC[i]>=2000 && deltaeta_JEC[i]>=6.5)
//			   th2[i]->Fill(1999, 6.1, actualWeight);
	   }
	   if(JET_down==1) {
		   if(Mjj_JER_down>=500&&Mjj_JER_down<800&&deltaeta_JER_down>=2.5&&deltaeta_JER_down<4.5) mjj_JER_down->Fill(0.5,actualWeight);//0~1, 2.5~4.5 and 500~800
		   if(Mjj_JER_down>=800&&Mjj_JER_down<1200&&deltaeta_JER_down>=2.5&&deltaeta_JER_down<4.5) mjj_JER_down->Fill(1.5,actualWeight);//1~2 2.5~4.5 and 800~1200
		   if(Mjj_JER_down>=1200&&deltaeta_JER_down>=2.5&&deltaeta_JER_down<4.5) mjj_JER_down->Fill(2.5,actualWeight);//2~3 2.5~4.5 1200~2000
		   if(Mjj_JER_down>=500&&Mjj_JER_down<800&&deltaeta_JER_down>=4.5&&deltaeta_JER_down<6) mjj_JER_down->Fill(3.5,actualWeight);//3~4 4.5~6 500~800 
		   if(Mjj_JER_down>=800&&Mjj_JER_down<1200&&deltaeta_JER_down>=4.5&&deltaeta_JER_down<6) mjj_JER_down->Fill(4.5,actualWeight);//4~5 4.5~6 800~1200
		   if(Mjj_JER_down>=1200&&deltaeta_JER_down>=4.5&&deltaeta_JER_down<6) mjj_JER_down->Fill(5.5,actualWeight);
		   if(Mjj_JER_down>=500&&Mjj_JER_down<800&&deltaeta_JER_down>=6) mjj_JER_down->Fill(6.5,actualWeight);
		   if(Mjj_JER_down>=800&&Mjj_JER_down<1200&&deltaeta_JER_down>=6) mjj_JER_down->Fill(7.5,actualWeight);
		   if(Mjj_JER_down>=1200&&deltaeta_JER_down>=6) mjj_JER_down->Fill(8.5,actualWeight);
	   }
	   if(JET_up==1) {
		   if(Mjj_JER_up>=500&&Mjj_JER_up<800&&deltaeta_JER_up>=2.5&&deltaeta_JER_up<4.5) mjj_JER_up->Fill(0.5,actualWeight);//0~1, 2.5~4.5 and 500~800
		   if(Mjj_JER_up>=800&&Mjj_JER_up<1200&&deltaeta_JER_up>=2.5&&deltaeta_JER_up<4.5) mjj_JER_up->Fill(1.5,actualWeight);//1~2 2.5~4.5 and 800~1200
		   if(Mjj_JER_up>=1200&&deltaeta_JER_up>=2.5&&deltaeta_JER_up<4.5) mjj_JER_up->Fill(2.5,actualWeight);//2~3 2.5~4.5 1200~2000
		   if(Mjj_JER_up>=500&&Mjj_JER_up<800&&deltaeta_JER_up>=4.5&&deltaeta_JER_up<6) mjj_JER_up->Fill(3.5,actualWeight);//3~4 4.5~6 500~800 
		   if(Mjj_JER_up>=800&&Mjj_JER_up<1200&&deltaeta_JER_up>=4.5&&deltaeta_JER_up<6) mjj_JER_up->Fill(4.5,actualWeight);//4~5 4.5~6 800~1200
		   if(Mjj_JER_up>=1200&&deltaeta_JER_up>=4.5&&deltaeta_JER_up<6) mjj_JER_up->Fill(5.5,actualWeight);
		   if(Mjj_JER_up>=500&&Mjj_JER_up<800&&deltaeta_JER_up>=6) mjj_JER_up->Fill(6.5,actualWeight);
		   if(Mjj_JER_up>=800&&Mjj_JER_up<1200&&deltaeta_JER_up>=6) mjj_JER_up->Fill(7.5,actualWeight);
		   if(Mjj_JER_up>=1200&&deltaeta_JER_up>=6) mjj_JER_up->Fill(8.5,actualWeight);
	   }
                
   }
   cout<<"OK"<<endl;
}
void jesrUncer::makefile(){
	TFile *file = new TFile("2d_jer.root","RECREATE");
        TH2D* h2[3];
	Loop(h2);
	cout<<"OK"<<endl;
	file->cd();
	h2[0]->Write();
	h2[1]->Write();
        h2[2]->Write();
	cout<<"OK"<<endl;
        mjj_JER_down->Write();
        mjj_JER_up->Write();
	cout<<"OK"<<endl;
        file->Close();
}
