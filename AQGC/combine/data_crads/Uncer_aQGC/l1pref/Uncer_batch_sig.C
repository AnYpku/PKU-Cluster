#define num 3
void run(TString cut1,TString tag,TString channel){
     TFile*file;
     TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/";     
     if(tag.Contains("16"))file=new TFile(dir+"unfold_"+tag+"outZA-EWK.root");
     else file=new TFile(dir+"unfold_"+tag+"outZA-EWK-pweight.root");
     TTree*tree=(TTree*)file->Get("demo");     
//     tree->SetBranchStatus("*",0);
     Double_t scalef,pileupWeight,prefWeight,prefWeightUp,prefWeightDown;
     Double_t Mva,jet1eta,jet2eta;
     tree->SetBranchAddress("Mva",&Mva);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("prefWeight",&prefWeight);
     tree->SetBranchAddress("prefWeightUp",&prefWeightUp);
     tree->SetBranchAddress("prefWeightDown",&prefWeightDown);
     if(tag.Contains("18")){
         prefWeight=1;prefWeightUp=1;prefWeightDown=1;
     }
     TString cut;
     if(channel.Contains("ele"))
             cut="lep==11";
     if(channel.Contains("mu"))
             cut="lep==13";
     TTreeFormula *tformula=new TTreeFormula("formula", cut1+"&&("+cut+")", tree);
     double actualWeight[num];
     TH1D*th1[num];
     TString th1name[num];
     double ZGbin[6] = {150,400,600,800,1000,2000};
     for(Int_t i=0;i<num;i++){
		     th1name[i]=Form("hist_%d",i);
		     th1[i] = new TH1D(th1name[i],th1name[i],5,ZGbin);
		     th1[i]->Sumw2(); 
     }      
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             double detajj=fabs(jet1eta-jet2eta);
	     int p=0;
	     if(Mva>2000)Mva=1999;
	     if (  tformula->EvalInstance() ){
		     for(Int_t i=0;i<(num);i++){
			     if(p==0)actualWeight[p]=scalef*prefWeight*pileupWeight;
			     if(p==1)actualWeight[p]=scalef*prefWeightUp*pileupWeight;
			     if(p==2)actualWeight[p]=scalef*prefWeightDown*pileupWeight;
			     th1[p]->Fill(Mva,actualWeight[p]);
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
	TString GenLEPmu  = "genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110";
	TString GenLEPele = "genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110";
	TString GenPhoton = "genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) )";
	TString GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
	TString GenDr = "gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5";
	TString GenSignalRegion = "genMjj >500 && gendetajj>2.5";

	TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
	TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
	TString photon = "photonet>100 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
	TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
	TString dr = "drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
        vector<TString> tag={"16","17","18"};
        for(int i=0;i<tag.size();i++){
           if(tag[i].Contains("17")){
              GenJet = " ( (!(fabs(genjet2eta)<3.14 && fabs(genjet2eta)>2.65) && !(fabs(genjet1eta)<3.14 && fabs(genjet1eta)>2.65) &&  genjet1pt<50 && genjet2pt<50 && genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)< 4.7 && fabs(genjet2eta)<4.7) || (genjet1pt>50 && genjet2pt>50 && fabs(genjet1eta)< 4.7 && fabs(genjet2eta)<4.7) ) ";
              jet=" ( (!(fabs(jet2eta)<3.14 && fabs(jet2eta)>2.65) && !(fabs(jet1eta)<3.14 && fabs(jet1eta)>2.65) &&  jet1pt<50 && jet2pt<50 && jet1pt>30 && jet2pt>30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) || (jet1pt>50 && jet2pt>50 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) ) ";
           }
           else{
                   GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
                   jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
           }
        }
	TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;
	TString SignalRegion = "Mjj>500 && deltaetajj>2.5 && Mva>100";
	TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
	TString cut1 ="(("+Reco+")&&("+Gen+"))";
	TString cut2 ="(("+Reco+")&& !("+Gen+"))";


        vector<TString> channels={"mu","ele"};
	const int kk=channels.size();
	for(int j=0;j<kk;j++){
		for(int i=0;i<tag.size();i++){
			run(Reco,tag[i],channels[j]);
		}
	}
	return 1;
}
