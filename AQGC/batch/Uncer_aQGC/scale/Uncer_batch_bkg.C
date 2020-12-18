//#define num 9
#define pi 3.1415926
void run(TFile*file, TString cut1,TString tag,int num,bool turn){
     TString name=file->GetName();
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
     Double_t scalef,pileupWeight,pweight[703],Mjj,zepp,puIdweight_M,prefWeight;
     double jet1pt,jet2pt,jet1eta,jet2eta,jet1e,jet2e,jet1phi,jet2phi;
     double photonet,photoneta,photone,photonphi;
     double ptVlep, yVlep, phiVlep, massVlep,Mva;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,ele_hlt_scale;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,muon_hlt_scale;
     double photon_id_scale,photon_veto_scale;
     int lep;
     double actualWeight;
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("Mva",&Mva);
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
     tree->SetBranchAddress("puIdweight_M",&puIdweight_M);
     tree->SetBranchAddress("prefWeight",&prefWeight);
     tree->SetBranchAddress("ele1_id_scale",&ele1_id_scale);
     tree->SetBranchAddress("ele2_id_scale",&ele2_id_scale);
     tree->SetBranchAddress("ele1_reco_scale",&ele1_reco_scale);
     tree->SetBranchAddress("ele2_reco_scale",&ele2_reco_scale);
     tree->SetBranchAddress("muon1_id_scale",&muon1_id_scale);
     tree->SetBranchAddress("muon2_id_scale",&muon2_id_scale);
     tree->SetBranchAddress("muon1_iso_scale",&muon1_iso_scale);
     tree->SetBranchAddress("muon2_iso_scale",&muon2_iso_scale);
     tree->SetBranchAddress("ele_hlt_scale",&ele_hlt_scale);
     tree->SetBranchAddress("muon_hlt_scale",&muon_hlt_scale);
     tree->SetBranchAddress("photon_id_scale",&photon_id_scale);
     tree->SetBranchAddress("photon_veto_scale",&photon_veto_scale);

     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
     double Weight[num];
     TH1D*th1[num];
     TString th1name[num];
     vector<double> ZGbin={150,400,600,800,1000,2e4};
     for(Int_t i=0;i<num;i++){
	     th1name[i]=Form("hist_%d",i);
	     th1[i] = new TH1D(th1name[i],th1name[i],ZGbin.size()-1,&ZGbin[0]);
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
	     if(Mva>2e4)Mva=1999;
	     detajj=fabs(jet1eta-jet2eta);
	     Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
	     photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
	     jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
	     jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
	     delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
	     if(tag.Contains("18"))prefWeight=1;
	     if(tag.Contains("17")==0)puIdweight_M=1;
	     actualWeight=scalef*pileupWeight*prefWeight*photon_id_scale*photon_veto_scale*puIdweight_M;
	     if(lep==11)
		     actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
	     if(lep==13)
		     actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;

	     if (delta_phi>pi) delta_phi=2*pi-delta_phi;
	     int p=0;
	     if (  tformula->EvalInstance() && (zepp<2.4 && delta_phi>1.9) ){
		     for(Int_t i=first;i<(num+first);i++){
			     if(name.Contains("EWK")==0 && tag.Contains("16")){
				     if( flag && (i==109 || i==111) ) continue;
				     if(p==0) Weight[p]=actualWeight*pweight[i];
				     else Weight[p]=actualWeight*pweight[i]*2;
				     if(k%1000==0)cout<<p<<" "<<Weight[p]<<endl;
				     th1[p]->Fill(Mva,Weight[p]);
			     }
			     else if(name.Contains("EWK")==0 && tag.Contains("16")==0){
				     if( flag && (i==5 || i==7) ) continue;
				     Weight[p]=actualWeight*pweight[i];
				     cout<<p<<" "<<Weight[p]<<endl;
				     th1[p]->Fill(Mva,Weight[p]);
			     }
			     else if(name.Contains("EWK")){
				     int k;
				     if(tag.Contains("16")==0)
					     k=15*i;
				     else k=i;
				     Weight[p]=actualWeight*pweight[k];
				     cout<<p<<" "<<Weight[p]<<endl;
				     th1[p]->Fill(Mva,Weight[p]);
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
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>100 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )  )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString Pi=Form("%f",pi);
	TString dr = "(  ( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5 )";
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5 )";

	vector<TString> tag={"16","17","18"};

	TFile*file1[3];
	TString dir1="/home/pku/anying/cms/rootfiles/2016/";
	TString dir2="/home/pku/anying/cms/rootfiles/2017/";
	TString dir3="/home/pku/anying/cms/rootfiles/2018/";
	file1[0]=new TFile(dir1+"cutla-outZA16.root");
	file1[1]=new TFile(dir2+"cutla-outZA17.root");
	file1[2]=new TFile(dir3+"cutla-outZA18.root");

	TFile*file2[3];
	file2[0]=new TFile(dir1+"cutla-outZA-EWK16.root");
	file2[1]=new TFile(dir2+"cutla-outZA-EWK17.root");
	file2[2]=new TFile(dir3+"cutla-outZA-EWK18.root");

	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else{
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		TString Reco= "((("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
		cout<<tag[i]<<" "<<jet<<endl;
		run(file1[i],Reco,tag[i],9,0);
		run(file2[i],Reco,tag[i],3,0);
	}
	return 1;
}
