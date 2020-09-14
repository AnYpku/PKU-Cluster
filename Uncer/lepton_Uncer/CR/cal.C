#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
#include "muon16_channel_scale.C"
void cal(TString particle,TString tag,TString cut,TH2D*th2[3],TString type){
	TFile* file_ID;TH2F*ID_ele;TH2F*ID_gamma;
	TFile*file_ID_sys1;TH2F*ID_muon_sys1;TH2D*ID_muon_stat1;TH2D*ID_muon_sys;
	TFile*file_ID_sys2;TH2F*ID_muon_sys2;TH2D*ID_muon_stat2;
	TFile*file_ISO_sys1;TH2F*ISO_muon_sys1;TH2D*ISO_muon_stat1;TH2D*ISO_muon_sys;
	TFile*file_ISO_sys2;TH2F*ISO_muon_sys2;TH2D*ISO_muon_stat2;
	TFile*file_reco; TH2F*Reco_ele;
	//        ofstream ftxt;
	if(particle.Contains("muon")&&tag.Contains("16")){
		file_ID_sys1=new TFile("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_systematic_RunBCDEF_SF_ID.root");
		file_ID_sys2=new TFile("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_systematic_RunGH_SF_ID.root");
		file_ISO_sys1=new TFile("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_systematic_RunBCDEF_SF_ISO.root");
		file_ISO_sys2=new TFile("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_systematic_RunGH_SF_ISO.root");
		ID_muon_sys1=(TH2F*)file_ID_sys1->Get("NUM_TightID_DEN_genTracks_eta_pt_syst");
		ID_muon_sys2=(TH2F*)file_ID_sys2->Get("NUM_TightID_DEN_genTracks_eta_pt_syst");
		ID_muon_stat1=(TH2D*)file_ID_sys1->Get("NUM_TightID_DEN_genTracks_eta_pt_stat");
		ID_muon_stat2=(TH2D*)file_ID_sys2->Get("NUM_TightID_DEN_genTracks_eta_pt_stat");
		ISO_muon_sys1=(TH2F*)file_ISO_sys1->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst");
		ISO_muon_sys2=(TH2F*)file_ISO_sys2->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst");
		ISO_muon_stat1=(TH2D*)file_ISO_sys1->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat");
		ISO_muon_stat2=(TH2D*)file_ISO_sys2->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_stat");
//		file_ID_sys1->Close();file_ID_sys2->Close();
//		file_ISO_sys1->Close();file_ISO_sys2->Close();

	}
	if(particle.Contains("muon")&&tag.Contains("17")){
		file_ID_sys1=new TFile("./muon_SFs/RunBCDEF_SF_ID_syst.root");
		file_ISO_sys1=new TFile("./muon_SFs/RunBCDEF_SF_ISO_syst.root");
		ID_muon_sys=(TH2D*)file_ID_sys1->Get("NUM_TightID_DEN_genTracks_pt_abseta_syst");
		ID_muon_stat1=(TH2D*)file_ID_sys1->Get("NUM_TightID_DEN_genTracks_pt_abseta_stat");
		ISO_muon_sys=(TH2D*)file_ISO_sys1->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta_syst");
		ISO_muon_stat1=(TH2D*)file_ISO_sys1->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta_syst");
//		file_ID_sys1->Close();file_ISO_sys1->Close();
	}
	if(particle.Contains("muon")&&tag.Contains("18")){
		file_ID_sys1=new TFile("./muon_SFs/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root");
		file_ISO_sys1=new TFile("./muon_SFs/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root");
		ID_muon_stat1=(TH2D*)file_ID_sys1->Get("NUM_TightID_DEN_TrackerMuons_pt_abseta");
		ISO_muon_stat1=(TH2D*)file_ISO_sys1->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");
//		file_ID_sys1->Close();file_ISO_sys1->Close();
	}
	if(particle.Contains("ele")&&tag.Contains("16")){
		file_ID=new TFile("./egamma_SFs/2016LegacyReReco_ElectronMedium_Fall17V2.root");
		file_reco=new TFile("./egamma_SFs/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root");     
		ID_ele=(TH2F*)file_ID->Get("EGamma_SF2D");
		Reco_ele=(TH2F*)file_reco->Get("EGamma_SF2D");
//		file_ID->Close();file_reco->Close();
	}
	if(particle.Contains("ele")&&tag.Contains("17")){
		file_ID=new TFile("./egamma_SFs/2017_ElectronMedium.root");
		file_reco=new TFile("./egamma_SFs/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");
		ID_ele=(TH2F*)file_ID->Get("EGamma_SF2D");
		Reco_ele=(TH2F*)file_reco->Get("EGamma_SF2D");
//		file_ID->Close();file_reco->Close();
	}
	if(particle.Contains("ele")&&tag.Contains("18")){
		file_ID=new TFile("./egamma_SFs/2018_ElectronMedium.root");
		file_reco=new TFile("./egamma_SFs/egammaEffi.txt_EGM2D_updatedAll.root");
		ID_ele=(TH2F*)file_ID->Get("EGamma_SF2D");
		Reco_ele=(TH2F*)file_reco->Get("EGamma_SF2D");
//		file_ID->Close();file_reco->Close();
	}
	if(particle.Contains("photon")&&tag.Contains("16")){
		file_ID=new TFile("./egamma_SFs/Fall17V2_2016_Medium_photons.root");
		ID_gamma=(TH2F*)file_ID->Get("EGamma_SF2D");
//		file_ID->Close();
	}
	if(particle.Contains("photon")&&tag.Contains("17")){
		file_ID=new TFile("./egamma_SFs/2017_PhotonsMedium.root ");
		ID_gamma=(TH2F*)file_ID->Get("EGamma_SF2D");
//		file_ID->Close();
	}
	if(particle.Contains("photon")&&tag.Contains("18")){
		file_ID=new TFile("./egamma_SFs/2018_PhotonsMedium.root ");
		ID_gamma=(TH2F*)file_ID->Get("EGamma_SF2D");
//		file_ID->Close();
	}
	cout<<"open SFs file successfully"<<endl;
	TFile*fin;
	if(tag.Contains("16"))
		fin=new TFile("/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/unfold_"+tag+"outZA-EWK.root");
	else fin=new TFile("/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/unfold_"+tag+"outZA-EWK-pweight.root");
	Double_t mjj_bins[4]={500, 800, 1200, 2000};
	Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
	for(int i=0;i<3;i++){
		th2[i] = new TH2D(Form("th2_%i",i),"th2",3, mjj_bins, 3, detajj_bins);
	}
	TTree*tree=(TTree*)fin->Get("demo");
	TTreeFormula *tformula=new TTreeFormula("formula", cut, tree);
	double photoneta,photonet,ptlep1,ptlep2,etalep1,etalep2;
	double muon1_id_scale,muon2_id_scale,ele1_id_scale,ele2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale;
        int lep;double Mjj,deltaetajj;
        tree->SetBranchAddress("lep",&lep);
        tree->SetBranchAddress("Mjj",&Mjj);
        tree->SetBranchAddress("deltaetajj",&deltaetajj);
	tree->SetBranchAddress("muon1_id_scale",   &muon1_id_scale);
	tree->SetBranchAddress("muon2_id_scale",   &muon2_id_scale);
	tree->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale);
	tree->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale);
	tree->SetBranchAddress("photon_id_scale", &photon_id_scale);
	tree->SetBranchAddress("ele1_id_scale",   &ele1_id_scale);
	tree->SetBranchAddress("ele2_id_scale",   &ele2_id_scale);
	tree->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale);
	tree->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale);
	tree->SetBranchAddress("ptlep1",&ptlep1);
	tree->SetBranchAddress("ptlep2",&ptlep2);
	tree->SetBranchAddress("etalep1",&etalep1);
	tree->SetBranchAddress("etalep2",&etalep2);
	tree->SetBranchAddress("photonet",&photonet);
	tree->SetBranchAddress("photoneta",&photoneta);
	double muon1_ID_Uncer,muon2_ID_Uncer,muon1_ISO_Uncer,muon2_ISO_Uncer,muon_WeightUp,muon_WeightDn,muon_Weight;
	double ele1_ID_Uncer,ele2_ID_Uncer,ele1_Reco_Uncer,ele2_Reco_Uncer,photon_ID_Uncer,ele_WeightUp,ele_WeightDn,photon_WeightUp,photon_WeightDn,ele_Weight,photon_Weight;
	double count_mu=0,count_muUp=0,count_muDn=0;
	double count_ele=0,count_eleUp=0,count_eleDn=0;
	double count_gamma=0,count_gammaUp=0,count_gammaDn=0;
        cout<<"begin the loop"<<endl;
	for(int k=0;k<tree->GetEntries();k++){
		tree->GetEntry(k);
		if(particle.Contains("muon")&&tag.Contains("16")&&lep==13){
			muon1_ID_Uncer=sqrt( pow(get_muon_ID_sys16(etalep1,ptlep1,ID_muon_sys1,ID_muon_sys2),2)+ pow(get_muon_ID_stat16(etalep1,ptlep1,ID_muon_stat1,ID_muon_stat2),2)  );
			muon2_ID_Uncer=sqrt( pow(get_muon_ID_sys16(etalep2,ptlep2,ID_muon_sys1,ID_muon_sys2),2)+ pow(get_muon_ID_stat16(etalep2,ptlep2,ID_muon_stat1,ID_muon_stat2),2)  );
			muon1_ISO_Uncer=sqrt(  pow(get_muon_iso_sys16(etalep1,ptlep1,ISO_muon_sys1,ISO_muon_sys2),2)+ pow(get_muon_iso_stat16(etalep1,ptlep1,ISO_muon_stat1,ISO_muon_stat2),2) );
			muon2_ISO_Uncer=sqrt(  pow(get_muon_iso_sys16(etalep2,ptlep2,ISO_muon_sys1,ISO_muon_sys2),2)+ pow(get_muon_iso_stat16(etalep2,ptlep2,ISO_muon_stat1,ISO_muon_stat2),2) );
			muon_WeightUp=(muon1_id_scale+muon1_ID_Uncer)*(muon2_id_scale+muon2_ID_Uncer)*(muon1_iso_scale+muon1_ISO_Uncer)*(muon2_iso_scale+muon2_ISO_Uncer) ;
			muon_WeightDn=(muon1_id_scale-muon1_ID_Uncer)*(muon2_id_scale-muon2_ID_Uncer)*(muon1_iso_scale-muon1_ISO_Uncer)*(muon2_iso_scale-muon2_ISO_Uncer) ;
			muon_Weight=muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale;
			if(k%5000==0)
                        cout<<tag<<" get muon SFs"<<endl;
		}
		if(particle.Contains("muon")&&tag.Contains("17")&&lep==13){
			muon1_ID_Uncer=sqrt( pow(get_muon_ID_sys(etalep1,ptlep1,ID_muon_sys),2)+ pow(get_muon_ID_stat(etalep1,ptlep1,ID_muon_stat1),2)  );
			muon2_ID_Uncer=sqrt( pow(get_muon_ID_sys(etalep2,ptlep2,ID_muon_sys),2)+ pow(get_muon_ID_stat(etalep2,ptlep2,ID_muon_stat1),2)  );
			muon1_ISO_Uncer=sqrt(  pow(get_muon_iso_sys(etalep1,ptlep1,ISO_muon_sys),2)+ pow(get_muon_iso_stat(etalep1,ptlep1,ISO_muon_stat1),2) );
			muon2_ISO_Uncer=sqrt(  pow(get_muon_iso_sys(etalep2,ptlep2,ISO_muon_sys),2)+ pow(get_muon_iso_stat(etalep2,ptlep2,ISO_muon_stat1),2) );
			muon_WeightUp=(muon1_id_scale+muon1_ID_Uncer)*(muon2_id_scale+muon2_ID_Uncer)*(muon1_iso_scale+muon1_ISO_Uncer)*(muon2_iso_scale+muon2_ISO_Uncer) ;
			muon_WeightDn=(muon1_id_scale-muon1_ID_Uncer)*(muon2_id_scale-muon2_ID_Uncer)*(muon1_iso_scale-muon1_ISO_Uncer)*(muon2_iso_scale-muon2_ISO_Uncer) ;
			muon_Weight=muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale;
			if(k%5000==0)
                        cout<<tag<<" get muon SFs"<<endl;
		}
		if(particle.Contains("muon")&&tag.Contains("18")&&lep==13){
			muon1_ID_Uncer=sqrt( pow(get_muon_ID_stat(etalep1,ptlep1,ID_muon_stat1),2)  );
			muon2_ID_Uncer=sqrt( pow(get_muon_ID_stat(etalep2,ptlep2,ID_muon_stat1),2)  );
			muon1_ISO_Uncer=sqrt( pow(get_muon_iso_stat(etalep1,ptlep1,ISO_muon_stat1),2) );
			muon2_ISO_Uncer=sqrt( pow(get_muon_iso_stat(etalep2,ptlep2,ISO_muon_stat1),2) );
			muon_WeightUp=(muon1_id_scale+muon1_ID_Uncer)*(muon2_id_scale+muon2_ID_Uncer)*(muon1_iso_scale+muon1_ISO_Uncer)*(muon2_iso_scale+muon2_ISO_Uncer) ;
			muon_WeightDn=(muon1_id_scale-muon1_ID_Uncer)*(muon2_id_scale-muon2_ID_Uncer)*(muon1_iso_scale-muon1_ISO_Uncer)*(muon2_iso_scale-muon2_ISO_Uncer) ;
			muon_Weight=muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale;
			if(k%5000==0)
                        cout<<tag<<" get muon SFs "<<muon_Weight<<" "<<muon_WeightUp<<" "<<muon_WeightDn<<endl;
		}
		if(particle.Contains("ele")&&lep==11){
			ele1_ID_Uncer=get_ele_ID(etalep1,ptlep1,ID_ele);
			ele2_ID_Uncer=get_ele_ID(etalep2,ptlep2,ID_ele);
			ele1_Reco_Uncer=get_ele_Reco(etalep1,ptlep1,Reco_ele);
			ele2_Reco_Uncer=get_ele_Reco(etalep2,ptlep2,Reco_ele);
			ele_Weight=ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale;
			if(type.Contains("reco")){
				ele_WeightUp=(ele1_id_scale)*(ele2_id_scale)*(ele1_reco_scale+ele1_Reco_Uncer)*(ele2_reco_scale+ele2_Reco_Uncer);
				ele_WeightDn=(ele1_id_scale)*(ele2_id_scale)*(ele1_reco_scale-ele1_Reco_Uncer)*(ele2_reco_scale-ele2_Reco_Uncer);
			}
			else{ 
				ele_WeightUp=(ele1_id_scale+ele1_ID_Uncer)*(ele2_id_scale+ele2_ID_Uncer)*(ele1_reco_scale)*(ele2_reco_scale);
				ele_WeightDn=(ele1_id_scale-ele1_ID_Uncer)*(ele2_id_scale-ele2_ID_Uncer)*(ele1_reco_scale)*(ele2_reco_scale);
			}
			if(k%5000==0)cout<<tag<<" get ele SFs "<<ele_Weight<<" "<<ele_WeightUp<<" "<<ele_WeightDn<<endl;
		}
		if(particle.Contains("photon")&&photonet>0){
			photon_ID_Uncer=get_photon_ID(photoneta,photonet,ID_gamma);
			photon_WeightUp=photon_id_scale+photon_ID_Uncer;
			photon_WeightDn=photon_id_scale-photon_ID_Uncer;
			photon_Weight=photon_id_scale;
			if(k%5000==0)cout<<tag<<" get photon SFs "<<photon_Weight<<" "<<photon_WeightUp<<" "<<photon_WeightDn<<endl;
		}

		if (  tformula->EvalInstance() ){
			if(lep==13){
				count_mu=count_mu+muon_Weight;
				count_muUp=count_muUp+muon_WeightUp;
				count_muDn=count_muDn+muon_WeightDn;
				th2[0]->Fill(Mjj,deltaetajj,muon_Weight);     
				th2[1]->Fill(Mjj,deltaetajj,muon_WeightUp);     
				th2[2]->Fill(Mjj,deltaetajj,muon_WeightDn);     
			}
			if(lep==11){
				count_ele  =count_ele+ele_Weight;
				count_eleUp=count_eleUp+ele_WeightUp;
				count_eleDn=count_eleDn+ele_WeightDn;
				th2[0]->Fill(Mjj,deltaetajj,ele_Weight);     
				th2[1]->Fill(Mjj,deltaetajj,ele_WeightUp);     
				th2[2]->Fill(Mjj,deltaetajj,ele_WeightDn);     
			}
			if(photonet>0){
				count_gamma  =count_gamma+photon_Weight;
				count_gammaUp=count_gammaUp+photon_WeightUp;
				count_gammaDn=count_gammaDn+photon_WeightDn;
				th2[0]->Fill(Mjj,deltaetajj,photon_Weight);     
				th2[1]->Fill(Mjj,deltaetajj,photon_WeightUp);     
				th2[2]->Fill(Mjj,deltaetajj,photon_WeightDn);     
			}
		}

	}
	cout<<particle<<" "<<count_mu<<" "<<count_muUp<<" "<<count_muDn<<endl;
	cout<<particle<<" "<<count_ele<<" "<<count_eleUp<<" "<<count_eleDn<<endl;
	cout<<particle<<" "<<count_gamma<<" "<<count_gammaUp<<" "<<count_gammaDn<<endl;
	TFile*fout=new TFile("./"+particle+"_"+type+"_2d_"+tag+".root","recreate");
	fout->cd();
	for(int i=0;i<3;i++){
            th2[i]->Write();
	}
        fout->Close();
}
int cal(){
	TString GenLEPmu  = "genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4";
	TString GenLEPele = "genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5";
	TString GenPhoton = "genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) )";
	TString GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
	TString GenDr = "gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5";
	TString GenSignalRegion = "genMjj >500 && gendetajj>2.5";
	TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
	TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
	TString photon = "photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
	TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
	TString dr = "drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
	TString SignalRegion = "Mjj>500 && deltaetajj>2.5 && Mva>100";
	TString ControlRegion = "Mjj>150 && Mjj<400 && Mva>100";
        TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+ControlRegion; 
	vector<TString> par={"ele","muon","photon"};
	TH2D*th2[3][3];//particle 3
	for(int i=0;i<par.size();i++){
		//		cal(par[i],"16");
		//		cal(par[i],"17");
		TString type;
		if(par[i].Contains("muon")){ 
			cal(par[i],"16",Reco,th2[i],"all");
			cal(par[i],"17",Reco,th2[i],"all");
			cal(par[i],"18",Reco,th2[i],"all");
		}
		if(par[i].Contains("photon")){ 
			cal(par[i],"16",Reco,th2[i],"ID");
			cal(par[i],"17",Reco,th2[i],"ID");
			cal(par[i],"18",Reco,th2[i],"ID");
		}
		if(par[i].Contains("ele")){ 
			cal(par[i],"16",Reco,th2[i],"ID");
			cal(par[i],"17",Reco,th2[i],"ID");
			cal(par[i],"18",Reco,th2[i],"ID");
			cal(par[i],"16",Reco,th2[i],"reco");
			cal(par[i],"17",Reco,th2[i],"reco");
			cal(par[i],"18",Reco,th2[i],"reco");
		}
	}
	return 1;
}
