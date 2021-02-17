#define num 3
#define pi 3.1415926
void run(vector<TString> vec_branchname,vector<vector<double>> bins,TString cut1,TString tag,TString sample){
     const int kk = vec_branchname.size();
     TString dir;
     dir="/home/pku/anying/cms/rootfiles/20"+tag+"/";
     TFile*file=new TFile(dir+"cutla-out"+sample+tag+".root");
     TString name=file->GetName();
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
//     tree->SetBranchStatus("*",0);
     map<TString, double> variables;
     for(int i=0;i<vec_branchname.size();i++){
             tree->SetBranchStatus(vec_branchname[i],1);
	     tree->SetBranchAddress(vec_branchname[i], &variables[vec_branchname[i]]);
     }
     Double_t scalef,pileupWeight,pweight[703],prefWeight,prefWeightUp,prefWeightDown;
     double Mjj,deltaetajj;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,muon_hlt_scale,ele_hlt_scale,puIdweight_M;
     int lep; double npT;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("npT",&npT);
     tree->SetBranchAddress("deltaetajj",&deltaetajj);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("pweight",pweight);
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
     tree->SetBranchAddress("puIdweight_M", &puIdweight_M);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
     double actualWeight[num],weight;
     TH1D*th1[num][kk];
     TString th1name[num][kk];
     Double_t mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     for(Int_t i=0;i<num;i++){
	     for(int j=0;j<kk;j++){
		     th1name[i][j]=vec_branchname[j]+Form("_%d",i);
		     if(vec_branchname[j].Contains("Mjj")==0)
			     th1[i][j] = new TH1D(th1name[i][j],th1name[i][j],bins[j].size()-1,&bins[j][0]);
		     else th1[i][j] = new TH1D(th1name[i][j],th1name[i][j],7,0,7);
	     }
     }      
     cout<<tag<<" "<<name<<endl;
     TString dir1="/home/pku/anying/cms/PKU-Cluster/RunII20"+tag+"/step1_add_weight/pu_calc/";
     TFile*fpu_up=new TFile(dir1+"puweight_up.root");
     TFile*fpu_dn=new TFile(dir1+"puweight_down.root");
     TH1D*h_up=(TH1D*)fpu_up->Get("h2");
     TH1D*h_dn=(TH1D*)fpu_dn->Get("h2");
     double pileupWeight_up,pileupWeight_down;
     for(int k=0;k<tree->GetEntries();k++){
	     tree->GetEntry(k);
	     int p=0;
             pileupWeight_up=h_up->GetBinContent(h_up->GetXaxis()->FindBin(npT));
             pileupWeight_down=h_dn->GetBinContent(h_dn->GetXaxis()->FindBin(npT));
             if(tag.Contains("17")==0) puIdweight_M=1;
             if(tag.Contains("18")==1) prefWeight=1;
	     weight=scalef*photon_id_scale*photon_veto_scale*puIdweight_M*prefWeight;
	     if(lep==11)
		     weight=weight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
	     if(lep==13)
		     weight=weight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;
             actualWeight[0]=weight*pileupWeight;
             actualWeight[1]=weight*pileupWeight_up;
             actualWeight[2]=weight*pileupWeight_down;
	     if (  tformula->EvalInstance() ){
		     for(Int_t i=0;i<(num);i++){
			     for(int j=0;j<kk;j++){
				     if(vec_branchname[j].Contains("Mjj")==0){
					     th1[p][j]->Fill(variables[vec_branchname[j]],actualWeight[p]);
				     }
				     else{
					     if(variables[vec_branchname[j]]>=500&&variables[vec_branchname[j]]<800&&deltaetajj>=2.5&&deltaetajj<4.5) 
						     th1[p][j]->Fill(0.5,actualWeight[p]);//0~1, 2.5~4.5 and 500~800
					     if(variables[vec_branchname[j]]>=800&&variables[vec_branchname[j]]<1200&&deltaetajj>=2.5&&deltaetajj<4.5)
						     th1[p][j]->Fill(1.5,actualWeight[p]);//1~2 2.5~4.5 and 800~1200
					     if(variables[vec_branchname[j]]>=1200&&deltaetajj>=2.5&&deltaetajj<4.5)
						     th1[p][j]->Fill(2.5,actualWeight[p]);//2~3 2.5~4.5 1200~2000
					     if(variables[vec_branchname[j]]>=500&&variables[vec_branchname[j]]<800&&deltaetajj>=4.5&&deltaetajj<6)
						     th1[p][j]->Fill(3.5,actualWeight[p]);//3~4 4.5~6 500~800 
					     if(variables[vec_branchname[j]]>=800&&variables[vec_branchname[j]]<1200&&deltaetajj>=4.5&&deltaetajj<6)
						     th1[p][j]->Fill(4.5,actualWeight[p]);//4~5 4.5~6 800~1200
					     if(variables[vec_branchname[j]]>=1200&&deltaetajj>=4.5&&deltaetajj<6)
						     th1[p][j]->Fill(5.5,actualWeight[p]);//5~6 6~infi 500~800
					     if(variables[vec_branchname[j]]>=500&&deltaetajj>=6)
						     th1[p][j]->Fill(6.5,actualWeight[p]);//6~7 6~infi 800~1200
				     }
			     }
			     p++;
		     }
	     }
     }
     TFile*fout[kk];
     for(int j=0;j<kk;j++){
	     fout[j]= new TFile("unfold_"+vec_branchname[j]+"_"+sample+"_pu"+tag+".root","recreate");
     }
     for(int j=0;j<kk;j++){
	     fout[j]->cd();
	     for(Int_t i=0;i<num;i++){
		     th1[i][j]->Write();
	     }
	     fout[j]->Close();
     }
     for(int j=0;j<kk;j++){
	     for(Int_t i=0;i<num;i++){
		     delete  th1[i][j];
	     }
     }
}
int Unfold_uncer_batch_bkg(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";
	TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && Mva>100)";
	vector<vector<double>> bins;
	vector<double> ptlepBins={20,80,120,200,400};
	vector<double> photonEtBins={20,80,120,200,400};
	vector<double> jetptBins={30,150,250,350,800};
	vector<double> MvaBins={100,150,1000};
	vector<double> MjjBins={500,800,1200,2000};
	bins.push_back(ptlepBins);
	bins.push_back(photonEtBins);
	bins.push_back(jetptBins);
	bins.push_back(MjjBins);

	TString dir[3];     
	TFile*file1[3];
	TFile*file2[3];

	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
//	vector<TString> genvars={"genMjj"};
//	vector<TString> recovars={"Mjj"};
	vector<TString> tag={"16","17","18"};
//	vector<TString> tag={"18"};
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else{
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString cut2 ="("+Reco+")";
		TString cut1 ="(("+Reco+")&& !("+Gen+"))";
//		if(tag[i].Contains("17")) continue;
		for(int k=0;k<sample.size();k++){
			run(recovars, bins,cut2,tag[i],sample[k]);
		}
	}
	return 1;
}
