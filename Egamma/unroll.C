#include "TH1.h"
#include "TFile.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include "TLegend.h"
using namespace std;

TH1D* unroll(TH2D* th2_in,char *hname, TString title)
{
    TH2D* th2 = th2_in;
    Int_t xbin = th2->GetXaxis()->GetNbins();
    Int_t ybin = th2->GetYaxis()->GetNbins();

    TH1D* h1_out= new TH1D(hname, title ,xbin*ybin,th2->GetXaxis()->GetXmin(),th2->GetXaxis()->GetXmax());
    for(Int_t iy=1; iy<=ybin; iy++){
	    for(Int_t ix=1; ix<=xbin; ix++){
		    h1_out->SetBinContent(ix+(iy-1)*xbin,th2->GetBinContent(ix,1));
		    h1_out->SetBinError(ix+(iy-1)*xbin,th2->GetBinError(ix,1));
//		    cout<<"ix = "<<ix<<", iy = "<<iy<<"; bin = "<<ix+(iy-1)*xbin<<", BinContent"<<th2->GetBinContent(ix,1)<<endl;
	    }
    }
    return h1_out;
}

