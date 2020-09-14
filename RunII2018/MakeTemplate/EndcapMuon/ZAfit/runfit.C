#include "fit.C"
#define num 8
void run_fit(){
    float lowchiso[21];
    float highchiso[21];
for(Int_t j=0;j<21;j++){
    if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
    if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
    if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;}
    if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;}
    if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;}
    if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
  }
// Double_t lowpt[num]= {20,25,30,35,40,45,50,60,80,120};
// Double_t highpt[num]={25,30,35,40,45,50,60,80,120,400};
  Double_t lowpt[num]= {20,25,30,40,50,60,80,120};
  Double_t highpt[num]={25,30,40,50,60,80,120,400};

// Double_t lowpt[num]= {25,30,40,50,65,80,130};
// Double_t highpt[num]={30,40,50,65,80,130,400};
// Double_t lowpt[num]= {25,30,35,45,55,65,85,130};
// Double_t highpt[num]={30,35,45,55,65,85,130,400};
 for(Int_t i=0;i<num;i++){
         fit(lowpt[i],highpt[i]);
  }
//	fit(25,30);
//	fit(30,35);
//	fit(35,40);
//	fit(40,45);
//	fit(45,50);
//	fit(50,60);
//	fit(60,80);
//	fit(80,120);
//	fit(120,400);

}

int runfit(){
    /*for(Int_t i=10;i<21;i++){*/
	run_fit();
	return 0;
}
