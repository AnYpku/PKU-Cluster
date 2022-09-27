#include "fit.C"
using namespace std;
void run_fit(Int_t b,Int_t a);
void run_fit(Int_t b,Int_t a){
    float lowchiso[21];
    float highchiso[21];
    Double_t lowpt[10] ={20,25,30,35,40,50,60,80,100,120};
    Double_t highpt[10]={25,30,35,40,50,60,80,100,120,400};

    for(Int_t j=0;j<21;j++){
	    if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
	    if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
	    if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;}
	    if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;}
	    if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;}
	    if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
    }
    fit(lowpt[b],highpt[b],lowchiso[a],highchiso[a]);
    /*fit(30,35,lowchiso[a],highchiso[a]);
      fit(35,40,lowchiso[a],highchiso[a]);
      fit(40,50,lowchiso[a],highchiso[a]);
      fit(50,65,lowchiso[a],highchiso[a]);
      fit(65,100,lowchiso[a],highchiso[a]);
      fit(100,400,lowchiso[a],highchiso[a]);*/

}

int runfit(){
	for(Int_t j=0;j<10;j++){
		for(Int_t i=0;i<11;i++){
			run_fit(j,i);}
	}
	return 0;
}
