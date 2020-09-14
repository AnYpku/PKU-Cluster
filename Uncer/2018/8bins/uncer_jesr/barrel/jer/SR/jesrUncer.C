#define jesrUncer_cxx
#include "TLorentzVector.h"
#include "jesrUncer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#define Pi 3.141592654 
using namespace std;
void jesrUncer::Loop(TH2D* th2[3])
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Double_t Mjj_JEC[3],Mjj_JER[3],deltaeta_JEC[3],deltaeta_JER[3],actualWeight;
   Double_t drjj, drjj_new,drjj_JER_up,drjj_JER_down,drll;
   Double_t delta_phi_new,delta_phi_JER_up,delta_phi_JER_down,delta_phi;
   Bool_t JET=0,JET_up=0,JET_down=0,JET_JEC[3]={0},JET_new=0;
   Double_t mjj_bins[4]={500, 800, 1200, 2000};
   Double_t deltaeta_bins[4]={2.5, 4.5,  6, 6.5};
   for(int i=0;i<3;i++){
	   th2[i] = new TH2D(Form("th2_%d",i),"Mjj vs deltaeta",3, mjj_bins, 3, deltaeta_bins);
	   th2[i]->Sumw2();
   }
   TLorentzVector Zp4, photonp4, jet1p4, jet2p4;
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
	   if (fabs(jet1phi_new-jet2phi_new)>Pi)
		   drjj_new = sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(2*Pi-fabs(jet1phi_new-jet2phi_new))*(2*Pi-fabs(jet1phi_new-jet2phi_new)));
	   else drjj_new = sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(fabs(jet1phi_new-jet2phi_new))*(fabs(jet1phi_new-jet2phi_new)));
	   if (fabs(jet1phi_JER_up-jet2phi_JER_up)>Pi) 
		   drjj_JER_up = sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(2*Pi-fabs(jet1phi_JER_up-jet2phi_JER_up))*(2*Pi-fabs(jet1phi_JER_up-jet2phi_JER_up)));
	   else drjj_JER_up = sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(fabs(jet1phi_JER_up-jet2phi_JER_up))*(fabs(jet1phi_JER_up-jet2phi_JER_up)));

	   Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
	   jet1p4.SetPtEtaPhiE(jet1pt_new, jet1eta_new, jet1phi_new, jet1e_new);
	   jet2p4.SetPtEtaPhiE(jet2pt_new, jet2eta_new, jet2phi_new, jet2e_new);
           delta_phi_new=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());

	   jet1p4.SetPtEtaPhiE(jet1pt_JER_up, jet1eta_JER_up, jet1phi_JER_up, jet1e_JER_up);
	   jet2p4.SetPtEtaPhiE(jet2pt_JER_up, jet2eta_JER_up, jet2phi_JER_up, jet2e_JER_up);
           delta_phi_JER_up=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());

	   jet1p4.SetPtEtaPhiE(jet1pt_JER_down, jet1eta_JER_down, jet1phi_JER_down, jet1e_JER_down);
	   jet2p4.SetPtEtaPhiE(jet2pt_JER_down, jet2eta_JER_down, jet2phi_JER_down, jet2e_JER_down);
           delta_phi_JER_down=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());

	   jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
	   jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
	   delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());

	   if (fabs(jet1phi_JER_down-jet2phi_JER_down)>Pi) 
		   drjj_JER_down = sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(2*Pi-fabs(jet1phi_JER_down-jet2phi_JER_down))*(2*Pi-fabs(jet1phi_JER_down-jet2phi_JER_down)));
	   else drjj_JER_down = sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(fabs(jet1phi_JER_down-jet2phi_JER_down))*(fabs(jet1phi_JER_down-jet2phi_JER_down)));
	   JET = jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 150 && drla > 0.7 && drla2 > 0.7 && drj1a > 0.5 && drj2a > 0.5 && drjj> 0.5 && drj1l > 0.5 && drj2l > 0.5 && drj1l2 > 0.5 && drj2l2 > 0.5 && zepp<2.4 && delta_phi>1.9;
	   JET_new = jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && drjj_new> 0.5 && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && zepp_new<2.4 && delta_phi_new>1.9;
	   JET_down = jet1pt_JER_down> 30 && jet2pt_JER_down > 30 && fabs(jet1eta_JER_down)< 4.7 && fabs(jet2eta_JER_down)<4.7 && Mjj_JER_down > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && drjj_JER_down> 0.5 && drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5 && zepp_JER_down<2.4 && delta_phi_JER_down>1.9;
	   JET_up = jet1pt_JER_up> 30 && jet2pt_JER_up > 30 && fabs(jet1eta_JER_up)< 4.7 && fabs(jet2eta_JER_up)<4.7 && Mjj_JER_up > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && drjj_JER_up> 0.5 && drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 && zepp_JER_up<2.4 && delta_phi_JER_down>1.9;

	   if( !((drll>0.3 &&drla>0.7 && drla2>0.7 && lep == 13 &&  HLT_Mu1 > 0 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet > 20. &&( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) )   && Mva>100) ||
		(drla>0.7 && drla2>0.7 && lep == 11 &&  ( HLT_Ele1 > 0) && ptlep1 > 25. && ptlep2 > 25. && fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0 && massVlep > 70. && massVlep < 110. && photonet > 20. &&( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) )  && Mva>100 )) ) 
		   continue;
           if(Mjj_new > 2000) Mjj_new = 1999; if(deltaeta_new > 6.5) deltaeta_new = 6.1;
           if(Mjj_JER_up > 2000) Mjj_JER_up = 1999;if(deltaeta_JER_up > 6.5) deltaeta_JER_up = 6.1;
           if(Mjj_JER_down > 2000) Mjj_JER_down = 1999;if(deltaeta_JER_down > 6.5) deltaeta_JER_down = 6.1;

           if(Mjj_JER_up > 2000) Mjj_JER_up = 1999;if(deltaeta_JER_up > 6.5) deltaeta_JER_up = 6.1;
           if(Mjj_JER_down > 2000) Mjj_JER_down = 1999;if(deltaeta_JER_down > 6.5) deltaeta_JER_down = 6.1;
	   Mjj_JEC[0] = Mjj_new;
