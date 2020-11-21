TH1D* run(TString year,TString name){
     TFile*f1=new TFile("/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/"+year+"/ScalSeq/output-slimmed-rootfiles/optimal_aqgc_"+name+".root");
     TTree* t1=(TTree*)f1->Get("outtree");
     double ZGmass,actualWeight;
     t1->SetBranchStatus("*",0);
     t1->SetBranchStatus("ZGmass",1);
     t1->SetBranchStatus("actualWeight",1);
     t1->SetBranchAddress("ZGmass",&ZGmass);
     t1->SetBranchAddress("actualWeight",&actualWeight);
     double ZGbin[6]={150,400,600,800,1000,2000};
     TH1D*h1=new TH1D("h1","ZGamma",5,ZGbin);
     for(int i=0;i<t1->GetEntries();i++){
	     t1->GetEntry(i);
             h1->Fill(ZGmass,actualWeight);
     }
     return h1;
}
int drawCom(){
        gStyle->SetOptStat(0);
        TH1D*h1=run("2016","ZA-EWK"); 
        TH1D*h2=run("2016","ZA") ;
        TH1D*h11=run("2017","ZA-EWK"); 
        TH1D*h22=run("2017","ZA") ;
        TCanvas*c1=new TCanvas("c1","",900,600);
	TLegend*l1=new TLegend(0.75,0.75,0.9,0.9);
        h1->SetLineColor(2);
        h11->SetLineColor(3);
        l1->AddEntry(h1,"2016 EW");
        l1->AddEntry(h11,"2017 EW");
        h11->DrawNormalized();
        h1->DrawNormalized("same") ;
	l1->Draw();
        c1->Print("EWcompNorm.pdf");
        TCanvas*c2=new TCanvas("c2","",900,600);
	TLegend*l2=new TLegend(0.75,0.75,0.9,0.9);
        h2->SetLineColor(2);
        h22->SetLineColor(3);
        l2->AddEntry(h2,"2016 QCD");
        l2->AddEntry(h22,"2017 QCD");
        h2->DrawNormalized();
        h22->DrawNormalized("same") ;
	l2->Draw();
        c2->Print("QCDcompNorm.pdf");
return 1;
}
