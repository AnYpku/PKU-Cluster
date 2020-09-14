void run(TString tag, TString type,TString sample){
	TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/"+tag+"/data_crads/"+type+"/";
	TFile*f1=new TFile(dir+sample+"_hist.root");
	TH1D*h1=(TH1D*)f1->Get("h2");
	for(int i=0;i<h1->GetNbinsX();i++){
            cout<<tag<<" "<<sample<<" channel "<<type<<" bin"<<i+1<<" entries "<<h1->GetBinContent(i+1)<<endl;
	}


}
int print_entries(){
//run("2016","ele","ZA_total");
//run("2017","ele","ZA");
//run("2018","ele","ZA");

run("2017","ele","ZA-EWK");
run("2016","ele","ZA-EWK");
run("2018","ele","ZA-EWK");

//run("2016","muon","ZA_total");
//run("2017","muon","ZA");
//run("2018","muon","ZA");

run("2017","muon","ZA-EWK");
run("2016","muon","ZA-EWK");
run("2018","muon","ZA-EWK");
return 1;
}
