void run(TString var,TString genvar,TString tag,TString filename){
	fstream f1("./summary_"+var+"_"+tag+".txt",ios::app);
        ifstream file(filename);
        string line;
        if( (tag.Contains("18")&&filename.Contains("l1pref"))==0 ){
		if(!file.is_open()) cout<<"can not open the file "<<filename<<endl;
		if(file.is_open()){
			while(!file.eof()){
				getline(file,line);
				f1<<line<<endl;
			} 
		}
	}
	else cout<<"2018 does not have l1prefiring, exit!"<<endl;
        file.close();
        f1.close();
}
int Print_Uncer_all(){
	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
        vector<TString> tag={"16","17","18"};
        vector<TString> filename;
        for(int i=0;i<recovars.size();i++){
		for(int j=0;j<tag.size();j++){
			TString f_fake        ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/fakephoton/"+recovars[i]+"_fake_uncer"+tag[j]+".txt";
			TString f_QCD_pdf     ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/pdf/"+recovars[i]+"_uncer_qcd_16.txt";
			TString f_Sigout_pdf  ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/pdf/"+recovars[i]+"_uncer_Sigout_"+tag[j]+".txt";
			TString f_Sig_pdf     ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/pdf/"+genvars[i]+"_uncer"+tag[j]+".txt";
			TString f_QCD_scale   ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/scale/"+recovars[i]+"_uncer_qcd_"+tag[j]+".txt";
			TString f_QCD_scaleband   ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/scale/"+recovars[i]+"_uncer_scaleband_"+tag[j]+".txt";
			TString f_QCD_scale_extra_up  ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/scale/"+recovars[i]+"_uncer_QCD_extra_up_"+tag[j]+".txt";
			TString f_QCD_scale_extra_down  ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/scale/"+recovars[i]+"_uncer_QCD_extra_down_"+tag[j]+".txt";
			TString f_Sigout_scale="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/scale/"+recovars[i]+"_uncer_SigOut_"+tag[j]+".txt";
			TString f_Sig_scale   ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/scale/"+genvars[i]+"_uncer"+tag[j]+".txt";
			TString f_jes         ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/jesr/jes/"+recovars[i]+"_uncer_"+tag[j]+".txt";
			TString f_jer         ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/jesr/jer/"+recovars[i]+"_uncer_"+tag[j]+".txt";
			TString f_l1pref      ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/l1pref/"+recovars[i]+"_l1pref"+tag[j]+"_uncer.txt";
			TString f_interf      ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/interf/"+recovars[i]+"_interf"+tag[j]+"_uncer.txt";
			TString f_ele_ID ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/lepton_uncer/"+recovars[i]+"_ele_ID_"+tag[j]+".txt";
			TString f_ele_reco ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/lepton_uncer/"+recovars[i]+"_ele_reco_"+tag[j]+".txt";
			TString f_mu_eff ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/lepton_uncer/"+recovars[i]+"_muon_all_"+tag[j]+".txt";
			TString f_mu_trigger ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/lepton_uncer/"+recovars[i]+"_muon_trigger_"+tag[j]+".txt";
			TString f_photon_ID ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/lepton_uncer/"+recovars[i]+"_photon_ID_"+tag[j]+".txt";
			TString f_pileup ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/pileup/"+recovars[i]+"_pileup"+tag[j]+"_uncer.txt";
                        TString f_puId_eff="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/puIdSF/"+recovars[i]+"_uncer_eff"+tag[j]+".txt";
                        TString f_puId_mis="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/puIdSF/"+recovars[i]+"_uncer_mis"+tag[j]+".txt";
                        TString f_puId_eff_sig="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/puIdSF/"+genvars[i]+"_uncer_eff"+tag[j]+".txt";
                        TString f_puId_mis_sig="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/puIdSF/"+genvars[i]+"_uncer_mis"+tag[j]+".txt";
                        TString f_l1pref_sig="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/l1pref/"+genvars[i]+"_uncer"+tag[j]+".txt";
                        TString f_pileup_sig="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/pileup/"+genvars[i]+"_uncer"+tag[j]+".txt";
                        TString f_interf_sig="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/interf/"+genvars[i]+"_uncer"+tag[j]+".txt";
                        TString f_jes_sig="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/jesr/jes/"+genvars[i]+"_uncer"+tag[j]+".txt";
                        TString f_jer_sig="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/jesr/jer/"+genvars[i]+"_uncer"+tag[j]+".txt";
			run(recovars[i],genvars[i],tag[j],f_fake);
			run(recovars[i],genvars[i],tag[j],f_QCD_pdf);
			run(recovars[i],genvars[i],tag[j],f_Sigout_pdf);
			run(recovars[i],genvars[i],tag[j],f_QCD_scale);
			run(recovars[i],genvars[i],tag[j],f_QCD_scaleband);
			run(recovars[i],genvars[i],tag[j],f_QCD_scale_extra_up);
			run(recovars[i],genvars[i],tag[j],f_QCD_scale_extra_down);
			run(recovars[i],genvars[i],tag[j],f_Sigout_scale);
			run(recovars[i],genvars[i],tag[j],f_jes);
			run(recovars[i],genvars[i],tag[j],f_jer);
			run(recovars[i],genvars[i],tag[j],f_l1pref);
			run(recovars[i],genvars[i],tag[j],f_interf);
			run(recovars[i],genvars[i],tag[j],f_Sig_scale);
			run(recovars[i],genvars[i],tag[j],f_Sig_pdf);
			run(recovars[i],genvars[i],tag[j],f_ele_ID);
			run(recovars[i],genvars[i],tag[j],f_ele_reco);
			run(recovars[i],genvars[i],tag[j],f_mu_eff);
			run(recovars[i],genvars[i],tag[j],f_mu_trigger);
			run(recovars[i],genvars[i],tag[j],f_photon_ID);
			run(recovars[i],genvars[i],tag[j],f_pileup);
			run(recovars[i],genvars[i],tag[j],f_pileup_sig);
			run(recovars[i],genvars[i],tag[j],f_l1pref_sig);
			run(recovars[i],genvars[i],tag[j],f_interf_sig);
			run(recovars[i],genvars[i],tag[j],f_jes_sig);
			run(recovars[i],genvars[i],tag[j],f_jer_sig);
			run(recovars[i],genvars[i],tag[j],f_puId_eff);
			run(recovars[i],genvars[i],tag[j],f_puId_mis);
			run(recovars[i],genvars[i],tag[j],f_puId_eff_sig);
			run(recovars[i],genvars[i],tag[j],f_puId_mis_sig);

		}
	}
	return 1;
}
