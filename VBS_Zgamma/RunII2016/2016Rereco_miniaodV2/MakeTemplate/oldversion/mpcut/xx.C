#define xx_cxx
#include <algorithm>
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
using namespace std;

void xx::Loop(TString name)
{
//   In a ROOT session, you can do:
//      root> .L xx.C
//      root> xx t
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
   if(name.Contains("WA")){
      f1 = new TFile("./root/waMC_template.root","recreate") ;} 
   if(name.Contains("SMu")){
      f1 = new TFile("./root/waData_template.root","recreate") ;} 
   for(Int_t i=0;i<ptnumber;i++){
      if(name.Contains("WA")){
           h_mcwa[i]=new TH1F(Form("hmcwa_pt%0.f-%0.f",lowpt[i],highpt[i]),"MC WA",bin,0,xhigh);
          fmcwa[i] = new TFile(Form("./root/fmcwa_%0.f_%0.f.root",lowpt[i],highpt[i]), "RECREATE"); 
	  tree_mcwa[i] = new TTree("tree_mcwa","tree_mcwa");
	  tree_mcwa[i]->Branch("sieie",&Sieie_wa);}
      if(name.Contains("SMu")){
           h_datawa[i]=new TH1F(Form("hdatawa_pt%0.f-%0.f",lowpt[i],highpt[i]),"data template",bin,0,xhigh);
           h_sieie[i]=new TH1F(Form("hsieie_pt%0.f-%0.f",lowpt[i],highpt[i]),"data template",bin,0,xhigh);
          fdata[i] = new TFile(Form("./root/fdata_%0.f_%0.f.root",lowpt[i],highpt[i]), "RECREATE"); 
	  tree_datawa[i] = new TTree("tree_datawa","tree_datawa");
	  tree_datawa[i]->Branch("sieie",&Sieie_wa);}
   }
//   nentries=100;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%1000000==0) cout<<jentry<<"; "<<nentries<<endl;
      // if (Cut(ientry) < 0) continue;
      for(Int_t j=0;j<6;j++){
          Photon_cut[j]= photon_pev[j]==1  && 
                        photon_hoe[j]<0.0396 && photon_chiso[j]<0.441 && 
          photon_nhiso[j]<2.725+0.0148*photon_pt[j]+0.000017*pow(photon_pt[j],2)       && photon_phoiso[j]<2.571 + 0.0047*photon_pt[j]&&
          abs(photon_eta[j])<1.4442;
          if(Photon_cut[j]){
             vector_pt.push_back(photon_pt[j]);}
          else {vector_pt.push_back(0);}
       }//fill the vector_pt
      size=vector_pt.size();
      biggest_pt = max_element(begin(vector_pt),end(vector_pt));
      if(*biggest_pt==0){
        vector_pt.clear();
        continue;}
      position = distance( begin(vector_pt), biggest_pt);
      if(jentry%10000==0) cout<<jentry<<"; the biggest pt = "<<*biggest_pt<<"; the position = "<<position<<endl;
      for(Int_t k=0;k<ptnumber;k++){
        if( photon_drla[position]>0.4 &&
            photon_pt[position]>lowpt[k] && photon_pt[position]<highpt[k]){
            ExTree->Fill();
            if(name.Contains("WA")){h_mcwa[k]->Fill(photon_sieie[position]);}
            if(name.Contains("SMu")){h_datawa[k]->Fill(photon_sieie[position]);}
            Sieie_wa=photon_sieie[position];
           
	    if(name.Contains("WA")){
		    fmcwa[k]->cd();
		    tree_mcwa[k]->Fill(); }
	    if(name.Contains("SMu")){
		    fdata[k]->cd();
		    tree_datawa[k]->Fill(); }
	    if(photon_sieie[position]<0.01022){
                     h_sieie[k]->Fill(photon_sieie[position]);}
	}
         }
          vector_pt.clear();
    }
if(name.Contains("WA")){
   for(Int_t i=0;i<ptnumber;i++){f1->cd();h_mcwa[i]->Write();}
 }
if(name.Contains("SMu")){
   for(Int_t i=0;i<ptnumber;i++){f1->cd();h_datawa[i]->Write();h_sieie[i]->Write();}
 }
   
}
