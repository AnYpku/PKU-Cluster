#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"

using namespace std;
void xx::Loop(TString name)
{
   if (fChain == 0) return;

   TFile*f_hltmu=new TFile("../muon_HLT_SF.root");
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
   //photon id
   TFile* ID_photon_file = TFile::Open("./SF/2018_PhotonsMedium.root");
   TH2F* ID_photon=0;
   ID_photon_file->GetObject("EGamma_SF2D", ID_photon);
   cout<<"open the photon ID file: 2018_PhotonsMedium.root"<<endl;
   Long64_t nentries = fChain->GetEntriesFast();
   int cut0=0, cut1=0;
   bool LEPele,LEPmu,JET,PHOTON,SignalRegion,DR;
//  nentries=1000;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      cut0++;//total events, cut0=t1->GetEntries()
       
      if(name.Contains("Mu")) scalef=1;
      if(name.Contains("Ele"))  scalef=1;

      ele_hlt_scale=1;
      muon_hlt_scale=1;
      if(lep==11)
              ele_hlt_scale=get_eleHLT_SF(etalep1,ptlep1,etalep2,ptlep2,HLT_MC1,HLT_SF1,HLT_MC2,HLT_SF2);
      if(lep==13)
              muon_hlt_scale=muon_HLT_scale(ptlep1,ptlep2,etalep1,etalep2,HLT_mu);

      if(drla==10) drla=-1; if(drla2==10) drla2=-1; if(drj1a==10) drj1a=-1;if(drj2a==10) drj2a=-1;
      if(photonet>0){
	      photon_id_scale=get_photon_ID(photoneta,photonet,ID_photon);
      }

      LEPele = lep==11 && (HLT_Ele1>0||HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
      LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 ;
      //      SignalRegion= Mjj>500 && deltaetajj>2.5;// && zepp<1.8;
      PHOTON= photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );
      JET=jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7;
      DR =drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5;
      if(jentry%100000==0)   cout<<jentry<<"; "<<nentries<<"; cut1 = "<<cut1<<endl;
      if( ! ( (LEPmu || LEPele) && PHOTON /*&& JET && DR&& SignalRegion*/) )
	      continue;
      if(m_dataset.Contains("ZA")&&m_dataset.Contains("plj")){
	      if(isprompt!=1 ) continue;
      }
      cut1++;//how many events passing the selection 
      ExTree->Fill(); //fill the brach when this entry pass the both selection

   }
}
