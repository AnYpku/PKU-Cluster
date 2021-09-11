#define num 3
#define pi 3.1415926
TH1D* run( TString sample,TString tag,TString vec_branchname,vector<double> bins,TString cut1){
     const int kk = bins.size();
     TString dir1;
     dir1="/home/pku/anying/cms/rootfiles/20"+tag+"/";
     TFile*file=new TFile(dir1+"cutla-outplj"+tag+"_weight"+sample+".root");
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
     map<TString, double> variables;
     tree->SetBranchStatus(vec_branchname,1);
     tree->SetBranchAddress(vec_branchname, &variables[vec_branchname]);
     Double_t scalef,pileupWeight;
     tree->SetBranchAddress("scalef",&scalef);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
//   TH1D*th1[kk];
     TString th1name;
     th1name=vec_branchname+sample;
     TH1D* th1;
     th1 = new TH1D(th1name,th1name,bins.size()-1,&bins[0]);
     th1->Sumw2(); 
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
	     if (  tformula->EvalInstance() ){
		     th1->Fill(variables[vec_branchname],scalef);
	     }
     }
     return th1;
}
int Unfold_uncer_batch_bkg(){
     TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4)";
     TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5)";
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
     vector<double> MjjBins={500,1000,1500,2000};
     bins.push_back(ptlepBins);
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
//     bins.push_back(MjjBins);

     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt"};
     vector<TString> recovars={"ptlep1","photonet","jet1pt"};
     vector<TString> tag={"16","17","18"};
     const int kk=genvars.size();
     TH1D*hist[3][kk];TH1D*hist_up[3][kk];TH1D*hist_down[3][kk];//hist[year][vars]
     for(int j=0;j<kk;j++){
	     for(int i=0;i<tag.size();i++){
//		     if(tag[i].Contains("17")==0) continue;
		     if(tag[i].Contains("16")){
			     jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		     }
		     else if(tag[i].Contains("17")){
			     jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
		     }
		     else if(tag[i].Contains("18")){
			     jet = "( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
		     }
		     TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		     TString cut1 ="("+Reco+")";
		     TString cut2 ="(("+Reco+")&& !("+Gen+"))";
		     hist[i][j]=run("",tag[i],recovars[j], bins[j],cut1);
		     hist_up[i][j]=run("_up",tag[i],recovars[j], bins[j],cut1);
		     hist_down[i][j]=run("_down",tag[i],recovars[j], bins[j],cut1);
	     }
     }
     //     cout<<hist[0][0]->GetBinContent(1);
     TFile*fout[3][kk];
     for(int j=0;j<kk;j++){
	     for(int i=0;i<3;i++){
		     fout[i][j]= new TFile("unfold_"+recovars[j]+"_plj"+tag[i]+".root","recreate");
		     cout<<hist[i][j]->GetBinContent(1)<<endl;
		     fout[i][j]->cd();
		     hist[i][j]->Write();
		     hist_up[i][j]->Write();
		     hist_down[i][j]->Write();
		     fout[i][j]->Close();
	     }//fout[year][vars]
     }
     return 1;
}
