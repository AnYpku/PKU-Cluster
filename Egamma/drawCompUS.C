TFile* file = new TFile("test.root","recreate");
void draw(TFile*f1){
	TString filename = f1->GetName();
	TH1D*het[2];
	TH1D*heta[2];
	TH1D*hnrgy[2];
	TH1D*hphi[2];
	TH1D*hdeta[2];
	TH1D*hdphi[2];
	TH1D*hsieie[2];
	TH1D*hmhits[2];
	TH1D*h3[8];
//	TEfficiency* h3[8];
	TLegend *l1[8];
	TLine* line[8];
	TCanvas* c1[8];

	Double_t etbins[7]={0,20,30,50,100,200,400};
	Double_t etabins[7]={0,0.5,1.0,1.4442,1.566,2.0,2.5};
	vector<TH1D*> hele;vector<TH1D*> hegHLT;
	het[0] = (TH1D*)f1->Get("hclusEt_ele");
	   hele.push_back(het[0]);
	het[1] = (TH1D*)f1->Get("het_eghltUS");
	   hegHLT.push_back(het[1]);
	heta[0] = (TH1D*)f1->Get("hdetEta_ele");
	   hele.push_back(heta[0]);
	heta[1] = (TH1D*)f1->Get("heta_eghltUS");
           hegHLT.push_back(heta[1]);
	hnrgy[0] = (TH1D*)f1->Get("hclusNrgy_ele");hele.push_back(hnrgy[0]);
	hnrgy[1] = (TH1D*)f1->Get("hnrgy_eghltUS");hegHLT.push_back(hnrgy[1]);
	hphi[0] = (TH1D*)f1->Get("hdetPhi_ele");hele.push_back(hphi[0]);
	hphi[1] = (TH1D*)f1->Get("hphi_eghltUS");hegHLT.push_back(hphi[1]);
	hdeta[0] = (TH1D*)f1->Get("hdEtaInSeed_ele");hele.push_back(hdeta[0]);
	hdeta[1] = (TH1D*)f1->Get("hetain_eghltUS");hegHLT.push_back(hdeta[1]);
	hdphi[0] = (TH1D*)f1->Get("hPhiIn_ele");hele.push_back(hdphi[0]);
	hdphi[1] = (TH1D*)f1->Get("hphiin_eghltUS");hegHLT.push_back(hdphi[1]);
	hsieie[0] = (TH1D*)f1->Get("hsieie_ele");hele.push_back(hsieie[0]);
	hsieie[1] = (TH1D*)f1->Get("hsieie_eghltUS");hegHLT.push_back(hsieie[1]);
	hmhits[0] = (TH1D*)f1->Get("hMHits_ele");hele.push_back(hmhits[0]);
	hmhits[1] = (TH1D*)f1->Get("hMHits_eghltUS");hegHLT.push_back(hmhits[1]);
	char hname[51];
	vector<double> vec_ymax;
	vector<double> vec_xmax;
	for(int i=0;i<8;i++){
		TString name = hegHLT[i]->GetTitle();
		cout<<name<<endl;
		file->cd();
		hele[i]->Write();
		hegHLT[i]->Write();

		vec_ymax.push_back(hegHLT[i]->GetMaximum());
		vec_ymax.push_back(hele[i]->GetMaximum());
		sort(vec_ymax.begin(), vec_ymax.end(), greater<double>());
		double ymax=vec_ymax[0];  
                hegHLT[i]->GetYaxis()->SetRangeUser(0,ymax*1.4);
                vec_ymax.clear();
	}
	for(int i=0;i<8;i++){
		TString name = hegHLT[i]->GetTitle();
		cout<<name<<endl;
		c1[i] = new TCanvas(hname,name,900,600);
		l1[i] = new TLegend(0.6,0.7,0.9,0.9);
		TPad *top_pad=new TPad("top_pad", "top_pad",0,0.2, 1.0, 1.0);
		top_pad->Draw();
		top_pad->cd();
		top_pad->SetGrid();
		top_pad->SetBottomMargin(0.005);
		hele[i]->SetTitle(name+"\t"+filename);
		hele[i]->SetLineColor(kAzure+6);
		hele[i]->SetLineWidth(3);
		hegHLT[i]->SetLineColor(kAzure-2);
		hegHLT[i]->SetLineWidth(4);
		hegHLT[i]->SetLineStyle(5);
		double norm2 =  hegHLT[i]->Integral();
		hegHLT[i]->Scale(1/norm2);
		double norm1 =  hele[i]->Integral();
		hele[i]->Scale(1/norm1);
//		hegHLT[i]->Draw("hist");
//		hele[i]->Draw("hist same");
		hegHLT[i]->DrawNormalized("hist");
		hele[i]->DrawNormalized("hist same");

		l1[i]->AddEntry(hele[i],"reco ele");
		l1[i]->AddEntry(hegHLT[i],"HLT ele");
		l1[i]->SetBorderSize(1);
		l1[i]->SetFillColor(0);

		c1[i]->cd();
		c1[i]->SetGrid();

		sprintf(hname,"h_%d",i);
		h3[i]= (TH1D *)hegHLT[i]->Clone();
		h3[i]->Divide(hele[i]);
		double xmin,xmax;
		xmin=hele[i]->GetXaxis()->GetXmin();
		xmax=hele[i]->GetXaxis()->GetXmax();
		line[i] = new TLine(xmin,1.,xmax,1);
		TPad *bottom_pad=new TPad("bottom_pad", "bottom_pad", 0, 0., 1.0, 0.2);
		bottom_pad->Draw();
		bottom_pad->cd();
		bottom_pad->SetTopMargin(0);
                h3[i]->Sumw2();
		h3[i]->GetYaxis()->SetRangeUser(0.5,1.5);
		h3[i]->Draw("EP");
		h3[i]->SetMarkerStyle(20);
		h3[i]->SetLineStyle(1);
		h3[i]->SetLineWidth(1);
		h3[i]->SetMarkerSize(1.0);
		h3[i]->SetTitle("");
		h3[i]->GetXaxis()->SetTitle( name );
		h3[i]->GetYaxis()->SetTitle("K factor ");
		h3[i]->GetXaxis()->CenterTitle();
		h3[i]->GetYaxis()->CenterTitle();
		h3[i]->SetLineColor(kBlack);
		h3[i]->GetXaxis()->SetTitleOffset(0.9);
		h3[i]->GetYaxis()->SetTitleOffset(0.22);
		h3[i]->GetXaxis()->SetTitleSize(0.15);
		h3[i]->GetYaxis()->SetTitleSize(0.15);
		h3[i]->GetXaxis()->SetLabelSize(0.12);
		h3[i]->GetYaxis()->SetLabelSize(0.1);
		double h3min,h3max;
                h3min=h3[i]->GetMinimum();
                h3max=h3[i]->GetMaximum();
//		h3[i]->SetMaximum(h3max+0.5);
//		h3[i]->SetMinimum(h3min-0.5);
		line[i]->SetLineColor(kRed);
		line[i]->SetLineWidth(2);
		line[i]->Draw();
		l1[i]->AddEntry(h3[i],"HLTUS/reco");
		top_pad->cd();
		l1[i]->Draw();
		c1[i]->Draw();
		c1[i]->Print("./"+filename+name+".pdf");
	}
	file->Close();
}
void Style(){
//       gStyle->SetPadBorderMode(0);
       gStyle->SetOptStat(0);
       gStyle->SetPadGridX(1);
       gStyle->SetPadGridY(1);
       gStyle->SetPadTickX(1);
       gStyle->SetPadTickY(1);
//       gStyle->SetPadTopMargin(0.07);
//       gStyle->SetPadBottomMargin(0.3);
       gStyle->SetPadRightMargin(0.05);
       gStyle->SetPadLeftMargin(0.14);
       gStyle->SetPadTickX(1);
       gStyle->SetPadTickY(1);
//       gStyle->SetAxisColor(1, "XYZ");
//       gStyle->SetStripDecimals(kTRUE);
//       gStyle->SetTickLength(0.03, "XYZ");
//       gStyle->SetNdivisions(510, "XYZ");
}
int drawCompUS(){
	Style();
	TFile* f1 = new TFile("./USrootfiles/120_200_barrel.root");
	TFile* f2 = new TFile("./USrootfiles/120_200_endcap.root");
	TFile* f3 = new TFile("./USrootfiles/50_120_barrel.root");
	TFile* f4 = new TFile("./USrootfiles/50_120_endcap.root");
	draw(f1);
	draw(f2);
	draw(f3);
	draw(f4);
	return 1;

}
