#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void xx::Loop(TString name,vector<double> ZGbin)
{
//   In a ROOT session, you can do:
//      Root > .L xx.C
//      Root > xx t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   double lumi=41.52;
//   double ZGbin[6] = {150,400,600,800,1000,2000};
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
      if( !(lep == 11 && (HLT_Ele1 >0 || HLT_Ele2 >0)  && ptlep1 > 25. && ptlep2 > 25. && abs(etalep1) < 2.5 && abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus ==0 && massVlep > 70. && massVlep < 110. && /*( (!(fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65) && !(fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) &&  jet1pt<50 && jet2pt<50 && jet1pt>30 && jet2pt>30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) || (jet1pt>50 && jet2pt>50 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) )*/(jet1pt>30 && jet2pt>30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) && Mjj>500. &&detajj>2.5 && photonet>100.&&(abs(photoneta)<1.4442||(abs(photoneta)>1.566&&abs(photoneta)<2.5)) ) )
            continue;
      if(ZGmass>2000) ZGmass=1999;
      if(abs(photoneta)<1.4442) photon_veto_scale=0.9862;
      if((abs(photoneta)>1.566&&abs(photoneta)<2.5))
	      photon_veto_scale=0.9638;
      if(name.Contains("plj")==0 && (name.Contains("Muon")==0 && name.Contains("Ele")==0) )
          actualWeight=actualWeight*photon_veto_scale*lumi;
      else actualWeight=actualWeight;
     
      cout<<"actualWeigiht "<<actualWeight<<endl;
      h1->Fill(ZGmass,actualWeight);
   }
   file->cd();
   h1->Write();
   file->Close();
}
