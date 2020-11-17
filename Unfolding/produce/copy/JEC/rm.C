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
void rm::Loop(TString tag)
{
   if (fChain == 0) return;
   Long64_t nbytes = 0, nb = 0;
   Long64_t npp = fChain->GetEntries("theWeight>0.");
   Long64_t nmm = fChain->GetEntries("theWeight<0.");
   double nentries=fChain->GetEntries();
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      ResetValue();
      genparticles();
      if(tag.Contains("16")){
	      if(m_dataset.Contains("ZA")&&m_dataset.Contains("EWK")==0){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight;}
	      if(m_dataset.Contains("ZA_interf")){ scalef=1000.*0.014/float(npp-nmm)*fabs(theWeight)/theWeight;}
	      if(m_dataset.Contains("EWK")){ scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight;}
      }
      if(tag.Contains("17")||tag.Contains("18")){
	      if(m_dataset.Contains("ZA")&&m_dataset.Contains("EWK")==0){ scalef=1000.*55.49/float(npp-nmm)*fabs(theWeight)/theWeight;}
	      if(m_dataset.Contains("ZA_interf")){ scalef=1000.*0.012/float(npp-nmm)*fabs(theWeight)/theWeight;}
	      if(m_dataset.Contains("EWK")){ scalef=1000.*0.1143/float(npp-nmm)*fabs(theWeight)/theWeight;}
      }
      //      cout<<genlep<<endl;
      if(jentry%50000==0)      cout<<jentry<<"; "<<scalef<<endl;
      ExTree->Fill();
   }
}
