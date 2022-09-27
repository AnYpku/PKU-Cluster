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

   TFile *newfile = new TFile( "./out"+name+ "_fakephoton.root", "recreate"); 
   TTree *newtree = fChain->CloneTree(0);
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
      for(Int_t j=0;j<6;j++){
	      if (photon_isprompt[j]==1 && photon_pevnew[j]==1){
		      cut1++;
		      continue;
	      }
      }
      if (cut1!=0)
	      cout<<"jentry = "<<jentry<<"  "<<"the real photon in one event "<<cut1<<endl;
      if (cut1!=0)
	      continue;
      cut2++;

      newtree->Fill();
   }
   newfile->cd();
   newtree->Write(); //fill this tree into KEY from OBJ
   newfile->Close();
   //print some information
   std::cout << "The total events are : " << cut0 << std::endl;
   std::cout << "the selected events   : " << cut2 << std::endl;
}
