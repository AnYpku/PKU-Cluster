#include "CMS_lumi.C"
void tree(TTree*t1);
void select(TTree*t1);

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
TH2D*h2d=new TH2D("h2d","",150,0.006,0.02,150,0.01,15);
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
void select(TTree*t1){
	bool Zjets[6],Leading_photon[6],medium_cut[6],loose_cut[6];
	Int_t nentries = t1->GetEntriesFast();
	cout<<"nentries = "<<nentries<<endl;
	vector<double> vector_pt;
	vector<double>::iterator biggest_pt;
	int position=0,size;
	for(Int_t i=0;i<nentries;i++){
		t1->GetEntry(i);
		for(Int_t j=0;j<6;j++){
			Zjets[j] = ptlep1 > 20. && ptlep2 > 20.&& abs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110;
			Leading_photon[j]= photon_isprompt[j]!=1 && photon_drla[j]>0.7 && photon_drla2[j]>0.7;// && photon_pt[j]<35.&&photon_pt[j]>25;
			medium_cut[j]= photon_pevnew[j]==1 &&
				photon_hoe[j]<0.02197  &&
				photon_nhiso[j]<1.715 + 0.0163*photon_pt[j] + 0.000014*photon_pt[j]*photon_pt[j] &&
				photon_phoiso[j]<3.863 + 0.0034*photon_pt[j]&&
				fabs(photon_eta[j])<1.4442 &&
				photon_pt[j]>25&&photon_pt[j]<400;//muon barrel 
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
//		if(scalef<0)scalef=scalef*(-1);
		h2d->Fill(photon_sieie[position],photon_chiso[position],scalef);
		vector_pt.clear();
	}  
}
int draw_2d(){

	TFile *f = new TFile("./outZJets_barrel.root");
	TTree *t =(TTree*)f->Get("demo");
	tree(t);
	select(t);
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	TPad* fPad1 = new TPad("pad1", "pad1", 0.00, 0.00, 0.99, 0.99);
	fPad1->Draw();
	fPad1->cd();
	fPad1->SetTicky();
	fPad1->SetLeftMargin(0.15);
	fPad1->SetTopMargin(0.1);
	fPad1->SetBottomMargin(0.18);
	fPad1->SetLogy();
	gStyle->SetOptStat(0);
	int kViolet=880;
	Int_t vec_cols[15];
	for(int i=0;i<15;i++){
		vec_cols[i]=29+i; 
	}
        Int_t Numbers=15;
        gStyle->SetPalette(Numbers,vec_cols);
        h2d->SetTitle(";#sigma_{i#etai#eta};I_{ch}");
        h2d->GetYaxis()->SetTitleOffset(1.25);
        h2d->GetYaxis()->SetTitleSize(0.06);
        h2d->GetYaxis()->SetNdivisions(303);
        h2d->GetXaxis()->SetLabelSize(0.04);
        h2d->GetYaxis()->SetLabelSize(0.04);
        h2d->GetXaxis()->SetLabelOffset(0.032);
        h2d->GetXaxis()->SetTitleSize(0.06);
        h2d->GetXaxis()->SetTitleOffset(1.32);
        h2d->Draw("colz");   
	double corr= h2d->GetCorrelationFactor();
        TString rho = Form("#rho = %.2f",corr);
	TLatex *textvalue = new TLatex(0.6, 0.3, rho);
	textvalue->SetNDC();
	textvalue->SetTextSize(0.06);
	textvalue->SetLineWidth(1);
	textvalue->Draw();
	CMS_lumi(fPad1, 4, 0, "59.7");
        c1->Print("2D_chiso_sieie.pdf");
	return 0;
}
