#define pi 3.1415926
void run(TString dir,TString tag,TString cut, TString cut1,TString cut2){
	ofstream f("./lepton_uncer"+tag+".txt");
        TFile*file;
	if(tag.Contains("16"))file=new TFile(dir+"unfold_"+tag+"outZA-EWK.root");
	else file=new TFile(dir+"unfold_"+tag+"outZA-EWK-pweight.root");
        TTree*tree=(TTree*)file->Get("demo");
        int total=tree->GetEntries(cut);cout<<"total events with reco cuts "<<total<<endl;
        int n_mu =tree->GetEntries(cut1);cout<<"total events with reco cuts in muon channel "<<n_mu<<endl; 
        int n_ele =tree->GetEntries(cut2);cout<<"total events with reco cuts in ele channel "<<n_ele<<endl; 
        cout<<"consistency check "<<n_mu+n_ele<<" "<<total<<endl;
        double valid_mu_eff=(1.005*n_mu+n_ele)/(n_mu+n_ele);
        double valid_ele_eff=(n_mu+1.023*n_ele)/(n_mu+n_ele);
        double valid_mu_trigger=(1.02*n_mu+n_ele)/(n_mu+n_ele);
        double valid_ele_trigger=(n_mu+1.02*n_ele)/(n_mu+n_ele);
        f<<"mu_eff"<<tag<<"=["<< valid_mu_eff<<"]"<<endl;
        f<<"mu_trigger"<<tag<<"=["<< valid_mu_trigger<<"]"<<endl;
        f<<"ele_eff"<<tag<<"=["<< valid_ele_eff<<"]"<<endl;
        f<<"ele_trigger"<<tag<<"=["<< valid_ele_trigger<<"]"<<endl;
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
	TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
	TString Reco_mu= "("+LEPmu+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
	TString Reco_ele= "("+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
	TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/";
	run(dir,"16",Reco,Reco_mu,Reco_ele);
	run(dir,"17",Reco,Reco_mu,Reco_ele);
	run(dir,"18",Reco,Reco_mu,Reco_ele);
	return 0;
}
