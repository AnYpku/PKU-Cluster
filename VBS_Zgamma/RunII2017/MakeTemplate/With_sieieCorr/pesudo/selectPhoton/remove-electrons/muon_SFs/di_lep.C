void di_lep(){
 TFile* file = new TFile("di_lep_eff.root","recreate");
 Double_t leadingPt[4]={20,40,80,200};
 Double_t SubleadingPt[4]={20,40,80,200};
 TH2D* h2 = new TH2D("h2","the trigger SF of di-muon channel",3,leadingPt,3,SubleadingPt);
 h2->SetBinContent(1,1,0.84); h2->SetBinError(1,1,0.02);
 h2->SetBinContent(2,1,0.94); h2->SetBinError(2,1,0.01);
 h2->SetBinContent(3,1,0.93); h2->SetBinError(3,1,0.02);
 h2->SetBinContent(1,2,1);    h2->SetBinError(1,2,0.0);
 h2->SetBinContent(2,2,0.99); h2->SetBinError(2,2,0.01);
 h2->SetBinContent(3,2,0.97); h2->SetBinError(3,2,0.01);
 h2->SetBinContent(1,3,1);    h2->SetBinError(1,3,0.0);
 h2->SetBinContent(2,3,1);    h2->SetBinError(2,3,0.0);
 h2->SetBinContent(3,3,0.98); h2->SetBinError(3,3,0.02);
 
 h2->Draw("COLZTEXTE");
 h2->Write();
 file->Close();







}
