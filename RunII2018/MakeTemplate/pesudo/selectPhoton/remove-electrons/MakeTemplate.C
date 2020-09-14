#define MakeTemplate_cxx
#include "MakeTemplate.h"
#include <TH2.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"

//#include <fiostream>
using namespace std;
void MakeTemplate::Loop(TString name)
{
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();

   TFile *newfile2 = new TFile( "./"+name+ "_fakeele.root", "recreate"); 
   TTree *newtree2 = fChain->CloneTree(0);
   Int_t position;
   newtree2->Branch("position",&position,"position/I");
//   nentries = 100000;
   int cut0=0,cut2=0,cut3=0,cut4=0;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      cut0++;
      if(jentry%1000000==0)  cout<<jentry<<" ; "<<nentries<<endl;
      Int_t cut1=0;
      int index[6] = {-1};
      for(Int_t j=0;j<6;j++){
	      if (photon_isprompt[j]==1&&photon_pevnew[j]==1){
		      cut1++;
                      index[j] = j;
		      continue;
	      }
      }
      for(Int_t i = 0; i<6; i++){
         if(index[i]>-1){ 
		 position = index[i];
		 break;
	 }
      }
      if (cut1!=0)
	      cout<<"jentry = "<<jentry<<"  "<<"there is"<<" "<<cut1<<" photon(s) in the array"<<endl;
      if (cut1==0)
	      continue;
      cut2++;

      newtree2->Fill();
      
   }
   newfile2->cd();
   newtree2->Write(); //fill this tree into KEY from OBJ
   newfile2->Close();
   //print some information
   std::cout << "The total events are : " << cut0 << std::endl;
   std::cout << "the selected events   : " << cut2 << std::endl;
}
