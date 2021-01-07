#define num 3
void run(TString cut1,TString sample,TString channel,TString type,bool turn){
     TString dir="/home/pku/anying/cms/rootfiles/2017/";     
     TFile*file;
     file=new TFile(dir+"cutla-out"+sample+"17.root");
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
//     tree->SetBranchStatus("*",0);
     Double_t scalef,pileupWeight,prefWeight,prefWeightUp,prefWeightDown;
     Double_t Mva,jet1eta,jet2eta;
     Double_t puIdweight_M,puIdweight_M_effUp,puIdweight_M_effDn,puIdweight_M_misUp,puIdweight_M_misDn;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
     double muon_hlt_scale,ele_hlt_scale;
     double weight;int lep;
     tree->SetBranchAddress("Mva",&Mva);
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("prefWeight",&prefWeight);
     tree->SetBranchAddress("puIdweight_M",&puIdweight_M);
     tree->SetBranchAddress("puIdweight_M_effUp",&puIdweight_M_effUp);
     tree->SetBranchAddress("puIdweight_M_effDn",&puIdweight_M_effDn);
     tree->SetBranchAddress("puIdweight_M_misUp",&puIdweight_M_misUp);
     tree->SetBranchAddress("puIdweight_M_misDn",&puIdweight_M_misDn);
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
     if(channel.Contains("ele"))
             cut="(lep==11)";
     if(channel.Contains("mu"))
             cut="(lep==13)";
     TTreeFormula *tformula=new TTreeFormula("formula", cut1+"&&("+cut+")", tree);
     double actualWeight[num];
     TH1D*th1[num];
     TString th1name[num];
     double ZGbin[6] = {150,400,600,800,1000,2e4};
     for(Int_t i=0;i<num;i++){
		     th1name[i]=Form("hist_%d",i);
		     th1[i] = new TH1D(th1name[i],th1name[i],5,ZGbin);
		     th1[i]->Sumw2(); 
     }      
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             double detajj=fabs(jet1eta-jet2eta);
	     int p=0;
	     if(lep==11)
		     weight=scalef*pileupWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale*ele_hlt_scale*prefWeight;
	     if(lep==13)
		     weight=scalef*pileupWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale*muon_hlt_scale*prefWeight;
	     if (  tformula->EvalInstance() ){
		     for(Int_t i=0;i<(num);i++){
			     if(type.Contains("eff")){
				     if(p==0)actualWeight[p]=weight*puIdweight_M;
				     if(p==1)actualWeight[p]=weight*puIdweight_M_effUp;
				     if(p==2)actualWeight[p]=weight*puIdweight_M_effDn;
			     }
			     else if(type.Contains("mis")){
				     if(p==0)actualWeight[p]=weight*puIdweight_M;
				     if(p==1)actualWeight[p]=weight*puIdweight_M_misUp;
				     if(p==2)actualWeight[p]=weight*puIdweight_M_misDn;

			     }
                             if(Mva>2e4) Mva=1999; 
			     th1[p]->Fill(Mva,actualWeight[p]);//8~9 6~infi 800~1200
			     p++;
		     }
	     }
     }
     TFile*fout;
     if(turn&&sample.Contains("EWK"))
	     fout= new TFile("hist_"+sample+"out_puId"+type+"_"+channel+".root","recreate");
     else
	     fout= new TFile("hist_"+sample+"_puId"+type+"_"+channel+".root","recreate");
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
	TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110&&(HLT_Mu1>0||HLT_Mu2>0))";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110&&(HLT_Ele1>0||HLT_Ele2>0))";
	TString photon = "(photonet>100 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";

	TString dr = "(drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";

        vector<TString> channels={"mu","ele"};
	vector<TString> sample={"ZA","ZA-EWK","TTA","others"};
	const int kk=channels.size();
	TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta) )";
	TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
	TString cut1 ="(("+Reco+")&&("+Gen+"))";
	TString cut2 ="(("+Reco+")&& !("+Gen+"))";
	for(int j=0;j<kk;j++){
		for(int i=0;i<sample.size();i++){
			if(sample[i].Contains("EWK")){
				run(Reco,sample[i],channels[j],"eff",0);
				run(Reco,sample[i],channels[j],"mis",0);
			}
			else{
				run(Reco,sample[i],channels[j],"eff",0);
				run(Reco,sample[i],channels[j],"mis",0);
			}
		}
	}
	return 1;
}
