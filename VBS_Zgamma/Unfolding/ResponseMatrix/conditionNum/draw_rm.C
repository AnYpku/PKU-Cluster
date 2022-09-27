#include "CMS_lumi.C"
TH2D*run(TString var,TString tag,int num){
	TFile*file=new TFile("/home/pku/anying/cms/PKU-Cluster/Unfolding/common/root/hist_ZA-EWK_"+var+tag+".root");
	TH1D*h2=(TH1D*)file->Get("histGen_"+var);
        const int binx=h2->GetNbinsX();
        TH1D*h1[num];
	for(int i=0;i<binx;i++){
		h1[i]=(TH1D*)file->Get(var+Form("_%i",i));
	}
        
        TH2D*hout=new TH2D("hout","",num,0,num,num,0,num);
        for(int i=0;i<binx;i++){
		for(int j=0;j<binx;j++){
                    double element=h1[i]->GetBinContent(j+1)/h2->GetBinContent(j+1);
//                    double element=h1[i]->GetBinContent(j+1);
                    hout->SetBinContent(i+1,j+1,element);
		}
	}
return hout;
}
int draw_rm(){
	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
        vector<TString> title={"p_{T}^{l_{1}}","p_{T}^{#gamma}","p_{T}^{j_{1}}","M_{jj}"};
	vector<int> num={4,4,4,7};
	vector<TString> tag={"16","17","18"};
        vector<vector<double>> bins;
        vector<double> ptlepBins={20,80,120,200,400};
        vector<double> photonEtBins={20,80,120,200,400};
        vector<double> jetptBins={30,150,250,350,800};
        bins.push_back(ptlepBins);
        bins.push_back(photonEtBins);
        bins.push_back(jetptBins);
       const char *name[7]={"0.5~0.8","0.8~1.2","1.2~2","0.5~0.8","0.8~1.2","1.2~2","0.5~2"};
	for(int i=0;i<genvars.size();i++){
		for(int j=0;j<tag.size();j++){
			TH2D*h1=run(genvars[i],tag[j],num[i]);
			TFile*file=new TFile("rm_"+genvars[i]+tag[j]+".root","recreate");
			file->cd();
			h1->Write();
			file->Close();
			TCanvas *c1  = new TCanvas("c1","c1",0,0,600,400);
			TPad*    fPads1 = new TPad("pad1", "", 0.00, 0., 0.99, 0.99);
			fPads1->Draw();
			fPads1->cd();
			fPads1->SetBottomMargin(0.15);
			Int_t palette[5];
			palette[0] = 19;
			palette[1] = 20;
			palette[2] = 23;
			palette[3] = 30;
			palette[4] = 32;
			gStyle->SetPalette(5,palette);
			gStyle->SetOptStat(0);
			for(int j=0;j<h1->GetNbinsX();j++){
				if(genvars[i].Contains("Mjj")==0){
					fPads1->SetLeftMargin(0.2);
					h1->GetYaxis()->SetBinLabel(j+1,Form("[%0.f,%0.f]",bins[i][j],bins[i][j+1]));
					h1->GetXaxis()->SetBinLabel(j+1,Form("[%0.f,%0.f]",bins[i][j],bins[i][j+1]));
					h1->GetYaxis()->SetTitle("Gen "+title[i]+" [GeV]");
					h1->GetXaxis()->SetTitle("Reco "+title[i]+"[GeV]");
					h1->GetYaxis()->SetTitleOffset(1.25);
					h1->GetXaxis()->SetTitleOffset(0.9);
				}
					else{
						fPads1->SetLeftMargin(0.15);
						h1->GetXaxis()->SetBinLabel(j+1,name[j]);
						h1->GetYaxis()->SetBinLabel(j+1,name[j]);
						h1->GetYaxis()->SetTitle("Gen "+title[i]+" [TeV]");
						h1->GetXaxis()->SetTitle("Reco "+title[i]+"[TeV]");
						h1->GetYaxis()->SetTitleOffset(1);
						h1->GetXaxis()->SetTitleOffset(1);
					}
					h1->GetYaxis()->SetTitleSize(0.07);
					h1->GetXaxis()->SetTitleSize(0.07);
					h1->GetYaxis()->SetTitleFont(22);
					h1->GetXaxis()->SetTitleFont(22);
					h1->GetYaxis()->SetLabelFont(12);
					h1->GetXaxis()->SetLabelFont(12);
					h1->GetYaxis()->SetLabelOffset(0.001);
					h1->GetYaxis()->SetLabelSize(0.07);
					h1->GetXaxis()->SetLabelSize(0.07);
			}
			h1->Draw("colz");
			TLine* vline1 = new TLine(h1->GetXaxis()->GetBinLowEdge(4),0,h1->GetXaxis()->GetBinLowEdge(4),7);
			TLine* vline2 = new TLine(h1->GetXaxis()->GetBinLowEdge(7),0,h1->GetXaxis()->GetBinLowEdge(7),7);
			vline1->SetLineStyle(2);
			vline2->SetLineStyle(2);
			vline1->SetLineWidth(2);
			vline2->SetLineWidth(2);
			string lumi;
			if(tag[j].Contains("16")) lumi="35.86";
			if(tag[j].Contains("17")) lumi="41.52";
			if(tag[j].Contains("18")) lumi="59.7";
			CMS_lumi(fPads1, 4, 0, lumi);
			if(genvars[i].Contains("Mjj")){
				TLatex latex1;
				latex1.SetTextSize(0.065);
				latex1.SetLineWidth(2);
				latex1.DrawLatex(0.08,2.5,"2.5<#Delta#eta_{jj}<4.5");
				latex1.DrawLatex(3.8,2.5,"4.5<#Delta#eta_{jj}<6");
				latex1.DrawLatex(6,2.5,"#Delta#eta_{jj}>6");
				vline1->Draw();
				vline2->Draw();
			}
//			c1->Print("rm_"+genvars[i]+tag[j]+".pdf");
		}
	}
	return 0;
}
