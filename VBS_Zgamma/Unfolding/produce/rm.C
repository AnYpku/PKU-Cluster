//gSystem->Load("/home/pku/anying/cms/Unfolding/RooUnfold/libRooUnfold.so");
#define rm_cxx
#include "genparticles.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLegend.h"
#include <iostream>

//#include "RooUnfoldResponse.h"
//#include "RooUnfoldBayes.h"
//#include "RooUnfoldSvd.h"
//#include "RooUnfoldTUnfold.h"
//#include "RooUnfoldInvert.h"
void rm::Loop()
{
   if (fChain == 0) return;
   Long64_t nbytes = 0, nb = 0;
   double nentries=fChain->GetEntries();
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      ResetValue();
      genparticles();
//      cout<<genlep<<endl;
      if(jentry%50000==0)      cout<<jentry<<"; OK3"<<endl;
      deltaetajj=fabs(jet1eta-jet2eta);
      ExTree->Fill();
   }
}
