#define num 8
ofstream file("./sideband-uncertainty.txt");
void open(double lowpt,double highpt,TString name1,TString name2,TString name3){

	ifstream f1,f2,f3;
        f1.open("./txt/fakerate_"+name1+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        f2.open("./txt/fakerate_"+name2+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        f3.open("./txt/fakerate_"+name3+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        double ff1,ff2,ff3;
        f1>>ff1;f2>>ff2;f3>>ff3;
//        cout<<lowpt<<"<pt<"<<highpt<<"; ff from ZA1:"<<ff1<<"; ff from ZA2:"<<ff2<<"; ff from ZA:"<<ff3<<"; uncertainty:"<<(ff1-ff2)/(2*ff3)<<endl;
        cout<<fabs(ff1-ff2)/(2*ff3)<<endl;
        file<<lowpt<<"<pt<"<<highpt<<"\t"<<ff1<<"\t"<<ff2<<"\t"<<ff3<<"\t"<<fabs(ff1-ff2)/(2*ff3)<<endl;
	//file<<lowpt<<"<pt<"<<highpt<<"\t"<<(ff1-ff2)/2*(ff1+ff2)<<endl;
}
int sideband(){

  Double_t lowpt[num]= {20,25,30,40,50,70,100,120};
  Double_t highpt[num]={25,30,40,50,70,100,120,400};
  for(int i = 0;i<num;i++){
         open(lowpt[i],highpt[i],"ZA1","ZA2","ZA");
  }
  return 1;

}
