TH1D* copy(TH1D*h1){
 const int bins=h1->GetNbinsX();
 Double_t ptBins[5]={20,80,120,200,400};
 TH1D*hist=new TH1D(h1->GetName(),h1->GetTitle(),bins,ptBins);
 hist->SetBinContent(1,h1->GetBinContent(1)+h1->GetBinContent(2));
 hist->SetBinContent(2,h1->GetBinContent(3));
 hist->SetBinContent(3,h1->GetBinContent(4));
 hist->SetBinContent(4,h1->GetBinContent(5));

 return hist;
}
 

int rebin(){
     

}



