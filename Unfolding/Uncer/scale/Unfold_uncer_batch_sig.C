#define num 3
void run( TFile*file,TString vec_branchname,TString reco,vector<double> bins,TString cut1,TString tag){
     const int kk=bins.size()-1;
     TTree*tree=(TTree*)file->Get("demo");     
//     tree->SetBranchStatus("*",0);
     map<TString, double> variables;
     tree->SetBranchStatus(vec_branchname,1);
     tree->SetBranchAddress(vec_branchname, &variables[vec_branchname]);
     tree->SetBranchAddress(reco, &variables[reco]);
     Double_t scalef,pileupWeight,pweight[703];
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("pweight",pweight);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
     double actualWeight[num];
     TH1D*th1[num][kk];
     TString th1name[num][kk];
     for(Int_t j=0;j<kk;j++){//Loop the binning cuts
	     for(Int_t i=0;i<num;i++){
		     th1name[i][j]=vec_branchname+Form("_scale%d_",i)+Form("recobin%d",j+1);
		     th1[i][j] = new TH1D(th1name[i][j],th1name[i][j],bins.size()-1,&bins[0]);
		     th1[i][j]->Sumw2(); 
	     }      
     }
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
	     if (  tformula->EvalInstance() ){
		     int p=0;
		     for(Int_t i=0;i<(num);i++){//Loop scale variation
			     int k;
			     if(tag.Contains("16")==0)
				     k=15*i;
			     else    k=i;
			     actualWeight[p]=scalef*pweight[k]*pileupWeight;
			     for(Int_t j=0;j<kk;j++){
				     if(j<kk-1 && variables[reco]>bins[j]&&variables[reco]<bins[j+1]){
					     th1[p][j]->Fill(variables[vec_branchname],actualWeight[p]);
				     }
				     else if(j==kk-1 && variables[reco]>bins[j]){
					     th1[p][j]->Fill(variables[vec_branchname],actualWeight[p]);
				     }
			     }
			     p++;
		     }
	     }
     }
     TFile*fout[kk];
     for(int j=0;j<kk;j++){
	    fout[j]= new TFile("./sig_root/unfold_"+vec_branchname+Form("_recobin%d",j+1)+"_ewk_scale"+tag+".root","recreate");
     }
     for(int j=0;j<kk;j++){
	     fout[j]->cd();
	     for(Int_t i=0;i<num;i++){
		     th1[i][j]->Write();
	     }
	     fout[j]->Close();
     }
}
int Unfold_uncer_batch_sig(){
     TString GenLEPmu  = "genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110";
     TString GenLEPele = "genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110";
     TString GenPhoton = "genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) )";
     TString GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
     TString GenDr = "gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5";
     TString GenSignalRegion = "genMjj >500 && gendetajj>2.5";
     TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;

     TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
     TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
     TString photon = "photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
     TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
     TString dr = "drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
     TString SignalRegion = "Mjj>500 && deltaetajj>2.5 && Mva>100";
     TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
     TString cut1 ="(("+Reco+")&&("+Gen+"))";
     TString cut2 ="(("+Reco+")&& !("+Gen+"))";
     vector<vector<double>> bins;
     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     vector<double> MvaBins={100,150,1000};
     vector<double> MjjBins={500,1000,1500,2000};
//     bins.push_back(ptlepBins);
//     bins.push_back(photonEtBins);
//     bins.push_back(jetptBins);
     bins.push_back(MvaBins);
     bins.push_back(MjjBins);
     
//     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt"};//,"genZGmass","genMjj"};
//     vector<TString> recovars={"ptlep1","photonet","jet1pt"};//,"Mva","Mjj"};
     vector<TString> genvars={"genZGmass","genMjj"};
     vector<TString> recovars={"Mva","Mjj"};
     TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/";     
     TFile*file1=new TFile(dir+"unfold_16outZA-EWK.root");
     TFile*file2=new TFile(dir+"unfold_17outZA-EWK-pweight.root");
     TFile*file3=new TFile(dir+"unfold_18outZA-EWK-pweight.root");
     for(int j=0;j<genvars.size();j++){
	     run(file1,genvars[j], recovars[j], bins[j],cut1,"16");
	     run(file2,genvars[j], recovars[j], bins[j],cut1,"17");
	     run(file3,genvars[j], recovars[j], bins[j],cut1,"18");
     }
     return 1;
}
