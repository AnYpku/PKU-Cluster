#include "fit.C"
#define num 6
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
// Double_t lowpt[num] ={20,25,30,35,40,50,60,100};
// Double_t highpt[num]={25,30,35,40,50,60,100,400};
   Double_t lowpt[num] ={20,25,30,40,50,60};
   Double_t highpt[num]={25,30,40,50,60,400};
   vector<Bool_t>isBarrel={1,0};
//   vector<TString> channel={"mm","emu","ee"}; 
   vector<TString> channel={"ee","mm"}; 
   for(int k=0;k<channel.size();k++){//channel
	   for(Int_t i=0;i<num;i++){
		   fit(lowpt[i],highpt[i],0,channel[k]);
	   }
   }

}

int runfit(){
	run_fit();
	return 0;
}
