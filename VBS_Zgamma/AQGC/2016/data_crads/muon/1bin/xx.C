#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void xx::Loop(TString name)
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

   double lumi=35.9;
   double ZGbin[2] = {150,2000};
   TH1D*h1=new TH1D(name,"Mva",1,ZGbin);
//   if(name.Contains("EWK")) h1->SetTitle("diboson"); 
//   if(name.Contains("Muon")||name.Contains("Ele")) h1->SetTitle("data_obs"); 
   TFile*file =new TFile(name+"_hist.root","recreate");
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   Double_t photon_veto_scale;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if( !(lep == 13 && (HLT_Mu2 >0 || HLT_Mu5 >0)  && ptlep1 > 20. && ptlep2 > 20. && abs(etalep1) < 2.4 && abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && jet1pt>30. && jet2pt>30.&& abs(jet1eta)< 4.7 && abs(jet2eta)<4.7 && Mjj>500. &&deltaetajj>2.5 && photonet>100.&&(abs(photoneta)<1.4442||(abs(photoneta)>1.566&&abs(photoneta)<2.5)) && ZGmass>100) )
            continue;
      if(ZGmass>2000) ZGmass=1999;
      if(abs(photoneta)<1.4442) photon_veto_scale=0.9938;
      if((abs(photoneta)>1.566&&abs(photoneta)<2.5))
              photon_veto_scale=0.9875;
      if(name.Contains("plj")==0 && (name.Contains("Muon")==0 && name.Contains("Ele")==0) )
          actualWeight=actualWeight*lumi*photon_veto_scale;
      else actualWeight=actualWeight;
     
      cout<<"actualWeigiht "<<actualWeight<<endl;
      h1->Fill(ZGmass,actualWeight);
   }
   file->cd();
   h1->Write();
   file->Close();
}
