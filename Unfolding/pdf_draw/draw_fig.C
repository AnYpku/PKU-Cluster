void run(TString tag){
TFile*file=new TFile("histo_mjj_xsec"+tag+".root","recreate");
double xsec,err;
if(tag.Contains("16")) xsec=4.37;
else if(tag.Contains("17")) xsec=4.25;
else if(tag.Contains("18")) xsec=4.19;
else cout<<"error,please check!"<<endl;

if(tag.Contains("16")) err=1.09;
else if(tag.Contains("17")) err=1.17;
else if(tag.Contains("18")) err=0.9;
else cout<<"error,please check!"<<endl;
TH1D*h1=new TH1D("h1","mjj",1,500,2000);
h1->SetBinContent(1,xsec/1000);
h1->SetBinError(1,err/1000);
file->cd();
h1->Write();
file->Close();
}
int draw_fig(){
run("16");
run("17");
run("18");
return 1;
}