//	   Mjj_JEC[0] = Mjj;deltaeta_JEC[0] = deltaeta;
	   Mjj_JEC[1]=Mjj_JER_up;
	   Mjj_JEC[2]=Mjj_JER_down;

	   Mjj_JER[0] = Mjj_new;
	   Mjj_JER[1]=Mjj_JER_up;
	   Mjj_JER[2]=Mjj_JER_down;

	   deltaeta_JEC[0] = deltaeta_new;
	   deltaeta_JEC[1]= deltaeta_JER_up;
	   deltaeta_JEC[2]= deltaeta_JER_down;

	   deltaeta_JER[0] = deltaeta_new;
	   deltaeta_JER[1]= deltaeta_JER_up;
	   deltaeta_JER[2]= deltaeta_JER_down;

           JET_JEC[0]=JET_new;JET_JEC[1]=JET_up;JET_JEC[2]=JET_down;
            if(lep==13)
		    actualWeight = scalef*lumiWeight* pileupWeight *muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale;
            if(lep==11)
		    actualWeight = scalef*lumiWeight* pileupWeight *ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale;
	   for(int i=0;i<3;i++){
		   if(JET_JEC[i] && Mjj_JEC[i]>500 && deltaeta_JEC[i]>2.5){ 
			   th2[i]->Fill(Mjj_JEC[i], deltaeta_JEC[i], actualWeight);
		   }
	   }
                
   }
   cout<<"OK"<<endl;
}
void jesrUncer::makefile(TString name){
	TFile *file = new TFile("2d_"+name+"_jer.root","RECREATE");
        TH2D* h2[3];
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
