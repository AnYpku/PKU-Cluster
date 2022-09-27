void run(TString channel, TString tag, TString sample,TString cut,vector<double>ZGbin){
	TFile*file;
	if(sample.Contains("plj")==0)file=new TFile("./rootfiles/optimal_"+sample+tag+".root");
	else file=new TFile("./rootfiles/optimal_"+sample+tag+"_weight.root");
	TTree*tree=(TTree*)file->Get("outtree");
	TString cut2;
	if(channel.Contains("ele")) cut2="(lep==11)";
        else if(channel.Contains("mu")) cut2="(lep==13)"; 
        cut="("+cut+"&&("+cut2+"))";
	TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
        TString hname="hist";
        TH1D*h1=new TH1D(hname,hname,ZGbin.size()-1,&ZGbin[0]);
	TString lumi;
	if(tag.Contains("16"))lumi=Form("%f",35.86);
	if(tag.Contains("17"))lumi=Form("%f",41.52);
	if(tag.Contains("18"))lumi=Form("%f",59.7);
        if(sample.Contains("plj")||sample.Contains("Muon")||sample.Contains("Ele")) lumi=Form("%f",1.0);
	cout<<sample<<" "<<channel<<" "<<tag<<" "<< lumi;
	tree->Draw("ZGmass>>"+hname,cut+"*actualWeight*"+lumi,"goff");
	cout<<" "<<h1->GetSumOfWeights()<<endl;
        int nbins=h1->GetNbinsX();
        h1->SetBinContent(nbins,h1->GetBinContent(nbins)+h1->GetBinContent(nbins+1)); 
	h1->SetBinError(nbins,sqrt(h1->GetBinError(nbins)*h1->GetBinError(nbins)+h1->GetBinError(nbins+1)*h1->GetBinError(nbins+1)));
        TFile*fout=new TFile("./hist_root/referee/hist_"+sample+tag+channel+".root","recreate");
	fout->cd();
	h1->Write();
	fout->Close();
	file->Close();
}
int Build_histo_aQGC(){
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && (HLT_Mu1>0||HLT_Mu2>0||HLT_Mu3>0))";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110 && (HLT_Ele1>0 || HLT_Ele2>0))";
	TString photon = "(photonet>120 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )  )";
	TString jet;
	TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && zepp<2.4 && delta_phi>1.9 )";
	vector<TString> tag={"16","17","18"};
	vector<TString> channel={"ele","mu"};
//	vector<TString> sample={"plj","ZA","ZA-EWK","others","Muon","Ele"};
//	vector<TString> sample={"ZA_interf"};
	vector<TString> sample={"Muon","Ele"};
	vector<double> ZGbin={150,400,600,800,1000,1200,2e4};
	TString Reco;
	for(int k=0;k<tag.size();k++){
                if(tag[k].Contains("16")){
                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
                }
                else if(tag[k].Contains("17")){
                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
                }
                else if(tag[k].Contains("18")){
                        jet = "( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
                }
		Reco= "(("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
//		if(tag[k].Contains("16")==0) continue;
		for(int i=0;i<sample.size();i++){
			for(int j=0;j<channel.size();j++){
				if(sample[i].Contains("Ele")&&channel[j].Contains("mu"))
					continue;
				if(sample[i].Contains("Muon")&&channel[j].Contains("ele"))
					continue;
				run(channel[j], tag[k], sample[i],Reco,ZGbin);
			}
		}
	}

	return 0;
} 
