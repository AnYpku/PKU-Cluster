void run(TString tag,TString filename){
	fstream f1("./summary_uncer_"+tag+".txt",ios::app);
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
        vector<TString> filename;
	for(int j=0;j<tag.size();j++){
		TString f_fake        ="./fakephoton/fake_uncer_"+tag[j]+".txt";
		TString f_jer         ="./jesr/jesr_uncer_jer1"+tag[j]+".txt";
		TString f_jes         ="./jesr/jesr_uncer_jesTotal"+tag[j]+".txt";
		TString f_pileup ="./pileup/pu_uncer_"+tag[j]+".txt";
		run(tag[j],f_fake);
		run(tag[j],f_jes);
		run(tag[j],f_jer);
		run(tag[j],f_pileup);
	}
	return 1;
}
