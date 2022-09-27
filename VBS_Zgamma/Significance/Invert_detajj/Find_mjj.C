#define pi 3.1415926
TH1D*run(TString sample,TString cut1,TString tag){
	TFile*file;
	if(sample.Contains("plj")==0)
		file=new TFile("/home/pku/anying/cms/PKU-Cluster/CombineDraw/ScalSeq/output-slimmed-rootfiles/optimal_"+sample+tag+".root");
	else 
		file=new TFile("/home/pku/anying/cms/PKU-Cluster/CombineDraw/ScalSeq/output-slimmed-rootfiles/optimal_"+sample+tag+"_weight.root");
	TTree*tree=(TTree*)file->Get("outtree");
        double init=800,step=150;
	vector<double> mjj_bins={500,600,700,800};
	cout<<file->GetName()<<endl;
	TString hist_name1="hist1_"+sample+tag;
	TString hist_name="hist_"+sample+tag;
        vector<TString> name;
        for(int i =0;i<mjj_bins.size()-1;i++){
		name.push_back(Form("%0.f-%0.f",mjj_bins[i],mjj_bins[i+1]));
		cout<<name[i]<<endl;
	}
	TH1D*h1=new TH1D(hist_name1,"",mjj_bins.size()-1,&mjj_bins[0]);
        TH1D*h1_clone=new TH1D(hist_name,"",mjj_bins.size()-1,0,mjj_bins.size()-1);
	TTreeFormula *tformula1=new TTreeFormula("formula1", "(("+cut1+"))", tree);
        int lep;double Mjj; double actualWeight,scalef;
	double puIdweight_M,puIdweight_T,puIdweight_L;
	tree->SetBranchAddress("lep",&lep);
	tree->SetBranchAddress("Mjj",&Mjj);
	tree->SetBranchAddress("scalef",&scalef);
	tree->SetBranchAddress("actualWeight",&actualWeight);
	tree->SetBranchAddress("puIdweight_L",&puIdweight_L);
	tree->SetBranchAddress("puIdweight_M",&puIdweight_M);
	tree->SetBranchAddress("puIdweight_T",&puIdweight_T);
        double lumi;
	if(tag.Contains("16")) lumi=35.9;
	if(tag.Contains("17")) lumi=41.52;
	if(tag.Contains("18")) lumi=59.7;
	if(sample.Contains("plj")) lumi=1;
	if(sample.Contains("Muon") || sample.Contains("Ele")){lumi=1;}
	for(int i=0;i<tree->GetEntries();i++){
		tree->GetEntry(i);
		if ( ! tformula1->EvalInstance() ) continue;
//		if(Mjj>800) Mjj=799;
                if(sample.Contains("Muon")&& lep==11) continue;
                if(sample.Contains("Ele")&& lep==13) continue;
		h1->Fill(Mjj,actualWeight*lumi); 
	}
        cout<<sample<<" "<<h1->GetEntries()<<"; "<<h1->GetSum()<<endl;
	for(int i=0;i<h1->GetNbinsX();i++){
                h1_clone->SetBinContent(i+1,h1->GetBinContent(i+1));
                h1_clone->SetBinError(i+1,h1->GetBinError(i+1));
                h1_clone->GetXaxis()->SetBinLabel(i+1,name[i]);
                if(sample.Contains("Muon") || sample.Contains("Ele"))cout<<sample<<" "<<tag<<" "<<h1->GetBinLowEdge(i+1)<<","<<h1->GetBinLowEdge(i+1)+h1->GetBinWidth(i+1)<<", the yields "<<h1->GetBinContent(i+1)<<endl;
	}
	return h1_clone;
}
int Find_mjj(){
	TString LEPmu = "(drll>0.3 && lep==13 && (HLT_Mu1>0 || HLT_Mu2>0 || HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet;
	TString Pi=Form("%f",pi);
	TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && detajj<2.5 && ZGmass>100)";
	vector<TString> tags={"16","17","18"};
	TString dir1;
	dir1="/home/pku/anying/cms/PKU-Cluster/CombineDraw/ScalSeq/output-slimmed-rootfiles/optimal_";
	vector<TString> names={"ZA-EWK","ST","VV","TTA","ZA","plj"};
	TString Reco;
	const int kk=tags.size();
	TH1D*h_ST[kk];TH1D*h_VV[kk];TH1D*h_TTA[kk];
	TH1D*h_plj[kk];TH1D*h_ZA[kk];TH1D*h_EWK[kk];
        TH1D*h_Muon[kk];TH1D*h_Ele[kk];
	for(int k=0;k<tags.size();k++){
		if(tags[k].Contains("16")==1){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		if(tags[k].Contains("17")==1){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
		}
		else if(tags[k].Contains("18")==1){
			jet = "( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
		}
		Reco= "((("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
		cout<<tags[k]<<" "<<jet<<endl;
//		if(tags[k].Contains("17")==1) continue;
		TCanvas*c1=new TCanvas("c1","",900,600);
		h_ST[k]=run("ST",Reco,tags[k]);
		h_VV[k]=run("VV",Reco,tags[k]);
		h_TTA[k]=run("TTA",Reco,tags[k]);
		h_ZA[k]=run("ZA",Reco,tags[k]);
		h_plj[k]=run("plj",Reco,tags[k]);
		h_EWK[k]=run("ZA-EWK",Reco,tags[k]);
		h_Muon[k]=run("Muon",Reco,tags[k]);
		h_Ele[k]=run("Ele",Reco,tags[k]);
		TH1D*h1=(TH1D*) h_Muon[k]->Clone();
		h1->Add(h_Ele[k]);
		h_plj[k]->SetFillColor(kYellow-7);
		h_plj[k]->SetMarkerColor(kYellow-7);
		h_plj[k]->SetLineColor(kYellow-7);
		h_EWK[k]->SetFillColor(kRed-7);
		h_EWK[k]->SetMarkerColor(kRed-7);
		h_EWK[k]->SetLineColor(kRed-7);
		h_ZA[k]->SetFillColor(kBlue-6);
		h_ZA[k]->SetMarkerColor(kBlue-6);
		h_ZA[k]->SetLineColor(kBlue-6);
		h_TTA[k]->SetFillColor(kCyan);
		h_TTA[k]->SetMarkerColor(kCyan);
		h_TTA[k]->SetLineColor(kCyan);
		h_ST[k]->SetFillColor(kGreen+2);
		h_ST[k]->SetMarkerColor(kGreen+2);
		h_ST[k]->SetLineColor(kGreen+2);
		h_VV[k]->SetFillColor(40);
		h_VV[k]->SetMarkerColor(40);
		h_VV[k]->SetLineColor(40);
		THStack* hs = new THStack("hs", "");
		hs->Add(h_ST[k]);
		hs->Add(h_TTA[k]);
		hs->Add(h_VV[k]);
		hs->Add(h_plj[k]);
		hs->Add(h_ZA[k]);
		hs->Add(h_EWK[k]);

		double max=hs->GetMaximum();
		hs->SetMaximum(max*2.5);
		hs->Draw("hist");
		h1->SetMarkerStyle(20);
		h1->SetLineColor(1);
		h1->Draw("PE same");
		TLegend* leg = new TLegend(0.62, 0.6, 0.85, 0.87);
		TLegend* leg1 = new TLegend(0.4, 0.6, 0.62, 0.87);
		leg->SetTextSize(0.04);
		leg1->SetFillColor(kWhite);
		leg->SetFillColor(kWhite);
		leg1->SetLineColor(0);
		leg->SetLineColor(0);
		leg1->SetTextSize(0.04);
		leg->AddEntry(h_EWK[k],Form("EWK[%.1f] ",h_EWK[k]->GetSum()) );
		leg->AddEntry(h_ZA[k], Form("Z#gamma [%.1f] ",h_ZA[k]->GetSum()));
		leg->AddEntry(h_plj[k], Form("non-prompt [%.1f] ",h_plj[k]->GetSum() ),"f");
		leg1->AddEntry(h_VV[k], Form("VV  [%.1f] ", h_VV[k]->GetSum() ) );
		leg1->AddEntry(h_TTA[k], Form("TT#gamma [%.1f] ",h_TTA[k]->GetSum()) );
		leg1->AddEntry(h_ST[k], Form("ST  [%.1f] ",h_ST[k]->GetSum() ) );
		leg->Draw();
		leg1->Draw();
		c1->SaveAs("hist_"+tags[k]+".pdf");
		TFile*f1=new TFile("./root/hist_"+tags[k]+".root","recreate");
		h_ST[k]->Write();
		h_TTA[k]->Write();
		h_VV[k]->Write();
		h_plj[k]->Write();
		h_ZA[k]->Write();
		h_EWK[k]->Write();
		h1->Write();
                hs->Write();
                f1->Close();
	}
	return 0;
}
