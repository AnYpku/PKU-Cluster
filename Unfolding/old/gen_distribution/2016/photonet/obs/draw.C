void draw(){
	TFile *f1=new TFile("hist_ZA-EWK.root");
	TH1D*hist4_new=(TH1D*)f1->Get("hist4");
        TH1D*hist4_up=(TH1D*)hist4_new->Clone();
        TH1D*hist4_down=(TH1D*)hist4_new->Clone();
        TH1D*h1=(TH1D*)hist4_new->Clone();
	const int n = hist4_new->GetNbinsX();
	double x[5],ymin[5],ymax[5],y[5],r[5]={2.776,2.061,1.511,1.031,0.38},yy[5];
	double err[5]={1.833,0.2178,0.2228,0.2384,0.4371};
	for(int i=0;i<hist4_new->GetNbinsX();i++)
	{
		x[i]=hist4_new->GetBinCenter(i+1);
		ymin[i]=hist4_new->GetBinContent(i+1)*(r[i]-sqrt(err[i]));
		ymax[i]=hist4_up->GetBinContent(i+1)*(r[i]+sqrt(err[i]));
		y[i]=hist4_new->GetBinContent(i+1)*r[i];
                yy[i]=hist4_new->GetBinContent(i+1);
	}
        for(int i=0;i<hist4_new->GetNbinsX();i++)
        {
		hist4_new->SetBinContent(i+1,y[i]);
		hist4_up->SetBinContent(i+1,ymax[i]);
		hist4_down->SetBinContent(i+1,ymin[i]);
		h1->SetBinContent(i+1,yy[i]);
	}
        cout<<hist4_new->GetBinContent(2)<<endl;
        cout<<hist4_up->GetBinContent(2)<<endl;
        cout<<hist4_down->GetBinContent(2)<<endl;

	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
	c1->SetGrid();
	c1->DrawFrame(0,0,2.2,12);
	TGraph *grmin = new TGraph(n,x,ymin);
	TGraph *grmax = new TGraph(n,x,ymax);
	TGraph *gr    = new TGraph(n,x,y);
	TGraph *gr1    = new TGraph(n,x,yy);
	TGraph *grshade = new TGraph(2*n);
	for (int i=0;i<n;i++) {
		grshade->SetPoint(i,x[i],ymax[i]);
		grshade->SetPoint(n+i,x[n-i-1],ymin[n-i-1]);
	}
        TLegend* l1 = new TLegend(0.7,0.7,0.9,0.9);
        gStyle->SetOptStat(0);
	grshade->SetFillStyle(3013);
	grshade->SetFillColor(16);
	hist4_new->Draw();
        hist4_new->GetYaxis()->SetRangeUser(0,ymax[1]+2);
	grshade->Draw("f");
	grmin->Draw("l");
	grmax->Draw("l");
	gr->SetLineWidth(4);
	gr->SetFillColor(0);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->Draw("CP");
	l1->AddEntry(gr,"unfold data");
	l1->AddEntry(gr1,"truth");
	l1->AddEntry(grshade,"#pm1#sigma");
	l1->Draw();
	gr1->SetLineColor(2);
	gr1->SetFillColor(0);
	gr->SetMarkerColor(4);
	gr1->SetLineWidth(4);
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(21);
	gr1->Draw("CP SAME");
	c1->Print("unfold_result.eps");
}
