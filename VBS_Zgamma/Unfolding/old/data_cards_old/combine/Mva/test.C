void test(){
TString dir16="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/2016/Mva/";
TString dir17="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/2017/Mva/";
TString dir18="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/2018/Mva/";
    TFile* f1= new TFile(dir16+"root/hist_ZA-EWK.root");
    TFile* f2= new TFile(dir16+"hist_Data.root");
    TFile* f3= new TFile(dir16+"hist_bkg.root");
//    TFile*frm=new TFile("hrm_ZA-EWK.root");
    TH1D* RecZA=(TH1D*)f1->Get("hist");
    TH1D* GenZA=(TH1D*)f1->Get("hist4");
    TH2D* ResZA=(TH2D*)f1->Get("h3");
    TH1D*hbkg=(TH1D*)f3->Get("hist");
    TH1D*hfake=(TH1D*)f1->Get("hist3");
    TH1D*hdata=(TH1D*)f2->Get("hist");

    TFile* ff1= new TFile(dir17+"root/hist_ZA-EWK.root");
    TFile* ff2= new TFile(dir17+"hist_Data.root");
    TFile* ff3= new TFile(dir17+"hist_bkg.root");
    TH1D* RecZA1=(TH1D*)ff1->Get("hist");
    TH1D* GenZA1=(TH1D*)ff1->Get("hist4");
    TH2D* ResZA1=(TH2D*)ff1->Get("h3");
    TH1D*hbkg1=(TH1D*)ff3->Get("hist");
    TH1D*hfake1=(TH1D*)ff1->Get("hist3");
    TH1D*hdata1=(TH1D*)ff2->Get("hist");

    TFile* fff1= new TFile(dir18+"root/hist_ZA-EWK.root");
    TFile* fff2= new TFile(dir18+"hist_Data.root");
    TFile* fff3= new TFile(dir18+"hist_bkg.root");
    TH1D* RecZA2=(TH1D*)fff1->Get("hist");
    TH1D* GenZA2=(TH1D*)fff1->Get("hist4");
    TH2D* ResZA2=(TH2D*)fff1->Get("h3");
    TH1D*hbkg2=(TH1D*)fff3->Get("hist");
    TH1D*hfake2=(TH1D*)fff1->Get("hist3");
    TH1D*hdata2=(TH1D*)fff2->Get("hist");
hdata->Add(hdata1);
hdata->Add(hdata2);
hbkg->Add(hbkg1);
hbkg->Add(hbkg2);
ResZA->Add(ResZA1);
ResZA->Add(ResZA2);
    double factor =( hdata->Integral(0,hdata->GetNbinsX())-hbkg->Integral(0,hbkg->GetNbinsX()))/RecZA->Integral(0,RecZA->GetNbinsX());
    factor = factor*(-1);
    cout<<"factor "<<factor<<endl;
    hdata->Add(hbkg,-1);
    TUnfoldDensity * density = new TUnfoldDensity(ResZA,
            TUnfold::kHistMapOutputHoriz,
            TUnfold::kRegModeNone,
            TUnfold::kEConstraintNone,
            TUnfoldDensity::kDensityModeBinWidthAndUser);

    density->SetInput(hdata);

    density->DoUnfold(0);

    TH1 * output = density->GetOutput("unfHist");
    output->Draw("hist");
    TFile*fout=new TFile("unfold_hist.root","recreate");
    fout->cd();
    output->Write();
    fout->Close();
}
