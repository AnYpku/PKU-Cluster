TH1D*run(TFile*fout,TString name){
        TH1D*h1=(TH1D*)fout->Get(name+"_emu");
	return h1;
}
int draw_alone(){
	TFile*fout=new TFile("histos_emua_HGC18.root");
	vector<TString> vars={"mll","photonet","photoneta","photonphi","lep1pt","lep1eta","lep1phi","lep2pt","lep2eta","lep2phi","mllg","ml1g","ml2g","ptll","phiVlep","yVlep","puppimet","puppimetphi","npvs","n_bjets","mT","mT2","PuppiMET_T1_pt","PuppiMET_T1_phi","njets","njets15","njets20","njets30","njets40","njets50","drl1a","drl2a","drll","ptlep1","ptlep2","dphill"};
        for(int i=0;i<vars.size();i++){
            TCanvas*c1=new TCanvas("c1","",800,600);
            TH1D*h1=run(fout,vars[i]);
            h1->Scale(59.7);
            h1->Draw("HIST");
            h1->GetXaxis()->SetTitleOffset(0.7);
            h1->GetYaxis()->SetTitleOffset(0.8);
            c1->Print("hist_"+vars[i]+".pdf");
	}
	fout->Close();
	return 0;
}
