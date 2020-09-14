#include<iostream>
#define pi 3.1415926
using namespace std;

template<class T>

int length(T& arr)
{
    //cout << sizeof(arr[0]) << endl;
    //cout << sizeof(arr) << endl;
    return sizeof(arr) / sizeof(arr[0]);
//    return sizeof(arr) ;
}
void run(TString dir,TString sample,TString var1, vector<double> bins,TString cut1,TString tag){
     const int nbins=bins.size()-1;
     TFile*file=new TFile(dir+"cutla-out"+sample+".root");
     TTree*tree=(TTree*)file->Get("demo");

     TString lumi;
     if(tag.Contains("16"))
	     lumi=Form("%f",35.86);cout<<lumi<<endl;
     if(tag.Contains("17"))
	     lumi=Form("%f",41.52);cout<<lumi<<endl;
     if(tag.Contains("18"))
	     lumi=Form("%f",58.7);cout<<lumi<<endl;
     TString th2name;
     th2name="hist_"+var1;
     TH1D*th2 = new TH1D(th2name,"reco && gen",nbins,&bins[0]);
     if(sample.Contains("plj"))
	     tree->Draw(var1+">>"+th2name,cut1+"*scalef","goff");
     else
	     tree->Draw(var1+">>"+th2name,cut1+"*scalef*"+lumi,"goff");

     th2->SetBinContent(nbins,th2->GetBinContent(nbins)+th2->GetBinContent(nbins+1));//add overflowbin
     TFile*fout=new TFile("hist_"+sample+"_"+var1+tag+".root","recreate");
     th2->Write();
     fout->Close();
}
int Build_UnfoldHist_bkg(){
     TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
     TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
     TString photon = "photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
     TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
     TString Pi=Form("%f",pi);
     TString dr = "( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
     TString ControlRegion = "Mjj>150 && Mjj<400 & Mva>100";
     TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+ControlRegion;
     TString cut1 ="("+Reco+")";

     vector<vector<double>> bins;
     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     vector<double> MvaBins={100,150,1000};
     vector<double> MjjBins={150,200,300,400};
     bins.push_back(ptlepBins); 
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
     bins.push_back(MvaBins);
     bins.push_back(MjjBins);
     TString sample[6]={"plj_weight","VV","ST","ZA","TTA","WA"};
     TString vars[5]={"ptlep1","photonet","jet1pt","Mva","Mjj"};
     TString dir1="/eos/user/y/yian/2016legacy/";
     TString dir2="/eos/user/y/yian/2017cutla/";
     TString dir3="/eos/user/y/yian/2018cutla/";
     for(int i=0;i< bins.size();i++){
	     for(int j=0;j<6;j++){//sample index
                     cout<<sample[j]<<" "<<bins[i].size()<<endl;
		     run(dir1,sample[j],vars[i],bins[i],cut1,"16");
		     run(dir2,sample[j],vars[i],bins[i],cut1,"17");
		     run(dir3,sample[j],vars[i],bins[i],cut1,"18");
	     }
 
     }    
     bins.clear();
     return 1;
}

