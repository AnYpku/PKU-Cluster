#define pi 3.1415926
void run(TString var,TString sample,TString particle,TString type,TString tag,double frac){
	ofstream f2("./"+var+"_"+particle+"_"+type+"_"+tag+"CR.txt",ios::app);
	TFile* file = new TFile("./root/"+var+"_"+particle+"_"+sample+"_"+type+tag+".root");
	cout<<var+particle+"_"+type+tag+".root"<<endl;
	TH1D* h1 = (TH1D*)file->Get(var+"_0");
	TH1D* h2 = (TH1D*)file->Get(var+"_1");
	TH1D* h3 = (TH1D*)file->Get(var+"_2");
        if(sample.Contains("ZA")&&sample.Contains("EWK")==0){
          TFile*file1;
          file1=new TFile("./root/"+var+"_"+particle+"_ZA_interf_"+type+tag+".root");
          TH1D*hh1 = (TH1D*)file1->Get(var+"_0");
          TH1D*hh2 = (TH1D*)file1->Get(var+"_1");
          TH1D*hh3 = (TH1D*)file1->Get(var+"_2");
          h1->Add(hh1,1);
          h2->Add(hh2,1);
          h3->Add(hh3,1);
        }

	const int num =h1->GetNbinsX();
	cout<<var<<" "<<sample<<" "<<particle<<" "<<type<<" "<<tag<<" "<<frac<<" uncertainty"<<endl;
	f2<<particle<<"_"<<sample<<"_"<<type<<"=[";
	for(int i=0;i<num;i++){
		Double_t bincontent_new,bincontent_up,bincontent_down;
		Double_t uncer;
		bincontent_new=h1->GetBinContent(i+1);
		bincontent_up=h2->GetBinContent(i+1);
		bincontent_down=h3->GetBinContent(i+1);
		if(bincontent_new>0)
			uncer=fabs(bincontent_up-bincontent_down)/2/bincontent_new*frac;
		else    uncer=0;
		if(i==0){
			f2<<fixed<<setprecision(3)<<1+uncer<<",";
			cout<<fixed<<setprecision(3)<<"["<<1+uncer<<",";
		}
		else if(i<num-1){
			f2<<fixed<<setprecision(3)<<1+uncer<<",";
			cout<<fixed<<setprecision(3)<<1+uncer<<",";
		}
		else{
			f2<<fixed<<setprecision(3)<<1+uncer<<"]"<<endl;
			cout<<fixed<<setprecision(3)<<1+uncer<<"]"<<endl;
		}
	}
}
int uncer_eff(){
	TString Pi=Form("%f",pi);
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ) )";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenControlRegion = "(genMjj >150 && genMjj<500 && genZGmass>100)";
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString drjj="(sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 || sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5)";
	TString dr = "("+drjj+" && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	vector<TString> par={"ele","muon","photon"};
	vector<TString> tag={"16","17","18"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	double frac_ele,frac_mu;
	for(int ik=0;ik<tag.size();ik++){
		if(tag[ik].Contains("17")){
			GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else{
			GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
//                if(tag[ik].Contains("17")==0) continue;
		TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenControlRegion;
		TString ControlRegion = "(Mjj>150 && Mjj<500 && Mva>100)";
		TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+ControlRegion;
		TString cut1 ="(("+Reco+")&& ("+Gen+"))";
		TString cut ="(("+Reco+"))";
		for(int k=0;k<sample.size();k++){
			TFile*fin;
			TString cut_final;
			if(sample[k].Contains("EWK")){
				cut_final=cut1;
				fin=new TFile("/home/pku/anying/cms/rootfiles/20"+tag[ik]+"/unfold_GenCutla-ZA-EWK"+tag[ik]+".root");
			}
			else{
				cut_final=cut;
				fin=new TFile("/home/pku/anying/cms/rootfiles/20"+tag[ik]+"/cutla-out"+sample[k]+tag[ik]+".root");
			}
			TTree*tree=(TTree*)fin->Get("ZPKUCandidates");
			double ntot=tree->GetEntries(cut_final);
			double n_ele=tree->GetEntries("("+cut_final+"&&(lep==11))");
			double n_mu =tree->GetEntries("("+cut_final+"&&(lep==13))");
			frac_ele=n_ele/ntot;
			frac_mu=n_mu/ntot;
			fin->Close();
			cout<<tag[ik]<<" "<<sample[k]<<" "<<frac_ele<<" "<<frac_mu<<endl;
			for(int j=0;j<recovars.size();j++){
				for(int i=0;i<par.size();i++){
					if(par[i].Contains("muon")){
						run(recovars[j],sample[k],par[i],"all",tag[ik],frac_mu);
						run(recovars[j],sample[k],par[i],"trigger",tag[ik],frac_mu);
					}
					if(par[i].Contains("photon")){
						run(recovars[j],sample[k],par[i],"ID",tag[ik],1);
					}
					if(par[i].Contains("ele")){
						run(recovars[j],sample[k],par[i],"ID",tag[ik],frac_ele);
						run(recovars[j],sample[k],par[i],"reco",tag[ik],frac_ele);
					}
				}
			}    
		}
	}
	return 1;
}
