void run(TFile*file,TString var1, TString sample, vector<double> bins,TString cut1,TString tag,int num){
	TTree*tree=(TTree*)file->Get("ZPKUCandidates");
     double actualWeight[num];
     TH1D*th1[num];
     TH2D*th2[num];
     TString th1name[num];
     Double_t mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     for(Int_t i=0;i<num;i++){
	     th1name[i]=var1+Form("_%d",i);
	     if(var1.Contains("Mjj")==0)th1[i] = new TH1D(th1name[i],th1name[i],bins.size()-1,&bins[0]);
	     else th2[i] = new TH2D(th1name[i],th1name[i],3,mjj_bins,3,detajj_bins);
     }      
     int p=0;
     int first;
     if(sample.Contains("ewk")) first=0;//16 or 17 or 18 ew sample
     else if(sample.Contains("ewk")==0 && tag.Contains("16"))first=104;//16 qcd sample
     else if(sample.Contains("ewk")==0 && tag.Contains("16")==0)first=0;//17 or 18 qcd sample 
     for(Int_t i=first;i<num+first;i++){
	     TString index;
	     if(sample.Contains("ewk")){
		     if(tag.Contains("16"))
			     index=Form("%i",i);
		     else
			     index=Form("%i",15*i);
	     }
	     else{
		     index=Form("%i",i);
	     }
	     if(var1.Contains("Mjj")==0) tree->Draw(var1+">>"+th1name[p],cut1+"*pweight["+index+"]","goff");
	     else tree->Draw("gendetajj:genMjj>>"+th1name[p],cut1+"*pweight["+index+"]","goff");
	     p++;
     }
     TFile*fout=new TFile(var1+"_unfold_"+sample+"_scale"+tag+".root","recreate");
     for(Int_t i=0;i<num;i++){
	     if(var1.Contains("Mjj")==0) th1[i]->Write();
	     else th2[i]->Write();
     }
     fout->Close();
}
int Unfold_uncer(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
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
	TString SignalRegion = "Mjj>500 && deltaetajj>2.5 && Mva>100";
	TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
	TString cut1 ="("+Gen+")";
	//     TString cut1 ="(("+Reco+")&&("+Gen+"))";
	TString cut2 ="(("+Reco+")&& !("+Gen+"))";

	vector<double> ptlepBins={20,80,120,200,400};
	vector<double> photonEtBins={20,80,120,200,400};
	vector<double> jetptBins={30,150,250,350,800};
	vector<double> MvaBins={100,150,1000};
	vector<double> MjjBins={500,2000};
	vector<vector<double>> bins;
	bins.push_back(MjjBins);
	bins.push_back(ptlepBins);
	bins.push_back(photonEtBins);
	bins.push_back(jetptBins);

	TString dir1="/home/pku/anying/cms/rootfiles/2016/";
	TString dir2="/home/pku/anying/cms/rootfiles/2017/";
	TString dir3="/home/pku/anying/cms/rootfiles/2018/";
	TFile*file1=new TFile(dir1+"unfold_GenCutla-ZA-EWK16.root");
	TFile*file2=new TFile(dir2+"unfold_GenCutla-ZA-EWK17.root");
	TFile*file3=new TFile(dir3+"unfold_GenCutla-ZA-EWK18.root");
	TFile*f1=new TFile(dir1+"unfold_GenCutla-ZA16.root");
	TFile*f2=new TFile(dir2+"unfold_GenCutla-ZA17.root");
	TFile*f3=new TFile(dir3+"unfold_GenCutla-ZA18.root");
	vector<TString> genvars={"genMjj","genlep1pt","genphotonet","genjet1pt"};
	vector<TString> recovars={"Mjj","ptlep1","photonet","jet1pt"};

	for(int i=0;i<genvars.size();i++){
//		run(file1,genvars[i],"ewk", bins[i],cut1,"16",3);
		run(file2,genvars[i],"ewk", bins[i],cut1,"17",3);
//		run(file3,genvars[i],"ewk", bins[i],cut1,"18",3);
//		run(f1,genvars[i],"qcd", bins[i],cut1,"16",9);
		run(f2,genvars[i],"qcd", bins[i],cut1,"17",9);
//		run(f3,genvars[i],"qcd", bins[i],cut1,"18",9);
	}
	return 1;
}
