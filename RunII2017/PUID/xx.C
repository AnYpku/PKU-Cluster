#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "ele_channel_scale.C"
#define Pi 3.141592653589793

using namespace std;
void xx::Loop(TString name)
{
   if (fChain == 0) return;

   cut0=0,cut1=0;
   bool LEPele,LEPmu,JET,PHOTON,SignalRegion,DR;
   TFile*file=new TFile("./PUIDMaps.root");
   TH2F*h2_eff_mc2017_L=(TH2F*)file->Get("h2_eff_mc2017_L");
   TH2F*h2_eff_mc2017_M=(TH2F*)file->Get("h2_eff_mc2017_M");
   TH2F*h2_eff_mc2017_T=(TH2F*)file->Get("h2_eff_mc2017_T");
   TH2F*h2_mistag_mc2017_L=(TH2F*)file->Get("h2_mistag_mc2017_L");
   TH2F*h2_mistag_mc2017_M=(TH2F*)file->Get("h2_mistag_mc2017_M");
   TH2F*h2_mistag_mc2017_T=(TH2F*)file->Get("h2_mistag_mc2017_T");
   TH2F*h2_eff_sf2017_L=(TH2F*)file->Get("h2_eff_sf2017_L");
   TH2F*h2_eff_sf2017_M=(TH2F*)file->Get("h2_eff_sf2017_M");
   TH2F*h2_eff_sf2017_T=(TH2F*)file->Get("h2_eff_sf2017_T");
   TH2F*h2_mistag_sf2017_L=(TH2F*)file->Get("h2_mistag_sf2017_L");
   TH2F*h2_mistag_sf2017_M=(TH2F*)file->Get("h2_mistag_sf2017_M");
   TH2F*h2_mistag_sf2017_T=(TH2F*)file->Get("h2_mistag_sf2017_T");
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
	   realjet1=1;realjet2=1;
	   puIdweight_T=1;puIdweight_L=1;puIdweight_M=1;
	   if(drla==10) drla=-1; if(drla2==10) drla2=-1; if(drj1a==10) drj1a=-1;if(drj2a==10) drj2a=-1;
	   LEPele = lep==11 && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
	   LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0||HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110;
	   PHOTON= photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );
	   JET=jet1pt>30&& fabs(jet1eta)<4.7 && jet2pt>30 && fabs(jet2eta)<4.7;

	   if(jentry%1000000==0)   cout<<jentry<<"; "<<nentries<<"; cut1 = "<<cut1<<endl;
	   if(  !( ( (LEPmu) || (LEPele) ) && PHOTON ) )
		   continue;
	   if(m_dataset.Contains("ZA")&&m_dataset.Contains("plj")){
		   if(isprompt!=1 ) continue;
	   }
	   double DR1=1e4,DR2=1e4;
	   int ip1=-1,ip2=-1;
	   for(int i=0;i<6;i++){
		   double DR1_tmp=delta_R(jet1eta,jet1phi,genjet_eta[i],genjet_phi[i]);
		   if(DR1_tmp<DR1){
			   DR1=DR1_tmp;
                           ip1=i;
		   }
	   }
	   for(int i=0;i<6;i++){
		   double DR2_tmp=delta_R(jet2eta,jet2phi,genjet_eta[i],genjet_phi[i]);
		   if(DR2_tmp<DR2){
			   ip2=i ;
			   if(ip1==ip2) continue;
			   DR2=DR2_tmp;
		   }

	   }
	   cout<<"DR1 "<<DR1<<"DR2 "<<DR2<<endl;
           if(jet1pt<50 && DR1<0.4){ 
		   realjet1=1;
	   }
	   else if(jet1pt<50 && DR1>0.4){ realjet1=0;
	   }
	   else if(jet1pt>50) realjet1=1;
           if(jet2pt<50 && DR2<0.4) realjet2=1;
	   else if(jet2pt<50 && DR2>0.4){ 
		   realjet2=0;
	   }
	   else if(jet2pt>50) realjet2=1;

           puIdweight_T=get_PUID_SF(jet1eta,jet1pt,jet2eta,jet2pt,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,realjet1,realjet2,jet1puIdTight,jet2puIdTight);
           puIdweight_L=get_PUID_SF(jet1eta,jet1pt,jet2eta,jet2pt,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,realjet1,realjet2,jet1puIdLoose,jet2puIdLoose);
           puIdweight_M=get_PUID_SF(jet1eta,jet1pt,jet2eta,jet2pt,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,realjet1,realjet2,jet1puIdMedium,jet2puIdMedium);

	   cut1++;//how many events passing the selection 
	   newtree->Fill(); 

   }
   cout<<cut0<<"; "<<cut1<<endl;
}
Double_t xx::delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2)
{       
        Double_t dp = phi1-phi2;
        if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
        Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
        return dr;
}
