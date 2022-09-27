Double_t fakerate[9];
Double_t lowpt[9]= {20,25,30,35,40,45,50,65,100};
Double_t highpt[9]={25,30,35,40,45,50,65,100,400};
Double_t bin_data[9],bin_plj[9],bin_za[9];
Double_t weight[9];
TFile* f1 = new TFile("./plj-hist/cutla-outDEle_plj_he.root");
TFile* f2 = new TFile("./plj-hist/cutla-outDEle_he.root");
TFile* f3 = new TFile("./plj-hist/cutla-outZA_contamination_he.root");
//TFile* f1 = new TFile("./plj-hist/cutla-outDEle_plj_he.root");
//TFile* f2 = new TFile("./plj-hist/cutla-outDEle_he.root");
 
TH1F* h1 = (TH1F*)f1->Get("h_cutla-outDEle_plj");
TH1F* h2 = (TH1F*)f2->Get("h_cutla-outDEle");
TH1D* h3 = (TH1D*)f3->Get("h_cutla-outZA_contamination");

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
    bin_za[i] = 59.97*h3->GetBinContent(i+1);
  }
}
void open(Int_t i){
    
    ifstream f1;
    f1.open(Form("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2018/MakeTemplate/ElectronEndcap/ZAfit/txt/fakerate_ZA_pt%0.f_%0.f.txt",lowpt[i],highpt[i]));
//    f1.open(Form("./eleBarrel-ff/fakerate_pt%0.f_%0.f.txt",lowpt[i],highpt[i]));
    if(!f1.is_open()) cout<<"can not open the file: "<<Form("fakerate_pt%0.f_%0.f.txt",lowpt[i],highpt[i])<<endl;
   // if(f1.is_open()) cout<<"open the file: "<<Form("fakerate_pt%0.f_%0.f.txt",lowpt[i],highpt[i])<<endl;
    f1>>fakerate[i];cout<<"fakerate = "<<fakerate[i]<<endl;
}
int pljweight(){
gStyle->SetOptStat(0);
for(Int_t i=0;i<9;i++){
   open(i);
 }
draw();
ofstream file("./ele-endcap-pljweight/pljweight.txt");
//ofstream file("./ele-barrel-pljweight/pljweight.txt");
const char *name[9]={"20~25","25~30","30~35","35~40","40~45","45~50","50~65","65~100","100~400"};
for(Int_t i=0;i<9;i++){
//   weight[i]=bin_data[i]*fakerate[i]/bin_plj[i];
//   cout<<"bin "<<name[i]<<" ;"<<"data : "<<bin_data[i]<<"; plj : "<<bin_plj[i]<<"; fakerate : "<<fakerate[i]<<"; weight : "<<weight[i]<<endl;
   weight[i]=bin_data[i]*fakerate[i]/(bin_plj[i]-bin_za[i]);
   cout<<"bin "<<name[i]<<" ;"<<"data : "<<bin_data[i]<<"; plj : "<<bin_plj[i]<<"; za contamination"<<bin_za[i]<<"; fakerate : "<<fakerate[i]<<"; weight : "<<weight[i]<<endl;
   file<<name[i]<<"\t"<<weight[i]<<endl;
  }
return 0;
}

