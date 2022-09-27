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
void rm::Loop(TString name)
{
   if (fChain == 0) return;

   Double_t mjj_bins[4]={500, 800, 1200, 2000};
   Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};

//   RooUnfoldResponse K(5,ptBins[0],ptBins[5],5,ptBins[0],ptBins[5]);
   TFile* file = new TFile("hist_"+name+".root","recreate");
//   TH1D* hist1[5]; 
   TH2D* hist_sig= new TH2D("hist_sig",name+Form("\t\t %0.f<Mjj<%0.f  reco && gen;;yields",mjj_bins[0],mjj_bins[3]),3,mjj_bins,3,detajj_bins);
   TH2D* hist_sigout= new TH2D("hist_sigout",name+Form("\t\t %0.f<Mjj<%0.f  reco && !gen;;yields",mjj_bins[0],mjj_bins[3]),3,mjj_bins,3,detajj_bins);
   TH2D* hist_bkg= new TH2D("hist_bkg",name+Form("\t\t %0.f<Mjj<%0.f  reco;;yields",mjj_bins[0],mjj_bins[3]),3,mjj_bins,3,detajj_bins);
   TH2D* hist_data= new TH2D("hist_data",name+Form("\t\t %0.f<Mjj<%0.f  reco;;yields",mjj_bins[0],mjj_bins[3]),3,mjj_bins,3,detajj_bins);
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   int i1=0,i2=0,i3=0,i4=0,i5=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      ResetValue();
      genparticles();
//      cout<<genlep<<endl;
      if(jentry%50000==0)      cout<<jentry<<"; OK"<<endl;
      deltaetajj=fabs(jet1eta-jet2eta);
      LEPmu = lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110;
      LEPele = lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
      photon = photonet>20 &&( /*(fabs(photoneta)<2.5&&fabs(photoneta)>1.566) ||*/ (fabs(photoneta)<1.4442) );
      jet = jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7;
      dr = drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5;
      SignalRegion = Mjj>500 && deltaetajj>2.5 && Mva>100; /*&& zepp<2.4* && delta_phi>1.9;*/
//      Reco = (LEPmu || LEPele) && photon && jet && dr && SignalRegion;
      Reco = LEPele  && photon && jet && dr && SignalRegion;
//      Reco = LEPele  && photon && jet && dr && SignalRegion;
      
      GenLEPmu  = genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4;
      GenLEPele = genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5;
      GenPhoton = genphotonet>20 && ( /*(fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) ||*/ (fabs(genphotoneta)<1.4442) );
      GenJet = genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7;
      GenDr = gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5;
      GenSignalRegion = genMjj >500 && gendetajj>2.5; /*&& genZGmass>100&& genzepp<2.4; && gendelta_phi>1.9;*/
      Gen =  GenLEPele  && GenPhoton && GenJet && GenDr && GenSignalRegion;
      if(Mjj>2000) Mjj=1999; if(deltaetajj>6.5) deltaetajj=6.1;
//      Gen =  GenLEPele  && GenPhoton && GenJet && GenDr && GenSignalRegion;
//      Gen = ( GenLEPmu || GenLEPele ) && GenPhoton && GenJet && GenDr && GenSignalRegion;
      
      if(name.Contains("EWK") ){ 
	      scalef =  pileupWeight * scalef*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale;
              if(Reco && Gen){ 
		      i1++;
		      hist_sig->Fill(Mjj,deltaetajj,scalef*lumi);
	      }
              if(Reco&& !Gen) {
                      i2++;
		      hist_sigout->Fill(Mjj,deltaetajj,scalef*lumi);
	      }
      }//signal out gen bincontent
      if(name.Contains("EWK")==0 && !(name.Contains("Muon")==1 || name.Contains("Data")==1) && Reco){
	      i3++;
	      if(name.Contains("plj")){
		      hist_bkg->Fill(Mjj,deltaetajj,scalef);
	      }
	      else{ 
		      scalef =  pileupWeight * scalef*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale;
		      hist_bkg->Fill(Mjj,deltaetajj,scalef*lumi);}
      }//bkg bincontent
      if( (name.Contains("Muon")==1 || name.Contains("Data")==1) && Reco){
	      hist_data->Fill(Mjj,deltaetajj);}//data bincontent
   } 
   cout<<"end the loop"<<endl;
   file->cd();
   if(name.Contains("EWK")==0&& (name.Contains("Muon")==0 || name.Contains("Data")==0 || name.Contains("Ele")==0) ){
	   hist_bkg->Write();
	   cout<<name<<" sample after reco  selection: "<<i3<<endl;
   }
   if( (name.Contains("Muon")==1 || name.Contains("Data")==1 || name.Contains("Ele")==1)  )
           hist_data->Write();
   if(name.Contains("EWK") ){
	   cout<<" reco && gen selection "<<i1<<endl;
	   cout<<" reco && !gen selection "<<i2<<endl;
	   hist_sig->Write();
	   hist_sigout->Write();
   }
   file->Close();
}
