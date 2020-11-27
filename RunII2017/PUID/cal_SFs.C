TH2D*SF(TString type){
    TFile*f1=new TFile("./effcyPUID_81Xtraining.root");
    TFile*f2=new TFile("./scalefactorsPUID_81Xtraining.root");
    TH2D*h1=(TH2D*)f1->Get("h2_eff_mc2017_"+type);
    TH2D*h2=(TH2D*)f1->Get("h2_mistag_mc2017_"+type);
    TH2D*h3=(TH2D*)f2->Get("h2_eff_sf2017_"+type);
    TH2D*h4=(TH2D*)f2->Get("h2_mistag_sf2017_"+type);
   
    int binsx=h1->GetNbinsX();int binsy=h1->GetNbinsY();
    TString hname="eff_"+type;
    TH2D* hsf=(TH2D*)h3->Clone("h2_sf_2017_"+type);
    hsf->SetTitle("PU jet ID SF, WP "+type+" 2017;Jet p_{T} [GeV];Jet #eta");
    for(int ix=1;ix<=binsx;ix++){
        for(int iy=1;iy<=binsy;iy++){
            double P_MC=h1->GetBinContent(ix,iy)*(1-h2->GetBinContent(ix,iy));
            double P_Data=h3->GetBinContent(ix,iy)*h1->GetBinContent(ix,iy)*(1-h4->GetBinContent(ix,iy)*h2->GetBinContent(ix,iy));
            double weight=P_Data/P_MC;
            hsf->SetBinContent(ix,iy,weight);
        }
    }

    return hsf;
}
TH2D*cal(TH2D*hMC,TH2D*hData){
    TH2D*hSF=(TH2D*)hMC->Clone("SF");
    hSF->SetTitle("e/#gamma scale factors");
    int binsx=hMC->GetNbinsX();int binsy=hMC->GetNbinsY();
    for(int ix=1;ix<=binsx;ix++){
        for(int iy=1;iy<=binsy;iy++){
            int temp=hData->GetBinContent(ix,iy)/hMC->GetBinContent(ix,iy)*1e3;
            double SF=temp/1e3;
            double temp_err=sqrt( pow(1/hMC->GetBinContent(ix,iy)*hData->GetBinError(ix,iy),2)+ pow(hData    ->GetBinContent(ix,iy)/pow(hMC->GetBinContent(ix,iy),2)*hMC->GetBinError(ix,iy),2) );
            temp=temp_err*1e3;
            double SF_err=temp/1e3;
//            double SF=hData->GetBinContent(ix,iy)/hMC->GetBinContent(ix,iy);
//            double SF_err=sqrt( pow(1/hMC->GetBinContent(ix,iy)*hData->GetBinError(ix,iy),2)+ pow(hData->GetBinContent(ix,iy)/pow(hMC->GetBinContent(ix,iy),2)*hMC->GetBinError(ix,iy),2) );
            hSF->SetBinContent(ix,iy,SF);
            hSF->SetBinError(ix,iy,SF_err);
        }
    }
return hSF;
}
int cal_SFs(){
    gStyle->SetOptStat(0);
    TH2D*hSF_M=SF("M");
    TH2D*hSF_L=SF("L");
    TH2D*hSF_T=SF("T");
    TFile*fout=new TFile("PUIDSFs.root","recreate");
    hSF_M->Write();
    hSF_L->Write();
    hSF_T->Write();
    fout->Close();

//    TCanvas*c1=new TCanvas("c1","",800,600);
//    c1->SetLogy();
//    hSF_M->Draw("colztext e");
//    c1->Print("egamma_SF.pdf");
    return 0;
}
