void cal(TString year,TString channel){
	TFile*f1=new TFile("hist_num"+channel+year+".root");
	cout<<f1->GetName()<<endl;
        TString file;
	if(channel=="mu") file="Muon";
	else{
		if(year=="18")	file="EGamma";
		else if(year=="17") file="Ele";
		else if(year.Contains("16")) file="Ele";
	}
	bool pre=0;
	if(year.Contains("pre")){ year="16"; pre=1;}
        TH1D*h_mu_T=(TH1D*)f1->Get("hist_"+channel+"_"+file+year+"_tight");
        TH1D*h_mu_L=(TH1D*)f1->Get("hist_"+channel+"_"+file+year+"_loose_not_tight");
	cout<<"hist_"+channel+"_"+file+year+"_loose_not_tight"<<endl;
	cout<<h_mu_L->GetSum()<<" "<<h_mu_T->GetSum()<<endl;
        TH1D*h_wjets_T=(TH1D*)f1->Get("hist_"+channel+"_WJets"+year+"_tight");
        TH1D*h_wjets_L=(TH1D*)f1->Get("hist_"+channel+"_WJets"+year+"_loose_not_tight");
        TH1D*h_dy_T=(TH1D*)f1->Get("hist_"+channel+"_DYJets"+year+"_tight");
        TH1D*h_dy_L=(TH1D*)f1->Get("hist_"+channel+"_DYJets"+year+"_loose_not_tight");

        h_mu_L->Add(h_wjets_L,-1);
        h_mu_L->Add(h_dy_L,-1);

        h_mu_T->Add(h_wjets_T,-1);
        h_mu_T->Add(h_dy_T,-1);

	h_mu_L->SetBinContent(h_mu_L->GetNbinsX(),h_mu_L->GetBinContent(h_mu_L->GetNbinsX())+h_mu_L->GetBinContent(h_mu_L->GetNbinsX()+1));
	h_mu_T->SetBinContent(h_mu_T->GetNbinsX(),h_mu_T->GetBinContent(h_mu_T->GetNbinsX())+h_mu_T->GetBinContent(h_mu_T->GetNbinsX()+1));

        TH1D*h1=(TH1D*)h_mu_T->Clone("TtoL");
        TH1D*h2=(TH1D*)h_mu_L->Clone();
//        h2->Add(h1,1);
        h1->Divide(h2); 
        gStyle->SetOptStat(0);
        TCanvas*c1=new TCanvas(channel,"",800,600);
        h1->Draw("PE colztext");
        h1->SetMarkerSize(2);
	if(pre) year="pre"+year;
        h1->SetTitle(channel+" fake rate "+year+";p_{T};fake weight");
        c1->Print(channel+"_fakerate"+year+".pdf");
        TFile*fout=new TFile(channel+year+"_fakerate.root","recreate");
        h_mu_T->Write("T");
        h_mu_L->Write("L");
        h1->Write();
	fout->Close();
}
int cal_weight(){

//cal("16","ele");
//cal("16","mu");
//cal("16pre","mu");
//cal("16pre","ele");
//cal("16","mu");
//cal("17","ele");
//cal("17","mu");
cal("18","ele");
//cal("18","mu");
return 0;
}
