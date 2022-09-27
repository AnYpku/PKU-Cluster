#define num 8
ofstream file("./trueTemplate-uncertainty.txt");
void open(double lowpt,double highpt,TString name1,TString name2){

	ifstream f1,f2;
        f1.open("./txt/fakerate_"+name1+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        f2.open("./txt/fakerate_"+name2+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        double ff1,ff2;
        f1>>ff1;f2>>ff2;
//        cout<<lowpt<<"<pt<"<<highpt<<"; ff from EWK:"<<ff1<<"; ff from ZA:"<<ff2<<"; uncertainty:"<<(ff1-ff2)/(ff1+ff2)<<endl;
       cout<<(ff1-ff2)/(ff1+ff2)<<endl;
        file<<lowpt<<"<pt<"<<highpt<<"\t"<<"EWK"<<"\t"<<ff1<<"\t"<<"ZA"<<"\t"<<ff2<<"\t"<<"uncertainty"<<"\t"<<(ff1-ff2)/(ff1+ff2)<<endl;
	//file<<lowpt<<"<pt<"<<highpt<<"\t"<<(ff1-ff2)/2*(ff1+ff2)<<endl;
}
int uncer(){

  Double_t lowpt[num]= {20,25,30,40,50,70,100,120};
  Double_t highpt[num]={25,30,40,50,70,100,120,400};
  for(int i = 0;i<num;i++){
         open(lowpt[i],highpt[i],"EWK","ZA");
  }
  return 1;

}
