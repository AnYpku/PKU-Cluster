#define num 103
void run( TFile*file,vector<TString> vec_branchname,vector<vector<double>> bins,TString cut1,TString tag){
     const int kk = vec_branchname.size();
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
//     tree->SetBranchStatus("*",0);
     map<TString, double> variables;
     double Mjj,deltaetajj,gendetajj;
     for(int i=0;i<vec_branchname.size();i++){
             tree->SetBranchStatus(vec_branchname[i],1);
	     tree->SetBranchAddress(vec_branchname[i], &variables[vec_branchname[i]]);
     }
     Double_t scalef,pileupWeight,pweight[703];
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("pweight",pweight);
     tree->SetBranchAddress("Mjj",&Mjj);
     tree->SetBranchAddress("deltaetajj",&deltaetajj);
     tree->SetBranchAddress("gendetajj",&gendetajj);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
     double actualWeight[num];
     TH1D*th1[num][kk];
     TH2D*th2[num][kk];
     Double_t mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TString th1name[num][kk];
     for(Int_t i=0;i<num;i++){
             for(int j=0;j<kk;j++){
		     th1name[i][j]=vec_branchname[j]+Form("_%d",i);
		     if(vec_branchname[j].Contains("Mjj")==0)
			     th1[i][j] = new TH1D(th1name[i][j],th1name[i][j],bins[j].size()-1,&bins[j][0]);
		     else th2[i][j] = new TH2D(th1name[i][j],th1name[i][j],3,mjj_bins,3,detajj_bins);
	     }
     }      
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
	     int p=0;
	     if (  tformula->EvalInstance() ){
		     int init;
		     if(tag.Contains("16"))
			     init=9;
		     else    init=45;
		     for(Int_t i=init;i<(num+init);i++){
//			     actualWeight[p]=scalef*pweight[i]*pileupWeight;
			     actualWeight[p]=/*scalef*/pweight[i];//*pileupWeight;
			     for(int j=0;j<kk;j++){
				     if(vec_branchname[j].Contains("Mjj")==0)
					     th1[p][j]->Fill(variables[vec_branchname[j]],actualWeight[p]);
				     else
					     th2[p][j]->Fill(variables[vec_branchname[j]],gendetajj,actualWeight[p]);
			     }
			     p++;
		     }
	     }
     }
     TFile*fout[kk];
     for(int j=0;j<kk;j++){
	    if(vec_branchname[j].Contains("Mjj")==0) fout[j]= new TFile("unfold_"+vec_branchname[j]+"_ewk_pdf"+tag+".root","recreate");
	    else fout[j]= new TFile("./2droot/unfold_"+vec_branchname[j]+"_ewk_pdf"+tag+".root","recreate");
     }
     for(int j=0;j<kk;j++){
	     fout[j]->cd();
	     for(Int_t i=0;i<num;i++){
		     if(vec_branchname[j].Contains("Mjj")==0)
			     th1[i][j]->Write();
		     else
			     th2[i][j]->Write();
	     }
	     fout[j]->Close();
     }
}
int Unfold_uncer_batch_sig(){
     TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
     TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110 )";
     TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ) )";
     TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
     TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
     TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";
     TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;

     TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
     TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
     TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
     TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
     TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
     TString SignalRegion = "(Mjj>500 && deltaetajj>2.5 && Mva>100)";
     TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
//     TString cut1 ="(("+Reco+")&&("+Gen+"))";
     TString cut1 ="("+Gen+")";
     TString cut2 ="(("+Reco+")&& !("+Gen+"))";
     vector<vector<double>> bins;
     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     vector<double> MvaBins={100,150,1000};
     vector<double> MjjBins={500,1000,1500,2000};
     bins.push_back(ptlepBins);
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
     bins.push_back(MjjBins);

     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
     vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
     TString dir1="/home/pku/anying/cms/rootfiles/2016/";
     TString dir2="/home/pku/anying/cms/rootfiles/2017/";
     TString dir3="/home/pku/anying/cms/rootfiles/2018/";
     TFile*file1=new TFile(dir1+"unfold_GenCutla-outZA-EWK16.root");
     TFile*file2=new TFile(dir2+"unfold_GenCutla-outZA-EWK17.root");
     TFile*file3=new TFile(dir3+"unfold_GenCutla-outZA-EWK18.root");
//     for(int i=0;i<bins.size();i++){
	     run(file1,genvars, bins,cut1,"16");
	     run(file2,genvars, bins,cut1,"17");
	     run(file3,genvars, bins,cut1,"18");
     return 1;
}
