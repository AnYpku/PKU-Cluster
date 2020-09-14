#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>

void xx::Loop(TString name, vector<double> ZGbin)
{
   if (fChain == 0) return;

//   double lumi=58.7;
//   double ZGbin[6] = {150,400,600,800,1000,2e4};
   TH1D*h1=new TH1D(name,"ZGamma",ZGbin.size()-1,&ZGbin[0]);
//   if(name.Contains("EWK")) h1->SetTitle("diboson"); 
//   if(name.Contains("Muon")||name.Contains("Ele")) h1->SetTitle("data_obs"); 
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
      if( !(
		      (lep == 11 && (HLT_Ele1 >0 || HLT_Ele2 >0)  && ptlep1 > 25. && ptlep2 > 25. && abs(etalep1) < 2.5 && abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus ==0 && massVlep > 70. && massVlep < 110. && jet1pt>30. && jet2pt>30.&& abs(jet1eta)< 4.7 && abs(jet2eta)<4.7 && Mjj>500. &&detajj>2.5 && photonet>100.&&(abs(photoneta)<1.4442||(abs(photoneta)>1.566&&abs(photoneta)<2.5)) )//||
		      //(lep == 13 && (HLT_Mu2 >0 || HLT_Mu1 >0) && ptlep1 > 20. && ptlep2 > 20. && abs(etalep1) < 2.4 && abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && jet1pt>30. && jet2pt>30.&& abs(jet1eta)< 4.7 && abs(jet2eta)<4.7 && Mjj>500. &&detajj>2.5 && photonet>100.&&(abs(photoneta)<1.4442||(abs(photoneta)>1.566&&abs(photoneta)<2.5)) ) 
	   ))
            continue;
      if(ZGmass>2000) ZGmass=1999;
      if(fabs(photoneta)<1.4442){
	      if(photonet<30) photon_veto_scale=0.9869;
	      else if(photonet>30 && photonet<60) photon_veto_scale=0.9908;
              else photon_veto_scale=1.0084;
      }
      if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566){
	      if(photonet<30) photon_veto_scale=0.9535;
	      else if(photonet>30 && photonet<60) photon_veto_scale=0.9646;
              else photon_veto_scale=1.0218;
      }
      if(name.Contains("plj")==0 && (name.Contains("Muon")==0 && name.Contains("Ele")==0) )
          actualWeight=actualWeight;
     
//      cout<<"actualWeigiht "<<actualWeight<<endl;
      h1->Fill(ZGmass,actualWeight);
   }
   file->cd();
   h1->Write();
   file->Close();
}
