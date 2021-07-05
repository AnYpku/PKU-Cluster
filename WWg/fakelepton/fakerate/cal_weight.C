void cal(TString year,TString channel){
	TFile*f1=new TFile("hist_num"+channel+".root");
	cout<<f1->GetName()<<endl;
        TString file;
	if(channel=="mu") file="DMuon";
	else file="DEle";
        TH2D*h_mu_T=(TH2D*)f1->Get("hist_"+channel+"_"+file+year+"_tight");
        TH2D*h_mu_L=(TH2D*)f1->Get("hist_"+channel+"_"+file+year+"_loose_not_tight");
	cout<<"hist_"+channel+"_"+file+year+"_loose_not_tight"<<endl;
	cout<<h_mu_L->GetSum()<<" "<<h_mu_T->GetSum()<<endl;
        TH2D*h_wjets_T=(TH2D*)f1->Get("hist_"+channel+"_WJets"+year+"_tight");
        TH2D*h_wjets_L=(TH2D*)f1->Get("hist_"+channel+"_WJets"+year+"_loose_not_tight");
        TH2D*h_dy_T=(TH2D*)f1->Get("hist_"+channel+"_DY"+year+"_tight");
        TH2D*h_dy_L=(TH2D*)f1->Get("hist_"+channel+"_DY"+year+"_loose_not_tight");

        h_mu_L->Add(h_wjets_L,-1);
        h_mu_L->Add(h_dy_L,-1);

        h_mu_T->Add(h_wjets_T,-1);
        h_mu_T->Add(h_dy_T,-1);

        TH2D*h1=(TH2D*)h_mu_T->Clone("TtoL");
        TH2D*h2=(TH2D*)h_mu_L->Clone();
        h2->Add(h1,1);
        h1->Divide(h2); 
        gStyle->SetOptStat(0);
        TCanvas*c1=new TCanvas(channel,"",800,600);
        h1->Draw("colztext");
        c1->Print(channel+"_fakerate"+year+".pdf");
        TFile*fout=new TFile("test_"+channel+year+".root","recreate");
        h_mu_T->Write("T");
        h_mu_L->Write("L");
        h1->Write();
	fout->Close();
}
int cal_weight(){

cal("18","ele");
cal("18","mu");
return 0;
}
