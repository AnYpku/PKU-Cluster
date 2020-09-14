#define apply_cxx
#include "apply.h"
#include <TH2.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include "TLorentzVector.h"
//#include <fiostream>
using namespace std;
void apply::Loop(TString name,TGraph* gr)
{
//   In a ROOT session, you can do:
//      root> .L apply.C
//      root> apply t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
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
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   TFile* file = new TFile("trans_"+name+"_applied.root","RECREATE");
   TH1D* h1 = new TH1D(name,"",1000,0,0.07);
   TFile* fout = new TFile("./T-"+name +".root", "RECREATE");
   TTree* ExTree = fChain->CloneTree(0);
   double actualWeight;
   
//   nentries = 100000;
   TLorentzVector leading_electron, subleading_electron, photon;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      leading_electron.SetPtEtaPhiM(ptlep1, etalep1, philep1, 0.0005);
      subleading_electron.SetPtEtaPhiM(ptlep2, etalep2, philep2, 0.0005);
      if(jentry%100000==0) cout<<jentry<<"; "<<nentries<<endl;
      // if (Cut(ientry) < 0) continue;
      LEP = lep==13 && ptlep1 > 20. && ptlep2 > 20.&& abs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110 && (HLT_Mu2>0 || HLT_Mu5>0) ;
      for(Int_t j=0;j<6;j++){
	  photon.SetPtEtaPhiE(photon_pt[j],photon_eta[j],photon_phi[j],photon_e[j]);
	  double tm1=(leading_electron+subleading_electron+photon).M();
          Photon_cut[j]=  photon_pevnew[j]==1 && photon_hoe[j]<0.0396  && photon_chiso[j]<0.441 &&
                          photon_nhiso[j]<2.725 + 0.0148*photon_pt[j] + 0.000017*photon_pt[j]*photon_pt[j] && 
                          photon_phoiso[j]<2.571 + 0.0047*photon_pt[j] && 
                          fabs(photon_eta[j])<1.4442 && photon_pt[j]>20 && 
                          /*photon_drla[j]>0.7 && photon_drla[j]!=10 && 
                          photon_drla2[j]>0.7&&photon_drla2[j]!=10 &&*/
                          tm1>70 && tm1<110;
          if(Photon_cut[j]&&LEP){
		  vector_pt.push_back(photon_pt[j]);
	  }
          else {vector_pt.push_back(0);}
       }//fill the vector_pt
    size=vector_pt.size();
    biggest_pt = max_element(begin(vector_pt),end(vector_pt));
    if(*biggest_pt==0){
        vector_pt.clear();
        continue;}
    ExTree->Fill();
    position = distance( begin(vector_pt), biggest_pt);
    double sieie;
    if(name.Contains("Jets")){
	    scalef = 0.070591*fabs(theWeight)/theWeight * prefWeight;
	    sieie = gr->Eval(photon_sieie[position]);
    }
    else {
	    scalef = 1;
	    sieie = photon_sieie[position];
    }
    h1->Fill(sieie,scalef);
    vector_pt.clear();
   }
   fout->cd();
   ExTree->Write();
   fout->Close();
   file->cd();
   h1->Write();
   file->Close();
}

void apply::style(){
 gStyle->SetOptStat(0);
 gStyle->SetPadGridX(1);
 gStyle->SetPadGridY(1);
 gStyle->SetPadTickX(1);
 gStyle->SetPadTickY(1);
 gStyle->SetAxisColor(1, "XYZ");
 gStyle->SetStripDecimals(kTRUE);
 gStyle->SetTickLength(0.03, "XYZ");
 }

void apply::histo(){
  bin=20;
  xlow= 0.0002;
  xhigh= 0.0202;
  for(Int_t i=0;i<9;i++){
         h1[i]=new TH1D(Form("h1_pt%0.f-%0.f",lowpt[i],highpt[i]),"true template",bin,xlow,xhigh);
         h2[i]=new TH1D(Form("h2_pt%0.f-%0.f",lowpt[i],highpt[i]),"fake template",bin,xlow,xhigh);
         h3[i]=new TH1D(Form("h3_pt%0.f-%0.f",lowpt[i],highpt[i]),"data template",bin,xlow,xhigh);
         h4[i]=new TH1D(Form("h4_pt%0.f_%0.f",lowpt[i],highpt[i]),"fake contribution from ZA",bin,xlow,xhigh);
     }
}

void apply::ResetVal(){

//   lowpt[7] ={25,30,35,40,50,65,100};
//   highpt[7]={30,35,40,50,65,100,400};
   bin=20;
   xlow=0.0002;
   xhigh=0.0202;
   for(Int_t i=0;i<9;i++){
      m1[i]=0;
      m2[i]=0;
      m3[i]=0;
      TrueNumber[i]=0;
      FakeNumber[i]=0;
     }
   position=0,size=0,m=0;
} 
