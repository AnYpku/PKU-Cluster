ofstream myfile;
vector<double> lowpt;vector<double> highpt;
void get(Double_t lowpt,Double_t highpt,TString tag,TString channel){
TString dir = "./closure/";
ifstream f1,f2;
f2.open(dir+channel+tag+Form("closure_test_pt%0.f_%0.f.txt",lowpt,highpt));
if(!f2.is_open()) cout<< "can't open the file"<<endl;
Double_t value[22],lowchiso,highchiso;
for(Int_t i=0;i<22;i++){
   f2>>lowchiso>>highchiso>>value[i+1];
 }
     myfile<<fixed<<setprecision(2)<<"*"<<"\t"<<"3"<<"\t"<<"4"<<"\t"<<"5"<<"\t"<<"6"<<"\t"<<"7"<<"\t"<<"8"<<endl;
     myfile<<fixed<<setprecision(2)<<"8"<<"\t"<<value[1]<<endl;
     myfile<<fixed<<setprecision(2)<<"9"<<"\t"<<value[2]<<"\t"<<value[7]<<endl;
     myfile<<fixed<<setprecision(2)<<"10"<<"\t"<<value[3]<<"\t"<<value[8]<<"\t"<<value[12]<<endl;
     myfile<<fixed<<setprecision(2)<<"11"<<"\t"<<value[4]<<"\t"<<value[9]<<"\t"<<value[13]<<"\t"<<value[16]<<endl;
     myfile<<fixed<<setprecision(2)<<"12"<<"\t"<<value[5]<<"\t"<<value[10]<<"\t"<<value[14]<<"\t"<<value[17]<<"\t"<<value[19]<<endl;
     myfile<<fixed<<setprecision(3)<<"13"<<"\t"<<value[6]<<"\t"<<value[11]<<"\t"<<value[15]<<"\t"<<value[18]<<"\t"<<value[20]<<"\t"<<value[21]<<endl;

     cout<<fixed<<setprecision(2)<<"*"<<"\t"<<"3"<<"\t"<<"4"<<"\t"<<"5"<<"\t"<<"6"<<"\t"<<"7"<<"\t"<<"8"<<endl;
     cout<<fixed<<setprecision(2)<<"8"<<"\t"<<value[1]<<endl;
     cout<<fixed<<setprecision(2)<<"9"<<"\t"<<value[2]<<"\t"<<value[7]<<endl;
     cout<<fixed<<setprecision(2)<<"10"<<"\t"<<value[3]<<"\t"<<value[8]<<"\t"<<value[12]<<endl;
     cout<<fixed<<setprecision(2)<<"11"<<"\t"<<value[4]<<"\t"<<value[9]<<"\t"<<value[13]<<"\t"<<value[16]<<endl;
     cout<<fixed<<setprecision(2)<<"12"<<"\t"<<value[5]<<"\t"<<value[10]<<"\t"<<value[14]<<"\t"<<value[17]<<"\t"<<value[19]<<endl;
     cout<<fixed<<setprecision(2)<<"13"<<"\t"<<value[6]<<"\t"<<value[11]<<"\t"<<value[15]<<"\t"<<value[18]<<"\t"<<value[20]<<"\t"<<value[21]<<endl;
    
  }
 void run(Int_t a,TString tag,TString channel){
     cout<<"pt: "<<lowpt[a]<<" ~ "<<highpt[a]<<" in "<<tag<<" "<<channel<<endl; 
     get(lowpt[a],highpt[a],tag,channel);
    }

int draw_closureTable(){
	vector<TString> tag={"2016","2017","2018"};
        vector<TString> channel={"mubarrel","muendcap","elebarrel","eleendcap"};
	for(int i=0;i<tag.size();i++){
		for(int j=0;j<channel.size();j++){
			cout<<tag[i]<<" "<<channel[j]<<endl;
			if(channel[j].Contains("barrel")) {
				lowpt={20,25,30,40,50,60};
				highpt={25,30,40,50,60,400};
			}
			else if(channel[j].Contains("endcap")) {
				lowpt={20,25,30,50};
				highpt={25,30,50,400};
			}
			myfile.open(channel[j]+tag[i]+"_result.txt");
			const int ptnumber=lowpt.size(); 
			for(Int_t k=0;k<ptnumber;k++){
				myfile<<fixed<<setprecision(0)<<"pt: "<<lowpt[k]<<" ~ "<<highpt[k]<<endl; 
				run(k,tag[i],channel[j]);
				myfile<<"############################################################"<<endl;
			}
			myfile.close();
		}
	}
	return 0;
}
