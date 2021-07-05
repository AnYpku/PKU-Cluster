TH2D*run(TString filename,TString cut,TString particle,TString year){

	vector<double> ptbins={20,30,40,50,60,70,80,100};
	vector<double> etabins={0,0.5,1,1.5,2,2.5};

	TFile*f1=new TFile("/home/pku/anying/cms/rootfiles/WWg/"+filename+year+"_fakerate.root");
	f1->Print();
	TTree*tree=(TTree*)f1->Get("Events");
//	tree->Print();

        cout<<"Total entries:" <<tree->GetEntries()<<endl;
        cout<<"Cut: "<<cut<<endl;
        cout<<"Selected entries: "<<tree->GetEntries(cut)<<endl;
        cout<<endl;

	if(particle.Contains("mu")){
		cut="("+cut+"&&(HLT_Mu17_TrkIsoVVL))";
	}

        cout<<"Total entries:" <<tree->GetEntries()<<endl;
        cout<<"Cut: "<<cut<<endl;
        cout<<"Selected entries: "<<tree->GetEntries(cut)<<endl;
        cout<<endl;

	TString histname="hist_"+particle+"_"+filename+year;
	TH2D*hist=new TH2D("h2",histname,etabins.size()-1,&etabins[0],ptbins.size()-1,&ptbins[0]);

        tree->Draw("lepton_pt:lepton_eta>>h2",cut,"colz");

        cout<<"hist entries: "<<hist->GetEntries()<<endl;

	return hist;

}
int cal(){
	TString cut="(puppimet<30 && puppimt<20)";

        TH2D*h_mu=run("DMuon",cut,"mu","18");

        TFile*file=new TFile("hist.root","recreate");
        h_mu->Write();     
  
	file->Close();
	return 0;
}
