#define pi 3.1415926
void run(TString dir,TString name,TString cut1,TString tag,TString channel){
     Double_t mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     
     TString fname=name+tag;
     TFile*file;
     if(name.Contains("plj")) file=new TFile(dir+fname+"_weight"+".root") ; 
     else file=new TFile(dir+fname+".root") ;
     cout<<tag<<" "<<name<<" "<<channel<<endl;
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");
//     TTree*tree=(TTree*)file->Get("outtree");
     int lep;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,pileupWeight,prefWeight,puIdweight_M;
     double jet1pt,jet2pt,jet1eta,jet2eta,jet1e,jet2e,jet1phi,jet2phi;
     double photonet,photoneta,photone,photonphi;
     double muon_hlt_scale,ele_hlt_scale;
     double ptVlep, yVlep, phiVlep, massVlep;
     double Mjj,scalef,zepp,delta_phi;
     tree->SetBranchAddress("lep",&lep);
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
     tree->SetBranchAddress("photoneta",&photoneta);
     tree->SetBranchAddress("photonet",&photonet);
     tree->SetBranchAddress("photonphi",&photonphi);
     tree->SetBranchAddress("photone",&photone);
     tree->SetBranchAddress("ptVlep",&ptVlep);
     tree->SetBranchAddress("yVlep",&yVlep);
     tree->SetBranchAddress("phiVlep",&phiVlep);
     tree->SetBranchAddress("massVlep",&massVlep);
     tree->SetBranchAddress("scalef", &scalef);
     tree->SetBranchAddress("pileupWeight", &pileupWeight);
     tree->SetBranchAddress("prefWeight", &prefWeight);
     tree->SetBranchAddress("puIdweight_M", &puIdweight_M);
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
     TString th2name,th2name_out;
     if(name.Contains("EWK")) {
	     th2name="hist_sig";
     }
     else  th2name="hist_bkg";
             
     TH1D* hist= new TH1D(th2name,name+Form("\t\t %0.f<Mjj<%0.f  reco;;yields",mjj_bins[0],mjj_bins[3]),9,0,9);
     
     TString var2="Mjj";
     TString var1="fabs(jet1eta-jet2eta)";
     double lumi;
     if(tag.Contains("16"))lumi=35.86;
     if(tag.Contains("17"))lumi=41.52;
     if(tag.Contains("18"))lumi=59.7;
     TString weight="1";
     TString cut;
     if(channel.Contains("elebarrel"))
	     cut="lep==11&&fabs(photoneta)<1.4442";
     if(channel.Contains("mubarrel"))
	     cut="lep==13&&fabs(photoneta)<1.4442";
     if(channel.Contains("eleendcap"))
	     cut="lep==11&&(fabs(photoneta)<2.5&&fabs(photoneta)>1.566)";
     if(channel.Contains("muendcap"))
	     cut="lep==13&&(fabs(photoneta)<2.5&&fabs(photoneta)>1.566)";
     TTreeFormula *tformula1=new TTreeFormula("formula1", "(("+cut1+")&&("+cut+"))", tree);
     double actualWeight,detajj;
     TLorentzVector Zp4, photonp4, jet1p4, jet2p4;
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
             detajj=fabs(jet1eta-jet2eta);
	     Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
	     photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
	     jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
	     jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
	     delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
	     if (delta_phi>pi) delta_phi=2*pi-delta_phi;
	     if(tag.Contains("18"))  prefWeight=1;
	     if(tag.Contains("17")==0)  puIdweight_M=1;
	     actualWeight=scalef*pileupWeight*prefWeight*puIdweight_M*lumi;
		     if(lep==11)       
			     actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale*ele_hlt_scale;
		     if(lep==13)       
			     actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale*muon_hlt_scale;
	     if(name.Contains("plj")) actualWeight=scalef;
	     if (  tformula1->EvalInstance() &&(zepp<2.4 && delta_phi>1.9) ){ 
		     //cout<<name<<" "<<scalef<<" "<<pileupWeight<<" "
		     //<<ele1_id_scale<<" "<<ele2_id_scale<<" "<<ele1_reco_scale<<" "<<ele2_reco_scale<<" "
		     //<<muon1_id_scale<<" "<<muon2_id_scale<<" "<<muon1_iso_scale<<" "<<muon2_iso_scale<<" "
		     //<<photon_id_scale<<" "
		     //<<prefWeight<<" "<<actualWeight<<endl;
		     if(Mjj>500&&Mjj<800&&detajj>2.5&&detajj<4.5)hist->Fill(0.5,actualWeight);//0~1, 2.5~4.5 and 500~800
		     if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5)hist->Fill(1.5,actualWeight);//1~2 2.5~4.5 and 800~1200
		     if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)hist->Fill(2.5,actualWeight);//2~3 2.5~4.5 1200~2000
		     if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6)hist->Fill(3.5,actualWeight);//3~4 4.5~6 500~800 
		     if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6)hist->Fill(4.5,actualWeight);//4~5 4.5~6 800~1200
		     if(Mjj>=1200&&detajj>=4.5&&detajj<6)hist->Fill(5.5,actualWeight);//5~6 6~infi 500~800
		     if(Mjj>=500&&Mjj<800&&detajj>=6)hist->Fill(6.5,actualWeight);//6~7 6~infi 800~1200
		     if(Mjj>=800&&Mjj<1200&&detajj>=6)hist->Fill(7.5,actualWeight);//7~8 6~infi800~1200
		     if(Mjj>=1200&&detajj>=6)hist->Fill(8.5,actualWeight);//8~9 6~infi 800~1200 

	     }
     }
     TFile*fout=new TFile("./root/hist_"+name+"_"+tag+channel+".root","recreate");
     fout->cd();
     hist->Write();
     fout->Close();
}
int Build_Hist(){
	TString LEPmu = "(lep==13 && (HLT_Mu1>0 || HLT_Mu2>0 || HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet;
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && Mva>100)";
//	TString opt="(zepp<2.4 && delta_phi>1.9)";
//	vector<TString> tags={"16","17","18"};
	vector<TString> tags={"17"};
	TString dir1;
	dir1="/home/pku/anying/cms/rootfiles/2017/m1/cutla-out";
	TString Reco;
//	vector<TString> names={"ZA-EWK","ST","VV","TTA","ZA","plj"};
	vector<TString> names={"ZA"};
	vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	for(int k=0;k<tags.size();k++){
		if(tags[k].Contains("17")==1){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else{
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		Reco= "((("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
		cout<<tags[k]<<" "<<jet<<endl;
//		if(tags[k].Contains("17")==0) continue;
		for(int j=0;j<names.size();j++){     
			for(int i=0;i<channels.size();i++){
				run(dir1,names[j],Reco,tags[k],channels[i]);
			}
		}
	}
	return 1;
}
