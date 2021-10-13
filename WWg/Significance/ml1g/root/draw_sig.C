void run(TString var,TString jets,TString year){
     TFile*f1=new TFile("hist_WWG_emu_"+var+"_"+jets+"_"+year+".root");
     TH2D*hsig=(TH2D*)f1->Get("sig");
     TCanvas*c1=new TCanvas("c1","",800,600);
     hsig->Draw("colztext");
     c1->Print("Sig_"+var+"_"+jets+"_"+year+".pdf");
}
int draw_sig(){
	vector<TString> vars={"ml1g","ml2g","mllg"};
	vector<TString> jets={"0jets","1jets"};
        for(int i=0;i<vars.size();i++){
		for(int j=0;j<jets.size();j++){
			run(vars[i],jets[j],"17");
			run(vars[i],jets[j],"18");
		}
	}
	return 1;
}
