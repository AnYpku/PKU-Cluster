#define pi 3.1415926
void run(TString var,TString particle,TString type,TString dir,TString cut, TString tag){
	ofstream f("./"+var+"_"+particle+"_"+type+tag+".txt");
        TFile*file1=new TFile(dir+"unfold_16outZA-EWK.root");
        TFile*file2=new TFile(dir+"unfold_17outZA-EWK.root");
        TFile*file3=new TFile(dir+"unfold_18outZA-EWK.root");
        TTree*tree1=(TTree*)file1->Get("demo");
        TTree*tree2=(TTree*)file2->Get("demo");
        TTree*tree3=(TTree*)file3->Get("demo");
        TChain*chain=new TChain("demo","");
	chain->Add(dir+"unfold_16outZA-EWK.root");
        chain->Add(dir+"unfold_17outZA-EWK-pweight.root");
        chain->Add(dir+"unfold_18outZA-EWK-pweight.root");
                
        int total=chain->GetEntries(cut);cout<<"total events with reco cuts with full run II"<<" "<<total<<endl;
        int n_frac16 =tree1->GetEntries(cut);
        int n_frac17 =tree1->GetEntries(cut);
        int n_frac18 =tree1->GetEntries(cut);
	if(particle.Contains("photon")==0){
		if(tag.Contains("16"))cout<<"total events with reco cuts in "<<particle<<" channel with full run II"<<" "<<n_frac16<<endl; 
		if(tag.Contains("17"))cout<<"total events with reco cuts in "<<particle<<" channel with full run II"<<" "<<n_frac17<<endl; 
		if(tag.Contains("18"))cout<<"total events with reco cuts in "<<particle<<" channel with full run II"<<" "<<n_frac18<<endl; 
	}
	else{   
		if(tag.Contains("16"))cout<<"total events with reco cuts when photonet >100 "<<n_frac16<<endl;
		if(tag.Contains("17"))cout<<"total events with reco cuts when photonet >100 "<<n_frac17<<endl;
		if(tag.Contains("18"))cout<<"total events with reco cuts when photonet >100 "<<n_frac18<<endl;
	}
        double uncer;
        ifstream f1;
        if(type.Contains("trigger")==0){
		f1.open("./txt/"+var+"_"+particle+"_"+type+"_"+tag+".txt");
                cout<<"./txt/"+var+"_"+particle+"_"+type+"_"+tag+".txt"<<endl;
		f1>>uncer;
	}
//	cout<<uncer<<" "<<n_frac<<" "<<(total-n_frac)<<endl;
	if(type.Contains("trigger")&& particle.Contains("muon")) uncer=1.02; 
        double valid_frac_uncer;
	if(tag.Contains("16")){
	       valid_frac_uncer	=(uncer*n_frac16+(total-n_frac16))/total;
	}
	if(tag.Contains("17")){
	       valid_frac_uncer	=(uncer*n_frac17+(total-n_frac17))/total;
	}
	if(tag.Contains("18")){
	       valid_frac_uncer	=(uncer*n_frac18+(total-n_frac18))/total;
	}
        if(type.Contains("trigger"))f<<particle<<tag<<"_"<<type<<"=["<<valid_frac_uncer<<"]"<<endl; 
	else f<<particle<<"_"<<type<<"=["<<valid_frac_uncer<<"]"<<endl; 
	file1->Close();
	file2->Close();
	file3->Close();
} 
int generate_frac(){
	TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
	TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
	TString photon = "photonet>100 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
	TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
	TString Pi=Form("%f",pi);
	TString dr = "( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
	TString SignalRegion = "Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && Mva>100";
	TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
	TString Reco_mu= "("+LEPmu+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
	TString Reco_ele= "("+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
	TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/";
        
	vector<TString> recovars={"Mva"};
        vector<TString> tag={"16","17","18"};
	for(int i=0;i<recovars.size();i++){
		for(int j=0;j<tag.size();j++){
			run(recovars[i],"ele","ID",dir,Reco_ele,tag[j]);
			run(recovars[i],"ele","reco",dir,Reco_ele,tag[j]);
			run(recovars[i],"muon","all",dir,Reco_mu,tag[j]);
			run(recovars[i],"muon","trigger",dir,Reco_mu,tag[j]);
			run(recovars[i],"photon","ID",dir,Reco,tag[j]);
		}
	}
	return 0;
}
