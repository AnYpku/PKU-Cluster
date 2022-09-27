#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include "TLegend.h"
using namespace std;

TH1D* unroll(TH2D* th2_in,Double_t* xbin, Double_t* ybin,  Int_t xbins_in, Int_t ybins_in,TString hname)
//TH1D* unroll(TH2D* th2_in,Double_t* xbin, Double_t* ybin,  Int_t xbins_in, Int_t ybins_in,char* hname)
{
	TH2D* th2 = th2_in;
	Int_t nbinsx =xbins_in;
	Int_t nbinsy =ybins_in;
	Int_t nbins = nbinsx*nbinsy;
	TH1D* h1= new TH1D("h1", "", nbins, 0, nbins);
	TH1D* h1_out= new TH1D(hname, "", nbins-1, 0, nbins-1);
	//    TH1D* h1_out= new TH1D(hname, "", 4, 0, 4);
	for(Int_t iy=1; iy<=nbinsy; iy++){
		for(Int_t ix=1; ix<=nbinsx; ix++){
			Double_t x_temp = 0.5*(xbin[ix-1]+xbin[ix]);
			Double_t y_temp = 0.5*(ybin[iy-1]+ybin[iy]);
			h1->SetBinContent(ix+(iy-1)*nbinsx,th2->GetBinContent(th2->FindBin(x_temp, y_temp)));//void SetBinContent(Int_t bin, Double_t content),the FindBin function can return Global bin number corresponding to x,y
			h1->SetBinError(ix+(iy-1)*nbinsx,th2->GetBinError(th2->FindBin(x_temp, y_temp)));
			//		    cout<<"ix = "<<ix<<", iy = "<<iy<<"; bin = "<<ix+(iy-1)*nbinsx<<", BinContent"<<41.52*th2->GetBinContent(th2->FindBin(x_temp, y_temp))<<endl;
		}
	}
	for(Int_t i=0;i<6;i++){
		h1_out->SetBinContent(i+1,h1->GetBinContent(i+1));
		h1_out->SetBinError(i+1,h1->GetBinError(i+1));
	} 
	h1_out->SetBinContent(7,h1->GetBinContent(7) + h1->GetBinContent(8));
	h1_out->SetBinContent(8,h1->GetBinContent(9));
	delete h1;
	return h1_out;
}

