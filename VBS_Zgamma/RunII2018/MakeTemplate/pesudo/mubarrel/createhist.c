#include "CMS_lumi.C"
TString b ="shapeTest1";
TString str="Z && lep && Leading photon && MediumID ";
TH1D *h2[6];
TH1D *h[6];
Int_t bin=10;
Double_t xlow= 0.0;
Double_t xhigh= 0.02;
Double_t chiso = 1.141;
void tree(TTree*t1);
void histo();
void select(TTree*t1);
void draw(TCanvas*c1);
Double_t s[6];
//the needed variables in the root file
Double_t ptlep1,ptlep2,etalep1,etalep2,massVlep;
Double_t scalef;
Int_t nlooseeles,nloosemus;
Double_t photon_drla[6],photon_pt[6],photon_drla2[6],photon_sieie[6],photon_chiso[6];
double photon_hoe[6];
double photon_nhiso[6];
double photon_phoiso[6];
double photon_eta[6];
int photon_isprompt[6];
bool photon_pevnew[6];
void tree(TTree*t1) {
	t1->SetBranchAddress("photon_isprompt",photon_isprompt); t1->SetBranchAddress("photon_hoe",photon_hoe);
	t1->SetBranchAddress("photon_pevnew",photon_pevnew); 
	t1->SetBranchAddress("photon_nhiso",photon_nhiso);
	t1->SetBranchAddress("photon_phoiso",photon_phoiso);
	t1->SetBranchAddress("photon_pt",photon_pt);
	t1->SetBranchAddress("photon_eta",photon_eta);
	t1->SetBranchAddress("scalef",&scalef);
	t1->SetBranchAddress("nloosemus",&nloosemus);
	t1->SetBranchAddress("nlooseeles",&nlooseeles);
	t1->SetBranchAddress("ptlep1",&ptlep1);
	t1->SetBranchAddress("ptlep2",&ptlep2);
	t1->SetBranchAddress("etalep1",&etalep1);
	t1->SetBranchAddress("etalep2",&etalep2);
	t1->SetBranchAddress("massVlep",&massVlep);
	t1->SetBranchAddress("photon_isprompt",photon_isprompt);
	t1->SetBranchAddress("photon_drla",photon_drla);
	t1->SetBranchAddress("photon_drla2",photon_drla2);
	t1->SetBranchAddress("photon_sieie",photon_sieie);
	t1->SetBranchAddress("photon_chiso",photon_chiso);
	t1->SetBranchAddress("photon_pt",photon_pt);
}

