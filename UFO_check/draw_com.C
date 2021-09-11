void draw(TH1D*h1,TH1D*h2,TString name,TString var,int index);
TH1D* run(TString name,TString cut,TString var,vector<double> bins,int index){
	double pweight[256],scalef;
        TString dir="/home/pku/anying/";
        TFile*f1=new TFile(dir+name+"_DelphesOut.root");
	TTree*tree=(TTree*)f1->Get("demo");
	TTreeFormula *tformula1=new TTreeFormula("formula1", "("+cut+")", tree);
        TString histname="hist_"+var;
	TH1D*h1;
        TString i=Form("%i",index);
	h1=new TH1D(histname,"",bins.size()-1,&bins[0]);
	tree->Draw(var+">>"+histname,"("+cut+")*scalef*pweight["+i+"]","goff");
        int nbins=h1->GetNbinsX();
        h1->SetBinContent(nbins,h1->GetBinContent(nbins)+h1->GetBinContent(nbins+1));
        return h1;
}
int draw_com(){
        TString LEPele="(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && massVlep >70. && massVlep<110)";
        TString LEPmu = "(drll>0.3 && lep==13 && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && massVlep >70. && massVlep<110)";
        TString photon = "(photonet>120 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
        TString dr = "(drjj>0.5 && drl1a>0.7 && drl2a>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l1>0.5&&drj2l1>0.5&&drj1l2>0.5&&drj2l2>0.5)";
        TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5 )";
        TString jet="( jet1pt>30 && fabs(jet1eta)<4.7 && jet2pt>30 && fabs(jet2eta)<4.7 )";
	TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
        vector<TString> opt={"fM0","fM1","fM2","fM3","fM4","fM5","fM6","fM7","fT0","fT1","fT2","fT5","fT6","fT7","fT8","fT9"};
        vector<TString> var={"ptlep1","photonet","jet1pt","Mjj"};
	vector<vector<double>> bins;
	vector<double> ptlep1Bins={20,80,120,200,400};
	vector<double> photonetBins={120,150,200,400};
	vector<double> jet1ptBins={30,150,250,350,800};
	vector<double> MjjBins={500,800,1200,1500,2000};
	bins.push_back(ptlep1Bins);
	bins.push_back(photonetBins);
	bins.push_back(jet1ptBins);
	bins.push_back(MjjBins);
	for(int j=0;j<var.size();j++){
		for(int index=1;index<=16;index++){
			int iii = 1+(index-1)*16;
			TString name=opt[index-1];
			TH1D*h1[17];TH1D*h2[17];//16 aQGC weights + 1 SM weights = 17 weights
		for(int i=0;i<16;i++){
				int k=iii+i;//
                                if(k==256) continue;
				h1[i]=run("LLAJJ_aQGC",Reco,var[j],bins[j],k);
				h2[i]=run("LLAJJ_aQGC_UFO",Reco,var[j],bins[j],k);
				draw(h1[i],h2[i],name,var[j],k);
			}
		}
		TH1D*h2;TH1D*h3;
                h2=run("LLAJJ_aQGC",Reco,var[j],bins[j],0);
                h3=run("LLAJJ_aQGC_UFO",Reco,var[j],bins[j],0);
		draw(h2,h3,"",var[j],0);
	}

	return 0;
}
void draw(TH1D*h1,TH1D*h2,TString name,TString var,int i){
	gStyle->SetOptStat(0);
	TCanvas*c1=new TCanvas("c1","",900,600);
	TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.3, 0.99, 0.99);
	TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.3);
	fPads1->SetBottomMargin(0);
	fPads2->SetTopMargin(0);
	fPads2->SetBottomMargin(0.5);
	fPads1->Draw();
	fPads2->Draw();
	fPads1->SetLogy();
	fPads1->cd();
	fPads1->SetGridx();
	fPads2->SetGridy();
	h1->SetLineColor(2);
	h2->SetLineColor(3);
	h1->SetTitle("");
	h1->GetXaxis()->SetTitle(var);
	h1->GetYaxis()->SetRangeUser(h1->GetMinimum()*0.1,2*h1->GetMaximum());
	h1->Draw("HIST E");
	h2->Draw("HIST E SAME");
	TLegend* leg = new TLegend(0.4, 0.1, 0.8, 0.3);
	if(i==0)leg->AddEntry(h1,"Official with the SM weight");
	else if(i==1)leg->AddEntry(h1,"Official for "+name+Form(" of the %ist weight",i));
	else if(i==2)leg->AddEntry(h1,"Official for "+name+Form(" of the %ind weight",i));
	else if(i==3)leg->AddEntry(h1,"Official for "+name+Form(" of the %ird weight",i));
	else  leg->AddEntry(h1,"Official for "+name+Form(" of the %ith weight",i));
	leg->AddEntry(h2,"check");
	leg->Draw();
	fPads1->Update();
	fPads2->cd();
	TH1D*nominal=(TH1D*)h2->Clone("nominal");
	TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
	TH1D*h=(TH1D*)h1->Clone();
	for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
	h->Divide(nominal);
	nominal->Divide(nomNoErr);
	nominal->SetFillStyle(3002);
	nominal->SetFillColor(kRed-7);
	nominal->SetLineColor(0);
	nominal->GetYaxis()->SetRangeUser(0.1,2);
	nominal->SetTitle(";"+var+" [GeV];Ratio");
	nominal->GetYaxis()->SetTitleOffset(0.23);
	nominal->GetYaxis()->SetTitleSize(0.2);
	nominal->GetYaxis()->SetNdivisions(404);
	nominal->GetYaxis()->SetLabelSize(0.15);
	nominal->GetXaxis()->SetLabelSize(0.2);
	nominal->GetXaxis()->SetLabelOffset(0.032);
	nominal->GetXaxis()->SetTitleSize(0.18);
	nominal->GetXaxis()->SetTitleOffset(1.32);
	nominal->Draw("E2");
	h->SetMarkerStyle(20);
	h->SetMarkerColor(1);
	h->SetLineColor(1);
	h->SetMarkerSize(1.2);
	h->Draw("EP same");
	fPads2->Update();
	TString index=Form("%i",i);
	c1->Print("com_figs/hist_"+var+"_"+name+"_"+index+".pdf");
}
