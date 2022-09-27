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

   Double_t ptBins[6]={20,50,80,120,200,400};

//   RooUnfoldResponse K(5,ptBins[0],ptBins[5],5,ptBins[0],ptBins[5]);
//   TH2D* h2 = new TH2D("h2", "gen selection", 5, ptBins,5,ptBins);
//   TH2D* h3 = new TH2D("h3", "gen && reco selection",5, ptBins,5,ptBins);
//   TH2D* hrm = new TH2D("rm","",5,ptBins,5,ptBins);
//   TH1D* hun[5];
   TFile* file = new TFile("hist_"+name+".root","recreate");
   TH1D* hist1[5]; 
   TH1D* hist5[5];
   TH1D* hist2= new TH1D("hist",name+Form("\t\t %0.f<leading p_{T}^{reco}<%0.f;leding p_{T}^{gen};yields",ptBins[0],ptBins[5]),5,ptBins);
   TH1D* hist3= new TH1D("hist3",name+Form("\t\t %0.f<leading p_{T}^{reco}<%0.f reco out of gen;leding p_{T}^{gen};yields",ptBins[0],ptBins[5]),5,ptBins);
   for(int i=0;i<5;i++)
        {
		hist1[i]= new TH1D(name+Form("_hist_%i",i+1),name+Form("\t\t %0.f<leading p_{T}^{reco}<%0.f;leding p_{T}^{gen};yields",ptBins[i],ptBins[i+1]),1,ptBins[i],ptBins[i+1]);
		hist5[i]= new TH1D(Form("hist5_%i",i+1),name+Form("\t\t %0.f<leading p_{T}^{reco}<%0.f;leding p_{T}^{gen};yields",ptBins[i],ptBins[i+1]),5,ptBins);
}
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
      if(jentry%50000==0)      cout<<jentry<<"; OK3"<<endl;
      LEPmu = lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110;
      LEPele = lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
      photon = photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );
      jet = jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7;
      dr = drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5;
      SignalRegion = Mjj>500 && deltaetajj>2.5 && Mva>100; /*&& zepp<2.4* && delta_phi>1.9;*/
//      Reco = (LEPmu || LEPele) && photon && jet && dr && SignalRegion;
      Reco = LEPmu  && photon && jet && dr && SignalRegion;
      
      GenLEPmu  = /*genlep==13 &&*/ genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4;
      GenLEPele = /*genlep==11 &&*/ genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5;
      GenPhoton = genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) );
      GenJet = genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7;
      GenDr = gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5;
      GenSignalRegion = genMjj >500 && gendetajj>2.5; /*&& genZGmass>100&& genzepp<2.4; && gendelta_phi>1.9;*/
      Gen =  GenLEPmu  && GenPhoton && GenJet && GenDr && GenSignalRegion;
//      Gen = ( GenLEPmu || GenLEPele ) && GenPhoton && GenJet && GenDr && GenSignalRegion;
      if(genlep1pt>400) genlep1pt=399;if(ptlep1>400) ptlep1=399;
      if(name.Contains("EWK") ){ 
              if(Reco){
		      i1++;
		      hist2->Fill(ptlep1,scalef);
	      }
              if(Gen)i2++;
              if(Reco && Gen) i3++;
              if(Reco&& !Gen) {
                      i4++;
		      hist3->Fill(ptlep1,scalef*lumi);
	      }
      }//signal out gen bincontent
      if(name.Contains("EWK")==0 && !(name.Contains("Muon")==1 || name.Contains("Data")==1) && Reco){
	      i1++;
	      if(name.Contains("plj")){
		      hist2->Fill(ptlep1,scalef);
	      }
	      else{ 
		      hist2->Fill(ptlep1,scalef*lumi);}
      }//bkg bincontent
      if( (name.Contains("Muon")==1 || name.Contains("Data")==1) && Reco){
	      hist2->Fill(ptlep1);}//data bincontent
      for(int kk=0;kk<5;kk++){
	      if(name.Contains("EWK") && Reco && Gen ){ 
		      if(ptlep1>ptBins[kk] && ptlep1<ptBins[kk+1]){
			      hist5[kk]->Fill(genlep1pt,scalef*lumi);
		      }
	      }//5 genbins content in different reco pt bins 
	      /*if(name.Contains("EWK")==0 && !(name.Contains("Muon")==1 || name.Contains("Data")==1) && Reco){
		      if(ptlep1>ptBins[kk] && ptlep1<ptBins[kk+1]){
			      if(name.Contains("plj")) {hist1[kk]->Fill(ptlep1,scalef);}
			      else hist1[kk]->Fill(ptlep1,scalef*lumi);
		      }
	      }
	      if( (name.Contains("Muon")==1 || name.Contains("Data")==1) && Reco){
		      if(ptlep1>ptBins[kk] && ptlep1<ptBins[kk+1]){
			      hist1[kk]->Fill(ptlep1);
		      }
	      }*/
      } 
   }
 cout<<"end the loop"<<endl;
 cout<<" after reco selection "<<i1<<endl;
 cout<<" after gen selection "<<i2<<endl;
 cout<<" reco && gen selection "<<i3<<endl;
 cout<<" reco && !gen selection "<<i4<<endl;
 file->cd();
 if(name.Contains("EWK")==0)
   hist2->Write();
 if(name.Contains("EWK") ){
	 hist2->Write();
	 hist3->Write();
	 for(int i=0;i<5;i++){
		 hist5[i]->Write();
	 }
 }
file->Close();
}
