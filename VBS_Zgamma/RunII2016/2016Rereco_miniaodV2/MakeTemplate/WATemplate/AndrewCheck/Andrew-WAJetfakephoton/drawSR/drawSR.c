Double_t massVlep_data,massVlep_za,massVlep_zj;
Double_t Mva_data,Mva_za,Mva_zj;
/*TH1D* h1_mczj = new TH1D("h1_mczj","massVlep",200,0,200);
TH1D* h1_mcza = new TH1D("h1_mcza","massVlep",200,0,200);
TH1D* h2_dza= new TH1D("h2_dza","ZGmass",200,0,200);
TH1D* h2_mczj= new TH1D("h2_mczj","ZGmass",200,0,200);
TH1D* h2_mcza= new TH1D("h2_mcza","ZGmass",200,0,200);*/
TH1D* getZA(TString name){
 TString dir = "./";
 TString filename ="T"+ name+".root";
 TFile* f1 = new TFile(dir+filename);
 TTree* t1 = (TTree*)f1->Get("demo");
 TH1D* h1_dza = new TH1D("h1_dza","",200,0,200);
 t1->Project("h1_dza","massVlep");
 return h1_dza;
}
TH1D* getWeight(TString name){
 TString dir = "./";
 TString filename ="T"+ name+".root";
 TFile* f1 = new TFile(dir+filename);
 TTree* t1 = (TTree*)f1->Get("demo");
 TH1D* h1_weight = new TH1D("h1_weight","",200,0,1);
 t1->Project("h1_weight","scalef");
 return h1_weight;
}
void draw(TH1D* h1,TH1D*h1weight,TH1D* h2,TH1D*h2weight,TH1D* h3){
 TCanvas* c1 =new TCanvas("c1","",900,600);
 TLegend* l1 =new TLegend(0.7,0.7,0.9,0.9);
 THStack* hs = new THStack("hs", "");
 h1->Multiply(h1weight);
 h2->Multiply(h2weight);
 h1->Scale(35.9*0.96);
 h2->Scale(35.9*0.96);
 h1->SetLineColor(kRed);
 h2->SetLineColor(kBlue);
 h3->SetLineColor(kBlack);
 l1->AddEntry("h1","Zjets","L");
 l1->AddEntry("h2","ZA","L");
 l1->AddEntry("h3","Data","L");
 hs->Add(h1);
 hs->Add(h2);
// h1->Draw("hist");
// h2->Draw("same hist");
 hs->Draw("hist");
 h3->Draw("eP same");
 l1->Draw();
 
 
// c1->Print("")
}
 
int drawSR(){
 TH1D* h1_dza = getZA("outDMuon"); 

 TH1D* h1_mzj = getZA("outZJets_FX"); 
 TH1D* h_weight_zj = getWeight("outZJets_FX"); 

 TH1D* h_weight_za = getWeight("outZA");  
 TH1D* h1_mza = getZA("outZA"); 
 draw(h1_mza,h_weight_za,h1_mzj,h_weight_zj,h1_dza);
 //h1_dza->Draw();
 return 1;
}
