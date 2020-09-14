void run(TString sample, TString type){
	TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/cuts_eff/"+sample+"/";
	TFile*f1=new TFile(dir+"2016_results.root");
	TFile*f2=new TFile(dir+"2017_results.root");
	TFile*f3=new TFile(dir+"2018_results.root");
        TH1D*h1=(TH1D*)f1->Get(type);
        TH1D*h2=(TH1D*)f2->Get(type);
        TH1D*h3=(TH1D*)f3->Get(type);
	double max=h1->GetMaximum()*3;
        h1->GetYaxis()->SetRangeUser(10,max);
        gStyle->SetOptStat(0);
        h3->SetLineColor(2); 
        h2->SetLineColor(3); 
        h1->SetLineColor(4); 
        TCanvas*c1=new TCanvas("","",900,600);
	c1->SetLogy();
        h1->Draw();
        h3->Draw("same");
        h2->Draw("same");
        TLegend*l1=new TLegend(0.75,0.75,0.9,0.9);
        l1->AddEntry(h3,"2018");
        l1->AddEntry(h2,"2017");
        l1->AddEntry(h1,"2016");
	l1->Draw();
        c1->Print(sample+"Com_"+type+".pdf");
}
int compare(){
TString type[3]={"entries","yields","eff_entries"};
for(int i=0;i<3;i++){
	run("EWK",type[i]);
	run("QCD",type[i]);
}
return 1;
}
