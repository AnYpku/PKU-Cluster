#include "fit.C"
using namespace std;
void run_fit(Int_t b,Int_t a);
void run_fit(Int_t b,Int_t a,TString tag,TString channel,vector<double> lowpt,vector<double> highpt){
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
    fit(lowpt[b],highpt[b],lowchiso[a],highchiso[a],tag,channel);

}

int runfit(){
	vector<TString> tag={"2016","2017","2018"};
	vector<TString> channel={"mubarrel","muendcap","elebarrel","eleendcap"};
	vector<double> lowpt;vector<double> highpt;
	for(Int_t i=0;i<21;i++){
		for(int ik=2;ik<3/*tag.size()*/;ik++){
			for(int jk=0;jk<channel.size();jk++){
				if(channel[jk].Contains("barrel")) {
					lowpt={20,25,30,40,50,60};
					highpt={25,30,40,50,60,400};
				}
				else if(channel[jk].Contains("endcap")) {
					lowpt={20,25,30,50};
					highpt={25,30,50,400};
				}
                                int ptnumber=lowpt.size();
				for(Int_t j=0;j<ptnumber;j++){
					run_fit(j,i,tag[ik],channel[jk],lowpt,highpt);
				}
			}
		}
	}
	return 0;
}
