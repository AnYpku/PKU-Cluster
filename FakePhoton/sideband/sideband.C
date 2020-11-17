ofstream file;
ofstream file1;
void run(double lowpt,double highpt,TString tag,TString channel,TString name1,TString name2,TString name3){
        ifstream f1,f2,f3;
        f1.open("/data/pku/home/anying/cms/PKU-Cluster/RunII"+tag+"/MakeTemplate/With_sieieCorr/"+channel+"/ZAfit/fractionfitResult_za/txt/fakerate_"+name1+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        f2.open("/data/pku/home/anying/cms/PKU-Cluster/RunII"+tag+"/MakeTemplate/With_sieieCorr/"+channel+"/ZAfit/fractionfitResult_za/txt/fakerate_"+name2+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        f3.open("/data/pku/home/anying/cms/PKU-Cluster/RunII"+tag+"/MakeTemplate/With_sieieCorr/"+channel+"/ZAfit/fractionfitResult_za/txt/fakerate_"+name3+Form("_pt%0.f_%0.f.txt",lowpt,highpt));
        if(!f1.is_open()){cout<<"can not open /data/pku/home/anying/cms/PKU-Cluster/RunII"+tag+"/MakeTemplate/With_sieieCorr/"<<"/MakeTemplate/With_sieieCorr/"<<channel<<"/ZAfit/fractionfitResult_za/txt/fakerate_"<<name1<<Form("_pt%0.f_%0.f.txt",lowpt,highpt)<<endl;}
        if(!f2.is_open()){cout<<"can not open /data/pku/home/anying/cms/PKU-Cluster/RunII"+tag+"/MakeTemplate/With_sieieCorr/"<<"/MakeTemplate/With_sieieCorr/"<<channel<<"/ZAfit/fractionfitResult_za/txt/fakerate_"<<name2<<Form("_pt%0.f_%0.f.txt",lowpt,highpt)<<endl;}
        if(!f2.is_open()){cout<<"can not open /data/pku/home/anying/cms/PKU-Cluster/RunII"+tag+"/MakeTemplate/With_sieieCorr/"<<"/MakeTemplate/With_sieieCorr/"<<channel<<"/ZAfit/fractionfitResult_za/txt/fakerate_"<<name3<<Form("_pt%0.f_%0.f.txt",lowpt,highpt)<<endl;}
        double ff1,ff2,ff3,fakerate;
	double sideband_uncer;
        f1>>ff1;f2>>ff2;f3>>ff3;
	sideband_uncer = fabs(ff1-ff2)/(2*ff3);
        file1<<fixed<<setprecision(2)<<fabs(ff1-ff2)/(2*ff3)<<"\t"<<ff3<<endl;
        file<<fixed<<setprecision(0)<<lowpt<<"~"<<highpt<<"\t"<<fixed<<setprecision(2)<<fabs(ff1-ff2)/(2*ff3)<<endl;
	cout<<tag<<" "<<channel<<" "<<lowpt<<"~"<<highpt<<" "<<name1<<" "<<ff1<<" "<<name2<<" "<<ff2<<" "<<name3<<" "<<ff3<<" "<<sideband_uncer<<endl;
}
int sideband(){
        vector<TString> tag={"2016","2017","2018"};
        vector<TString> channel={"BarrelMuon","EndcapMuon","ElectronBarrel","ElectronEndcap"};
        vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
        vector<double> lowpt;vector<double> highpt;
        for(int i=0;i<tag.size();i++){
                for(int j=0;j<channel.size();j++){
                        cout<<tag[i]<<" "<<channel[j]<<endl;
                        if(channel[j].Contains("Barrel")) {
                                lowpt={20,25,30,35,40,50,60,100};
                                highpt={25,30,35,40,50,60,100,400};
                        }
                        else if(channel[j].Contains("Endcap")) {
                                lowpt={20,25,30,40,50,60};
                                highpt={25,30,40,50,60,400};
                        }
                        const int ptnumber=lowpt.size();
                        cout<<"ptnumber "<<ptnumber<<endl;
			file1.open("./sideband_uncer/"+channels[j]+tag[i]+"_sideband_uncer.txt");
			file.open("./"+channels[j]+tag[i]+"_sideband_uncer.txt");
                        for(Int_t k=0;k<ptnumber;k++){
                           run(lowpt[k],highpt[k],tag[i], channel[j],"ZA1","ZA2","ZA");
                        }
			file1.close();
			file.close();

                }
        }
return 0;
}

