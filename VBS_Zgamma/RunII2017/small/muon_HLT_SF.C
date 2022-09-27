void muon_HLT_SF(){
double SF[4][4]={{0.9497,0.9506,0.9644,0.9713},{0.9503,0.9558,0.9688,0.9845},{0.9645,0.9699,0.9884,0.9681},{0.9711,0.9827,0.9670,0.9793}};
double SF_err[4][4]={{0.0035,0.0064,0.0043,0.0086},{0.0062,0.0122,0.0082,0.0166},{0.0046,0.0068,0.0053,0.0095},{0.0116,0.0196,0.0082,0.0178}};
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
