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
     TFile*file;
     if(sample.Contains("plj")) file=new TFile(dir+"cutla-outplj"+tag+"_weight.root");
     else file=new TFile(dir+"cutla-out"+sample+tag+".root");
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");

     TString lumi;
     if(tag.Contains("16"))
	     lumi=Form("%f",35.86);cout<<lumi<<endl;
     if(tag.Contains("17"))
	     lumi=Form("%f",41.52);cout<<lumi<<endl;
     if(tag.Contains("18"))
	     lumi=Form("%f",59.7);cout<<lumi<<endl;
     TString th2name;
     th2name="hist_"+var1;
     TH1D*th2 = new TH1D(th2name,"reco && gen",nbins,&bins[0]);
     TString weight;
     if(tag.Contains("16"))
        weight="*scalef*pileupWeight*photon_id_scale*photon_veto_scale*fabs(ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale)*fabs(muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale)*prefWeight*puIdweight_M*"+lumi;
     else if(tag.Contains("17"))
        weight="*scalef*pileupWeight*photon_id_scale*photon_veto_scale*fabs(ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale)*fabs(muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale)*prefWeight*puIdweight_T*"+lumi;
     else if(tag.Contains("18"))
        weight="*scalef*pileupWeight*photon_id_scale*photon_veto_scale*fabs(ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale)*fabs(muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale)*puIdweight_L*"+lumi;
     if(sample.Contains("plj"))
	     tree->Draw(var1+">>"+th2name,cut1+"*scalef","goff");
     else if(sample.Contains("Ele"))
	     tree->Draw(var1+">>"+th2name,"("+cut1+"&&!(lep==13))*1","goff");
     else if(sample.Contains("Muon"))
	     tree->Draw(var1+">>"+th2name,"("+cut1+"&&!(lep==11))*1","goff");
     else
	     tree->Draw(var1+">>"+th2name,cut1+weight,"goff");

     th2->SetBinContent(nbins,th2->GetBinContent(nbins)+th2->GetBinContent(nbins+1));//add overflowbin
     th2->SetBinError(nbins,sqrt(pow(th2->GetBinError(nbins),2)+pow(th2->GetBinError(nbins+1),2)));
     TFile*fout=new TFile("./root/hist_"+sample+"_"+var1+tag+".root","recreate");
     th2->Write();
     fout->Close();
}
int Build_UnfoldHist_bkg(){
     TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
     TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
     TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
     TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
     TString Pi=Form("%f",pi);
     TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5 )";
     TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && Mva>100)";

     vector<vector<double>> bins;
     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     bins.push_back(ptlepBins); 
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
//     vector<TString> sample={"plj","VV","ST","ZA","TTA"};
//     vector<TString> sample={"DMuon","DEle"};
     vector<TString> sample={"ZA_interf"};
     TString vars[3]={"ptlep1","photonet","jet1pt"};
     TString dir[3];
     dir[0]="/home/pku/anying/cms/rootfiles/2016/";
     dir[1]="/home/pku/anying/cms/rootfiles/2017/";
     dir[2]="/home/pku/anying/cms/rootfiles/2018/";
     vector<TString> tag={"16","17","18"};
     for(int k=0;k<tag.size();k++){
	     if(tag[k].Contains("16")){
		     jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
	     }
	     else if(tag[k].Contains("17")){
		     jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
	     }
	     else if(tag[k].Contains("18")){
		     jet = "( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
	     }
	     TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
	     TString cut1 ="("+Reco+")";
	   //if(tag[k].Contains("17")==0) continue;
	     for(int i=0;i< bins.size();i++){
		     for(int j=0;j<sample.size();j++){//sample index
			     cout<<sample[j]<<" "<<bins[i].size()<<endl;
			     run(dir[k],sample[j],vars[i],bins[i],cut1,tag[k]);
		     }
	     }

     }    
     bins.clear();
     return 1;
}

