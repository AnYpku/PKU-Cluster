#include <iostream>
#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLine.h"

using namespace std;
 
TH1D* correction(TTree*tt, std::string filename){
	char buffer1[256];
        sprintf(buffer1, "%s",filename.c_str());
        TTree* t=tt;
        TH1D*h=new TH1D(buffer1,buffer1,200,0.004,0.034);
//        TH1D*h=new TH1D(buffer1,buffer1,200,0.01,0.064);
	TFile* file;TTree*Tree;
/*	if(filename.find("mc") != std::string::npos){
		file = new TFile("./DY.root","RECREATE");
                Tree=tt->CloneTree(0);
	}else{
		file = new TFile("./Data.root","RECREATE");
		Tree=tt->CloneTree(0);
	}*/

	float el_1overEminus1overP;
	float el_5x5_sieie;
	float el_abseta;
	float el_chIso;
	float el_dEtaIn;
	float el_dEtaSeed;
	float el_dPhiIn;	
	float el_hoe;
	float el_neuIso;
	float el_phi;
	float el_phoIso;
	float el_pt;
	float el_sieie;
	float el_dxy;
	float el_dz;
	float el_mHits;
	float tag_Ele_abseta;
	float tag_Ele_pt;
	float pair_mass;
	float totWeight;


	t->SetBranchStatus("*",0);
	t->SetBranchStatus("el_1overEminus1overP",1);
	t->SetBranchStatus("el_5x5_sieie",1);
	t->SetBranchStatus("el_abseta",1);
	t->SetBranchStatus("el_chIso",1);
	t->SetBranchStatus("el_dEtaIn",1);
	t->SetBranchStatus("el_dPhiIn",1);
	t->SetBranchStatus("el_hoe",1);
	t->SetBranchStatus("el_pt",1);
	t->SetBranchStatus("el_sieie",1);
	t->SetBranchStatus("el_dxy",1);
	t->SetBranchStatus("el_dz",1);
	t->SetBranchStatus("el_mHits",1);
	t->SetBranchStatus("tag_Ele_abseta",1);
	t->SetBranchStatus("tag_Ele_pt",1);
	t->SetBranchStatus("pair_mass",1);
	if(filename.find("mc") != std::string::npos) t->SetBranchStatus("totWeight",1);

	t->SetBranchAddress("el_1overEminus1overP",&el_1overEminus1overP);
	t->SetBranchAddress("el_5x5_sieie",&el_5x5_sieie);
        t->SetBranchAddress("el_abseta",&el_abseta);
        t->SetBranchAddress("el_chIso",&el_chIso);
        t->SetBranchAddress("el_dEtaIn",&el_dEtaIn);
        t->SetBranchAddress("el_dPhiIn",&el_dPhiIn);
        t->SetBranchAddress("el_hoe",&el_hoe);
        t->SetBranchAddress("el_pt",&el_pt);
        t->SetBranchAddress("el_sieie",&el_sieie);
        t->SetBranchAddress("el_dxy",&el_dxy);
        t->SetBranchAddress("el_dz",&el_dz);
        t->SetBranchAddress("el_mHits",&el_mHits);
        t->SetBranchAddress("tag_Ele_abseta",&tag_Ele_abseta);
        t->SetBranchAddress("tag_Ele_pt",&tag_Ele_pt);
        t->SetBranchAddress("pair_mass",&pair_mass);
	if(filename.find("mc") != std::string::npos) t->SetBranchAddress("totWeight", &totWeight);

	Long64_t nentries=t->GetEntries();
	for(Long64_t i=0;i<nentries;i++){
		if(filename.find("data") != std::string::npos) totWeight=1.;
		if(i%100000==0)std::cout<<"processing "<<i<<" event"<<std::endl;
		t->GetEntry(i);
		if(pair_mass<70||pair_mass>110||tag_Ele_abseta>2.1||tag_Ele_pt<30) continue;
//		Tree->Fill(); 
//                if( !(fabs(el_dEtaIn)<0.00311 && fabs(el_dPhiIn)<0.103 && el_hoe<0.253 && el_pt>25 && el_chIso<20 &&(el_chIso/el_pt)<0.3 && fabs(el_1overEminus1overP)<0.134 &&el_mHits<=1 &&el_abseta<1.479) ) continue;
		if(fabs(el_dEtaIn)<0.00311 && fabs(el_dPhiIn)<0.103 && el_hoe<0.253 && el_pt>25 && el_chIso<20 &&(el_chIso/el_pt)<0.3 && fabs(el_1overEminus1overP)<0.134 &&el_mHits<=1 &&el_abseta<1.479) h->Fill(el_5x5_sieie, totWeight);
//		if(fabs(el_dEtaIn)<0.00609 && fabs(el_dPhiIn)<0.045  && el_hoe<0.878 && el_pt>25 && el_chIso<20 &&(el_chIso/el_pt)<0.3 && fabs(el_1overEminus1overP)<0.13 &&el_mHits<=1 &&el_abseta>1.479) h->Fill(el_5x5_sieie, totWeight);
	}
//        file->cd();
//        Tree->Write();
//        file->Close();
	return h;
}

