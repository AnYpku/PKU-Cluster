void muon_HLT_SF(){
double SF[4][4]={{0.9572,0.9513,0.9708,0.9572},{0.9515,0.9665,0.9755,0.9613},{0.9708,0.9755,0.9875,0.9848},{0.9571,0.9610,0.9822,0.9655}};
double SF_err[4][4]={{0.0036,0.0104,0.0044,0.0095},{0.0065,0.0132,0.0073,0.0136},{0.0046,0.0076,0.0053,0.0238},{0.0127,0.0183,0.0114,0.0178}};
double etabin[5]={0,0.9,1.2,2.1,2.4};
TH2D*h2=new TH2D("h2","muon HLT SF",4, etabin,4,etabin);
for(int i=0;i<5;i++){
	for(int j=0;j<5;j++){
		h2->SetBinContent(j+1,i+1,SF[i][j]);
		h2->SetBinError(j+1,i+1,SF_err[i][j]);
	}
}
TFile*file=new TFile("muon_HLT_SF.root","recreate");
file->cd();
h2->Write();
file->Close();


}
