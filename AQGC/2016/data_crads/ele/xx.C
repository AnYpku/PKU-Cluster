#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void xx::Loop(TString name)
{
   if (fChain == 0) return;

   double lumi=35.86;
   double ZGbin[6] = {150,400,600,800,1000,2e4};
   TH1D*h1=new TH1D(name,"ZGamma",5,ZGbin);
   TH1D*h2=new TH1D("h2","ZGamma",5,ZGbin);
   TFile*file =new TFile(name+"_hist.root","recreate");
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   double detajj;
   double photon_veto_scale;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      detajj=fabs(jet1eta-jet2eta);
      if( !(lep == 11 && (HLT_Ele1 >0 || HLT_Ele2 >0)  && ptlep1 > 25. && ptlep2 > 25. && abs(etalep1) < 2.5 && abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus ==0 && massVlep > 70. && massVlep < 110. && (jet1pt>30 && jet2pt>30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) && Mjj>500. &&detajj>2.5 && photonet>100.&&(abs(photoneta)<1.4442||(abs(photoneta)>1.566&&abs(photoneta)<2.5)) ) )
            continue;
      if(ZGmass>2e4) ZGmass=1999;
      if(name.Contains("plj")==0 && (name.Contains("Muon")==0 && name.Contains("Ele")==0) )
          actualWeight=actualWeight*lumi;
      else actualWeight=actualWeight;
     
      cout<<"actualWeigiht "<<actualWeight<<endl;
      h1->Fill(ZGmass,actualWeight);
      h2->Fill(ZGmass);
   }
   file->cd();
   h1->Write();
   h2->Write();
   file->Close();
}
