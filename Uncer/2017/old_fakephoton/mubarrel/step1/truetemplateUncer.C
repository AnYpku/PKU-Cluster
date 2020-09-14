#define num 7
double truetemplate_uncer;
ofstream file2("./txt/trueTemplate-uncertainty.txt");
void open(double lowpt,double highpt,TString name1,TString name2){

	ifstream f1,f2;
        f1.open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2017/MakeTemplate/BarrelMuon/ZAfit/txt/fakerate_"+name1+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        f2.open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2017/MakeTemplate/BarrelMuon/ZAfit/txt/fakerate_"+name2+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        double ff1,ff2;
        f1>>ff1;f2>>ff2;
//        cout<<lowpt<<"<pt<"<<highpt<<"; ff from EWK:"<<ff1<<"; ff from ZA:"<<ff2<<"; uncertainty:"<<(ff1-ff2)/(ff1+ff2)<<endl;
       cout<<fixed<<setprecision(0)<<lowpt<<"<pt<"<<highpt<<"\t"<<fixed<<setprecision(3)<<fabs(ff1-ff2)/(ff1+ff2)<<endl;
       file2<<fixed<<setprecision(0)<<lowpt<<"<pt<"<<highpt<<"\t"<<fixed<<setprecision(3)<<fabs(ff1-ff2)/(ff1+ff2)<<endl;
       truetemplate_uncer = fabs(ff1-ff2)/(ff1+ff2);
	//file<<lowpt<<"<pt<"<<highpt<<"\t"<<(ff1-ff2)/2*(ff1+ff2)<<endl;
}
int truetemplateUncer(){

  Double_t lowpt[num]= {20,25,30,40,50,70,100};
  Double_t highpt[num]={25,30,40,50,70,100,400};
  for(int i = 0;i<num;i++){
         open(lowpt[i],highpt[i],"EWK","ZA");
  }
  return 1;

}
