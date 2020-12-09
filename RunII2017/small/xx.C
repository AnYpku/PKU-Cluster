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

//PU jetID
//   TFile*fPUeff=new TFile("/home/pku/anying/cms/PKU-Cluster/RunII2017/PUID/effcyPUID_81Xtraining.root");
//   TFile*fPUsf=new TFile("/home/pku/anying/cms/PKU-Cluster/RunII2017/PUID/scalefactorsPUID_81Xtraining.root");
//   TH2F*h2_eff_mc2017_L=(TH2F*)fPUeff->Get("h2_eff_mc2017_L");
//   TH2F*h2_eff_mc2017_M=(TH2F*)fPUeff->Get("h2_eff_mc2017_M");
//   TH2F*h2_eff_mc2017_T=(TH2F*)fPUeff->Get("h2_eff_mc2017_T");
//   TH2F*h2_mistag_mc2017_L=(TH2F*)fPUeff->Get("h2_mistag_mc2017_L");
//   TH2F*h2_mistag_mc2017_M=(TH2F*)fPUeff->Get("h2_mistag_mc2017_M");
//   TH2F*h2_mistag_mc2017_T=(TH2F*)fPUeff->Get("h2_mistag_mc2017_T");
//   TH2F*h2_eff_sf2017_L=(TH2F*)fPUsf->Get("h2_eff_sf2017_L");
//   TH2F*h2_eff_sf2017_M=(TH2F*)fPUsf->Get("h2_eff_sf2017_M");
//   TH2F*h2_eff_sf2017_T=(TH2F*)fPUsf->Get("h2_eff_sf2017_T");
//   TH2F*h2_mistag_sf2017_L=(TH2F*)fPUsf->Get("h2_mistag_sf2017_L");
//   TH2F*h2_mistag_sf2017_M=(TH2F*)fPUsf->Get("h2_mistag_sf2017_M");
//   TH2F*h2_mistag_sf2017_T=(TH2F*)fPUsf->Get("h2_mistag_sf2017_T");
  

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

	   if(drla==10) drla=-1; if(drla2==10) drla2=-1; if(drj1a==10) drj1a=-1;if(drj2a==10) drj2a=-1;
	   puIdweight_L=1;
	   puIdweight_M=1;
	   puIdweight_T=1;
//	   puIdweight_L=get_PUID_SF(jet1eta,jet1pt,h2_eff_mc2017_L,h2_mistag_mc2017_L,h2_eff_sf2017_L,h2_mistag_sf2017_L);
//	   puIdweight_M=get_PUID_SF(jet1eta,jet1pt,h2_eff_mc2017_M,h2_mistag_mc2017_M,h2_eff_sf2017_M,h2_mistag_sf2017_M);
//	   puIdweight_T=get_PUID_SF(jet1eta,jet1pt,h2_eff_mc2017_T,h2_mistag_mc2017_T,h2_eff_sf2017_T,h2_mistag_sf2017_T);

	   LEPele = lep==11 && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
	   LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0||HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110;
	   PHOTON= photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );

	   if(jentry%1000000==0)   cout<<jentry<<"; "<<nentries<<"; cut1 = "<<cut1<<endl;
	   if(  !( ( (LEPmu) || (LEPele) ) && PHOTON ) )
		   continue;
	   if(m_dataset.Contains("ZA")&&m_dataset.Contains("plj")){
		   if(isprompt!=1 ) continue;
	   }
	   cut1++;//how many events passing the selection 
	   newtree->Fill(); 

   }
   cout<<cut0<<"; "<<cut1<<endl;
}
