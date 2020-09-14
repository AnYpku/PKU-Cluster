#include "CMS_lumi.C"
void cmsLumi(bool channel);
void run(TString var, vector<double> Err,TString title){
	TFile*file1=new TFile("./yields/"+var+"_unfold_ewk_scale16.root");
	TFile*file2=new TFile("./yields/"+var+"_unfold_ewk_scale17.root");
	TFile*file3=new TFile("./yields/"+var+"_unfold_ewk_scale18.root");
	TH1D*h1[3];TH1D*h2[3];TH1D*h3[3];
        for(int i=0;i<3;i++){
           h1[i]=(TH1D*)file1->Get(var+Form("_%i",i));
           h2[i]=(TH1D*)file2->Get(var+Form("_%i",i));
           h3[i]=(TH1D*)file3->Get(var+Form("_%i",i));
           h1[i]->Scale(35.86);
           h2[i]->Scale(41.52);
           h3[i]->Scale(58.7);
           h1[i]->Add(h2[i],1);
           h1[i]->Add(h3[i],1);
	}
        const int kk=h1[0]->GetNbinsX();
	for(int i=0;i<3;i++){
		h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
		h2[i]->SetBinContent(kk,h2[i]->GetBinContent(kk)+h2[i]->GetBinContent(kk+1));
		h3[i]->SetBinContent(kk,h3[i]->GetBinContent(kk)+h3[i]->GetBinContent(kk+1));
	}
	TH1D*hist_clone=(TH1D*)h1[0]->Clone();
	for(int i=0;i<hist_clone->GetNbinsX();i++){
		hist_clone->SetBinError(i+1,Err[i]*h1[0]->GetBinContent(i+1));
	}
	hist_clone->SetLineColor(1);
       TCanvas*c1=new TCanvas("c0","reco && gen",800,600);
       c1->cd();
       TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.4, 0.99, 0.99);
       TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.4);
       fPads1->SetBottomMargin(0);
       fPads2->SetTopMargin(0);
       fPads2->SetBottomMargin(0.3);
       fPads2->Draw();
       fPads1->Draw();
       CMS_lumi(fPads1, 4, 0, "136.1");
       fPads1->cd();
       h1[0]->GetYaxis()->SetLabelSize(0.07);
       h1[0]->SetTitle("");
       h1[0]->GetYaxis()->SetRangeUser(0,h1[0]->GetMaximum()*1.6);
       h1[0]->SetLineColor(2);
       h1[0]->SetLineWidth(2);
       h1[0]->Draw("hist error");
       h1[0]->SetLineStyle(1);
       hist_clone->SetMarkerStyle(20);
       hist_clone->SetMarkerColor(1);
       hist_clone->SetLineColor(2);
       hist_clone->Draw("PE same");
       cout<<h1[0]->GetBinContent(4)<<endl;
//       h1[0]->Draw("EP same");
       double uf[3]={1,2,0.5};
       TLegend*l1=new TLegend(0.7,0.3,0.9,0.9);
       TLegend*l2=new TLegend(0.5,0.7,0.7,0.9);
       l1->AddEntry(h1[0],"p_{T}^{gen} #times r");
       for(int i=0;i<3;i++){
	  if(i!=0){
		  h1[i]->SetLineColor(2+i);
		  h1[i]->Draw("same hist error");
		  l1->AddEntry(h1[i],Form("p_{T}^{gen} #mu_{f}=%1.2f",uf[i]));
	  }
       }
      l1->AddEntry(hist_clone,"#pm #Delta r");
      l1->Draw();
      cmsLumi(0);
      fPads1->Update();
      fPads2->cd();
      TH1D*nominal=(TH1D*)h1[0]->Clone("nominal");
      TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
      for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
      TH1D*h_up=(TH1D*)h1[1]->Clone();
      TH1D*h_down=(TH1D*)h1[2]->Clone();
      h_up->Divide(nominal);
      h_down->Divide(nominal);

      nominal->Divide(nomNoErr);
      nominal->SetFillStyle(3001);
      nominal->SetFillColor(2);
      const int num=Err.size();
      nominal->GetYaxis()->SetRangeUser(h_up->GetMaximum()-0.05,h_down->GetMaximum()+0.05);
      nominal->SetTitle("");
      nominal->GetXaxis()->SetLabelSize(0.1);
      nominal->GetXaxis()->SetTitleSize(0.15);
      nominal->GetXaxis()->SetTitleOffset(0.8);
      nominal->GetXaxis()->SetTitleFont(32);
      nominal->GetXaxis()->SetTitle(title);
      nominal->GetYaxis()->SetTitle("ratio");
      nominal->GetYaxis()->SetTitleOffset(0.45);
      nominal->GetYaxis()->SetTitleSize(0.08);
      nominal->GetYaxis()->SetTitleFont(32);
      nominal->GetYaxis()->SetLabelSize(0.1);
      TLine*line=new TLine(nominal->GetXaxis()->GetXmin(),1,nominal->GetXaxis()->GetXmax(),1);
      line->SetLineColor(2);
      nominal->Draw("E2");
      h_up->Draw("same hist ][");
      h_down->Draw("same hist ][");
      line->Draw();
      cout<<h1[0]->GetBinError(1)/h1[0]->GetBinContent(1)<<endl;
      cout<<nominal->GetBinError(1)<<" "<<hist_clone->GetBinError(1)<<endl;
      fPads2->Update();
      fPads1->cd();
      l1->AddEntry(nominal,"Stat","f");
      l1->Draw();
      fPads1->Update();
      c1->Print(var+"_unfold_scale.pdf");


}
int Add(){
	gStyle->SetOptStat(0);
	vector<double> Err_ptlep1={0.6,0.38,0.37,0.49};
	vector<double> Err_photonet={0.5,0.43,0.45,0.55};
	vector<double> Err_jet1pt={0.66,0.29,0.42,0.52};
	vector<vector<double>> Err;
	Err.push_back(Err_ptlep1);
	Err.push_back(Err_photonet);
	Err.push_back(Err_jet1pt);
	vector<TString> title={"leading p_{T}^{lep}","leading p_{T}^{#gamma}","leading p_{T}^{j}","M_{jj}","m_{Z#gamma}"};
	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genZGmass","genMjj"};
	for(int i=0;i<Err.size();i++){
		run(genvars[i],Err[i],title[i]);
	}
	return 0;

}
void cmsLumi(bool channel)
{
	TLatex latex;
	latex.SetNDC();
	latex.SetTextSize(0.05);
	latex.SetLineWidth(2);
	float lumiel=136.1;
	float lumimu=136.1;
	int beamcomenergytev=13;
	latex.SetTextAlign(31);
	latex.SetTextAlign(11);
	latex.DrawLatex(0.18,0.82,"Preliminary");
	latex.DrawLatex(0.18,0.86,"CMS");
	latex.SetTextSize(0.045);
	latex.DrawLatex(0.76,0.92,Form("136.1 fb^{-1} (%d TeV)", (beamcomenergytev)));
}
