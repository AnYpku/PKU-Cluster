#define pi 3.1415926
void run(TString dir,TString name,TString cut1,TString cut2,TString tag,TString channel){
     vector<double> mjj_bins={150,300,400,500};
     TFile*file;
     if(name.Contains("EWK"))
             file=new TFile(dir+name+tag+".root") ;
     else if(name.Contains("plj")) file=new TFile(dir+name+tag+"_weight.root") ;
     else file=new TFile(dir+name+tag+".root") ;
     cout<<tag<<" "<<name<<" "<<channel<<endl;
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");
     int lep;double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,pileupWeight,prefWeight,puIdweight_M;
     double ele_hlt_scale,muon_hlt_scale;
     double Mjj,jet1eta,jet2eta,scalef;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("Mjj",&Mjj);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
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
     tree->SetBranchAddress("ele_hlt_scale", &ele_hlt_scale);
     tree->SetBranchAddress("muon_hlt_scale", &muon_hlt_scale);
     TString th2name,th2name_out;
     if(name.Contains("EWK")) {
	     th2name="hist_sig";
	     th2name_out="hist_sigout";
     }
     else  th2name="hist_bkg";
             
     TH1D* hist= new TH1D(th2name,name+Form("\t\t %0.f<Mjj<%0.f  reco && gen;;yields",mjj_bins[0],mjj_bins[mjj_bins.size()-1]),mjj_bins.size()-1,mjj_bins[0],mjj_bins[mjj_bins.size()-1]);
     TH1D* hist_out= new TH1D(th2name_out,name+Form("\t\t %0.f<Mjj<%0.f  reco && !gen;;yields",mjj_bins[0],mjj_bins[mjj_bins.size()-1]),mjj_bins.size()-1,mjj_bins[0],mjj_bins[mjj_bins.size()-1]);
     
     TString var2="Mjj";
     TString var1="fabs(jet1eta-jet2eta)";

     double lumi;
     if(tag.Contains("16"))lumi=35.86;
     if(tag.Contains("17"))lumi=41.52;
     if(tag.Contains("18"))lumi=59.7;
     TString weight="1";
     if(channel.Contains("mu")){
             if(tag.Contains("2018")==0){
		     weight=weight+"*pileupWeight * scalef*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*prefWeight*photon_veto_scale";
	     }
	     else 
		     weight=weight+"*pileupWeight * scalef*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale";
     }
     if(channel.Contains("ele")){
	     if(tag.Contains("2018")==0){
		     weight=weight+"*pileupWeight * scalef*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*prefWeight*photon_veto_scale";
	     }
	     else
		     weight=weight+"*pileupWeight * scalef*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale";
     }
     TString cut;
     if(channel.Contains("elebarrel"))
	     cut="(lep==11&&fabs(photoneta)<1.4442)";
     if(channel.Contains("mubarrel"))
	     cut="(lep==13&&fabs(photoneta)<1.4442)";
     if(channel.Contains("eleendcap"))
	     cut="(lep==11&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566)";
     if(channel.Contains("muendcap"))
	     cut="(lep==13&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566)";
     TTreeFormula *tformula1=new TTreeFormula("formula1", "("+cut1+"&&("+cut+"))", tree);
     TTreeFormula *tformula2=new TTreeFormula("formula1", "("+cut2+"&&("+cut+"))", tree);
     double actualWeight;
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
             double detajj=fabs(jet1eta-jet2eta);
             if(tag.Contains("18"))  prefWeight=1;
             if(tag.Contains("17")==1)  puIdweight_M=1;
             actualWeight=scalef*pileupWeight*prefWeight*lumi*photon_veto_scale*puIdweight_M;
	     if(lep==11)       
		     actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*ele_hlt_scale;
	     if(lep==13)       
		     actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*muon_hlt_scale;
             if(name.Contains("plj")) actualWeight=scalef;
	     if (  tformula1->EvalInstance() ){ 
		     //cout<<name<<" "<<scalef<<" "<<pileupWeight<<" "
		     //    <<ele1_id_scale<<" "<<ele2_id_scale<<" "<<ele1_reco_scale<<" "<<ele2_reco_scale<<" "
		     //    <<muon1_id_scale<<" "<<muon2_id_scale<<" "<<muon1_iso_scale<<" "<<muon2_iso_scale<<" "
		     //    <<photon_id_scale<<" "
		     //    <<prefWeight<<" "<<actualWeight<<endl;
		     if(Mjj<500&&Mjj>=150)hist->Fill(Mjj,actualWeight);//0~1, 2.5~4.5 and 500~800

	     }
	     if(name.Contains("EWK")){
		     if (  tformula2->EvalInstance() ){ 
			     if(Mjj>=150&&Mjj<500)hist_out->Fill(Mjj,actualWeight);//0~1, 2.5~4.5 and 500~800
		     }
	     }
     }
     //     if(name.Contains("EWK")){
     //	     tree->Draw(var1+":"+var2+">>"+th2name,"("+cut1+"&&("+cut+"))*"+weight+"*"+lumi,"goff");
     //	     tree->Draw(var1+":"+var2+">>"+th2name_out,"("+cut2+"&&("+cut+"))*"+weight+"*"+lumi,"goff");
     //     }
     //     else if(name.Contains("plj")){
     //	     tree->Draw(var1+":"+var2+">>"+th2name,"("+cut1+"&&("+cut+"))*scalef*"+lumi,"goff");
     //     }
     //     else{
     //	     tree->Draw(var1+":"+var2+">>"+th2name,"("+cut1+"&&("+cut+"))*"+weight+"*"+lumi,"goff");
     //     }
     TFile*fout=new TFile("./root/hist_"+name+"_"+tag+"CR_"+channel+".root","recreate");
