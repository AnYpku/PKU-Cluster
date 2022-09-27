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
   TH1D* h1 = new TH1D("h1","gen",5, ptBins);
   TH2D* h2 = new TH2D("h2", "gen selection", 5, ptBins,5,ptBins);
   TH2D* h3 = new TH2D("h3", "gen && reco selection",5, ptBins,5,ptBins);
   TH2D* hrm = new TH2D("rm","",5,ptBins,5,ptBins);
   TFile* file = new TFile("hist_"+name+".root","recreate");
   TH1D* hun[5];
   TH1D* hist[5]; 
   for(int i=0;i<5;i++)
        {
		hun[i]=new TH1D(Form("h_%i",i+1),Form("%0.f<leading p_{T}^{reco}<%0.f;leding p_{T}^{gen};yields",ptBins[i],ptBins[i+1]),5,ptBins);
		hist[i]= new TH1D(name+Form("_hist_%i",i+1),name+Form("\t%0.f<leading p_{T}^{reco}<%0.f;leding p_{T}^{gen};yields",ptBins[i],ptBins[i+1]),1,ptBins[i],ptBins[i+1]);
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
      if(jentry%20000==0)      cout<<jentry<<"; OK3"<<endl;
      LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110;
      LEPele = lep==11 && HLT_Ele1>0 && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
      photon = photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );
      jet = jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7;
      dr = drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5&&drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5;
      SignalRegion = Mjj>500 && deltaetajj>2.5 && Mva>100;  /*zepp<2.4 && delta_phi>1.9;*/
      Reco = (LEPmu || LEPele) && photon && jet && dr && SignalRegion;
      
      GenLEPmu = genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110;
      GenLEPele = genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5 && nlooseeles<3 && nloosemus ==0  && massVlep >70. && massVlep<110;
      GenPhoton = genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) );
      GenJet = genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7;
      GenDr = gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5;
      GenSignalRegion = genMjj >500 && gendetajj>2.5 /*&& genZGmass>100*/;
      Gen = ( GenLEPmu || GenLEPele ) && GenPhoton && GenJet && GenDr && GenSignalRegion;
      if(genlep1pt>400) genlep1pt=399;if(ptlep1>400) ptlep1=399;
      if(Gen) {h2->Fill(genlep1pt,ptlep1,scalef*lumi);h1->Fill(genlep1pt,scalef*lumi);}
      if(Gen && Reco) {h3->Fill(genlep1pt,ptlep1,scalef*lumi);}
   }
   cout<<i1<<endl;
//   hEff->Divide(hgen);
      for(int ix=1;ix<=hrm->GetXaxis()->GetNbins();ix++){
              double numerator = 0;
	      for(int iy=1;iy<=hrm->GetYaxis()->GetNbins();iy++){
                              numerator = numerator +h2->GetBinContent(ix,iy);
	      }
              cout<<numerator<<endl;
	      for(int iy=1;iy<=hrm->GetYaxis()->GetNbins();iy++){
			      double a = h3->GetBinContent(ix,iy)/h1->GetBinContent(ix);
			      int b1 = 1000*a; int b2 = 100*a;
			      if( (b1-10*b2)>=5) b2 = b2+1;
			      else b2=b2;
			      double c = b2/100.;
			      hrm->SetBinContent(ix,iy,c);
	      }

      }
    h2->SetMarkerSize(1.5);
    h3->SetMarkerSize(1.5);
    hrm->SetMarkerSize(1.5);
    hrm->SetTitle("response matrix; reco leading p_{T}; gen leading p_{T}");
    h3->SetTitle("GEN && RECO selection; reco leading p_{T}; gen leading p_{T}");
    h2->SetTitle("GEN selection; reco leading p_{T};gen leading p_{T}");
    TCanvas* c1 = new TCanvas("c1");
    h2->Draw("colztext");
    TCanvas* c2 = new TCanvas("c2");
    h3->Draw("colztext");
    TCanvas* c3 = new TCanvas("c3");
    hrm->Draw("colztext");
    c1->SaveAs("h2.eps");
    c2->SaveAs("h3.eps");
    c3->SaveAs("hrm.eps");
   
/*   TH2D* hResponse = (TH2D*) K.HresponseNoOverflow();
   TH1D* hProjY = hResponse->ProjectionY();
   for (Int_t i = 1; i <= 5; i++) {
	   for (Int_t j = 5; j <= 5; j++) {
		   // Normalize each row to sum up to the efficiency
		   hResponse->SetBinContent(i,j,hEff->GetBinContent(j)*hResponse->GetBinContent(i,j)/hProjY->GetBinContent(j));
	   }
   }
   hResponse->SetTitle("Response matrix;Detector level;Particle level");
   hResponse->SetStats(kFALSE);
   hResponse->Draw("colz");*/
  file->cd();
  hrm->Write(); 
  h1->Write();
  h2->Write();
  h3->Write();
}
