{
#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>

	TFile *fout = new TFile("out1.root", "RECREATE");

	vector<TString> files;
	files.push_back("optimal_outDMuon");
	files.push_back("optimal_outphotonlikejet_mu_mediumlikephoton");
	files.push_back("optimal_outZA-EWK");
	files.push_back("optimal_bkg");
	files.push_back("optimal_ZA");


	const int nfiles = files.size();
	cout<<"file size "<<nfiles<<endl;




	for(int i=0; i<nfiles; i++)
	{
		TString filename = "../../../../for_aQGC/muon_barrelandendcap/"+files.at(i)+".root";
		TString hname = "ZG_"+files.at(i);  //Base
		if(hname=="ZG_optimal_outZA-EWK") {
			hname="ZG_optimal_outZA_EWK"; }

		TFile * input1 = new TFile (filename);
		TTree *Outtree1 = (TTree*)input1->Get("outtree");

		int nentries1 = (int)Outtree1->GetEntries();
		cout<<"Sample = "<<filename<<" "<<"nentries1 = "<<nentries1<<endl;

		Double_t        ZGmass;
		Double_t        Mjj;
		Double_t        photonet;
		Double_t        weight_all;
		Double_t        weight_all_up;
		Double_t        weight_all_down;
		Double_t	detajj;


		Outtree1->SetBranchAddress("ZGmass",&ZGmass);
		Outtree1->SetBranchAddress("Mjj",&Mjj);
		Outtree1->SetBranchAddress("photonet",&photonet);
		Outtree1->SetBranchAddress("detajj",&detajj);
		Outtree1->SetBranchAddress("weight_all", &weight_all); 
		Outtree1->SetBranchAddress("weight_all_up", &weight_all_up); 
		Outtree1->SetBranchAddress("weight_all_down", &weight_all_down); 

		//double ZGbin[6] = {150,250,350,400,600,700};
		double ZGbin[6] = {150,400,600,800,1000,1500};
		TH1D *PTA1   = new TH1D(hname+"_nominal"," ",5,ZGbin);
		TH1D *PTA1_up   = new TH1D(hname+"_up"," ",5,ZGbin);
		TH1D *PTA1_down   = new TH1D(hname+"_down"," ",5,ZGbin);
		//        double ZGbin[16] = {0.,30.,60.,90.,120.,150.,180.,210.,240.,270.,300.,330.,360.,390.,420.,450.};
		//        TH1D *PTA1   = new TH1D(hname," ",15,ZGbin);
		PTA1->Sumw2(); 
		PTA1_up->Sumw2(); 
		PTA1_down->Sumw2(); 

		for(int j=0; j<nentries1; j++)
		{
			Outtree1->GetEntry(j);

			bool ipass=photonet>80;

			double lumi=35.862; 

			if(hname=="ZG_optimal_outDMuon"||hname=="ZG_optimal_outphotonlikejet_mu_mediumlikephoton") {
				lumi=1.0;
			}

			if(ipass>0) {
				PTA1->Fill(ZGmass,lumi*weight_all);
				PTA1_up->Fill(ZGmass,lumi*weight_all_up);
				PTA1_down->Fill(ZGmass,lumi*weight_all_down);
			}   

		} 


		PTA1->SetBinContent(5, PTA1->GetBinContent(5)+PTA1->GetBinContent(6));
		PTA1_up->SetBinContent(5, PTA1_up->GetBinContent(5)+PTA1_up->GetBinContent(6));
		PTA1_down->SetBinContent(5, PTA1_down->GetBinContent(5)+PTA1_down->GetBinContent(6));
		double xe=sqrt(PTA1->GetBinError(5)*PTA1->GetBinError(5)+PTA1->GetBinError(6)*PTA1->GetBinError(6));
		double xe_up=sqrt(PTA1_up->GetBinError(5)*PTA1_up->GetBinError(5)+PTA1_up->GetBinError(6)*PTA1_up->GetBinError(6));
		double xe_down=sqrt(PTA1_down->GetBinError(5)*PTA1_down->GetBinError(5)+PTA1_down->GetBinError(6)*PTA1_down->GetBinError(6));
		PTA1->SetBinError(5, xe);   
		PTA1_up->SetBinError(5, xe_up);   
		PTA1_down->SetBinError(5, xe_down);   

		/*    
		      if(hname=="ZG_optimal_outDMuon")  {
		      PTA1->SetName("data_obs");
		      }
		      if(hname=="optimal_outZA-EWK")  {
		      PTA1->SetName("signal_SM");
		      }
		      if(hname=="ZG_bkg")  {
		      PTA1->SetName("background");
		      TH1D *PTA2   = (TH1D*) PTA1->Clone("");
		      PTA2->SetName("background_mu_backshapeUp");
		      TH1D *PTA3   = (TH1D*) PTA1->Clone("");
		      PTA3->SetName("background_mu_backshapeDown");
		      for(int k=1; k<8; k++) {
		      cout<<k<<" "<<PTA1->GetBinContent(k)<<" "<<PTA1->GetBinError(k)<<endl;
		      PTA2->SetBinContent(k, PTA1->GetBinContent(k)+PTA1->GetBinError(k));
		      double xd=PTA1->GetBinContent(k)-PTA1->GetBinError(k);
		      PTA3->SetBinContent(k, max(xd,0.0));
		      }
		      }
		 */

		fout->cd(); 
		PTA1->Write();   
		PTA1_up->Write();   
		PTA1_down->Write();   

		/*         if(hname=="ZG_bkg")  {
			   PTA2->Write();   
			   PTA3->Write();   
			   }
		 */
	}
	fout->Write(); 
	fout->Close();
}
