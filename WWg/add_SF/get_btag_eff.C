void run(TString tag,vector<double> ptbins,double eff[ptbins.size()-1]){
   TH1D*h1=new TH1D("btag_eff"+tag,"",ptbins.size()-1,&ptbins[0]);
   for(int i=0;i<h1->GetNbinsX();i++){
	   h1->SetBinContent(i+1,eff[i]);
   }
   TFile*fout=new TFile("eff_btag"+tag+".root","recreate");
   fout->cd();
   h1->Write();
   fout->Close();
}
int get_btag_eff(){
	Double_t eff_b_jet_medium[10] = {0.565127, 0.663282, 0.714194, 0.737916, 0.750325, 0.745599, 0.701239, 0.590619, 0.390365, 0.216667};
	vector<double> pt_bin = {20, 30, 50, 70, 100, 140, 200, 300, 600, 1000, 1500};
        run("18",pt_bin,eff_b_jet_medium);
	return 1;
}
