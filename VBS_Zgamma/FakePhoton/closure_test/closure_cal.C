#include <iostream>
#include <ostream>
#include <fstream>
#include <TROOT.h>
//#define ptnumber 8
using namespace std;
void calculate(Double_t lowpt,Double_t highpt,Double_t lowchiso,Double_t highchiso,TString channel,TString tag);
TString dir = "/home/pku/anying/cms/PKU-Cluster/FakePhoton/closure_test/fit_all/fractionfitResult_za/txt/";
TString dir1="./";
ofstream file1;
ofstream file2;
//(dir1+channel+tag+"_closure_uncer.txt");
void calculate(Double_t lowpt,Double_t highpt,Double_t lowchiso,Double_t highchiso,TString channel,TString tag){
	ifstream f1;
	double mcFake, fitFake,fitErr,fr,fr_Err;
	double uncer_closure;
	f1.open(Form(dir + channel+tag+"_FakeNumber_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt,highpt,lowchiso,highchiso));
	if(!f1.is_open()){cout<<"can not open the file"<<Form(dir + channel+tag+"_FakeNumber_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt,highpt,lowchiso,highchiso)<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;}
	f1>>mcFake>>fitFake>>fitErr>>fr>>fr_Err;

	uncer_closure= TMath::Abs((mcFake-fitFake)/mcFake);
        file1<<fixed<<setprecision(0)<<lowpt<<"~"<<highpt<<"\t"<<lowchiso<<"~"<<highchiso<<"\t"<<fixed<<setprecision(2)<<uncer_closure<<endl;
	file2<<uncer_closure<<endl;

}  


int closure_cal(){
	vector<TString> tag={"2016","2017","2018"};
	vector<TString> channel={"mubarrel","muendcap","elebarrel","eleendcap"};
	vector<double> lowpt;vector<double> highpt;
	double lowchiso,highchiso;
        vector<double> lpt;vector<double> hpt;
	for(int i=0;i<tag.size();i++){
		for(int j=0;j<channel.size();j++){
			cout<<tag[i]<<" "<<channel[j]<<endl;
			if(channel[j].Contains("barrel")) {
				lowpt={20,25,30,40,50,60};
				highpt={25,30,40,50,60,400};
                                lpt={20,25,30,35,40,50,60,100};
                                hpt={25,30,35,40,50,60,100,400};
			}
			else if(channel[j].Contains("endcap")) {
				lowpt={20,25,30,50};
				highpt={25,30,50,400};
				lpt={20,25,30,40,50,60};
				hpt={25,30,40,50,60,400};
			}
			file1.open(dir1+channel[j]+tag[i]+"_closure_uncer.txt");
			file2.open(dir1+"closure_uncer/"+channel[j]+tag[i]+"_closure_uncer.txt");
			if(channel[j].Contains("mubarrel")){
				if(tag[i].Contains("16")){
					lowchiso=8;highchiso=13;
				}
				if(tag[i].Contains("17")){
					lowchiso=5;highchiso=11;
				}
				if(tag[i].Contains("18")){
					lowchiso=6;highchiso=12;
				}
			}
			if(channel[j].Contains("elebarrel")){
				if(tag[i].Contains("16")){
					lowchiso=5;highchiso=10;
				}
				if(tag[i].Contains("17")){
					lowchiso=4;highchiso=9;
				}
				if(tag[i].Contains("18")){
					lowchiso=4;highchiso=9;
				}
			}
			if(channel[j].Contains("muendcap")){
				if(tag[i].Contains("16")){
					lowchiso=5;highchiso=11;
				}
				if(tag[i].Contains("17")){
					lowchiso=4;highchiso=9;
				}
				if(tag[i].Contains("18")){
					lowchiso=4;highchiso=9;
				}
			}
			if(channel[j].Contains("eleendcap")){
				if(tag[i].Contains("16")){
					lowchiso=4;highchiso=9;
				}
				if(tag[i].Contains("17")){
					lowchiso=4;highchiso=9;
				}
				if(tag[i].Contains("18")){
					lowchiso=4;highchiso=9;
				}
			}
			const int ptnumber=lpt.size();
			cout<<"ptnumber "<<ptnumber<<endl;
                        int m=0;
			for(Int_t k=0;k<ptnumber;k++){
                                file1<<fixed<<setprecision(0)<<lpt[k]<<"~"<<hpt[k]<<"\t";
				if(lowpt[m]==lpt[k] && highpt[m]==hpt[k])
					calculate(lowpt[m],highpt[m],lowchiso,highchiso, channel[j],tag[i]);
				if(lowpt[m]==lpt[k] && highpt[m]>hpt[k])
				{ calculate(lowpt[m],highpt[m],lowchiso,highchiso, channel[j],tag[i]);
					m = m-1;
				}
				if(lowpt[m]<lpt[k] && highpt[m]==hpt[k])
				{  calculate(lowpt[m],highpt[m],lowchiso,highchiso, channel[j],tag[i]);
				}
				if(lowpt[m]<lpt[k] && highpt[m]>hpt[k])
				{  calculate(lowpt[m],highpt[m],lowchiso,highchiso, channel[j],tag[i]);
					m = m-1;
				}
				m++;

			}
			file1.close();
			file2.close();

		}
	}
	return 0; 
}


