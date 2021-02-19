void run(TString tag){
	double uncer_tag,uncer;
	if(tag.Contains("16")){uncer=(1.022*35.86+41.52+58.7)/(35.86+41.52+58.7);uncer_tag=1.022;}
	if(tag.Contains("17")){uncer=(1.02*35.86+41.52+58.7)/(35.86+41.52+58.7);uncer_tag=1.02;}
	if(tag.Contains("18")){uncer=(1.015*35.86+41.52+58.7)/(35.86+41.52+58.7);uncer_tag=1.015;}
	ofstream f1("./lumi_uncer"+tag+".txt");
	fstream f("./lumi_uncer.txt",ios::app);
	if(tag.Contains("1"))f1<<fixed<<setprecision(3)<<"lumi"<<tag<<"=["<<uncer_tag<<"]"<<endl;
        f<<fixed<<setprecision(3)<<"lumi"<<tag<<"=["<<uncer<<"]"<<endl;
}
int uncer_lumi(){
	vector<TString> tag={"16","17","18"};
	for(int i=0;i<tag.size();i++){
		run(tag[i]);
	}
	return 0;

}
