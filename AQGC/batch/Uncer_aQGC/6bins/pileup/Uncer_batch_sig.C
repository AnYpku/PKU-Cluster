#define num 3
void run(TString cut1,TString tag,TString sample){
     vector<double> ZGbin = {150,400,600,800, 1000,1200, 2e4};
     TString dir="../../../rootfiles/";
     TFile*file;
     file=new TFile(dir+"optimal_"+sample+tag+".root");
     TTree*tree=(TTree*)file->Get("outtree");     
     //tree->SetBranchStatus("*",0);
     Double_t scalef,pileupWeight,prefWeight,prefWeightUp,prefWeightDown,puIdweight_T;
     Double_t ZGmass,jet1eta,jet2eta;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
     double muon_hlt_scale,ele_hlt_scale;
     double weight;int lep;Double_t npT;
     tree->SetBranchAddress("ZGmass",&ZGmass);
     tree->SetBranchAddress("npT",&npT);
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("puIdweight_T",&puIdweight_T);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("prefWeight",&prefWeight);
     tree->SetBranchAddress("prefWeightUp",&prefWeightUp);
     tree->SetBranchAddress("prefWeightDown",&prefWeightDown);
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

     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
     TString dir1="/home/pku/anying/cms/PKU-Cluster/RunII20"+tag+"/step1_add_weight/pu_calc/";
     TFile*fpu_up=new TFile(dir1+"puweight_up.root");
     TFile*fpu_dn=new TFile(dir1+"puweight_down.root");
     TH1D*h_up=(TH1D*)fpu_up->Get("h2");
     TH1D*h_dn=(TH1D*)fpu_dn->Get("h2");
     double pileupWeight_up,pileupWeight_down;

     double actualWeight[num];
     TH1D*th1[num];
     TString th1name[num];
     for(Int_t i=0;i<num;i++){
	     th1name[i]=Form("hist_%d",i);
	     th1[i] = new TH1D(th1name[i],th1name[i],ZGbin.size()-1,&ZGbin[0]);
	     th1[i]->Sumw2(); 
     }      
     for(int k=0;k<tree->GetEntries();k++){
	     tree->GetEntry(k);
	     double detajj=fabs(jet1eta-jet2eta);
	     int p=0;
	     pileupWeight_up=h_up->GetBinContent(h_up->GetXaxis()->FindBin(npT));
	     pileupWeight_down=h_dn->GetBinContent(h_dn->GetXaxis()->FindBin(npT));
	     if(tag.Contains("17")==0) puIdweight_T=1;
	     if(tag.Contains("18")) prefWeight=1;
	     if(lep==11)
		     weight=scalef*prefWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale*ele_hlt_scale*puIdweight_T;
	     if(lep==13)
		     weight=scalef*prefWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale*muon_hlt_scale*puIdweight_T;
	     if (  tformula->EvalInstance() ){
		     for(Int_t i=0;i<(num);i++){
			     if(p==0)actualWeight[p]=weight*pileupWeight;
			     if(p==1)actualWeight[p]=weight*pileupWeight_up;
			     if(p==2)actualWeight[p]=weight*pileupWeight_down;
			     th1[p]->Fill(ZGmass,actualWeight[p]);//0~1, 2.5~4.5 and 500~800
			     p++;
		     }
	     }
     }
     TFile*fout;
     fout= new TFile("./root/hist_"+sample+"_pileup_"+tag+".root","recreate");
     fout->cd();
     for(Int_t i=0;i<num;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Uncer_batch_sig(){
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>120 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString dr = "(drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	vector<TString> tag={"16","17","18"};
//	vector<TString> tag={"18"};
	vector<TString> sample={"ZA","ZA-EWK","others"};
	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
		}
		else{
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		if(tag[i].Contains("17")==0) continue;
		TString SignalRegion = "( Mjj>500 && detajj>2.5)";
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString cut2 ="(("+Reco+"))";
		cout<<tag[i]<<" "<<jet<<endl;
		for(int n=0;n<sample.size();n++){
			run(cut2,tag[i],sample[n]);
		}
	}
	return 1;
}
