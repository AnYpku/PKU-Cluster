void run(TString tag,TString filename,TString var,TString njets){
	fstream f1("./summary_uncer_"+var+"_"+njets+"_"+tag+".txt",ios::app);
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
        vector<TString> tag={"16","17","18"};
	vector<TString> vars={"ml1g","ml2g","mllg"};
	vector<TString> njets={"0jets","1jets"};
        vector<TString> filename;
	for(int i=0;i<njets.size();i++){
		for(int j=1;j<tag.size();j++){
			for(int n=0;n<vars.size();n++){
				TString f_jer         ="./jesr/jesr_uncer_"+vars[n]+"_"+njets[i]+"_jer1"+tag[j]+".txt";
				TString f_jes         ="./jesr/jesr_uncer_"+vars[n]+"_"+njets[i]+"_jesTotal"+tag[j]+".txt";
				TString f_fake        ="./batch/fakephoton_uncer_"+vars[n]+"_"+njets[i]+"_"+tag[j]+".txt";
				TString f_pileup      ="./batch/pileup_uncer_"+vars[n]+"_"+njets[i]+"_"+tag[j]+".txt";
				TString f_scale       ="./batch/scale_uncer_"+vars[n]+"_"+njets[i]+"_"+tag[j]+".txt";
				TString f_pdf         ="./batch/pdf_uncer_"+vars[n]+"_"+njets[i]+"_"+tag[j]+".txt";
				TString f_pref        ="./batch/l1pref_uncer_"+vars[n]+"_"+njets[i]+"_"+tag[j]+".txt";
				TString f_btag        ="./batch/btag_uncer_"+vars[n]+"_"+njets[i]+"_"+tag[j]+".txt";
				run(tag[j],f_fake,vars[n],njets[i]);
				run(tag[j],f_jes,vars[n],njets[i]);
				run(tag[j],f_jer,vars[n],njets[i]);
				run(tag[j],f_pileup,vars[n],njets[i]);
				run(tag[j],f_scale,vars[n],njets[i]);
				run(tag[j],f_pdf,vars[n],njets[i]);
				run(tag[j],f_pref,vars[n],njets[i]);
				run(tag[j],f_btag,vars[n],njets[i]);
			}
		}
	}
	return 1;
}