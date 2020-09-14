#define jesrUncer_cxx
#include "TLorentzVector.h"
#include "jesrUncer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#define Pi 3.141592654 
using namespace std;
void jesrUncer::Loop(TH1D* th1[3])
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
   Double_t drjj,drjj_JEC_up,drjj_JEC_down,drll;
   Bool_t JET=0,JET_up=0,JET_down=0,JET_JEC[3]={0};
   Double_t delta_phi_JEC_up,delta_phi_JEC_down,delta_phi;
   Double_t mjj_bins[4]={500,800,1200, 2000};
   Double_t deltaeta_bins[4]={2.5,4.5,6,6.5};
   for(int i=0;i<3;i++){
	   th1[i] = new TH1D(Form("th1_%d",i),"",9,0,9);
	   th1[i]->Sumw2();
   }

   Long64_t nbytes = 0, nb = 0;
   TLorentzVector Zp4, photonp4;
   TLorentzVector jet1p4,jet2p4,jet1p4_JEC_up,jet2p4_JEC_up,jet1p4_JEC_down,jet2p4_JEC_down;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	   double detajj     =fabs(jet1eta     -jet2eta);
	   double detajj_JEC_up  =fabs(jet1eta_JEC_up  -jet2eta_JEC_up);
	   double detajj_JEC_down=fabs(jet1eta_JEC_down-jet2eta_JEC_down);
	   // if (Cut(ientry) < 0) continue;
                if (fabs(philep1-philep2)>Pi) drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(2*Pi-fabs(philep1-philep2))*(2*Pi-fabs(philep1-philep2)));
                else drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(fabs(philep1-philep2))*(fabs(philep1-philep2)));
	   if (fabs(jet1phi-jet2phi)>Pi) 
		   drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
	   else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));
	   if (fabs(jet1phi_JEC_up-jet2phi_JEC_up)>Pi) 
		   drjj_JEC_up = sqrt((jet1eta_JEC_up-jet2eta_JEC_up)*(jet1eta_JEC_up-jet2eta_JEC_up)+(2*Pi-fabs(jet1phi_JEC_up-jet2phi_JEC_up))*(2*Pi-fabs(jet1phi_JEC_up-jet2phi_JEC_up)));
	   else drjj_JEC_up = sqrt((jet1eta_JEC_up-jet2eta_JEC_up)*(jet1eta_JEC_up-jet2eta_JEC_up)+(fabs(jet1phi_JEC_up-jet2phi_JEC_up))*(fabs(jet1phi_JEC_up-jet2phi_JEC_up)));

	   if (fabs(jet1phi_JEC_down-jet2phi_JEC_down)>Pi) 
		   drjj_JEC_down = sqrt((jet1eta_JEC_down-jet2eta_JEC_down)*(jet1eta_JEC_down-jet2eta_JEC_down)+(2*Pi-fabs(jet1phi_JEC_down-jet2phi_JEC_down))*(2*Pi-fabs(jet1phi_JEC_down-jet2phi_JEC_down)));
	   else drjj_JEC_down = sqrt((jet1eta_JEC_down-jet2eta_JEC_down)*(jet1eta_JEC_down-jet2eta_JEC_down)+(fabs(jet1phi_JEC_down-jet2phi_JEC_down))*(fabs(jet1phi_JEC_down-jet2phi_JEC_down)));
	   photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
           Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
           jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
           jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
           delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());

           jet1p4_JEC_up.SetPtEtaPhiE(jet1pt_JEC_up, jet1eta_JEC_up, jet1phi_JEC_up, jet1e_JEC_up);
           jet2p4_JEC_up.SetPtEtaPhiE(jet2pt_JEC_up, jet2eta_JEC_up, jet2phi_JEC_up, jet2e_JEC_up);
           delta_phi_JEC_up=fabs((Zp4+photonp4).Phi()-(jet1p4_JEC_up+jet2p4_JEC_up).Phi());

           jet1p4_JEC_down.SetPtEtaPhiE(jet1pt_JEC_down, jet1eta_JEC_down, jet1phi_JEC_down, jet1e_JEC_down);
           jet2p4_JEC_down.SetPtEtaPhiE(jet2pt_JEC_down, jet2eta_JEC_down, jet2phi_JEC_down, jet2e_JEC_down);
           delta_phi_JEC_down=fabs((Zp4+photonp4).Phi()-(jet1p4_JEC_down+jet2p4_JEC_down).Phi());

           jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
           jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
           delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
           if (delta_phi>Pi) delta_phi=2*Pi-delta_phi;
           if (delta_phi_JEC_up>Pi) delta_phi_JEC_up=2*Pi-delta_phi_JEC_up;
           if (delta_phi_JEC_down>Pi) delta_phi_JEC_down=2*Pi-delta_phi_JEC_down;
	   JET = jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 500 && drla > 0.7 && drla2 > 0.7 && drj1a > 0.5 && drj2a > 0.5 && drjj> 0.5 && drj1l > 0.5 && drj2l > 0.5 && drj1l2 > 0.5 && drj2l2 > 0.5 && deltaeta >2.5&& zepp<2.4 && delta_phi>1.9;
	   JET_down = jet1pt_JEC_down> 30 && jet2pt_JEC_down > 30 && fabs(jet1eta_JEC_down)< 4.7 && fabs(jet2eta_JEC_down)<4.7 && Mjj_JEC_down > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && drjj_JEC_down> 0.5 && drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5 && deltaeta_JEC_down>2.5&&zepp_JEC_down<2.4 && delta_phi_JEC_down>1.9;
	   JET_up = jet1pt_JEC_up> 30 && jet2pt_JEC_up > 30 && fabs(jet1eta_JEC_up)< 4.7 && fabs(jet2eta_JEC_up)<4.7 && Mjj_JEC_up > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && drjj_JEC_up> 0.5 && drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 && deltaeta_JEC_up>2.5 && zepp_JEC_up<2.4 && delta_phi_JEC_up>1.9;

           if(  !( ( drla>0.7 && drla2>0.7 && lep == 13 /*&& (HLT_Mu1>0||HLT_Mu2 > 0)*/ && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet > 20.&&( (fabs(photoneta) < 1.4442) || (fabs(photoneta)>1.566&&fabs(photoneta)<2.5)) && Mva>100)||
                 ((drla>0.7 && drla2>0.7 && lep == 11 &&  /*( HLT_Ele1 > 0|| HLT_Ele2 > 0) &&*/ ptlep1 > 25. && ptlep2 > 25. && fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0 && massVlep > 70. && massVlep < 110. && photonet > 20. &&( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) )&& Mva>100 )) ))
		   continue;
           if(Mjj > 2000) Mjj = 1999; if(deltaeta > 6.5) deltaeta = 6.1;
           if(Mjj_JEC_up > 2000) Mjj_JEC_up = 1999;if(deltaeta_JEC_up > 6.5) deltaeta_JEC_up = 6.1;
           if(Mjj_JEC_down > 2000) Mjj_JEC_down = 1999;if(deltaeta_JEC_down > 6.5) deltaeta_JEC_down = 6.1;

           if(Mjj_JER_up > 2000) Mjj_JER_up = 1999;if(deltaeta_JER_up > 6.5) deltaeta_JER_up = 6.1;
           if(Mjj_JER_down > 2000) Mjj_JER_down = 1999;if(deltaeta_JER_down > 6.5) deltaeta_JER_down = 6.1;
	   if(JET){
		   if(Mjj>=500 &&Mjj<800&&detajj>=2.5&&detajj<4.5)
			   th1[0]->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		   if(Mjj>=800 &&Mjj<1200&&detajj>=2.5&&detajj<4.5)
			   th1[0]->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		   if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)
			   th1[0]->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
		   if(Mjj>=500 &&Mjj<800&&detajj>=4.5&&detajj<6)
			   th1[0]->Fill(3.5,scalef);//3~4 4.5~6 500~800 
		   if(Mjj>=800 &&Mjj<1200&&detajj>=4.5&&detajj<6)
			   th1[0]->Fill(4.5,scalef);//4~5 4.5~6 800~1200
		   if(Mjj>=1200&&detajj>=4.5&&detajj<6)
			   th1[0]->Fill(5.5,scalef);//5~6 6~infi 500~800
		   if(Mjj>=500 &&Mjj<800&&detajj>=6)
			   th1[0]->Fill(6.5,scalef);//6~7 6~infi 800~1200
		   if(Mjj>=800 &&Mjj<1200&&detajj>=6)
			   th1[0]->Fill(7.5,scalef);//7~8 6~infi800~1200
		   if(Mjj>=1200&&detajj>=6)
			   th1[0]->Fill(8.5,scalef);//8~9 6~infi 800~1200 
	   }
	   if(JET_up){
		   if(Mjj_JEC_up>=500 &&Mjj_JEC_up<800&&detajj_JEC_up>=2.5&&detajj_JEC_up<4.5)
			   th1[1]->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		   if(Mjj_JEC_up>=800 &&Mjj_JEC_up<1200&&detajj_JEC_up>=2.5&&detajj_JEC_up<4.5)
			   th1[1]->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		   if(Mjj_JEC_up>=1200&&detajj_JEC_up>=2.5&&detajj_JEC_up<4.5)
			   th1[1]->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
		   if(Mjj_JEC_up>=500 &&Mjj_JEC_up<800&&detajj_JEC_up>=4.5&&detajj_JEC_up<6)
			   th1[1]->Fill(3.5,scalef);//3~4 4.5~6 500~800 
		   if(Mjj_JEC_up>=800 &&Mjj_JEC_up<1200&&detajj_JEC_up>=4.5&&detajj_JEC_up<6)
			   th1[1]->Fill(4.5,scalef);//4~5 4.5~6 800~1200
		   if(Mjj_JEC_up>=1200&&detajj_JEC_up>=4.5&&detajj_JEC_up<6)
			   th1[1]->Fill(5.5,scalef);//5~6 6~infi 500~800
		   if(Mjj_JEC_up>=500 &&Mjj_JEC_up<800&&detajj_JEC_up>=6)
			   th1[1]->Fill(6.5,scalef);//6~7 6~infi 800~1200
		   if(Mjj_JEC_up>=800 &&Mjj_JEC_up<1200&&detajj_JEC_up>=6)
			   th1[1]->Fill(7.5,scalef);//7~8 6~infi800~1200
		   if(Mjj_JEC_up>=1200&&detajj_JEC_up>=6)
			   th1[1]->Fill(8.5,scalef);//8~9 6~infi 800~1200
	   }
	   if(JET_down){
		   if(Mjj_JEC_down>=500 &&Mjj_JEC_down<800&&detajj_JEC_down>=2.5&&detajj_JEC_down<4.5)
			   th1[2]->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		   if(Mjj_JEC_down>=800 &&Mjj_JEC_down<1200&&detajj_JEC_down>=2.5&&detajj_JEC_down<4.5)
			   th1[2]->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		   if(Mjj_JEC_down>=1200&&detajj_JEC_down>=2.5&&detajj_JEC_down<4.5)
			   th1[2]->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
		   if(Mjj_JEC_down>=500 &&Mjj_JEC_down<800&&detajj_JEC_down>=4.5&&detajj_JEC_down<6)
			   th1[2]->Fill(3.5,scalef);//3~4 4.5~6 500~800 
		   if(Mjj_JEC_down>=800 &&Mjj_JEC_down<1200&&detajj_JEC_down>=4.5&&detajj_JEC_down<6)
			   th1[2]->Fill(4.5,scalef);//4~5 4.5~6 800~1200
		   if(Mjj_JEC_down>=1200&&detajj_JEC_down>=4.5&&detajj_JEC_down<6)
			   th1[2]->Fill(5.5,scalef);//5~6 6~infi 500~800
		   if(Mjj_JEC_down>=500 &&Mjj_JEC_down<800&&detajj_JEC_down>=6)
			   th1[2]->Fill(6.5,scalef);//6~7 6~infi 800~1200
		   if(Mjj_JEC_down>=800 &&Mjj_JEC_down<1200&&detajj_JEC_down>=6)
			   th1[2]->Fill(7.5,scalef);//7~8 6~infi800~1200
		   if(Mjj_JEC_down>=1200&&detajj_JEC_down>=6)
			   th1[2]->Fill(8.5,scalef);//8~9 6~infi 800~1200
	   }

   }
   cout<<"OK"<<endl;
}
void jesrUncer::makefile(TString name){
	TFile *file = new TFile("2d_"+name+"_jec.root","RECREATE");
	TH1D* h2[3];
	Loop(h2);
	cout<<"OK"<<endl;
	file->cd();
	h2[0]->Write();
	h2[1]->Write();
	h2[2]->Write();
	cout<<"OK"<<endl;
	cout<<"OK"<<endl;
	file->Close();
}
