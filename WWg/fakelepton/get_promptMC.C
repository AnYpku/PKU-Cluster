void run(TString var,TString cut,vector<double> bins){
	vector<TString>sample={"MuonEG","ZGJets","TTGJets","WGJets","ST","VV","WW","tZq"};
	const int num=sample.size();
	cout<<var<<endl;
        TFile*fout=new TFile("hist_"+var+".root","recreate");
	TH1D*h1[num];
	for(int i=0;i<num;i++){
		TFile*fin=new TFile("/home/pku/anying/cms/rootfiles/WWg/cutla-out"+sample[i]+"18_fakeL.root");
		TString histname="hist_"+sample[i];
		h1[i]=new TH1D(histname,"prompt photon contribution",bins.size()-1,&bins[0]);
		TTree*tree=(TTree*)fin->Get("Events");
		tree->Draw(var+">>"+histname,"("+cut+")*scalef","goff");
		cout<<sample[i]<<" "<<tree->GetEntries()<<" "<<h1[i]->GetSum()<<endl;
//		fin->Close();
	}
        gStyle->SetOptStat(0);
	TLegend*l1=new TLegend(0.65,0.65,0.9,0.9);
	TCanvas*c1=new TCanvas("c_"+var,"",800,600);
	c1->SetLogy();
	h1[0]->SetLineColor(2);
	h1[0]->SetLineWidth(2);
	h1[0]->Draw("HIST E");
        h1[0]->GetYaxis()->SetRangeUser(0.001,h1[0]->GetMaximum()*100);
	h1[0]->SetTitle(";"+var+";yields");
	l1->AddEntry(h1[0],sample[0]);
	fout->cd();
        h1[0]->Write();
	for(int i=1;i<num;i++){
                h1[i]->Scale(-1);
		h1[i]->SetLineColor(2+i);
		l1->AddEntry(h1[i],sample[i]);
		h1[i]->Draw("HIST same E");
		fout->cd();
		h1[i]->Write();
	}
        fout->Close();
        l1->Draw();
	c1->Print("hist_"+var+".pdf"); 
}
int get_promptMC(){
	vector<double> ptbins={20,25,30,40,60,100};
	TString cut="(pass_selection>0 && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && !(lep1_is_tight==1 && lep2_is_tight==1 ) && lep1_isprompt==1 && lep2_isprompt==1 && n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 )) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && PuppiMET_T1_pt > 20 && puppimt>60 && n_bjets==0)";

	run("photonet", cut, ptbins);

	return 0;
} 
