#define num 8
double truetemplate_uncer;
ofstream file2("./txt/trueTemplate-uncertainty.txt");
void open(double lowpt,double highpt,TString name1,TString name2){

	ifstream f1,f2;
        f1.open("/home/pku/anying/cms/RunII2016/analysis_code/MakeTemplate/ZAfit/MuonEndcap/txt/fakerate_"+name1+Form("pt%0.f_%0.f.txt",lowpt,highpt));
        f2.open("/home/pku/anying/cms/RunII2016/analysis_code/MakeTemplate/ZAfit/MuonEndcap/txt/fakerate_"+name2+Form("pt%0.f_%0.f.txt",lowpt,highpt));
        double ff1,ff2;
        f1>>ff1;f2>>ff2;
        cout<<lowpt<<"<pt<"<<highpt<<"; ff from EWK:"<<ff1<<"; ff from ZA:"<<ff2<<"; uncertainty:"<<(ff1-ff2)/(ff1+ff2)<<endl;
//	cout<<fixed<<setprecision(0)<<lowpt<<"<pt<"<<highpt<<"\t"<<fixed<<setprecision(2)<<fabs(ff1-ff2)/(ff1+ff2)<<endl;
       file2<<fixed<<setprecision(0)<<lowpt<<"<pt<"<<highpt<<"\t"<<fixed<<setprecision(2)<<fabs(ff1-ff2)/(ff1+ff2)<<endl;
       truetemplate_uncer = fabs(ff1-ff2)/(ff1+ff2);
	//file<<lowpt<<"<pt<"<<highpt<<"\t"<<(ff1-ff2)/2*(ff1+ff2)<<endl;
}
int truetemplateUncer(){

	Double_t lowpt[num]= {20,25,30,35,40,50,65,100};
	Double_t highpt[num]={25,30,35,40,50,65,100,400};
	for(int i = 0;i<num;i++){
		open(lowpt[i],highpt[i],"EWK","ZA");
	}
	return 1;
}
