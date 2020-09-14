#define num 3
void run(TFile*file,TString var1, TString sample, vector<double> bins,TString cut1,TString tag){
	TTree*tree=(TTree*)file->Get("demo");
     double actualWeight[num];
     TH1D*th1[num];
     TString th1name[num];
     for(Int_t i=0;i<num;i++){
	     th1name[i]=var1+Form("_%d",i);
	     th1[i] = new TH1D(th1name[i],th1name[i],bins.size()-1,&bins[0]);
	     th1[i]->Sumw2(); 
     }      
     int p=0;
     for(Int_t i=0;i<num;i++){
//	     actualWeight[p]=scalef*pweight[i]*pileupWeight;
	     TString index;
             if(tag.Contains("16"))
		     index=Form("%i",i);
	     else
		     index=Form("%i",15*i);
//             tree->Draw(var1+">>"+th1name[p],cut1+"*pweight["+index+"]","goff");
             tree->Draw(var1+">>"+th1name[i],cut1+"*scalef*pweight["+index+"]","goff");
	     p++;
     }
     TFile*fout=new TFile(var1+"_unfold_"+sample+"_scale"+tag+".root","recreate");
     for(Int_t i=0;i<num;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Unfold_uncer(){
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

     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     vector<double> MvaBins={100,150,1000};
     vector<double> MjjBins={500,1000,1500,2000};
     vector<vector<double>> bins;
     bins.push_back(ptlepBins);
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
     bins.push_back(MvaBins);
     bins.push_back(MjjBins);

     TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/";
     TFile*file1=new TFile(dir+"unfold_16outZA-EWK.root");
     TFile*file2=new TFile(dir+"unfold_17outZA-EWK-pweight.root");
     TFile*file3=new TFile(dir+"unfold_18outZA-EWK-pweight.root");
     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt"};//,"genZGmass","genMjj"};
     vector<TString> recovars={"ptlep1","photonet","jet1pt"};//,"Mva","Mjj"};

//     run(file1,"genlep1pt","ewk",ptlepBins ,cut1,"16");
     for(int i=0;i<genvars.size();i++){
	     run(file1,genvars[i],"ewk", bins[i],cut1,"16");
	     run(file2,genvars[i],"ewk", bins[i],cut1,"17");
	     run(file3,genvars[i],"ewk", bins[i],cut1,"18");
     }
     return 1;
}
