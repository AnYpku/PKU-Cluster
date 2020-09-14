//#define num 9
#define pi 3.1415926
void run(TFile*file, vector<TString> vec_branchname,vector<vector<double>> bins,TString cut1,TString tag,int num){
     const int kk = vec_branchname.size();
     TString name=file->GetName();
     TTree*tree=(TTree*)file->Get("demo");     
//     tree->SetBranchStatus("*",0);
     map<TString, double> variables;
     for(int i=0;i<vec_branchname.size();i++){
             tree->SetBranchStatus(vec_branchname[i],1);
	     tree->SetBranchAddress(vec_branchname[i], &variables[vec_branchname[i]]);
     }
     Double_t scalef,pileupWeight,pweight[703];
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("pweight",pweight);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
     double actualWeight[num];
     TH1D*th1[num][kk];
     TString th1name[num][kk];
     for(Int_t i=0;i<num;i++){
             for(int j=0;j<kk;j++){
		     th1name[i][j]=vec_branchname[j]+Form("_%d",i);
		     th1[i][j] = new TH1D(th1name[i][j],th1name[i][j],bins[j].size()-1,&bins[j][0]);
		     th1[i][j]->Sumw2(); 
	     }
     }      
     bool flag=false;
     if(num==7) flag = true;
     int first;
     if(name.Contains("EWK")) first=0;//16 or 17 or 18 ew sample
     else if(name.Contains("EWK")==0 && tag.Contains("16"))first=104;//16 qcd sample
     else if(name.Contains("EWK")==0 && tag.Contains("16")==0)first=0;//17 or 18 qcd sample
    
     cout<<"enter the loop"<<endl;
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
	     int p=0;
	     if (  tformula->EvalInstance() ){
		     for(Int_t i=first;i<(num+first);i++){
			     if(name.Contains("EWK")==0 && tag.Contains("16")){
				     if( flag && (i==109 || i==111) ) continue;
				     if(p==0) actualWeight[p]=scalef*pweight[i]*pileupWeight;
				     else actualWeight[p]=scalef*pweight[i]*pileupWeight*2;
				     if(k%1000==0)cout<<p<<" "<<actualWeight[p]<<endl;
				     for(int j=0;j<kk;j++){
					     th1[p][j]->Fill(variables[vec_branchname[j]],actualWeight[p]);
				     }
			     }
			     else if(name.Contains("EWK")==0 && tag.Contains("16")==0){
				     if( flag && (i==5 || i==7) ) continue;
				     actualWeight[p]=scalef*pweight[i]*pileupWeight;
				     actualWeight[p]=scalef*pweight[i]*pileupWeight*2;
				     cout<<p<<" "<<actualWeight[p]<<endl;
				     for(int j=0;j<kk;j++){
					     th1[p][j]->Fill(variables[vec_branchname[j]],actualWeight[p]);
				     }
			     }
			     else if(name.Contains("EWK")){
				     int k;
				     if(tag.Contains("16")==0)
					     k=15*i;
				     else k=i;
					     actualWeight[p]=scalef*pweight[k]*pileupWeight;
				     cout<<p<<" "<<actualWeight[p]<<endl;
				     for(int j=0;j<kk;j++){
					     th1[p][j]->Fill(variables[vec_branchname[j]],actualWeight[p]);
				     }
			     }
				     p++;
		     }
	     }
     }
     cout<<name<<endl;
     TFile*fout[kk];
     for(int j=0;j<kk;j++){
	     if(name.Contains("EWK"))
		     fout[j]= new TFile("./unfold_"+vec_branchname[j]+"_SigOut_scale"+tag+".root","recreate");
	     else
		     fout[j]= new TFile("./unfold_"+vec_branchname[j]+"_qcd_scale"+tag+".root","recreate");
     }
     for(int j=0;j<kk;j++){
	     fout[j]->cd();
	     for(Int_t i=0;i<num;i++){
		     th1[i][j]->Write();
	     }
	     fout[j]->Close();
     }
}
int Unfold_uncer_batch_bkg(){
	gSystem->Load("libTreePlayer.so");
     TString GenLEPmu  = "genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110";
     TString GenLEPele = "genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110";
     TString GenPhoton = "genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) )";
     TString GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
     TString GenDr = "gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5";
     TString GenControlRegion = "genMjj >150 && genMjj<400 && genZGmass>100";
     TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenControlRegion;

     TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
     TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
     TString photon = "photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
     TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
     TString Pi=Form("%f",pi);
     TString dr = "( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
     TString ControlRegion = "Mjj>150 && Mjj<400 && Mva>100";
     TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+ControlRegion;
     TString cut1 ="("+Reco+")";
     TString cut2 ="(("+Reco+")&& !("+Gen+"))";
     vector<vector<double>> bins;
     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     vector<double> MvaBins={100,150,1000};
     vector<double> MjjBins={150,200,300,400};
//     bins.push_back(ptlepBins);
//     bins.push_back(photonEtBins);
//     bins.push_back(jetptBins);
     bins.push_back(MvaBins);
     bins.push_back(MjjBins);

//     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt"};//,"genZGmass","genMjj"};
//     vector<TString> recovars={"ptlep1","photonet","jet1pt"};//,"Mva","Mjj"};
     vector<TString> genvars={"genZGmass","genMjj"};
     vector<TString> recovars={"Mva","Mjj"};
//     for(int i=0;i<bins.size();i++){
     TString dir16="/eos/user/y/yian/2016legacy/";     
     TFile*file16=new TFile(dir16+"cutla-outZA_pweight.root");
     TString dir17="/eos/user/y/yian/2017cutla/";     
     TFile*file17=new TFile(dir17+"cutla-outZA-pweight.root");
     TString dir18="/eos/user/y/yian/2018cutla/";     
     TFile*file18=new TFile(dir18+"cutla-outZA_pweight.root");

     TString dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/";
     TFile*file1=new TFile(dir1+"unfold_16outZA-EWK.root");
     TFile*file2=new TFile(dir1+"unfold_17outZA-EWK-pweight.root");
     TFile*file3=new TFile(dir1+"unfold_18outZA-EWK-pweight.root");
     run(file16, recovars, bins,cut1,"16",9);
     run(file17, recovars, bins,cut1,"17",9);
     run(file18, recovars, bins,cut1,"18",9);

     run(file1, recovars, bins,cut2,"16",3);
     run(file2, recovars, bins,cut2,"17",3);
     run(file3, recovars, bins,cut2,"18",3);
     return 1;
}
