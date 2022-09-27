Double_t fakerate[9];
Double_t lowpt[9]= {25,30,35,40,45,50,60,80,120};
Double_t highpt[9]={30,35,40,45,50,60,80,120,400};
Double_t bin_data[9],bin_plj[9];
Double_t weight[9];
TFile* f1 = new TFile("../plj-hist/cutLEP-outpljDMuon_hlep.root");
TFile* f2 = new TFile("../plj-hist/cutLEP-outDMuon_hlep.root");
 
TH1F* h1 = (TH1F*)f1->Get("hlep_cutLEP-outpljDMuon");
TH1F* h2 = (TH1F*)f2->Get("hlep_cutLEP-outDMuon");
void draw(){

 TCanvas* c1 = new TCanvas("c1","plj vs data",900,700);
// for(Int_t j=1;j<=9;j++){ h1->GetXaxis()->SetBinLabel(j,name[j-1]);}
 h1->SetLineColor(kRed);
 h1->SetLineWidth(3);
 h1->SetLineStyle(5);

 h2->SetLineWidth(3);
 h2->SetLineColor(kGreen);
 h2->SetLineStyle(5);
 TLegend *leg = new TLegend(0.7, 0.8, 0.88, 0.88, NULL, "brNDC");
 leg->SetFillColor(10);
 leg->AddEntry(h1, "plj", "L");
 leg->AddEntry(h2, "data", "L");
 h1->Draw();
 h2->Draw("Same");
 leg->Draw();
 c1->Print("./plj_vs_data.eps");
 delete c1;
 for(Int_t i=0;i<9;i++){
    bin_data[i]=h2->GetBinContent(i+1);
    bin_plj[i] =h1->GetBinContent(i+1);
  }
}
void open(Int_t i){
    
    ifstream f1;
    f1.open(Form("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/fit/fakerate_pt%0.f_%0.f.txt",lowpt[i],highpt[i]));
    if(!f1.is_open()) cout<<"can not open the file: "<<Form("fakerate_pt%0.f_%0.f.txt",lowpt[i],highpt[i])<<endl;
   // if(f1.is_open()) cout<<"open the file: "<<Form("fakerate_pt%0.f_%0.f.txt",lowpt[i],highpt[i])<<endl;
    f1>>fakerate[i];cout<<"fakerate = "<<fakerate[i]<<endl;
}
int pljweight(){
for(Int_t i=0;i<9;i++){
   open(i);
 }
draw();
ofstream file("./pljweight.txt");
const char *name[9]={"25~30","30~35","35~40","40~45","45~50","50~60","60~80","80~120","120~400"};
for(Int_t i=0;i<9;i++){
   weight[i]=bin_data[i]/(bin_plj[i]*fakerate[i]);
//   weight[i]=bin_data[i]*fakerate[i]/bin_plj[i];
   cout<<"bin "<<name[i]<<" ;"<<"data : "<<bin_data[i]<<"; plj : "<<bin_plj[i]<<"; fakerate : "<<fakerate[i]<<"; weight : "<<weight[i]<<endl;
   file<<name[i]<<"\t"<<weight[i]<<endl;
  }
return 0;
}
