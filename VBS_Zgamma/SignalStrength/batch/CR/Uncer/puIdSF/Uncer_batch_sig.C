#define num 3
void run(TString cut1,TString sample,TString channel,TString type,bool turn,TString tag){
     Double_t Mjj_bins[4]={150,300,400,500};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TString dir="/home/pku/anying/cms/rootfiles/20"+tag+"/";     
     TFile*file;
     if(sample.Contains("EWK"))
	     file=new TFile(dir+"unfold_GenCutla-"+sample+tag+".root");
     else
	     file=new TFile(dir+"cutla-out"+sample+tag+".root");
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
//     tree->SetBranchStatus("*",0);
     Double_t scalef,pileupWeight,prefWeight,prefWeightUp,prefWeightDown;
     Double_t Mjj,jet1eta,jet2eta;
     Double_t puIdweight_T,puIdweight_T_effUp,puIdweight_T_effDn,puIdweight_T_misUp,puIdweight_T_misDn;
     Double_t puIdweight_M,puIdweight_M_effUp,puIdweight_M_effDn,puIdweight_M_misUp,puIdweight_M_misDn;
     Double_t puIdweight_L,puIdweight_L_effUp,puIdweight_L_effDn,puIdweight_L_misUp,puIdweight_L_misDn;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
     double muon_hlt_scale,ele_hlt_scale;
     double weight;int lep;
     tree->SetBranchAddress("Mjj",&Mjj);
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("prefWeight",&prefWeight);
     tree->SetBranchAddress("puIdweight_T",&puIdweight_T);
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

     TString cut;
     if(channel.Contains("elebarrel"))
             cut="(lep==11&&fabs(photoneta)<1.4442)";
     if(channel.Contains("mubarrel"))
             cut="(lep==13&&fabs(photoneta)<1.4442)";
     if(channel.Contains("eleendcap"))
             cut="(lep==11&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566)";
     if(channel.Contains("muendcap"))
             cut="(lep==13&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566)";
     TTreeFormula *tformula=new TTreeFormula("formula", cut1+"&&("+cut+")", tree);
     double actualWeight[num];
     TH1D*th1[num];
     TString th1name[num];
     for(Int_t i=0;i<num;i++){
		     th1name[i]=Form("hist_%d",i);
		     th1[i] = new TH1D(th1name[i],th1name[i],3,Mjj_bins);
		     th1[i]->Sumw2(); 
     }      
     double puIdweight,puIdweight_effUp,puIdweight_effDn,puIdweight_misUp,puIdweight_misDn;
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             double detajj=fabs(jet1eta-jet2eta);
	     int p=0;
	     if(lep==11)
		     weight=scalef*pileupWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale*ele_hlt_scale*prefWeight;
	     if(lep==13)
		     weight=scalef*pileupWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale*muon_hlt_scale*prefWeight;
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
			     if(Mjj<500)th1[p]->Fill(Mjj,actualWeight[p]);//0~1, 2.5~4.5 and 500~800
			     p++;
		     }
	     }
     }
     TFile*fout;
     if(turn&&sample.Contains("EWK"))
	     fout= new TFile("hist_"+sample+"out_puId"+type+"_"+channel+tag+"CR.root","recreate");
     else
	     fout= new TFile("hist_"+sample+"_puId"+type+"_"+channel+tag+"CR.root","recreate");
     fout->cd();
     for(Int_t i=0;i<num;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Uncer_batch_sig(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenControlRegion = "(genMjj <500 && genMjj>150 && genZGmass>100)";

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString dr = "(drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString jet;

        vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	vector<TString> sample={"ZA_interf"};
//	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	const int kk=channels.size();
	TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenControlRegion;
	TString ControlRegion = "(Mjj<500 && Mjj>150  && Mva>100)";
	vector<TString> tag={"16","17","18"};
	for(int j=0;j<kk;j++){
		for(int i=0;i<sample.size();i++){
			for(int k=0;k<tag.size();k++){
                                if(tag[k].Contains("16")){
                                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
                                }
                                else if(tag[k].Contains("17")){
                                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
                                }
                                else if(tag[k].Contains("18")){
                                        jet = "( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
                                }
                                TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+ControlRegion;
                                TString cut1 ="(("+Reco+")&&("+Gen+"))";
                                TString cut2 ="(("+Reco+")&& !("+Gen+"))";
                                cout<<tag[k]<<" "<<channels[j]<<" "<<sample[i]<<endl;
				if(sample[i].Contains("EWK")){
					run(cut2,sample[i],channels[j],"eff",1,tag[k]);
					run(cut2,sample[i],channels[j],"mis",1,tag[k]);
					run(cut1,sample[i],channels[j],"eff",0,tag[k]);
					run(cut1,sample[i],channels[j],"mis",0,tag[k]);
				}
				else{
					run(Reco,sample[i],channels[j],"eff",0,tag[k]);
					run(Reco,sample[i],channels[j],"mis",0,tag[k]);
				}
			}
		}
	}
	return 1;
}
