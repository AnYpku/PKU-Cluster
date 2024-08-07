#define num 3
#define pi 3.1415926
void run( TString sample,vector<TString> vec_branchname,vector<vector<double>> bins,TString cut1,TString tag,TString type){
     const int kk = vec_branchname.size();
     TFile*file;
     if(sample.Contains("EWK")) file=new TFile("/home/pku/anying/cms/rootfiles/20"+tag+"/unfold_GenCutla-"+sample+tag+".root");
     else file=new TFile("/home/pku/anying/cms/rootfiles/20"+tag+"/cutla-out"+sample+tag+".root");
     TString name=file->GetName();
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
//     tree->SetBranchStatus("*",0);
     map<TString, double> variables;
     for(int i=0;i<vec_branchname.size();i++){
             tree->SetBranchStatus(vec_branchname[i],1);
	     tree->SetBranchAddress(vec_branchname[i], &variables[vec_branchname[i]]);
     }
     Double_t scalef,pileupWeight,prefWeight;
     double Mjj,deltaetajj;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,muon_hlt_scale,ele_hlt_scale;
     int lep;
     Double_t puIdweight_T,puIdweight_T_effUp,puIdweight_T_effDn,puIdweight_T_misUp,puIdweight_T_misDn;
     Double_t puIdweight_M,puIdweight_M_effUp,puIdweight_M_effDn,puIdweight_M_misUp,puIdweight_M_misDn;
     Double_t puIdweight_L,puIdweight_L_effUp,puIdweight_L_effDn,puIdweight_L_misUp,puIdweight_L_misDn;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("deltaetajj",&deltaetajj);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
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
     tree->SetBranchAddress("puIdweight_T_effUp",&puIdweight_T_effUp);
     tree->SetBranchAddress("puIdweight_T_effDn",&puIdweight_T_effDn);
     tree->SetBranchAddress("puIdweight_T_misUp",&puIdweight_T_misUp);
     tree->SetBranchAddress("puIdweight_T_misDn",&puIdweight_T_misDn);
     tree->SetBranchAddress("puIdweight_M",&puIdweight_M);
     tree->SetBranchAddress("puIdweight_M_effUp",&puIdweight_M_effUp);
     tree->SetBranchAddress("puIdweight_M_effDn",&puIdweight_M_effDn);
     tree->SetBranchAddress("puIdweight_M_misUp",&puIdweight_M_misUp);
     tree->SetBranchAddress("puIdweight_M_misDn",&puIdweight_M_misDn);
     tree->SetBranchAddress("puIdweight_L",&puIdweight_L);
     tree->SetBranchAddress("puIdweight_L_effUp",&puIdweight_L_effUp);
     tree->SetBranchAddress("puIdweight_L_effDn",&puIdweight_L_effDn);
     tree->SetBranchAddress("puIdweight_L_misUp",&puIdweight_L_misUp);
     tree->SetBranchAddress("puIdweight_L_misDn",&puIdweight_L_misDn);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
     double actualWeight[num],weight;
     TH1D*th1[num][kk];
     TString th1name[num][kk];
     for(Int_t i=0;i<num;i++){
	     for(int j=0;j<kk;j++){
		     th1name[i][j]=vec_branchname[j]+Form("_%d",i);
		     th1[i][j] = new TH1D(th1name[i][j],th1name[i][j],bins[j].size()-1,&bins[j][0]);
	     }
     }      
     cout<<tag<<" "<<name<<endl;
     double puIdweight,puIdweight_effUp,puIdweight_effDn,puIdweight_misUp,puIdweight_misDn;
     for(int k=0;k<tree->GetEntries();k++){
	     tree->GetEntry(k);
	     int p=0;
             if(tag.Contains("16")) {
                     puIdweight=puIdweight_M;
                     puIdweight_effUp=puIdweight_M_effUp;  puIdweight_misUp=puIdweight_M_misUp;
                     puIdweight_effDn=puIdweight_M_effDn;  puIdweight_misDn=puIdweight_M_misDn;
             }
             if(tag.Contains("17")){
                     puIdweight=puIdweight_T;
                     puIdweight_effUp=puIdweight_T_effUp;  puIdweight_misUp=puIdweight_T_misUp;
                     puIdweight_effDn=puIdweight_T_effDn;  puIdweight_misDn=puIdweight_T_misDn;
             }
             if(tag.Contains("18")){
                     puIdweight=puIdweight_L;
                     puIdweight_effUp=puIdweight_L_effUp;  puIdweight_misUp=puIdweight_L_misUp;
                     puIdweight_effDn=puIdweight_L_effDn;  puIdweight_misDn=puIdweight_L_misDn;
                     prefWeight=1;
             }
	     weight=scalef*pileupWeight*prefWeight*photon_id_scale*photon_veto_scale;
	     if(lep==11)
		     weight=weight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
	     if(lep==13)
		     weight=weight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;
	     if (  tformula->EvalInstance() ){
		     for(Int_t i=0;i<(num);i++){
			     if(type.Contains("eff")){
				     if(p==0)actualWeight[p]=weight*puIdweight;
				     if(p==1)actualWeight[p]=weight*puIdweight_effUp;
				     if(p==2)actualWeight[p]=weight*puIdweight_effDn;
			     }
			     else if(type.Contains("mis")){
				     if(p==0)actualWeight[p]=weight*puIdweight;
				     if(p==1)actualWeight[p]=weight*puIdweight_misUp;
				     if(p==2)actualWeight[p]=weight*puIdweight_misDn;

			     }
			     for(int j=0;j<kk;j++){
				     th1[p][j]->Fill(variables[vec_branchname[j]],actualWeight[p]);
			     }
			     p++;
		     }
	     }
     }
     TFile*fout[kk];
     for(int j=0;j<kk;j++){
	     if(name.Contains("EWK")==1){
		     fout[j]= new TFile("unfold_"+vec_branchname[j]+"_"+sample+"out_"+type+tag+".root","recreate");
	     }
	     else{
		     fout[j]= new TFile("unfold_"+vec_branchname[j]+"_"+sample+"_"+type+tag+".root","recreate");
	     }
     }
     for(int j=0;j<kk;j++){
	     fout[j]->cd();
	     for(Int_t i=0;i<num;i++){
		     th1[i][j]->Write();
	     }
	     fout[j]->Close();
     }
     for(int j=0;j<kk;j++){
	     for(Int_t i=0;i<num;i++){
		     delete  th1[i][j];
	     }
     }
}
int Unfold_uncer_batch_bkg(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenControlRegion = "(genMjj >150 && genMjj<500 && genZGmass>100)";
	TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenControlRegion;

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString ControlRegion = "(Mjj>150 && Mjj<500 && Mva>100)";
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
//	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	vector<TString> sample={"ZA_interf"};
	vector<TString> tag={"16","17","18"};
	for(int i=0;i<3;i++){
                if(tag[i].Contains("16")){
                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
                }
                else if(tag[i].Contains("17")){
                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
                }
                else if(tag[i].Contains("18")){
                        jet = "( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
                }
		TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+ControlRegion;
		TString cut2 ="("+Reco+")";
		TString cut1 ="(("+Reco+")&& !("+Gen+"))";
		for(int j=0;j<sample.size();j++){
			if(sample[j].Contains("EWK")){	
				run(sample[j],recovars, bins,cut1,tag[i],"eff");
				run(sample[j],recovars, bins,cut1,tag[i],"mis");
			}
			else{   
				run(sample[j],recovars, bins,cut2,tag[i],"eff");
				run(sample[j],recovars, bins,cut2,tag[i],"mis");
			}
		}
	}
	return 1;
}
