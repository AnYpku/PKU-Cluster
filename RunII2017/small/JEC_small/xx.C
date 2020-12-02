#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
//#include "muon_channel_scale.C"

using namespace std;
void xx::Loop(TString name)
{
   if (fChain == 0) return;

   cut0=0,cut1=0;
   bool LEPele,LEPmu,JET,PHOTON,SignalRegion,DR;

   //muon hlt
   TFile*f_hltmu=new TFile("./muon_HLT_SF.root");
   TH2D*HLT_mu=(TH2D*)f_hltmu->Get("h2");
   cout<<"open the muon hlt file: muon_HLT_SF.root"<<endl;

   //ele hlt
   TFile*f_ele1=new TFile("../egammaEffi.txt_EGM2D_leg1.root");
   TFile*f_ele2=new TFile("../egammaEffi.txt_EGM2D_leg2.root");
   TH2F*HLT_MC1=(TH2F*)f_ele1->Get("EGamma_EffMC2D");
   TH2F*HLT_MC2=(TH2F*)f_ele2->Get("EGamma_EffMC2D");
   TH2F*HLT_SF1=(TH2F*)f_ele1->Get("EGamma_SF2D");
   TH2F*HLT_SF2=(TH2F*)f_ele2->Get("EGamma_SF2D");
   cout<<"open the ele hlt file"<<endl;

//PU jetID
   TFile*fPUeff=new TFile("/home/pku/anying/cms/PKU-Cluster/RunII2017/PUID/effcyPUID_81Xtraining.root");
   TFile*fPUsf=new TFile("/home/pku/anying/cms/PKU-Cluster/RunII2017/PUID/scalefactorsPUID_81Xtraining.root");
   TH2F*h2_eff_mc2017_L=(TH2F*)fPUeff->Get("h2_eff_mc2017_L");
   TH2F*h2_eff_mc2017_M=(TH2F*)fPUeff->Get("h2_eff_mc2017_M");
   TH2F*h2_eff_mc2017_T=(TH2F*)fPUeff->Get("h2_eff_mc2017_T");
   TH2F*h2_mistag_mc2017_L=(TH2F*)fPUeff->Get("h2_mistag_mc2017_L");
   TH2F*h2_mistag_mc2017_M=(TH2F*)fPUeff->Get("h2_mistag_mc2017_M");
   TH2F*h2_mistag_mc2017_T=(TH2F*)fPUeff->Get("h2_mistag_mc2017_T");
   TH2F*h2_eff_sf2017_L=(TH2F*)fPUsf->Get("h2_eff_sf2017_L");
   TH2F*h2_eff_sf2017_M=(TH2F*)fPUsf->Get("h2_eff_sf2017_M");
   TH2F*h2_eff_sf2017_T=(TH2F*)fPUsf->Get("h2_eff_sf2017_T");
   TH2F*h2_mistag_sf2017_L=(TH2F*)fPUsf->Get("h2_mistag_sf2017_L");
   TH2F*h2_mistag_sf2017_M=(TH2F*)fPUsf->Get("h2_mistag_sf2017_M");
   TH2F*h2_mistag_sf2017_T=(TH2F*)fPUsf->Get("h2_mistag_sf2017_T");

   Long64_t nbytes = 0, nb = 0;
   int nentries= fChain->GetEntries();
   //  nentries=1000;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	   cut0++;//total events, cut0=t1->GetEntries()

	   if(name.Contains("Muon")) scalef=1;
	   if(name.Contains("Ele")) scalef=1;

	   if(drla==10) drla=-1;
	   if(drla2==10) drla2=-1; 
	   if(drj1a==10) drj1a=-1;
	   if(drj2a==10) drj2a=-1;
           ele_hlt_scale=1;
           muon_hlt_scale=1;
	   puIdweight_L=1;puIdweight_M=1;puIdweight_T=1;
	   puIdweight_L_new=1;puIdweight_M_new=1;puIdweight_T_new=1;
	   puIdweight_L_JEC_up=1;puIdweight_M_JEC_up=1;puIdweight_T_JEC_up=1;
	   puIdweight_L_JEC_down=1;puIdweight_M_JEC_down=1;puIdweight_T_JEC_down=1;
	   if(lep==11)                        
                   ele_hlt_scale=get_eleHLT_SF(etalep1,ptlep1,etalep2,ptlep2,HLT_MC1,HLT_SF1,HLT_MC2,HLT_SF2);
	   if(lep==13)
		   muon_hlt_scale=muon_HLT_scale(ptlep1,ptlep2,etalep1,etalep2,HLT_mu);
	   if(jet1pt>30 && jet2pt>30){
		   puIdweight_L=get_PUID_SF(jet1eta,jet1pt,h2_eff_mc2017_L,h2_mistag_mc2017_L,h2_eff_sf2017_L,h2_mistag_sf2017_L)*get_PUID_SF(jet2eta,jet2pt,h2_eff_mc2017_L,h2_mistag_mc2017_L,h2_eff_sf2017_L,h2_mistag_sf2017_L);
		   puIdweight_M=get_PUID_SF(jet1eta,jet1pt,h2_eff_mc2017_M,h2_mistag_mc2017_M,h2_eff_sf2017_M,h2_mistag_sf2017_M)*get_PUID_SF(jet2eta,jet2pt,h2_eff_mc2017_M,h2_mistag_mc2017_M,h2_eff_sf2017_M,h2_mistag_sf2017_M);
		   puIdweight_T=get_PUID_SF(jet1eta,jet1pt,h2_eff_mc2017_T,h2_mistag_mc2017_T,h2_eff_sf2017_T,h2_mistag_sf2017_T)*get_PUID_SF(jet2eta,jet2pt,h2_eff_mc2017_T,h2_mistag_mc2017_T,h2_eff_sf2017_T,h2_mistag_sf2017_T);
	   }

	   if(jet1pt_new>30 && jet2pt_new>30){
		   puIdweight_L_new=get_PUID_SF(jet1eta_new,jet1pt_new,h2_eff_mc2017_L,h2_mistag_mc2017_L,h2_eff_sf2017_L,h2_mistag_sf2017_L)*get_PUID_SF(jet2eta_new,jet2pt_new,h2_eff_mc2017_L,h2_mistag_mc2017_L,h2_eff_sf2017_L,h2_mistag_sf2017_L);
		   puIdweight_M_new=get_PUID_SF(jet1eta_new,jet1pt_new,h2_eff_mc2017_M,h2_mistag_mc2017_M,h2_eff_sf2017_M,h2_mistag_sf2017_M)*get_PUID_SF(jet2eta_new,jet2pt_new,h2_eff_mc2017_M,h2_mistag_mc2017_M,h2_eff_sf2017_M,h2_mistag_sf2017_M);
		   puIdweight_T_new=get_PUID_SF(jet1eta_new,jet1pt_new,h2_eff_mc2017_T,h2_mistag_mc2017_T,h2_eff_sf2017_T,h2_mistag_sf2017_T)*get_PUID_SF(jet2eta_new,jet2pt_new,h2_eff_mc2017_T,h2_mistag_mc2017_T,h2_eff_sf2017_T,h2_mistag_sf2017_T);
	   }

	   if(jet1pt_JEC_up>30 && jet2pt_JEC_up>30){
		   puIdweight_L_JEC_up=get_PUID_SF(jet1eta_JEC_up,jet1pt_JEC_up,h2_eff_mc2017_L,h2_mistag_mc2017_L,h2_eff_sf2017_L,h2_mistag_sf2017_L)*get_PUID_SF(jet2eta_JEC_up,jet2pt_JEC_up,h2_eff_mc2017_L,h2_mistag_mc2017_L,h2_eff_sf2017_L,h2_mistag_sf2017_L);
		   puIdweight_M_JEC_up=get_PUID_SF(jet1eta_JEC_up,jet1pt_JEC_up,h2_eff_mc2017_M,h2_mistag_mc2017_M,h2_eff_sf2017_M,h2_mistag_sf2017_M)*get_PUID_SF(jet2eta_JEC_up,jet2pt_JEC_up,h2_eff_mc2017_M,h2_mistag_mc2017_M,h2_eff_sf2017_M,h2_mistag_sf2017_M);
		   puIdweight_T_JEC_up=get_PUID_SF(jet1eta_JEC_up,jet1pt_JEC_up,h2_eff_mc2017_T,h2_mistag_mc2017_T,h2_eff_sf2017_T,h2_mistag_sf2017_T)*get_PUID_SF(jet2eta_JEC_up,jet2pt_JEC_up,h2_eff_mc2017_T,h2_mistag_mc2017_T,h2_eff_sf2017_T,h2_mistag_sf2017_T);
	   }

	   if(jet1pt_JEC_down>30 && jet2pt_JEC_down>30){
		   puIdweight_L_JEC_down=get_PUID_SF(jet1eta_JEC_down,jet1pt_JEC_down,h2_eff_mc2017_L,h2_mistag_mc2017_L,h2_eff_sf2017_L,h2_mistag_sf2017_L)*get_PUID_SF(jet2eta_JEC_down,jet2pt_JEC_down,h2_eff_mc2017_L,h2_mistag_mc2017_L,h2_eff_sf2017_L,h2_mistag_sf2017_L);
		   puIdweight_M_JEC_down=get_PUID_SF(jet1eta_JEC_down,jet1pt_JEC_down,h2_eff_mc2017_M,h2_mistag_mc2017_M,h2_eff_sf2017_M,h2_mistag_sf2017_M)*get_PUID_SF(jet2eta_JEC_down,jet2pt_JEC_down,h2_eff_mc2017_M,h2_mistag_mc2017_M,h2_eff_sf2017_M,h2_mistag_sf2017_M);
		   puIdweight_T_JEC_down=get_PUID_SF(jet1eta_JEC_down,jet1pt_JEC_down,h2_eff_mc2017_T,h2_mistag_mc2017_T,h2_eff_sf2017_T,h2_mistag_sf2017_T)*get_PUID_SF(jet2eta_JEC_down,jet2pt_JEC_down,h2_eff_mc2017_T,h2_mistag_mc2017_T,h2_eff_sf2017_T,h2_mistag_sf2017_T);
	   }

	   LEPele = lep==11 && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
	   LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0||HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && ngoodmus>1;
	   PHOTON= photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );
	   JET= ( ( (fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65) && (fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) &&  jet1pt<50 && jet2pt<50 && jet1pt>30 && jet2pt>30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && jet1puIdTight==1 && jet2puIdTight==1) || (jet1pt>50 && jet2pt>50 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) ); 
	   DR =drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5;

	   if(jentry%1000000==0)   cout<<jentry<<"; "<<nentries<<"; cut1 = "<<cut1<<endl;
	   //	   if(  !( ( (LEPmu) || (LEPele) ) && PHOTON ) )
	   //		   continue;
	   //	   if(m_dataset.Contains("ZA_plj")){
	   //		   if(isprompt!=1 ) continue;
	   //	   }
	   cut1++;//how many events passing the selection 
	   newtree->Fill(); 

   }
   cout<<cut0<<"; "<<cut1<<endl;
}
