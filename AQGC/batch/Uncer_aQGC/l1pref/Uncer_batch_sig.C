#define num 3
void run(TString cut1,TString tag,TString channel){
     TFile*file;
     TString dir="../../rootfiles/";     
     file=new TFile(dir+"optimal_ZA-EWK"+tag+".root");
     TTree*tree=(TTree*)file->Get("outtree");     
     Double_t scalef,pileupWeight,prefWeight,prefWeightUp,prefWeightDown;
     Double_t ZGmass,jet1eta,jet2eta,actualWeight;
     tree->SetBranchAddress("ZGmass",&ZGmass);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("prefWeight",&prefWeight);
     tree->SetBranchAddress("prefWeightUp",&prefWeightUp);
     tree->SetBranchAddress("prefWeightDown",&prefWeightDown);
     tree->SetBranchAddress("actualWeight",&actualWeight);
     if(tag.Contains("18")){
         prefWeight=1;prefWeightUp=1;prefWeightDown=1;
     }
     TString cut;
     if(channel.Contains("ele"))
             cut="lep==11";
     else if(channel.Contains("mu"))
             cut="lep==13";
     else    cut="(lep==11||lep==13)";
     TTreeFormula *tformula=new TTreeFormula("formula", cut1+"&&("+cut+")", tree);
     double Weight[num];
     TH1D*th1[num];
     TString th1name[num];
     double ZGbin[6] = {150,400,600,800,1000,2e4};
     for(Int_t i=0;i<num;i++){
		     th1name[i]=Form("hist_%d",i);
		     th1[i] = new TH1D(th1name[i],th1name[i],5,ZGbin);
		     th1[i]->Sumw2(); 
     }      
     double lumi;
     if(tag.Contains("16"))lumi=35.86;
     if(tag.Contains("17"))lumi=41.52;
     if(tag.Contains("18"))lumi=58.7;
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             double detajj=fabs(jet1eta-jet2eta);
	     int p=0;
	     if(ZGmass>2e4)ZGmass=1999;
	     if (  tformula->EvalInstance() ){
		     for(Int_t i=0;i<(num);i++){
			     if(p==0)Weight[p]=actualWeight/prefWeight*prefWeight*pileupWeight*lumi;
			     if(p==1)Weight[p]=actualWeight/prefWeight*prefWeightUp*pileupWeight*lumi;
			     if(p==2)Weight[p]=actualWeight/prefWeight*prefWeightDown*pileupWeight*lumi;
			     th1[p]->Fill(ZGmass,Weight[p]);
			     p++;
		     }
	     }
     }
     TFile*fout;
     fout= new TFile("hist_ewk_pref_"+tag+channel+".root","recreate");
     fout->cd();
     for(Int_t i=0;i<num;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Uncer_batch_sig(){

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>100 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )  )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
        vector<TString> tag={"16","17","18"};
        for(int i=0;i<tag.size();i++){
           if(tag[i].Contains("17")){
		   jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
           }
           else{
                   jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
           }
        }
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta) && ZGmass>100)";
	TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
        vector<TString> channels={"mu","ele",""};
	const int kk=channels.size();
	for(int j=0;j<kk;j++){
		for(int i=0;i<tag.size();i++){
			run(Reco,tag[i],channels[j]);
		}
	}
	return 1;
}
