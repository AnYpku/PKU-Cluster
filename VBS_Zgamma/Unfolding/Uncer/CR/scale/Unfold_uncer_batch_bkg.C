//#define num 9
#define pi 3.1415926
void run(TFile*file, vector<TString> vec_branchname,vector<vector<double>> bins,TString cut1,TString tag,int num){
     const int kk = vec_branchname.size();
     TString name=file->GetName();
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
//     tree->SetBranchStatus("*",0);
     map<TString, double> variables;
     for(int i=0;i<vec_branchname.size();i++){
             tree->SetBranchStatus(vec_branchname[i],1);
	     tree->SetBranchAddress(vec_branchname[i], &variables[vec_branchname[i]]);
     }
     double deltaetajj;
     Double_t scalef,pileupWeight,pweight[703],prefWeight;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,muon_hlt_scale,ele_hlt_scale,puIdweight_T,puIdweight_M,puIdweight_L,puIdweight;
     int lep;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("deltaetajj",&deltaetajj);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("pweight",pweight);
     tree->SetBranchAddress("prefWeight",&prefWeight);
     tree->SetBranchAddress("photon_id_scale", &photon_id_scale);
     tree->SetBranchAddress("photon_veto_scale", &photon_veto_scale);
     tree->SetBranchAddress("ele1_id_scale",   &ele1_id_scale);
     tree->SetBranchAddress("ele2_id_scale",   &ele2_id_scale);
     tree->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale);
     tree->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale);
     tree->SetBranchAddress("muon1_id_scale",   &muon1_id_scale);
     tree->SetBranchAddress("muon2_id_scale",   &muon2_id_scale);
     tree->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale);
     tree->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale);
     tree->SetBranchAddress("muon_hlt_scale", &muon_hlt_scale);
     tree->SetBranchAddress("ele_hlt_scale", &ele_hlt_scale);
     tree->SetBranchAddress("puIdweight_T", &puIdweight_T);
     tree->SetBranchAddress("puIdweight_M", &puIdweight_M);
     tree->SetBranchAddress("puIdweight_L", &puIdweight_L);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
     double actualWeight[num],weight;
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
     if(name.Contains("interf"))   first=0;
     cout<<"enter the loop"<<endl;
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             if(tag.Contains("16")){ puIdweight=puIdweight_M;}
             if(tag.Contains("17")){ puIdweight=puIdweight_T;}
             if(tag.Contains("18")){ prefWeight=1;  puIdweight=puIdweight_L;}
             weight=scalef*pileupWeight*prefWeight*photon_id_scale*photon_veto_scale*puIdweight;
             if(lep==11)
                     weight=weight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
             if(lep==13)
                     weight=weight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;
	     int p=0;
	     if ( !tformula->EvalInstance() ) continue;
	     for(Int_t i=first;i<(num+first);i++){
		     if(name.Contains("EWK")==0 && tag.Contains("16")){
			     if( flag && (i==109 || i==111) ) continue;
			     if(p==0) actualWeight[p]=weight*pweight[i];
			     else actualWeight[p]=weight*pweight[i]*2;
//			     if(k%1000==0)cout<<p<<" "<<actualWeight[p]<<endl;
			     for(int j=0;j<kk;j++){
				     th1[p][j]->Fill(variables[vec_branchname[j]],actualWeight[p]);
			     }
		     }
		     else if(name.Contains("EWK")==0 && tag.Contains("16")==0){
			     if( flag && (i==5 || i==7) ) continue;
			     actualWeight[p]=weight*pweight[i];
//			     cout<<p<<" "<<actualWeight[p]<<endl;
			     for(int j=0;j<kk;j++){
				     th1[p][j]->Fill(variables[vec_branchname[j]],actualWeight[p]);
			     }
		     }
		     else if(name.Contains("EWK")||name.Contains("interf")==1){
			     int k;
			     if(tag.Contains("16")&&name.Contains("EWK"))
				     k=i;
			     else
				     k=15*i;
			     actualWeight[p]=weight*pweight[k];
//			     cout<<p<<" "<<actualWeight[p]<<endl;
			     for(int j=0;j<kk;j++){
				     th1[p][j]->Fill(variables[vec_branchname[j]],actualWeight[p]);
			     }
		     }
		     p++;
	     }
     }
     cout<<name<<endl;
     TFile*fout[kk];
     for(int j=0;j<kk;j++){
	     if(name.Contains("EWK"))
		     fout[j]= new TFile("./unfold_"+vec_branchname[j]+"_SigOut_scale"+tag+".root","recreate");
	     else if(name.Contains("interf"))
		     fout[j]= new TFile("./unfold_"+vec_branchname[j]+"_interf_scale"+tag+".root","recreate");
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
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >150 && genMjj<500 && genZGmass>100)";
	TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>150 && Mjj<500 && Mva>100)";
	vector<vector<double>> bins;
	vector<double> ptlepBins={20,80,120,200,400};
	vector<double> photonEtBins={20,80,120,200,400};
	vector<double> jetptBins={30,150,250,350,800};
	vector<double> MjjBins={150,300,400,500};
	bins.push_back(ptlepBins);
	bins.push_back(photonEtBins);
	bins.push_back(jetptBins);
	bins.push_back(MjjBins);

	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
	TString dir[3];TFile* f2[3];
	TFile* f1[3];
	TFile* f3[3];
	vector<TString> tag={"16","17","18"};
	for(int i=0;i<3;i++){
                if(tag[i].Contains("16")==1){
                        GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 &&fabs(genjet2eta)<4.7)";
                        jet="(  ( (jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1) || (fabs(jet1eta)<4.7&& jet1pt>50) ) && ( (jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)||(fabs(jet2eta)<4.7 && jet2pt>50) )  )";      
                }
                else if(tag[i].Contains("17")){
                        GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";                        jet="(  ( (jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1) || (fabs(jet1eta)<4.7&& jet1pt>50) ) && ( (jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)||(fabs(jet2eta)<4.7 && jet2pt>50) )  )";        
                }
                else if(tag[i].Contains("18")){
                        GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
                        jet="(  ( (jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1) || (fabs(jet1eta)<4.7&& jet1pt>50) ) && ( (jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)||(fabs(jet2eta)<4.7 && jet2pt>50) )  )";
                }
		TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString cut1 ="("+Reco+")";
		TString cut2 ="(("+Reco+")&& !("+Gen+"))";
//		if(tag[i].Contains("17")==0) continue;
		dir[i]="/home/pku/anying/cms/rootfiles/20"+tag[i]+"/";
		f1[i]=new TFile(dir[i]+"unfold_GenCutla-ZA-EWK"+tag[i]+".root");
		f2[i]=new TFile(dir[i]+"cutla-outZA"+tag[i]+".root");
		f3[i]=new TFile(dir[i]+"cutla-outZA_interf"+tag[i]+".root");
		run(f3[i], recovars, bins,cut1,tag[i],3);
//		run(f2[i], recovars, bins,cut1,tag[i],9);
//		run(f1[i], recovars, bins,cut2,tag[i],3);
	}
	return 1;
}
