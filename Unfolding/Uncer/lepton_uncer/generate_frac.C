#define pi 3.1415926
void run(TString var,TString particle,TString type,TString tag,TString dir,TString cut, TString cut1){
	ofstream f("./"+var+"_"+particle+"_"+type+"_"+tag+".txt");
        TFile*file;
	file=new TFile(dir+"unfold_GenCutla-outZA-EWK"+tag+".root");
        TTree*tree=(TTree*)file->Get("ZPKUCandidates");
        int total=tree->GetEntries(cut);cout<<"total events with reco cuts in 20"<<tag<<" "<<total<<endl;
        int n_frac =tree->GetEntries(cut1);
	if(particle.Contains("photon")==0)cout<<"total events with reco cuts in "<<particle<<" channel in 20"<<tag<<" "<<n_frac<<endl; 
	else cout<<"total events with reco cuts when photonet >20"<<n_frac<<endl;
        double uncer;
        ifstream f1;
        if(type.Contains("trigger")==0){
		f1.open("./txt/"+var+"_"+particle+"_"+type+"_"+tag+".txt");
                cout<<"./txt/"+var+"_"+particle+"_"+type+"_"+tag+".txt"<<endl;
		f1>>uncer;
	}
	cout<<uncer<<" "<<n_frac<<" "<<(total-n_frac)<<endl;
	if(type.Contains("trigger")&& particle.Contains("muon")) uncer=1.02; 
        double valid_frac_uncer=(uncer*n_frac+(total-n_frac))/total;
        if(type.Contains("trigger"))f<<particle<<tag<<"_"<<type<<"=["<<valid_frac_uncer<<"]"<<endl; 
	else f<<particle<<"_"<<type<<"=["<<valid_frac_uncer<<"]"<<endl; 
	file->Close();
} 
int generate_frac(){
	TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
	TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
	TString photon = "photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
	TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
	TString Pi=Form("%f",pi);
	TString dr = "( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
	TString SignalRegion = "Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && Mva>100";
        
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
        vector<TString> tag={"16","17","18"};
	for(int i=0;i<recovars.size();i++){
		for(int j=0;j<tag.size();j++){
                if(tag[j].Contains("17")){
			jet="(  ( (fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65&&jet1pt>30&&jet1pt<50&&jet1puIdTight==1) || (!(fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) && fabs(jet1eta)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta)<4.7&& jet1pt>50) ) && ( (fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65&&jet2pt>30&&jet2pt<50&&jet2puIdTight==1)||(!(fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65)&&fabs(jet2eta)<4.7&&jet2pt>30&&jet2pt<50) ||(fabs(jet2eta)<4.7 && jet2pt>50) ) )";
		}
		else{
			jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
		}
		TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString Reco_mu= "("+LEPmu+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString Reco_ele= "("+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString dir="/home/pku/anying/cms/rootfiles/20"+tag[j]+"/";
		run(recovars[i],"ele","ID",tag[j],dir,Reco,Reco_ele);
		run(recovars[i],"ele","reco",tag[j],dir,Reco,Reco_ele);
		run(recovars[i],"muon","all",tag[j],dir,Reco,Reco_mu);
		run(recovars[i],"muon","trigger",tag[j],dir,Reco,Reco_mu);
		run(recovars[i],"photon","ID",tag[j],dir,Reco,Reco);
		}
	}
	return 0;
}
