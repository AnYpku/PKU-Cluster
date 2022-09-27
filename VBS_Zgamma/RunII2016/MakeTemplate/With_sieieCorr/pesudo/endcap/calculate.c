#include <iostream>
#include <ostream>
#include <fstream>
#include <TROOT.h>
#define ptnumber 6
using namespace std;
// Double_t lowpt[ptnumber]= {20,30,40,60,80,120};
// Double_t highpt[ptnumber]={30,40,60,80,120,400};
// Double_t lowpt[ptnumber] ={20,25,30,35,40,45,50,60,80,120};
// Double_t highpt[ptnumber]={25,30,35,40,45,50,60,80,120,400};
 Double_t lowpt[ptnumber]= {20,25,30,35,50,60};
 Double_t highpt[ptnumber]={25,30,35,50,60,400};
Double_t closureFake_test;
Double_t closureTrue_test;
void calculate(Double_t lowpt,Double_t highpt,Double_t lowchiso,Double_t highchiso);
void run_calculate(Int_t a);
TString b="nosieiecut_endcap";
//TString b="sieiecut";
TString dir3 = "./roofit/";
ofstream file (dir3 + b+"_closure_True.txt");
ofstream file1(dir3 + b+"_closure_Fake.txt");
ofstream file2(dir3 + b+"_Fakefraction.txt");
ofstream file3(dir3 + b+"_total.txt");
//TString dir = "./resultNew/txt/";
TString dir = "./txt/";
TString dir1 = "./roofit/txt/";
TString dir2 = "./roofit/closure_barrel_roofit/";
void calculate(Double_t lowpt,Double_t highpt,Double_t lowchiso,Double_t highchiso){
    ofstream myfile(Form(dir2 + "closure-test_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt,highpt,lowchiso,highchiso));
    ofstream myfile1(Form(dir2 + "closure-true-test_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt,highpt,lowchiso,highchiso));
    ifstream f1,f2,f3,f4,f5;

    f1.open(Form(dir + b+"truenumber_pt%0.f-%0.f.txt",lowpt,highpt));
    if(!f1.is_open()){cout<<"can not open the file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;}
    
    Double_t selectTrue_number,TrueNumber,fitTrue_number,fitTrue_error,ptlow,pthigh,FakeNumber,fitFake_number,fitFake_error,chisolow,chisohigh,selectData_number,fit_fakerate,fit_fakerateErr;
    f1>>ptlow>>pthigh>>selectTrue_number>>TrueNumber;
    cout<<"pt range"<<ptlow<<" ~ "<<pthigh<<"  "<<"chiso range"<<lowchiso<<" ~ "<<highchiso<<endl;
    cout<<"selectTrue_number"<<selectTrue_number<<endl;
    
    f2.open(Form(dir1 + "TrueNumber_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt,highpt,lowchiso,highchiso));
    if(!f2.is_open()){cout<<"can not open the file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;}
    f2>>fitTrue_number>>fitTrue_error;
    cout<<"fitTrue_number "<<fitTrue_number<<" "<<"fitTrue_error"<<fitTrue_error<<endl;
    closureTrue_test = TMath::Abs((TrueNumber - fitTrue_number)/fitTrue_error);
    file<<Form("%0.f  <pt<%0.f ",lowpt,highpt)<<"\t"<<Form("%0.f<chiso range<%0.f ",lowchiso,highchiso)<<"\t"<<TrueNumber<<"\t"<<fitTrue_number<<"\t"<<fitTrue_error<<"\t"<<closureTrue_test<<endl;
    cout<<"the value of closure is "<<closureTrue_test<<endl;
    
    f3.open(Form(dir + b+"mfakenumber_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt,highpt,lowchiso,highchiso));
    if(!f3.is_open()){cout<<"can not open the file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;}
    f3>>ptlow>>pthigh>>chisolow>>chisohigh>>FakeNumber;
//    cout<<"selectFake_number"<<selectFake_number;
    cout<<" FakeNumber"<<FakeNumber<<endl;

    f4.open(Form(dir1 + "FakeNumber_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt,highpt,lowchiso,highchiso));
    if(!f4.is_open()){cout<<"can not open the file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;}
    f4>>fitFake_number>>fitFake_error>>fit_fakerate>>fit_fakerateErr;
    
     closureFake_test = TMath::Abs((FakeNumber - fitFake_number)/fitFake_error);
    file1<<Form("%0.f <pt<%0.f ",lowpt,highpt)<<"\t"<<Form("%0.f<chiso range<%0.f ",lowchiso,highchiso)<<"\t"<<FakeNumber<<"\t"<<fitFake_number<<"\t"<<fitFake_error<<"\t"<<closureFake_test<<endl;
    f5.open(Form(dir + b+"datanumber_pt%0.f-%0.f.txt",lowpt,highpt));
    if(!f5.is_open()){cout<<"can not open the file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;}
    f5>>ptlow>>pthigh>>selectData_number;
    Double_t fake_fraction=FakeNumber/selectData_number;
    file2<<Form("%0.f <pt<%0.f ",lowpt,highpt)<<"\t"<<Form("%0.f<chiso range<%0.f ",lowchiso,highchiso)<<"\t"<<selectData_number<<"\t"<<FakeNumber<<"\t"<<fake_fraction<<"\t"<<fit_fakerate<<"\t"<<fit_fakerateErr<<"\t"<<TMath::Abs((fake_fraction - fit_fakerate)/fit_fakerateErr)<<endl;
    file3<<Form("%0.f <pt<%0.f ",lowpt,highpt)<<"\t"<<Form("%0.f<chiso range<%0.f ",lowchiso,highchiso)<<"\t"<<selectData_number<<"\t"<<FakeNumber<<"\t"<<TrueNumber<<"\t"<<fitFake_number<<"\t"<<fitTrue_number<<"\t"<<closureFake_test<<"\t"<<closureTrue_test<<endl;

    myfile<<closureFake_test<<endl;
    myfile1<<closureTrue_test<<endl;
    
 }  
 void run_calculate(Int_t a,Int_t b){
     Double_t lc[6]={3,4,5,6,7,8};
     Double_t hc[6]={8,9,10,11,12,13};
     Double_t lowchiso[21];
     Double_t highchiso[21];
     for(Int_t j=0;j<21;j++){
        if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
        if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
        if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;}
        if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;}
        if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;}
        if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
     }
     calculate(lowpt[a],highpt[a],lowchiso[b],highchiso[b]);

 }

int calculate (){
    file<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"TrueNumber"<<"\t"<<"fitTrue_number"<<"\t"<<"fitTrue_error"<<"\t"<<"closureTrue_test"<<endl;
    file<<"#######################################################################################"<<endl;    
    file1<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"FakeNumber"<<"\t"<<"fitFake_number"<<"\t"<<"fitFake_Err"<<"\t"<<"closure"<<endl;
    file1<<"#######################################################################################"<<endl;    
    file2<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"DataNumber"<<"\t"<<"FakeNumber"<<"\t"<<"fake_fraction"<<"\t"<<"fit_fakerate"<<"\t"<<"fit_fakerateErr"<<"\t"<<"closure"<<endl;
    file2<<"#######################################################################################"<<endl;    
    file3<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"DataNumber"<<"\t"<<"FakeNumber"<<"\t"<<"TrueNumber"<<"\t"<<"fitFake_number"<<"\t"<<"fitTrue_number"<<"\t"<<"closureFake_test"<<"\t"<<"closureTrue_test"<<endl;
  file3<<"#######################################################################################"<<endl;    
  for(Int_t i=0;i<ptnumber;i++){
//  myfile<<"*"<<"\t"<<"3"<<"\t"<<"4"<<"\t"<<"5"<<"\t"<<"6"<<"\t"<<"7"<<"\t"<<"8"<<endl;
    ofstream myfile2(dir2 + Form("closure-test_pt%0.f-%0.f.txt",lowpt[i],highpt[i]));
    ofstream myfile3(dir2 + Form("closure-true-test_pt%0.f-%0.f.txt",lowpt[i],highpt[i]));
      for(Int_t j=0;j<21;j++){
         run_calculate(i,j);
         myfile2<<closureFake_test<<endl;
         myfile3<<closureTrue_test<<endl;
       }
  file<<"#######################################################################################"<<endl;    
  file1<<"#######################################################################################"<<endl;    
  file2<<"#######################################################################################"<<endl;    
  file3<<"#######################################################################################"<<endl;    
//  myfile<<"#######################################################################################"<<endl;    
   }
  return 0; 
}