int main(){
	TFile* fdata = TFile::Open("/eos/cms/store/group/phys_egamma/soffi/TnP/ntuples_04162018-Legacy2016/Legacy16_V1/data/TnPTree_07Aug17_Run2016BCDEFGH.root");
	TDirectory* ddata = (TDirectory*)fdata->Get("tnpEleIDs");
	TTree* tdata = (TTree*)ddata->Get("fitter_tree");
	TFile* fmc = TFile::Open("/eos/cms/store/group/phys_egamma/soffi/TnP/ntuples_04162018-Legacy2016/Legacy16_V1/mc/TnPTree_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_all.root");
	TDirectory* dmc = (TDirectory*)fmc->Get("tnpEleIDs");
	TTree* tmc = (TTree*)dmc->Get("fitter_tree");

	TCanvas* c=new TCanvas("","",800,600);	
	TH1D* hdata= correction(tdata, "data");
	hdata->SetStats(0);
	TH1D* hmc= correction(tmc, "mc");
	hmc->SetStats(0);
	TH1D*hclone=(TH1D*)hmc->Clone();

	double xmc[200], ymc[200];
        double xda[200], yda[200];

        for(int i=0;i<200;i++){
                xmc[i]=(i+1)*1.0/200;
                xda[i]=(i+1)*1.0/200;
        }
	hdata->GetQuantiles(200, yda, xda);
        hmc->GetQuantiles(200, ymc, xmc);
	TGraph*g1=new TGraph(200, ymc, yda);
	g1->SetNameTitle("barrel","barrel");
//	g1->SetNameTitle("endcap","endcap");
	TFile*fout=new TFile("transformation_barrel.root","RECREATE");
//	TFile*fout=new TFile("transformation_endcap.root","RECREATE");
	fout->cd();
	g1->Write();
	fout->Close();

	TLegend *leg = new TLegend(0.75,0.76,0.9,0.9);
	TLine* lineAtZero = new TLine(hclone->GetXaxis()->GetXmin(), 1, hclone->GetXaxis()->GetXmax(), 1);
	lineAtZero->SetLineColor(2);

        TPad*fPads1 = new TPad("pad1", "", 0.00, 0.20, 0.99, 0.99);
        TPad*fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.20);
        fPads1->SetFillColor(0);
        fPads1->SetLineColor(0);
        fPads2->SetFillColor(0);
        fPads2->SetLineColor(0);
        fPads1->SetBottomMargin(0);
        fPads2->SetTopMargin(0);
        fPads2->SetBottomMargin(0.3);

        fPads1->Draw();
        fPads2->Draw();

        fPads1->SetLogy();
        fPads1->cd();
        hdata->SetLineColor(kBlack);
        hdata->Draw();
        hmc->Scale(hdata->Integral()/hmc->Integral());
        hclone->Scale(hdata->Integral()/hclone->Integral());
        hclone->Divide(hdata);
        hmc->SetLineColor(kRed);
        hmc->Draw("SAME");
	leg->AddEntry(hdata, "hdata");
	leg->AddEntry(hmc, "hmc");
	leg->Draw();

	fPads2->cd();
	hclone->GetYaxis()->SetLabelSize(0.1);
	hclone->GetXaxis()->SetLabelSize(0.1);
	hclone->SetMaximum(2);
	hclone->SetMinimum(0);
        hclone->Draw();
	lineAtZero->Draw("same");
//	c->cd();
//	c->SetLogy();
//	hdata->SetLineColor(kBlack);
//	hdata->Draw();
//	hmc->SetLineColor(kRed);
//	hmc->Scale(hdata->Integral()/hmc->Integral());
//	hmc->Draw("SAME");
//	c->SaveAs("aa_barrel.png");
	c->SaveAs("aa_barrel.pdf");
//	c->SaveAs("aa_endcap.png");
	return 1;
}
