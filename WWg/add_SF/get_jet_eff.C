void run(TString tag,TString name,vector<double> ptbins,double eff[ptbins.size()-1]){
   TH1D*h1=new TH1D(name+"_eff"+tag,"",ptbins.size()-1,&ptbins[0]);
   for(int i=0;i<h1->GetNbinsX();i++){
	   h1->SetBinContent(i+1,eff[i]);
   }
   TFile*fout=new TFile("eff_"+name+tag+".root","recreate");
   fout->cd();
   h1->Write();
   fout->Close();
}
int get_jet_eff(){
	Double_t eff_b_jet_medium[10] = {0.565127, 0.663282, 0.714194, 0.737916, 0.750325, 0.745599, 0.701239, 0.590619, 0.390365, 0.216667};
	Double_t eff_c_jet_medium[10] = {0.120439, 0.128175, 0.130494, 0.13781, 0.14765, 0.154195, 0.146221, 0.120963, 0.0666874, 0.0311927};
	Double_t eff_l_jet_medium[10] = {0.00904002, 0.00806116, 0.00810405, 0.00924306, 0.0113922, 0.0137251, 0.0159489, 0.0189461, 0.0130992, 0.004265};
	vector<double> pt_bin = {20, 30, 50, 70, 100, 140, 200, 300, 600, 1000, 1500};
	run("18","b_jet",pt_bin,eff_b_jet_medium);
	run("18","c_jet",pt_bin,eff_c_jet_medium);
	run("18","l_jet",pt_bin,eff_l_jet_medium);
	return 1;
}
