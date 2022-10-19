void run(TString year,TString style,vector<double> ptbins){
        gStyle->SetOptStat(0);
	TFile*file=new TFile("hist"+year+".root");
        TH1D*hdata=(TH1D*)file->Get("data_"+style);
        TH1D*hmc=(TH1D*)file->Get("mc_"+style);
        hdata->Add(hmc,-1);
	hdata->Scale(1/hdata->Integral());
	TF1*f=new TF1("f","pol2");
        hdata->Fit("f");
        cout<<"total bins for tight photon "<<f->GetParameter(0)<<" "<<f->GetParameter(1)<<" "<<f->GetParameter(2)<<endl;
	TCanvas *c1= new TCanvas("c1","fitFunc",500,500) ;
	c1->SetGridx(1) ;
	c1->SetGridy(1) ;
	hdata->SetLineWidth(2) ;
	hdata->SetLineColor(kBlue) ;
	hdata->Draw("PE") ;
	TLegend *leg = new TLegend(0.4,0.58,0.89,0.88) ;
	leg->SetFillColor(10) ;
	leg->AddEntry(hdata,"Fitted line: r =  p2 x^{2} + p1 x + p0","L") ;
	leg->AddEntry(hdata,Form("p0 = %0.3f ",f->GetParameter(0)),"") ;
	leg->AddEntry(hdata,Form("p1 = %0.3f ",f->GetParameter(1)),"") ;
	leg->AddEntry(hdata,Form("p2 = %0.3f ",f->GetParameter(2)),"") ;
//	leg->AddEntry(hdata,Form("p3 = %0.3f ",f->GetParameter(3)),"") ;
	leg->Draw();
        c1->Print("fit_data_"+style+".pdf");
	for(int i=0;i<ptbins.size()-1;i++){
		TH1D*h1=(TH1D*)file->Get(Form("data_"+style+"_%0.f_%0.f",ptbins[i],ptbins[i+1]));
		TH1D*h2=(TH1D*)file->Get(Form("mc_"+style+"_%0.f_%0.f",ptbins[i],ptbins[i+1]));
		h1->Add(h2,-1);
		h1->Scale(1/h1->Integral());
		TF1*f1=new TF1("f1","pol2");
		h1->Fit("f1");
		cout<<style<<" photon in bins of "<<ptbins[i]<<"-"<<ptbins[i+1]<<" "<<f1->GetParameter(0)<<" "<<f1->GetParameter(1)<<" "<<f1->GetParameter(2)<<endl;
		TCanvas *c2= new TCanvas("c2","fitFunc",500,500) ;
		c2->SetGridx(1) ;
		c2->SetGridy(1) ;
		h1->SetLineWidth(2) ;
		h1->SetLineColor(kBlue) ;
		h1->Draw("PE") ;
		TLegend *leg1 = new TLegend(0.4,0.58,0.89,0.88) ;
		leg1->SetFillColor(10) ;
		leg1->AddEntry(h1,"Fitted line: r =  p2 x^{2} + p1 x + p0","L") ;
		leg1->AddEntry(h1,Form("p0 = %0.3f ",f1->GetParameter(0)),"") ;
		leg1->AddEntry(h1,Form("p1 = %0.3f ",f1->GetParameter(1)),"") ;
		leg1->AddEntry(h1,Form("p2 = %0.3f ",f1->GetParameter(2)),"") ;
//		leg1->AddEntry(h1,Form("p3 = %0.3f ",f1->GetParameter(3)),"") ;
		leg1->Draw();
		c2->Print(Form("data_"+style+"_%0.f_%0.f.pdf",ptbins[i],ptbins[i+1]));
	}


}
int draw(){
	vector<double> ptbins={25,40,60};
	run("18","tight",ptbins);
	run("18","fake",ptbins);



	return 0;
}
