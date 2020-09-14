#define num 8
void Uncer(){

Double_t lpt[num]= {20,25,30,35,40,50,60,100};
Double_t hpt[num]={25,30,35,40,50,60,100,400};
ofstream f4("./summary.txt");
ofstream f5("./plj_summary.txt");

ofstream f0("./pljweight.txt");
ofstream fup("./pljweight_up.txt");
ofstream fdown("./pljweight_down.txt");

TFile* f1 = new TFile("/afs/cern.ch/work/y/yian/work/PKU-Cluster/RunII2018/plj/plj-plot/MuonBarrel/plj-hist/cutla-outDMuon_plj_h.root");
TFile* f2 = new TFile("/afs/cern.ch/work/y/yian/work/PKU-Cluster/RunII2018/plj/plj-plot/MuonBarrel/plj-hist/cutla-outDMuon_h.root");
TFile* f3 = new TFile("/afs/cern.ch/work/y/yian/work/PKU-Cluster/RunII2018/plj/plj-plot/MuonBarrel/plj-hist/cutla-outZA_plj_h.root");

TH1F* h1 = (TH1F*)f1->Get("h_cutla-outDMuon_plj");
TH1F* h2 = (TH1F*)f2->Get("h_cutla-outDMuon");
TH1D* h3 = (TH1D*)f3->Get("h_cutla-outZA_plj");

f4<<"pt"<<"\t"<<"closure"<<"\t\t"<<"sideband"<<"\t"<<"template"<<"\t"<<"total"<<"\t"<<"fakefraction"<<"\t"<<"fakefraction_up"<<"\t"<<"fakefraction_down"<<endl;
f5<<"pt"<<"\t"<<"plj"<<"\t\t"<<"plj_up"<<"\t\t"<<"plj_down"<<endl; 

Double_t bin_data[num],bin_plj[num],bin_za[num];
Double_t weight[num],weight_up[num],weight_down[num];

ifstream ff1,ff2,ff3,ff4;
ff1.open("./txt/trueTemplate-uncertainty.txt");
ff2.open("./txt/sideband-uncertainty.txt");
ff3.open("./txt/closure_FakeUncer.txt");
ff4.open("./txt/fakefraction.txt");
double uncer_tot,fakefraction_up,fakefraction_down,closure_uncer,sideband_uncer,truetemplate_uncer,fakefraction;
for(Int_t i=0;i<num;i++){
         ff1>>truetemplate_uncer;ff2>>sideband_uncer;ff3>>closure_uncer;ff4>>fakefraction;
	 uncer_tot = sqrt(closure_uncer*closure_uncer+sideband_uncer*sideband_uncer+truetemplate_uncer*truetemplate_uncer);
         fakefraction_up = fakefraction*(1+uncer_tot);
         fakefraction_down = fakefraction*(1-uncer_tot);
	 f4<<fixed<<setprecision(0)<<lpt[i]<<"~"<<hpt[i]<<"\t"<<fixed<<setprecision(2)<<closure_uncer<<"\t\t"<<sideband_uncer<<"\t\t"<<truetemplate_uncer<<"\t\t"<<sqrt(closure_uncer*closure_uncer+sideband_uncer*sideband_uncer+truetemplate_uncer*truetemplate_uncer)<<"\t\t"<<fakefraction<<"\t\t"<<fakefraction_up<<"\t\t"<<fakefraction_down<<endl;
	 cout<<fixed<<setprecision(0)<<lpt[i]<<"~"<<hpt[i]<<"\t"<<fixed<<setprecision(2)<<closure_uncer<<"\t\t"<<sideband_uncer<<"\t\t"<<truetemplate_uncer<<"\t\t"<<sqrt(closure_uncer*closure_uncer+sideband_uncer*sideband_uncer+truetemplate_uncer*truetemplate_uncer)<<"\t\t"<<fakefraction<<"\t\t"<<fakefraction_up<<"\t\t"<<fakefraction_down<<endl;

    bin_data[i]=h2->GetBinContent(i+1);
    bin_plj[i] =h1->GetBinContent(i+1);
    bin_za[i] = 35.8*h3->GetBinContent(i+1);
    weight[i]=bin_data[i]*fakefraction/(bin_plj[i]-bin_za[i]);
    weight_up[i]=bin_data[i]*fakefraction_up/(bin_plj[i]-bin_za[i]);
    weight_down[i]=bin_data[i]*fakefraction_down/(bin_plj[i]-bin_za[i]);
    f5<<fixed<<setprecision(0)<<lpt[i]<<"~"<<hpt[i]<<"\t"<<fixed<<setprecision(3)<<weight[i]<<"\t\t"<<weight_up[i]<<"\t\t"<<weight_down[i]<<endl;
    f0<<weight[i]<<endl;
    fup<<weight_up[i]<<endl;
    fdown<<weight_down[i]<<endl;
   }


}
