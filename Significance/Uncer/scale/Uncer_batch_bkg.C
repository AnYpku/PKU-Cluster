//#define num 9
#define pi 3.1415926
void run(TFile*file, TString cut1,TString tag,int num,bool turn){
     TString name=file->GetName();
     TTree*tree=(TTree*)file->Get("outtree");     
     Double_t scalef,pileupWeight,pweight[703],Mjj,zepp,actualWeight;
     double jet1pt,jet2pt,jet1eta,jet2eta,jet1e,jet2e,jet1phi,jet2phi;
     double photonet,photoneta,photone,photonphi;
     double ptVlep, yVlep, phiVlep, massVlep;
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("actualWeight",&actualWeight);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("pweight",pweight);
     tree->SetBranchAddress("Mjj",&Mjj);
     tree->SetBranchAddress("zepp",&zepp);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     tree->SetBranchAddress("jet1e",&jet1e);
     tree->SetBranchAddress("jet2e",&jet2e);
     tree->SetBranchAddress("jet1pt",&jet1pt);
     tree->SetBranchAddress("jet2pt",&jet2pt);
     tree->SetBranchAddress("jet1phi",&jet1phi);
     tree->SetBranchAddress("jet2phi",&jet2phi);
     tree->SetBranchAddress("photonet",&photonet);
     tree->SetBranchAddress("photonphi",&photonphi);
     tree->SetBranchAddress("photone",&photone);
     tree->SetBranchAddress("ptVlep",&ptVlep);
     tree->SetBranchAddress("yVlep",&yVlep);
     tree->SetBranchAddress("phiVlep",&phiVlep);
     tree->SetBranchAddress("massVlep",&massVlep);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
     double Weight[num];
     TH1D*th1[num];
     TString th1name[num];
     for(Int_t i=0;i<num;i++){
	     th1name[i]=Form("hist_%d",i);
	     th1[i] = new TH1D(th1name[i],th1name[i],9,0,9);
	     th1[i]->Sumw2(); 
     }      
     bool flag=false;
     if(num==7) flag = true;
     int first;
     if(name.Contains("EWK")) first=0;//16 or 17 or 18 ew sample
     else if(name.Contains("EWK")==0 && tag.Contains("16"))first=104;//16 qcd sample
     else if(name.Contains("EWK")==0 && tag.Contains("16")==0)first=0;//17 or 18 qcd sample

     cout<<"enter the loop"<<endl;
     TLorentzVector Zp4, photonp4, jet1p4, jet2p4;
     double delta_phi,detajj;
     for(int k=0;k<tree->GetEntries();k++){
	     tree->GetEntry(k);
	     detajj=fabs(jet1eta-jet2eta);
	     Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
	     photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
	     jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
	     jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
	     delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
	     if (delta_phi>pi) delta_phi=2*pi-delta_phi;
	     int p=0;
	     if (  tformula->EvalInstance() && (zepp<2.4 && delta_phi>1.9) ){
		     for(Int_t i=first;i<(num+first);i++){
			     if(name.Contains("EWK")==0 && tag.Contains("16")){
				     if( flag && (i==109 || i==111) ) continue;
				     if(p==0) Weight[p]=actualWeight*pweight[i];
				     else Weight[p]=actualWeight*pweight[i]*2;
				     if(k%1000==0)cout<<p<<" "<<Weight[p]<<endl;
				     if(Mjj>=500&&Mjj<800&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(0.5,Weight[p]);//0~1, 2.5~4.5 and 500~800
				     if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(1.5,Weight[p]);//1~2 2.5~4.5 and 800~1200
				     if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(2.5,Weight[p]);//2~3 2.5~4.5 1200~2000
				     if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6)th1[p]->Fill(3.5,Weight[p]);//3~4 4.5~6 500~800 
				     if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6)th1[p]->Fill(4.5,Weight[p]);//4~5 4.5~6 800~1200
				     if(Mjj>=1200&&detajj>=4.5&&detajj<6)th1[p]->Fill(5.5,Weight[p]);//5~6 6~infi 500~800
				     if(Mjj>=500&&Mjj<800&&detajj>=6)th1[p]->Fill(6.5,Weight[p]);//6~7 6~infi 800~1200
				     if(Mjj>=800&&Mjj<1200&&detajj>=6)th1[p]->Fill(7.5,Weight[p]);//7~8 6~infi800~1200
				     if(Mjj>=1200&&detajj>=6)th1[p]->Fill(8.5,Weight[p]);//8~9 6~infi 800~1200
			     }
			     else if(name.Contains("EWK")==0 && tag.Contains("16")==0){
				     if( flag && (i==5 || i==7) ) continue;
				     Weight[p]=actualWeight*pweight[i];
				     cout<<p<<" "<<Weight[p]<<endl;
				     if(Mjj>=500&&Mjj<800&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(0.5,Weight[p]);//0~1, 2.5~4.5 and 500~800
				     if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(1.5,Weight[p]);//1~2 2.5~4.5 and 800~1200
				     if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(2.5,Weight[p]);//2~3 2.5~4.5 1200~2000
				     if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6)th1[p]->Fill(3.5,Weight[p]);//3~4 4.5~6 500~800 
				     if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6)th1[p]->Fill(4.5,Weight[p]);//4~5 4.5~6 800~1200
				     if(Mjj>=1200&&detajj>=4.5&&detajj<6)th1[p]->Fill(5.5,Weight[p]);//5~6 6~infi 500~800
				     if(Mjj>=500&&Mjj<800&&detajj>=6)th1[p]->Fill(6.5,Weight[p]);//6~7 6~infi 800~1200
				     if(Mjj>=800&&Mjj<1200&&detajj>=6)th1[p]->Fill(7.5,Weight[p]);//7~8 6~infi800~1200
				     if(Mjj>=1200&&detajj>=6)th1[p]->Fill(8.5,Weight[p]);//8~9 6~infi 800~1200
			     }
			     else if(name.Contains("EWK")){
				     int k;
				     if(tag.Contains("16")==0)
					     k=15*i;
				     else k=i;
				     Weight[p]=actualWeight*pweight[k];
				     cout<<p<<" "<<Weight[p]<<endl;
				     if(Mjj>=500&&Mjj<800&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(0.5,Weight[p]);//0~1, 2.5~4.5 and 500~800
				     if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(1.5,Weight[p]);//1~2 2.5~4.5 and 800~1200
				     if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(2.5,Weight[p]);//2~3 2.5~4.5 1200~2000
				     if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6)th1[p]->Fill(3.5,Weight[p]);//3~4 4.5~6 500~800 
				     if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6)th1[p]->Fill(4.5,Weight[p]);//4~5 4.5~6 800~1200
				     if(Mjj>=1200&&detajj>=4.5&&detajj<6)th1[p]->Fill(5.5,Weight[p]);//5~6 6~infi 500~800
				     if(Mjj>=500&&Mjj<800&&detajj>=6)th1[p]->Fill(6.5,Weight[p]);//6~7 6~infi 800~1200
				     if(Mjj>=800&&Mjj<1200&&detajj>=6)th1[p]->Fill(7.5,Weight[p]);//7~8 6~infi800~1200
				     if(Mjj>=1200&&detajj>=6)th1[p]->Fill(8.5,Weight[p]);//8~9 6~infi 800~1200
			     }
			     p++;
		     }
	     }
     }
     cout<<name<<endl;
     TFile*fout;
     if(name.Contains("EWK")){
	     if(turn==1)	     
		     fout= new TFile("./hist_SigOut_scale"+tag+".root","recreate");
	     else	     
		     fout= new TFile("./hist_ewk_scale"+tag+".root","recreate");
     }
     else
	     fout= new TFile("./hist_qcd_scale"+tag+".root","recreate");
     fout->cd();
     for(Int_t i=0;i<num;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Uncer_batch_bkg(){
	gSystem->Load("libTreePlayer.so");
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
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
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && ZGmass>100)";

	vector<TString> tag={"16","17","18"};

	TFile*file1[3];
        TString dir="/home/pku/anying/cms/PKU-Cluster/CombineDraw/ScalSeq/output-slimmed-rootfiles/optimal_";
	TString dir1="/home/pku/anying/cms/rootfiles/2016/";
	TString dir2="/home/pku/anying/cms/rootfiles/2017/";
	TString dir3="/home/pku/anying/cms/rootfiles/2018/";
	file1[0]=new TFile(dir+"ZA16.root");
	file1[1]=new TFile(dir+"ZA17.root");
	file1[2]=new TFile(dir+"ZA18.root");

	TFile*file2[3];
	file2[0]=new TFile(dir+"ZA-EWK16.root");
	file2[1]=new TFile(dir+"ZA-EWK17.root");
	file2[2]=new TFile(dir+"ZA-EWK18.root");

	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else{
			GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString cut1 ="("+Reco+")&&("+Gen+")";
		TString cut2 ="(("+Reco+")&& !("+Gen+"))";
		cout<<tag[i]<<" "<<jet<<endl;
		cout<<tag[i]<<" "<<GenJet<<endl;
		run(file1[i],Reco,tag[i],9,0);
		run(file2[i],Reco,tag[i],3,0);
	}
	return 1;
}
