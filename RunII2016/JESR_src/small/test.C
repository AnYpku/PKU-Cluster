#include "unroll.C"
#define num 27
void test(){
//	TFile* f_ZA=new TFile("./output/hist_outZA-JESR-src.root");
        gStyle->SetPadBorderMode(0);
        gStyle->SetOptStat(0);
        gStyle->SetPadTickX(1);
        gStyle->SetPadTickY(1);
        gStyle->SetPadTickX(1);
        gStyle->SetPadTickY(1);
        gStyle->SetAxisColor(1, "XYZ");
        gStyle->SetStripDecimals(kTRUE);
        gStyle->SetTickLength(0.03, "XYZ");
        gStyle->SetNdivisions(510, "XYZ");
        TFile* f_ZA=TFile::Open("./hist_outZA-JESR-src.root");
        TH2D* th2_ZA_up[num];
        TH1D* t_ZA_up[num];
        TH2D* th2_ZA_down[num];
        TH1D* t_ZA_down[num];
        TH2D* th2_ZA;
        TH1D* t_ZA;
	TFile* fout = new TFile("aa.root","RECREATE");
	Double_t mjj_bins[4]={500, 800, 1200,2000};
	Double_t deltaeta_bins[4]={2.5,4.5,6,6.5};
        const char *name[8]={"Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~1200","Mjj 1200~2000"};
        th2_ZA=(TH2D*)f_ZA->Get("h");
        t_ZA=unroll(th2_ZA, mjj_bins, deltaeta_bins, 3,3,"hist");
	for(Int_t j=1;j<=t_ZA->GetNbinsX()*t_ZA->GetNbinsY();j++){ t_ZA->GetXaxis()->SetBinLabel(j,name[j-1]);}
	vector<double> vec_ymax;
        for(Int_t i=0;i<num;i++){
                th2_ZA_up[i]=(TH2D*)f_ZA->Get(Form("hist_up_%i",i));
                th2_ZA_down[i]=(TH2D*)f_ZA->Get(Form("hist_down_%i",i));
                cout<<th2_ZA_up[i]->GetName()<<endl;
                cout<<th2_ZA_up[i]->GetBinContent(1,2)<<endl;
                cout<<th2_ZA_down[i]->GetName()<<endl;
                cout<<th2_ZA_down[i]->GetBinContent(1,2)<<endl;
                t_ZA_up[i]=unroll(th2_ZA_up[i], mjj_bins, deltaeta_bins, 3,3,Form("hist1_up_%i",i));
                t_ZA_down[i]=unroll(th2_ZA_down[i], mjj_bins, deltaeta_bins, 3,3,Form("hist1_down_%i",i));
		vec_ymax.push_back(t_ZA_up[i]->GetMaximum());
	}
     TCanvas* c1 = new TCanvas("c1","Mjj vs deltajj",900,600);
     TLine* line = new TLine(t_ZA->GetXaxis()->GetXmin(),0,t_ZA->GetXaxis()->GetXmax(),0);
     c1->SetFrameFillColor(41);
     TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.4, 0.99, 0.99);
     TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.4);
     fPads1->SetBottomMargin(0);
     fPads2->SetTopMargin(0);
     fPads2->SetBottomMargin(0.3);
     fPads1->Draw();
     fPads2->Draw();
     fPads1->cd();
     TLegend *l2 = new TLegend(0.7,0.7,0.9,0.9);
     t_ZA->SetLineWidth(1);
     t_ZA->SetLineColor(kRed);
     t_ZA->GetYaxis()->SetRangeUser(0,vec_ymax[0]+0.3*vec_ymax[0]);
     t_ZA->Draw("HIST");
     t_ZA->GetXaxis()->SetTitle("mjj(GeV)");
     t_ZA->GetXaxis()->SetTitleSize(0.1);
     t_ZA->GetXaxis()->SetLabelSize(0.1);
     t_ZA->GetXaxis()->SetTitleSize(0.065);
     t_ZA->GetXaxis()->SetTitleFont(12);
     l2->AddEntry(t_ZA,"mjj_new");
     for(Int_t i=1;i<num;i++){
          t_ZA_up[i]->SetLineColor(kGreen);
          t_ZA_up[i]->SetLineWidth(1);
          t_ZA_up[i]->SetLineStyle(2);
          for(Int_t j=1;j<=t_ZA_up[i]->GetNbinsX()*t_ZA_up[i]->GetNbinsY();j++){ t_ZA_up[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
          t_ZA_up[i]->Draw("HIST,SAME");

          t_ZA_down[i]->SetLineColor(kBlue);
          t_ZA_down[i]->SetLineWidth(1);
          t_ZA_down[i]->SetLineStyle(2);
          for(Int_t j=1;j<=t_ZA_down[i]->GetNbinsX()*t_ZA_down[i]->GetNbinsY();j++){ t_ZA_down[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
          t_ZA_down[i]->Draw("HIST,SAME");
       }
//       l2->AddEntry(t_ZA_up[0],"mjj_up");
//       l2->AddEntry(t_ZA_down[0],"mjj_down");
       l2->Draw();
       fPads1->Update();
       fPads2->cd();

       TH1D*nominal=(TH1D*)t_ZA->Clone("nominal");
       TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
       for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
       TH1D*h_up[num];
       TH1D*h_down[num];
       for(int i=0;i<num;i++){
	       h_up[i]=(TH1D*)t_ZA_up[i]->Clone();
	       h_down[i]=(TH1D*)t_ZA_down[i]->Clone();
	       h_up[i]->Divide(nominal);
	       h_down[i]->Divide(nominal);
       }
       nominal->Divide(nomNoErr);
       nominal->SetFillStyle(3001);
       nominal->SetFillColor(16);
       nominal->GetYaxis()->SetRangeUser(0.5,1.5);
       nominal->Draw();
       for(int i=0;i<num;i++){
	       h_up[i]->Draw("same hist ][");
	       h_down[i]->Draw("same hist ][");
       }
       fPads2->Update();
       c1->Print("./figs/hist-2d.eps");
       c1->Print("./figs/hist-2d.pdf");
       fout->cd();
           t_ZA->Write();
       for(Int_t i=0;i<num;i++){
            t_ZA_up[i]->Write();
            t_ZA_down[i]->Write();
       }




}