/*     int binx=hist->GetNbinsX();
     int biny=hist->GetNbinsY();
     for(int i=1;i<binx+1;i++){
	     hist->SetBinContent(i,biny,hist->GetBinContent(i,biny)+hist->GetBinContent(i,biny+1));
	     if(name.Contains("EWK"))
		     hist_out->SetBinContent(i,biny,hist_out->GetBinContent(i,biny)+hist_out->GetBinContent(i,biny+1));
     }
     for(int j=1;j<biny+1;j++){
	     hist->SetBinContent(binx,j,hist->GetBinContent(binx,j)+hist->GetBinContent(binx+1,j));
	     if(name.Contains("EWK"))
		     hist_out->SetBinContent(binx,j,hist_out->GetBinContent(binx,j)+hist_out->GetBinContent(binx+1,j));
     }
     hist->SetBinContent(binx,biny,hist->GetBinContent(binx,biny)+hist->GetBinContent(binx+1,biny+1));
     //add overflow bin*/
     hist->Write();
     if(name.Contains("EWK"))
	     hist_out->Write();
     fout->Close();
}
int Build_Hist(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4 && genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5 && genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenControlRegion = "(genMjj <500 && genMjj>150 && genZGmass>100)";

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString ControlRegion = "(Mjj>150 && Mjj<500 && Mva>100)";

        vector<TString> tags={"16","17","18"};
        TString dir1[3],dir[3];
        dir1[0]="/home/pku/anying/cms/rootfiles/2016/cutla-out";
        dir1[1]="/home/pku/anying/cms/rootfiles/2017/cutla-out";
        dir1[2]="/home/pku/anying/cms/rootfiles/2018/cutla-out";

        dir[0]="/home/pku/anying/cms/rootfiles/2016/unfold_GenCutla-";
        dir[1]="/home/pku/anying/cms/rootfiles/2017/unfold_GenCutla-";
        dir[2]="/home/pku/anying/cms/rootfiles/2018/unfold_GenCutla-";

	vector<TString> names={"ZA-EWK","ST","VV","TTA","ZA","plj"};
//	vector<TString> names={"ZA-EWK"};
	vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};

	for(int k=0;k<tags.size();k++){
		if(tags[k].Contains("17")){
			GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)"; 
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else{
			GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
//		if(tags[k].Contains("17")==0) continue;
		TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenControlRegion;
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+ControlRegion;
		TString cut1 ="(("+Reco+")&&("+Gen+"))";
		TString cut2 ="(("+Reco+")&& !("+Gen+"))";
                cout<<dir1[k]<<" "<<tags[k]<<" "<<jet<<endl;
                cout<<GenJet<<endl;
		for(int j=0;j<names.size();j++){     
			for(int i=0;i<channels.size();i++){
				if(names[j].Contains("EWK")){
					run(dir[k],"ZA-EWK",cut1,cut2,tags[k],channels[i]);
				}
				else{
					run(dir1[k],names[j],Reco,Reco,tags[k],channels[i]);
				}
			}
		}
	}
	return 1;
}
