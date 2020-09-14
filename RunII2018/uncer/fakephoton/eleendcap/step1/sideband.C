#define num 9
double sideband_uncer;
double fakefraction;
ofstream file("./txt/sideband-uncertainty.txt");
void open(double lowpt,double highpt,TString name1,TString name2,TString name3){

	ifstream f1,f2,f3;
        f1.open("/home/pku/anying/cms/RunII2018/MakeTemplate/ElectronEndcap/ZAfit/txt/fakerate_"+name1+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        f2.open("/home/pku/anying/cms/RunII2018/MakeTemplate/ElectronEndcap/ZAfit/txt/fakerate_"+name2+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        f3.open("/home/pku/anying/cms/RunII2018/MakeTemplate/ElectronEndcap/ZAfit/txt/fakerate_"+name3+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        double ff1,ff2,ff3;
        f1>>ff1;f2>>ff2;f3>>ff3;
	fakefraction = ff3;
        cout<<fixed<<setprecision(0)<<lowpt<<"<pt<"<<highpt<<fixed<<setprecision(2)<<"; ff from ZA1:"<<ff1<<"; ff from ZA2:"<<ff2<<"; ff from ZA:"<<ff3<<"; uncertainty:"<<fixed<<setprecision(2)<<fabs(ff1-ff2)/(2*ff3)<<endl;
//        cout<<fixed<<setprecision(0)<<lowpt<<"<pt<"<<highpt<<"\t"<<fixed<<setprecision(2)<<fabs(ff1-ff2)/(2*ff3)<<endl;
        file<<fixed<<setprecision(0)<<lowpt<<"<pt<"<<highpt<<"\t"<<fixed<<setprecision(2)<<"\t"<<fabs(ff1-ff2)/(2*ff3)<<endl;
	//file<<lowpt<<"<pt<"<<highpt<<"\t"<<(ff1-ff2)/2*(ff1+ff2)<<endl;
	sideband_uncer = fabs(ff1-ff2)/(2*ff3);
}
int sideband(){

	Double_t lowpt[num]  ={20,25,30,35,40,45,50,65,100};
	Double_t highpt[num]={25,30,35,40,45,50,65,100,400};
	for(int i = 0;i<num;i++){
		open(lowpt[i],highpt[i],"ZA1","ZA2","ZA");
	}
	return 1;

}
