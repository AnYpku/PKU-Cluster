void run(TString tag,TString name,vector<double> ptbins,vector<double> eff){
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
	vector<Double_t> eff_b_jet_medium; 
	vector<Double_t> eff_c_jet_medium;
	vector<Double_t> eff_l_jet_medium;
        vector<TString> tag={"17","18"};
	vector<double> pt_bin = {20, 30, 50, 70, 100, 140, 200, 300, 600, 1000, 1500};
	for(int i=0;i<tag.size()-1;i++){
		if(tag[i].Contains("17")){
			eff_b_jet_medium= {0.550703, 0.655257, 0.708018, 0.733123, 0.743445, 0.73445, 0.685051, 0.559069, 0.337587, 0.156085};
			eff_c_jet_medium= {0.100341, 0.111135, 0.115312, 0.123547, 0.132176, 0.137718, 0.12915, 0.102925, 0.0532662, 0.022082};
			eff_l_jet_medium= {0.0073096, 0.00782829, 0.00801778, 0.00894073, 0.0105117, 0.0122973, 0.0130844, 0.0131463, 0.00887536, 0.00256148};

		}
		else if(tag[i].Contains("18")){
			eff_b_jet_medium = {0.565127, 0.663282, 0.714194, 0.737916, 0.750325, 0.745599, 0.701239, 0.590619, 0.390365, 0.216667};
			eff_c_jet_medium = {0.120439, 0.128175, 0.130494, 0.13781, 0.14765, 0.154195, 0.146221, 0.120963, 0.0666874, 0.0311927};
			eff_l_jet_medium = {0.00904002, 0.00806116, 0.00810405, 0.00924306, 0.0113922, 0.0137251, 0.0159489, 0.0189461, 0.0130992, 0.004265};
		}
		run(tag[i],"b_jet",pt_bin,eff_b_jet_medium);
		run(tag[i],"c_jet",pt_bin,eff_c_jet_medium);
		run(tag[i],"l_jet",pt_bin,eff_l_jet_medium);
	}
	return 1;
}
