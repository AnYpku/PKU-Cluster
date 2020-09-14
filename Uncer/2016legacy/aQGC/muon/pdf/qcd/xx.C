#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#define num 103
#define Pi 3.1415926
void xx::Loop( TString name)
{
   if (fChain == 0) return;

   double ZGammabins[6]={150,400,600,800,1000,2000};
   double lumi=35.9;
   double actualWeight[num];
   TH1D*th2[num];
   char th2name[num];
   for(Int_t i=0;i<num;i++){
       sprintf(th2name,"th2_%d",i);
           th2[i] = new TH1D(th2name,th2name,5,ZGammabins);
           th2[i]->Sumw2();
   }
   TFile*f1=new TFile(name+"-scale_hist.root","RECREATE");
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   int p;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      p=0;
      if (fabs(philep1-philep2)>Pi) drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(2*Pi-fabs(philep1-philep2))*(2*Pi-fabs(philep1-philep2)));
      else drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(fabs(philep1-philep2))*(fabs(philep1-philep2)));
      if (fabs(jet1phi-jet2phi)>Pi) drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
      else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));
      if( !(     (lep == 13 && (HLT_Mu2 >0 || HLT_Mu5 >0)  && ptlep1 > 20. && ptlep2 > 20. && abs(etalep1) < 2.4 && abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet>100.&&(abs(photoneta)<1.4442||(abs(photoneta)>1.566&&abs(photoneta)<2.5)) && jet1pt>30. && jet2pt>30.&& abs(jet1eta)< 4.7 && abs(jet2eta)<4.7 && Mjj>500. &&deltaetajj>2.5 && drj1a>0.5 &&drj2a>0.5 && drj1l>0.5 && drj2l>0.5 && drjj>0.5 && drll>0.3 && drla>0.7 && drla2>0.7) ||
                  (lep == 11 &&  ( HLT_Ele1 > 0|| HLT_Ele2 > 0) && ptlep1 > 25. && ptlep2 > 25. && fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0 && massVlep > 70. && massVlep < 110. && photonet > 100. &&( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) )  && jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && drj1a>0.5 &&drj2a>0.5 && drj1l>0.5 && drj2l>0.5 && drjj>0.5&& Mjj>500 && deltaetajj>2.5 && drla>0.7 && drla2>0.7)     ))
            continue;
      if(Mva>2000) Mva=1999;
      for(Int_t i=0;i<103;i++){
	      actualWeight[p]=scalef*lumiWeight*pweight[i];//*pileupWeight;
	      th2[p]->Fill(Mva, actualWeight[p]);
	      p++;
      } 
      for(Int_t k=0;k<113;k++){
//	      if( (k==109 || k==111) ) continue;
	      cout<<"pweight ["<<k<<"] = "<<pweight[k]<<endl;
      }
      for(Int_t k=0;k<num;k++){
//	      cout<<"scalef "<<scalef<<endl;
//	      cout<<"pileupWeight "<<pileupWeight<<endl;
	      cout<<"actualWeight ["<<k<<"] = "<<actualWeight[k]<<endl;
      }
      cout<<"######################################"<<endl;
   }
   f1->cd();
   for(int i=0;i<num;i++){
      th2[i]->Write();
   }
   f1->Close();
}
