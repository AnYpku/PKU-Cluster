#define num 3
#define pi 3.1415926
TH1D* run( TString sample,TString tag,TString cut1){
     Double_t Mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TString dir1;
     dir1="/home/pku/anying/cms/rootfiles/20"+tag+"/cutla-out";
     TFile*file=new TFile(dir1+"plj"+tag+"_weight"+sample+".root");
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");
     map<TString, double> variables;
     double Mjj,jet1eta,jet2eta;
     Double_t scalef;
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("Mjj",&Mjj);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     TTreeFormula *tformula=new TTreeFormula("formula","("+ cut1+")", tree);
//     TH1D*th1[kk];
     TString th1name;
     th1name="Mjj"+sample;
     TH1D* th1;
     th1 = new TH1D(th1name,th1name,7,0,7);
     th1->Sumw2(); 
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
	     double detajj=fabs(jet1eta-jet2eta);
	     if (  tformula->EvalInstance() ){
		     if(Mjj>=500&&Mjj<800&&detajj>=2.5&&detajj<4.5)th1->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		     if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5)th1->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		     if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)th1->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
		     if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6)th1->Fill(3.5,scalef);//3~4 4.5~6 500~800 
		     if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6)th1->Fill(4.5,scalef);//4~5 4.5~6 800~1200
		     if(Mjj>=1200&&detajj>=4.5&&detajj<6)th1->Fill(5.5,scalef);//5~6 6~infi 500~800
		     if(Mjj>=500&&detajj>=6)th1->Fill(6.5,scalef);//6~7 6~infi 800~1200
	     }
     }
     return th1;
}
int Unfold_uncer_batch_bkg_Mjj(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && Mva>100)";

	vector<TString> tag={"16","17","18"};
	TH1D*hist[3];TH1D*hist_up[3];TH1D*hist_down[3];//hist[year][channels]
	for(int i=0;i<tag.size();i++){
                if(tag[i].Contains("16")){
                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
                }
                else if(tag[i].Contains("17")){
                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
                }
                else if(tag[i].Contains("18")){
                        jet = "( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
                }
		cout<<tag[i]<<" "<<jet<<endl;
		cout<<tag[i]<<" "<<GenJet<<endl;
		TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString cut1 ="("+Reco+")";
		TString cut2 ="(("+Reco+")&& !("+Gen+"))";
		hist[i]=run("",tag[i],cut1);
		hist_up[i]=run("_up",tag[i],cut1);
		hist_down[i]=run("_down",tag[i],cut1);
	}
	//     cout<<hist[0][0]->GetBinContent(1);
	TFile*fout[3];
	for(int i=0;i<3;i++){
		fout[i]= new TFile("unfold_Mjj_plj"+tag[i]+".root","recreate");
		cout<<hist[i]->GetBinContent(1)<<endl;
		fout[i]->cd();
		hist[i]->Write();
		hist_up[i]->Write();
		hist_down[i]->Write();
		fout[i]->Close();
	}
	return 1;
}
