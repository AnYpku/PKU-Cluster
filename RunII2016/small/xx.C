#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
//#include "muon_channel_scale.C"

using namespace std;
void xx::Loop(TString name)
{
   if (fChain == 0) return;

   cut0=0,cut1=0;
   bool LEPele,LEPmu,JET,PHOTON,SignalRegion,DR;

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

      LEPele = lep==11 && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
      LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && ngoodmus>1;
      PHOTON= photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );
      JET= ( ( (fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65) && (fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) &&  jet1pt<50 && jet2pt<50 && jet1pt>30 && jet2pt>30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && jet1puIdTight==1 && jet2puIdTight==1) || (jet1pt>50 && jet2pt>50 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) ); 
      SignalRegion= Mjj>500 && deltaetajj>2.5;// && zepp<1.8;
      DR =drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5;

      if(jentry%100000==0)   cout<<jentry<<"; "<<nentries<<"; cut1 = "<<cut1<<endl;
      if(  !( ( (LEPmu) || (LEPele) ) /*&& JET && DR && SignalRegion*/) )
	      continue;
      if( !(PHOTON) )continue;
      if(m_dataset.Contains("ZA")&&m_dataset.Contains("plj")){
	      if(isprompt!=1 ) continue;
      }
      cut1++;//how many events passing the selection 
      newtree->Fill(); 

    }
   cout<<cut0<<"; "<<cut1<<endl;
}