void histo(){
	for(Int_t i=1;i<6;i++){
		h2[i]=new TH1D(Form("h2%d",i),"",bin,xlow,xhigh);
	}
}
void draw(TCanvas*c1){
	gStyle->SetOptStat(0);
	gStyle->SetAxisColor(1, "XYZ");
	gStyle->SetStripDecimals(kTRUE);
	gStyle->SetTickLength(0.03, "XYZ");

	c1=new TCanvas("c1","",500,400);   
	//c1->SetGrid();
	TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.3, 0.99, 0.99);
	TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.3);
	fPads1->SetBottomMargin(0.028);
	fPads2->SetTopMargin(0.012);
	fPads2->SetBottomMargin(0.45);
	fPads1->Draw();
	fPads2->Draw();
	fPads1->cd();

	h2[1]->SetLineColor(1);
	h2[1]->GetYaxis()->SetTitle("A.U.");
	h2[1]->GetYaxis()->SetTitleOffset(0.6);
	h2[1]->GetYaxis()->SetTitleSize(0.07);
	h2[1]->GetYaxis()->SetLabelSize(0.06);
	h2[1]->GetXaxis()->SetLabelSize(0.0);
	h2[1]->GetYaxis()->SetNdivisions(505);
	h2[1]->SetLineStyle(1);
	h2[1]->SetLineWidth(1);
	h2[2]->SetLineColor(kRed);
	h2[3]->SetLineColor(kGreen+1);
	h2[4]->SetLineColor(kBlue);
	h2[5]->SetLineColor(kOrange);
        h2[1]->SetMarkerStyle(20);
        h2[1]->SetMarkerSize(1.2);
	h2[1]->GetXaxis()->SetRangeUser(0.006,0.02);
	h2[1]->DrawNormalized("PE");
	for(Int_t i=2;i<6;i++){
		h2[i]->SetLineWidth(3);
		h2[i]->SetLineStyle(2);
		h2[i]->DrawNormalized("HIST,SAME e");
	}
	TLegend *l1 = new TLegend(0.55,0.55,0.89,0.89);
	l1->AddEntry(h2[1],"I_{ch} < 1.141"); 
	l1->AddEntry(h2[2],"4 < I_{ch} < 10");
	l1->AddEntry(h2[3],"5 < I_{ch} < 10");
	l1->AddEntry(h2[4],"6 < I_{ch} < 10");
	l1->AddEntry(h2[5],"5 < I_{ch} < 12");
        l1->SetTextSize(0.06);
        l1->SetLineColor(0);  
	l1->Draw(); 

	CMS_lumi(fPads1, 4, 0, "59.7");
	fPads1->Update();
	fPads2->cd();
	fPads2->SetGridy();

	h[1]->SetTitle(";#sigma_{i#etai#eta};Ratio");
	h[1]->GetYaxis()->SetTitleOffset(0.32);
	h[1]->GetYaxis()->SetTitleSize(0.16);
	h[1]->GetYaxis()->SetNdivisions(303);
	h[1]->GetXaxis()->SetLabelSize(0.13);
	h[1]->GetYaxis()->SetLabelSize(0.13);
	h[1]->GetXaxis()->SetLabelOffset(0.032);
	h[1]->GetXaxis()->SetTitleSize(0.2);
	h[1]->GetXaxis()->SetTitleOffset(1.05);
	h[1]->GetYaxis()->SetRangeUser(0.4,1.9);
	h[1]->GetXaxis()->SetRangeUser(0.006,0.02);
        h[1]->SetLineColor(kRed-7);
        h[1]->SetFillColor(kRed-7);
	h[1]->Draw("PE2");
	for(int i=0;i<h[1]->GetNbinsX();i++){
		cout<<h[1]->GetBinContent(i+1)<<" "<<h[1]->GetBinError(i+1)<<endl;
	}
	h[2]->SetLineColor(kRed);
	h[3]->SetLineColor(kGreen+1);
	h[4]->SetLineColor(kBlue);
	h[5]->SetLineColor(kOrange);
	for(Int_t i=2;i<6;i++){
		h[i]->SetMaximum(1.5);
		h[i]->SetMinimum(0.5);
		h[i]->SetLineWidth(2);
		h[i]->Draw("P SAME");
	}
	TLine *line = new TLine(0.006,1,0.02,1);
	line->SetLineColor(2);
	line->SetLineWidth(2);
	line->SetLineStyle(2);

	fPads2->Update();
	c1->Print("./"+b+"_sieie.eps");
	c1->Print("./"+b+"_sieie.pdf");
}
void select(TTree*t1){
	bool Zjets[6],Leading_photon[6],medium_cut[6],loose_cut[6];
	Int_t nentries = t1->GetEntriesFast();
	cout<<"nentries = "<<nentries<<endl;
	// nentries=100;
	vector<double> vector_pt;
	vector<double>::iterator biggest_pt;
	int position=0,size;
	for(Int_t i=0;i<nentries;i++){
		t1->GetEntry(i);
		for(Int_t j=0;j<6;j++){
			Zjets[j] = ptlep1 > 20. && ptlep2 > 20.&& abs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110;
			Leading_photon[j]=photon_isprompt[j] != 1  &&  photon_drla[j]>0.7 && photon_drla2[j]>0.7;// && photon_pt[j]<35.&&photon_pt[j]>25;
			medium_cut[j]= photon_pevnew[j]==1 &&
				photon_hoe[j]<0.02197  &&
				photon_nhiso[j]<1.715 + 0.0163*photon_pt[j] + 0.000014*photon_pt[j]*photon_pt[j] &&
				photon_phoiso[j]<3.863 + 0.0034*photon_pt[j]&&
				fabs(photon_eta[j])<1.4442 &&
				photon_pt[j]>25;//muon barrel 
			if(Zjets[j]&&Leading_photon[j]&&medium_cut[j]){
				vector_pt.push_back(photon_pt[j]);
			}
			else {vector_pt.push_back(0);}
		}//fill the vector_pt
		size=vector_pt.size();
		biggest_pt = max_element(begin(vector_pt),end(vector_pt));
		if(*biggest_pt==0){
			vector_pt.clear();
			continue;}
		position = distance( begin(vector_pt), biggest_pt);
		if(photon_chiso[position]<chiso) 
		{
			h2[1]->Fill(photon_sieie[position],scalef);
		} 
		if(photon_chiso[position]<10 &&photon_chiso[position]>4)   
		{
			h2[2]->Fill(photon_sieie[position],scalef);
		}  
		if(photon_chiso[position]>5 && photon_chiso[position]<10)   
		{
			h2[3]->Fill(photon_sieie[position],scalef);
		}
		if(photon_chiso[position]>6&&photon_chiso[position]<10 )   
		{
			h2[4]->Fill(photon_sieie[position],scalef);
		}
		if(photon_chiso[position]>5&&photon_chiso[position]<12)   
		{
			h2[5]->Fill(photon_sieie[position],scalef);
		}
		vector_pt.clear();
	}  
	//  s[1]=1/h2[1]->Integral();
	for(Int_t i=1;i<6;i++){
		s[i]=1/h2[i]->Integral();
		cout<<"s"<<i<<" = "<<s[i]<<endl;
		h2[i]->Scale(s[i]);
		if(i>1){
			h[i] = (TH1D *)h2[i]->Clone();
			h[i]->Divide(h2[1]);}
		else if(i==1){
			TH1D*h_clone=(TH1D*)h2[1]->Clone();
			for(int i=0;i<h_clone->GetNbinsX();i++){
				h_clone->SetBinError(i+1,0);
			}
			h[i] = (TH1D *)h2[i]->Clone();
			h[i]->Divide(h_clone);
		}
	} 
}
int createhist(){

	// TFile *f = new TFile("/home/pku/anying/cms/file_in_cms/2017RunIIrootfiles/ptotal.root");
	TFile *f = new TFile("./outZJets_barrel.root");
	TTree *t =(TTree*)f->Get("demo");
	tree(t);
	histo();
	select(t);
	TCanvas *c1= new TCanvas("c1","test graph",500,400);
	draw(c1);
	return 0;
}
//TCanvas *c2=new TCanvas("c2","two dimension distribution",900,600);
// c2->SetLogz();
// hh11->SetTitle("ZJetscut&&Leading photon&&LooseID&&photon_chiso[0]<1.295; photon_sieie; photon_chiso");
// //h3->Draw("COLTEXTZ");
// Double_t cc1=hh21->GetCorrelationFactor();
// cout<< "cc1 = "<<cc1<<endl;
// TPaveText *pt1 = new TPaveText(0.60, 0.30, 0.90, 0.40, "BRNDC");
// pt1->SetFillColor(19);
// pt1->SetBorderSize(1);
// pt1->SetTextAlign(12);
// pt1->SetTextSize(0.04);
// char cor1[20];
// sprintf(cor1,"%f",cc1);
// TString par1=cor1;
// TString Par1 = "#rho = " + par1;
// TText *text1 = pt1->AddText(Par1);
// hh21->Draw("COLZ");
// pt1->Draw();
// c2->Print("./"+b+"_hh21.eps");
//TCanvas *c3=new TCanvas("c3","two dimension distribution",900,600);
// c3->SetLogz();
// hh22->SetTitle("Zjets&&Leading photon&&LooseID&&0.1<photon_chiso[0]<10; photon_sieie; photon_chiso");
// //h33->Draw("COLTEXTZ");
// Double_t cc2=hh22->GetCorrelationFactor();
// cout<< "cc2 = "<<cc2<<endl;
// TPaveText *pt2 = new TPaveText(0.60, 0.10, 0.90, 0.20, "BRNDC");
// pt2->SetFillColor(19);
// pt2->SetBorderSize(1);
// pt2->SetTextAlign(12);
// pt2->SetTextSize(0.04);
// char cor2[20];
// sprintf(cor2,"%f",cc2);
// TString par2=cor2;
// TString Par2 = "#rho = " + par2;
// TText *text2 = pt2->AddText(Par2);
// hh22->Draw("COLZ");
// pt2->Draw();
// c3->Print("./"+b+"_hh22.eps");
//TCanvas *c4=new TCanvas("c4","two dimension distribution",900,600);
// c4->SetLogz();
// hh23->SetTitle("Zjets&&Leading photon&&LooseID&&2<photon_chiso[0]<4; photon_sieie; photon_chiso");
// //h33->Draw("COLTEXTZ");
// Double_t cc3=hh23->GetCorrelationFactor();
// cout<< "cc3 = "<<cc3<<endl;
// TPaveText *pt3 = new TPaveText(0.60, 0.10, 0.90, 0.20, "BRNDC");
// pt3->SetFillColor(19);
// pt3->SetBorderSize(1);
// pt3->SetTextAlign(12);
// pt3->SetTextSize(0.04);
// char cor3[20];
// sprintf(cor3,"%f",cc3);
// TString par3=cor3;
// TString Par3 = "#rho = " + par3;
// TText *text3 = pt3->AddText(Par3);
// hh23->Draw("COLZ");
// pt3->Draw();
// c4->Print("./"+b+"_hh23.eps");
