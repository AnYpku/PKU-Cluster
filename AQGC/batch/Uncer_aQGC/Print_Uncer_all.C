void run(TString channel,TString tag,TString filename){
	fstream f1("./summary_uncer_"+channel+tag+".txt",ios::app);
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
        vector<TString> tag={"16","17","18",""};
        vector<TString> channel={"ele","mu"};
        vector<TString> filename;
        for(int i=0;i<channel.size();i++){
		for(int j=0;j<tag.size();j++){
			TString f_fake        ="./fakephoton/fake_uncer_"+channel[i]+tag[j]+".txt";
			TString f_interf        ="./interf/interf_uncer"+tag[j]+"_"+".txt";
			TString f_QCD_pdf     ="./pdf/uncer_qcd"+tag[j]+".txt";
			TString f_Sig_pdf     ="./pdf/uncer_ewk"+tag[j]+".txt";
			TString f_QCD_scale   ="./scale/uncer_qcd"+tag[j]+".txt";
			TString f_QCD_scale_band   ="./scale/uncer_qcd_scaleband"+tag[j]+".txt";
			TString f_QCD_scale_extra_up  ="./scale/uncer_QCD_extra_up"+tag[j]+".txt";
			TString f_QCD_scale_extra_down  ="./scale/uncer_QCD_extra_down"+tag[j]+".txt";
			TString f_Sig_scale   ="./scale/uncer_ewk"+tag[j]+".txt";
			TString f_jes         ="./jesr/jes/jes_uncer"+tag[j]+".txt";
			TString f_jer         ="./jesr/jer/jer_uncer"+tag[j]+".txt";
			TString f_l1pref      ="./l1pref/l1pref_uncer_"+tag[j]+".txt";
			TString f_ele_ID ="./lepton_uncer/txt/ele_ID"+tag[j]+".txt";
			TString f_ele_reco ="./lepton_uncer/txt/ele_reco"+tag[j]+".txt";
			TString f_mu_eff ="./lepton_uncer/txt/muon_all"+tag[j]+".txt";
			TString f_mu_trigger ="./lepton_uncer/txt/muon_trigger"+tag[j]+".txt";
			TString f_photon_ID ="./lepton_uncer/txt/photon_ID"+tag[j]+".txt";
			TString f_lumi ="./lumi/lumi_uncer"+tag[j]+".txt";
			run(channel[i],tag[j],f_fake);
			run(channel[i],tag[j],f_interf);
			run(channel[i],tag[j],f_QCD_pdf);
			run(channel[i],tag[j],f_QCD_scale);
			run(channel[i],tag[j],f_QCD_scale_band);
			run(channel[i],tag[j],f_QCD_scale_extra_up);
			run(channel[i],tag[j],f_QCD_scale_extra_down);
			run(channel[i],tag[j],f_jes);
			run(channel[i],tag[j],f_jer);
			run(channel[i],tag[j],f_l1pref);
			run(channel[i],tag[j],f_Sig_scale);
			run(channel[i],tag[j],f_Sig_pdf);
			run(channel[i],tag[j],f_ele_ID);
			run(channel[i],tag[j],f_ele_reco);
			run(channel[i],tag[j],f_mu_eff);
			run(channel[i],tag[j],f_mu_trigger);
			run(channel[i],tag[j],f_photon_ID);
			run(channel[i],tag[j],f_lumi);
		}
	}
	return 1;
}
