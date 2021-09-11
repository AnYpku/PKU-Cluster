#define num 3
#define pi 3.1415926
TH1D* run( TString sample,TString tag,TString vec_branchname,vector<double> bins,TString cut1){
     TString dir1;
     dir1="/home/pku/anying/cms/PKU-Cluster/CombineDraw/ScalSeq/output-slimmed-rootfiles/optimal_";
     TFile*file;
     if(sample.Contains("EWK"))
	     file=new TFile(dir1+"ZA-"+sample+tag+".root");
     else    file=new TFile(dir1+"ZA_"+sample+tag+".root");
     TTree*tree=(TTree*)file->Get("outtree");     
     map<TString, double> variables;
     double jet1eta,jet2eta;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,pileupWeight,prefWeight,muon_hlt_scale,ele_hlt_scale,puIdweight_T,puIdweight_M,puIdweight_L;
     Double_t scalef;
     int lep;
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     tree->SetBranchAddress("pileupWeight", &pileupWeight);
     tree->SetBranchAddress("prefWeight", &prefWeight);
     tree->SetBranchAddress("photon_id_scale", &photon_id_scale);
     tree->SetBranchAddress("photon_veto_scale", &photon_veto_scale);
     tree->SetBranchAddress("ele1_id_scale",   &ele1_id_scale);
     tree->SetBranchAddress("ele2_id_scale",   &ele2_id_scale);
     tree->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale);
     tree->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale);
     tree->SetBranchAddress("muon1_id_scale",   &muon1_id_scale);
     tree->SetBranchAddress("muon2_id_scale",   &muon2_id_scale);
     tree->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale);
     tree->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale);
     tree->SetBranchAddress("muon_hlt_scale", &muon_hlt_scale);
     tree->SetBranchAddress("ele_hlt_scale", &ele_hlt_scale);
     tree->SetBranchAddress("puIdweight_T", &puIdweight_T);
     tree->SetBranchAddress("puIdweight_M", &puIdweight_M);
     tree->SetBranchAddress("puIdweight_L", &puIdweight_L);
     tree->SetBranchAddress(vec_branchname, &variables[vec_branchname]);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
//     TH1D*th1[kk];
     TString th1name;
     th1name=vec_branchname+"_"+sample;
     TH1D* th1;
     th1= new TH1D(th1name,th1name,bins.size()-1,&bins[0]);
     th1->Sumw2(); 
     double actualWeight,puIdweight;
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
	     double detajj=fabs(jet1eta-jet2eta);
             if(tag.Contains("18"))  {prefWeight=1;puIdweight=puIdweight_L;}
	     if(tag.Contains("17")) puIdweight=puIdweight_T;
	     if(tag.Contains("16")) puIdweight=puIdweight_M;
             actualWeight=scalef*pileupWeight*photon_id_scale*photon_veto_scale*puIdweight*prefWeight;
	     if(lep==11)
		     actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
	     if(lep==13)
		     actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;
	     if (  !tformula->EvalInstance() ) continue;
	     th1->Fill(variables[vec_branchname],actualWeight);
     }
     return th1;
}
int Unfold_batch_bkg(){
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	vector<TString> tag={"16","17","18"};
	vector<TString> sample={"EWK","interf"};
        vector<TString> recovars={"Mjj"};
        vector<vector<double>> bins;
        vector<double> MjjBins={500,600,700,800};
        bins.push_back(MjjBins);
	const int kk=sample.size();
	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("16")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else if(tag[i].Contains("17")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
		}
		else if(tag[i].Contains("18")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
		}
		TString SignalRegion = "(Mjj>500 && detajj<2.5 && ZGmass>100)";
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		for(int k=0;k<recovars.size();k++){
			TH1D*h1[kk];
			TFile*f1=new TFile("hist_"+recovars[k]+tag[i]+".root","recreate");
			for(int j=0;j<kk;j++){
				cout<<sample[j]<<" "<<tag[i]<<" "<<recovars[k]<<endl;
				h1[j]=run(sample[j],tag[i],recovars[k],bins[k],Reco);
				f1->cd();
				h1[j]->Write();
			}
			f1->Close();
		}
	}
	return 1;
}
