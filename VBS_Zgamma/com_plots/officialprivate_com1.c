
TString name[14] = {"photonet","photoneta","etalep1","etalep2","ptlep1","ptlep2","jet1pt","jet2pt","jet1eta","jet2eta","ptVlep","npT","nVtx","Mjj"};
Int_t bin=100;
Double_t low[14] ={0,-3.3,-3.,-3.,0.,0.,0.,0.,-5.,-5.,0.,0.,0.,0.};
Double_t high[14]={100,3.3,3.,3.,120.,120.,120.,120.,5.,5.,120.,120.,50.,1200 };
Double_t scalef;
Double_t lumiWeight;
Double_t pileupWeight;

Double_t photonet;
Double_t photoneta;
Double_t jet1eta,jet2eta;
Double_t jet1pt,jet2pt;
Double_t ptlep1,etalep1;
Double_t ptlep2,etalep2;
Double_t npT,ptVlep,Mjj;
Int_t nVtx;
TH1D *h1[14];
TH1D *h2[14];

void draw(TString title[14],TH1D* h3[14],int p1,int p2);
void open(std::string filename, TH1D* h[14]);

void open(std::string dir,std::string filename, TH1D* h[14]){
  string file = dir + filename + ".root";
  TFile *f1=new TFile(file.c_str());
  cout<<"open the file "+ filename + ".root"<<endl;
  TTree* t=(TTree *)f1->Get("demo");
  Long64_t en=t->GetEntries();
//  en=10000;
  t->SetBranchAddress("scalef",&scalef);
  t->SetBranchAddress("lumiWeight",&lumiWeight);
  t->SetBranchAddress("pileupWeight",&pileupWeight);
      t->SetBranchAddress(name[0],&photonet);
      t->SetBranchAddress(name[1],&photoneta);
      t->SetBranchAddress(name[2],&etalep1);
      t->SetBranchAddress(name[3],&etalep2);
      t->SetBranchAddress(name[4],&ptlep1);
      t->SetBranchAddress(name[5],&ptlep2);
      t->SetBranchAddress(name[6],&jet1pt);
      t->SetBranchAddress(name[7],&jet2pt);
      t->SetBranchAddress(name[8],&jet1eta);
      t->SetBranchAddress(name[9],&jet2eta);
      t->SetBranchAddress(name[10],&ptVlep);
      t->SetBranchAddress(name[11],&npT);
      t->SetBranchAddress(name[12],&nVtx);
      t->SetBranchAddress(name[13],&Mjj);

  Double_t a[14];
  Double_t actualWeight;
  TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
  TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
  TString cut="(("+LEPmu+")||("+LEPele+"))";
  TTreeFormula *tformula=new TTreeFormula("formula", cut, t);
  for (Long64_t i = 0; i < en; i++) {
    /* code */
    t->GetEntry(i);
    if ( ! tformula->EvalInstance() )
	    continue;
    actualWeight=scalef*lumiWeight*pileupWeight;
    a[0]=photonet;a[1]=photoneta;a[2]=etalep1;a[3]=etalep2;a[4]=ptlep1;a[5]=ptlep2;a[6]=jet1pt;
    a[7]=jet2pt; a[8]=jet1eta; a[9]=jet2eta;a[10]=ptVlep;a[11]=npT;  a[12]=nVtx; a[13]=Mjj;
   // if(a[12]>0) cout<<"nVtx = "<<a[12]<<endl;
   // if(a[13]>0) cout<<"Mjj = "<<a[13]<<endl;
    for(Int_t i=0;i<14;i++){
       h[i]->Fill(a[i],actualWeight);}
  }
}
void draw(TString title[14],TH1D* h3[14],int p1,int p2){
      gStyle->SetPadBorderMode(0);
      gStyle->SetOptStat(0);
      gStyle->SetPadGridX(1);
      gStyle->SetPadGridY(1);
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);
      gStyle->SetPadTopMargin(0.07);
      gStyle->SetPadBottomMargin(0.3);
      gStyle->SetPadRightMargin(0.05);
      gStyle->SetPadLeftMargin(0.14);
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);
      gStyle->SetAxisColor(1, "XYZ");
      gStyle->SetStripDecimals(kTRUE);
      gStyle->SetTickLength(0.03, "XYZ");
      gStyle->SetNdivisions(510, "XYZ");


      TCanvas *c1[14];
      TLegend *l1[14];
      TLine* line[14];

   for(Int_t i=0;i<14;i++){
//       if(!(i==p1||i==p2))
//	       continue;
      c1[i] = new TCanvas(title[i],title[i],750,500);
      l1[i] = new TLegend(0.6,0.7,0.9,0.9);
   //   l1[i]->SetTextSize();
      TPad *top_pad=new TPad("top_pad", "top_pad",0,0.2, 1.0, 1.0);
      top_pad->Draw();
      top_pad->cd();
      top_pad->SetBottomMargin(0.1);
      //top_pad->SetLogy();
      h1[i]->SetLineColor(kRed);
      h1[i]->SetLineWidth(3);
      h1[i]->SetMarkerStyle(20);
      h1[i]->Draw("HIST");

      h2[i]->SetLineColor(kBlue);
      h2[i]->SetLineWidth(4);
      h2[i]->SetLineStyle(5);
      h2[i]->SetMarkerStyle(20);
      h2[i]->Draw("HIST same");
      l1[i]->AddEntry(h1[i],"Sherpa");
      l1[i]->AddEntry(h2[i],"MG");
//      l1[i]->Draw();
      l1[i]->SetBorderSize(1);
      l1[i]->SetFillColor(0);

      c1[i]->cd();
      line[i] = new TLine(low[i],1.,high[i],1);
      TPad *bottom_pad=new TPad("bottom_pad", "bottom_pad", 0, 0., 1.0, 0.2);
      bottom_pad->Draw();
      bottom_pad->cd();
      bottom_pad->SetTopMargin(0);
      h3[i]->Draw("HIST");
      h3[i]->SetTitle("");
      h3[i]->GetXaxis()->SetTitle( title[i] +" [GeV] ");
      h3[i]->GetYaxis()->SetTitle("K factor ");
      h3[i]->GetXaxis()->CenterTitle();
      h3[i]->GetYaxis()->CenterTitle();
      h3[i]->SetLineColor(kBlack);
      h3[i]->GetXaxis()->SetTitleOffset(0.9);
      h3[i]->GetYaxis()->SetTitleOffset(0.22);
      h3[i]->GetXaxis()->SetTitleSize(0.15);
      h3[i]->GetYaxis()->SetTitleSize(0.15);
      h3[i]->GetXaxis()->SetLabelSize(0.12);
      h3[i]->GetYaxis()->SetLabelSize(0.1);
      h3[i]->SetMaximum(1.35);
      h3[i]->SetMinimum(0.7);
      line[i]->SetLineColor(kRed);
      line[i]->Draw();
      l1[i]->AddEntry(h3[i],"MG/Sherpa");
      top_pad->cd();
      l1[i]->Draw();
      c1[i]->Draw();
      c1[i]->Print(title[i] +".pdf");
     
   }
}

int main(){
TFile*file[14];
for(int i=0;i<14;i++){
     h1[i]=new TH1D(Form("h1_%d",i),name[i],bin,low[i],high[i]);
     h2[i]=new TH1D(Form("h2_%d",i),name[i],bin,low[i],high[i]);
     file[i]=new TFile("hist_"+name[i]+".root","recreate");
   }
      open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2017/step1_add_weight/","outZA_sherpa17",h1);
      open("/eos/user/y/yian/2017cutla/","cutlep-outZA",h2);
      
      TH1D *h3[14];
      for(Int_t i=0;i<14;i++){
      h3[i]= (TH1D *)h2[i]->Clone();
      h3[i]->Divide(h1[i]);
      }
      for(Int_t i=0;i<14;i++){ 
         file[i]->cd();
         h1[i]->Write();
         h2[i]->Write();
         h3[i]->Write();
         file[i]->Close();
      }
      draw(name,h3,12,13);

      return 0;
}




