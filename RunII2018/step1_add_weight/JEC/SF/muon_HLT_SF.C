void muon_HLT_SF(){
double SF[4][4]={{0.9693,0.9555,0.9683,0.9743},{0.9556,0.9484,0.9681,0.9955},{0.9690,0.9680,0.9958,0.9938},{0.9748,0.9935,0.9942,1.0218}};
double SF_err[4][4]={{0.0082,0.0073,0.0049,0.0128},{0.0072,0.0122,0.0087,0.0173},{0.0051,0.0091,0.0053,0.0108},{0.0155,0.0255,0.0128,0.0236}};
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
