#include "fitfraction.C"
#define ptnumber 5
void run_fitf(Int_t b,Int_t a);
void run_fitf(Int_t b,Int_t a){
    float lowchiso[21];
    float highchiso[21];
  Double_t lowpt[ptnumber]= {20,25,30,35,45};
  Double_t highpt[ptnumber]={25,30,35,45,400};
    for(Int_t j=0;j<21;j++){
	    if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
	    if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
	    if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;}
	    if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;}
	    if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;}
	    if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
    }
    fitf(lowpt[b],highpt[b],lowchiso[a],highchiso[a]);
}

int runfitf(){
	for(Int_t j=0;j<ptnumber;j++){
		for(Int_t i=0;i<21;i++){
			run_fitf(j,i);}
	}//run_fitf(1,1);
	return 0;
}
