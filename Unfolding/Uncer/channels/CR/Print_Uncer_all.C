void run(TString var,TString genvar,TString tag,TString channel,TString filename){
	fstream f1("./summary_"+var+"_"+tag+channel+"CR.txt",ios::app);
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
        vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
        vector<TString> filename;
        for(int i=0;i<recovars.size();i++){
		for(int j=0;j<tag.size();j++){
			for(int k=0;k<channels.size();k++){
				TString f_fake        ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/fakephoton/"+recovars[i]+"_fake_uncer_"+tag[j]+channels[k]+"CR.txt";
				TString f_QCD_pdf     ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/pdf/"+recovars[i]+"_uncer_qcd_16CR.txt";
				TString f_Sigout_pdf  ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/pdf/"+recovars[i]+"_uncer_Sigout_"+tag[j]+"CR.txt";
				TString f_Sig_pdf     ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/pdf/"+genvars[i]+"_uncer"+tag[j]+"CR.txt";
				TString f_QCD_scale   ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/scale/"+recovars[i]+"_uncer_qcd_"+tag[j]+"CR.txt";
				TString f_QCD_scale_extra_up  ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/scale/"+recovars[i]+"_uncer_QCD_extra_up_"+tag[j]+"CR.txt";
				TString f_QCD_scale_extra_down  ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/scale/"+recovars[i]+"_uncer_QCD_extra_down_"+tag[j]+"CR.txt";
				TString f_Sigout_scale="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/scale/"+recovars[i]+"_uncer_SigOut_"+tag[j]+"CR.txt";
				TString f_Sig_scale   ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/scale/"+genvars[i]+"_uncer"+tag[j]+"CR.txt";
				TString f_jes         ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/jes/"+recovars[i]+"_jes_uncer"+tag[j]+"CR.txt";
				TString f_jer         ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/jer/"+recovars[i]+"_jer_uncer"+tag[j]+"CR.txt";
				TString f_l1pref      ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/l1pref/"+recovars[i]+"_l1pref_"+tag[j]+channels[k]+"_uncerCR.txt";
				TString f_ele_ID ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/lepton_uncer/"+recovars[i]+"_ele_ID_"+tag[j]+".txt";
				TString f_ele_reco ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/lepton_uncer/"+recovars[i]+"_ele_reco_"+tag[j]+".txt";
				TString f_mu_eff ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/lepton_uncer/"+recovars[i]+"_muon_all_"+tag[j]+".txt";
				TString f_mu_trigger ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/lepton_uncer/"+recovars[i]+"_muon_trigger_"+tag[j]+".txt";
				TString f_photon_ID ="/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/channels/CR/lepton_uncer/"+recovars[i]+"_photon_ID_"+tag[j]+".txt";
				run(recovars[i],genvars[i],tag[j],channels[k],f_fake);
				run(recovars[i],genvars[i],tag[j],channels[k],f_QCD_pdf);
				run(recovars[i],genvars[i],tag[j],channels[k],f_Sigout_pdf);
				run(recovars[i],genvars[i],tag[j],channels[k],f_QCD_scale);
				run(recovars[i],genvars[i],tag[j],channels[k],f_QCD_scale_extra_up);
				run(recovars[i],genvars[i],tag[j],channels[k],f_QCD_scale_extra_down);
				run(recovars[i],genvars[i],tag[j],channels[k],f_Sigout_scale);
				run(recovars[i],genvars[i],tag[j],channels[k],f_jes);
				run(recovars[i],genvars[i],tag[j],channels[k],f_jer);
				run(recovars[i],genvars[i],tag[j],channels[k],f_l1pref);
				run(recovars[i],genvars[i],tag[j],channels[k],f_Sig_scale);
				run(recovars[i],genvars[i],tag[j],channels[k],f_Sig_pdf);
				run(recovars[i],genvars[i],tag[j],channels[k],f_ele_ID);
				run(recovars[i],genvars[i],tag[j],channels[k],f_ele_reco);
				run(recovars[i],genvars[i],tag[j],channels[k],f_mu_eff);
				run(recovars[i],genvars[i],tag[j],channels[k],f_mu_trigger);
				run(recovars[i],genvars[i],tag[j],channels[k],f_photon_ID);
			}
		}
	}
	return 1;
}
