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

      if(drla==10) drla=-1; if(drla2==10) drla2=-1; if(drj1a==10) drj1a=-1;if(drj2a==10) drj2a=-1;

      LEPele = lep==11 && (HLT_Ele1>0||HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
      LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 ;
      SignalRegion= Mjj>500 && deltaetajj>2.5;// && zepp<1.8;
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
