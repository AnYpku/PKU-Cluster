#include <iostream>
#include <ostream>
#include <fstream>
#include <TROOT.h>
#define ptnumber 6
#define num 8
using namespace std;
Double_t lowpt[ptnumber] ={20,25,30,40,50,65};
Double_t highpt[ptnumber]={25,30,40,50,65,400};

Double_t lpt[num]= {20,25,30,40,50,65,100,125};
Double_t hpt[num]={25,30,40,50,65,100,125,400};

Double_t closureFake_test;
Double_t closure_uncer;
void calculate(Double_t lowpt,Double_t highpt,Double_t lowchiso,Double_t highchisoi,int i);
void run_calculate(Int_t a,Int_t b);
TString b="nosieiecut_mubarrel";
TString dir4 = "./txt/";
ofstream file1(dir4 + b+"_closure_FakeUncer.txt");
TString dir = "/home/pku/anying/cms/RunII2018/MakeTemplate/pesudo/mubarrel/txt/";
TString dir1 = "/home/pku/anying/cms/RunII2018/MakeTemplate/pesudo/mubarrel/roofit/txt/";
void calculate(Double_t lowpt,Double_t highpt,Double_t lowchiso,Double_t highchiso,int i){
    ifstream f1,f2,f3,f4,f5;
    Double_t ptlow,pthigh;
     Double_t selectFake_number,FakeNumber,fitFake_number,fitFake_error,chisolow,chisohigh,fit_fakerate,fit_fakerateErr;

    f3.open(Form(dir + b+"mfakenumber_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt,highpt,lowchiso,highchiso));
    if(!f3.is_open()){cout<<"can not open the file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;}
    f3>>ptlow>>pthigh>>chisolow>>chisohigh>>FakeNumber>>selectFake_number;

    f4.open(Form(dir1 + "FakeNumber_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt,highpt,lowchiso,highchiso));
    if(!f4.is_open()){cout<<"can not open the file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;}
    f4>>fitFake_number>>fitFake_error>>fit_fakerate>>fit_fakerateErr;
    
    cout<<fixed<<setprecision(0)<<lpt[i]<<"~"<<fixed<<setprecision(0)<<hpt[i]<<"\t"<<chisolow<<"~"<<chisohigh<<"\t"<<fixed<<setprecision(3)<<FakeNumber<<"\t"<<fitFake_number<<"\t"<<fabs(FakeNumber-fitFake_number)/FakeNumber<<endl;
//    cout<<fixed<<setprecision(0)<<lpt[i]<<"~"<<fixed<<setprecision(3)<<hpt[i]<<"\t"<<fabs(FakeNumber-fitFake_number)/FakeNumber<<endl;
     closureFake_test = TMath::Abs((FakeNumber - fitFake_number)/fitFake_error);
    file1<<Form("%0.f<pt<%0.f",lpt[i],hpt[i])<<"\t"<<Form("%0.f<chiso range<%0.f",lowchiso,highchiso)<<"\t"<<fixed<<setprecision(2)<<FakeNumber<<"\t"<<fixed<<setprecision(2)<<fitFake_number<<"\t"<<fixed<<setprecision(2)<<fabs(FakeNumber-fitFake_number)/FakeNumber<<endl;
    closure_uncer = fabs(FakeNumber-fitFake_number)/FakeNumber;
    
 }  
 void run_calculate(Int_t a,Int_t b){
     Double_t lc[6]={3,4,5,6,7,8};
     Double_t hc[6]={8,9,10,11,12,13};
     Double_t lowchiso[21],low;
     Double_t highchiso[21],high;
     for(Int_t j=0;j<21;j++){
        if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
        if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
        if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;}
        if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;}
        if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;}
        if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
	if(lowchiso[j]==6) low = lowchiso[j];
        if(highchiso[j]==12) high = highchiso[j];
     }
     calculate(lowpt[a],highpt[a],low,high,b);

 }

int closure(){
cout<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"FakeNumber"<<"\t"<<"fitFake_number"<<"\t"<<"closure uncertainty"<<endl; 
    file1<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"FakeNumber"<<"\t"<<"fitFake_number"<<"\t"<<"closure uncertainty"<<endl;
    int j = 0 ;
    int n = 0 ;
  for(Int_t i=0;i<num;i++){
          if(j>=ptnumber-1) j=ptnumber-1;
          if(lowpt[j]==lpt[i] && highpt[j]==hpt[i])
                  run_calculate(j,i);
          if(lowpt[j]==lpt[i] && highpt[j]>hpt[i])
                 { run_calculate(j,i);
                         j = j-1;
                 }
          if(lowpt[j]<lpt[i] && highpt[j]==hpt[i])
                 {  run_calculate(j,i);
                         j = j-1;
                 }
          if(lowpt[j]<lpt[i] && highpt[j]>hpt[i])
                 {  run_calculate(j,i);
                         j = j-1;
                 }
	  j++;
          if(j>=ptnumber-1) j=ptnumber-1;
   }
  return 0; 
}


