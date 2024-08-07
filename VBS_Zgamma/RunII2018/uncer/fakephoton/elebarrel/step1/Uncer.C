#include "closure.C"
#include "sideband.C"
#include "truetemplateUncer.C"
void Uncer(){
ofstream f4("./summary.txt");
ofstream f5("./plj_summary.txt");

ofstream f0("./pljweight.txt");
ofstream fup("./pljweight_up.txt");
ofstream fdown("./pljweight_down.txt");

TFile* f1 = new TFile("/home/pku/anying/cms/RunII2018/plj/plj-plot/EleBarrel/plj-hist/cutla-outDEle_plj_hb.root");
TFile* f2 = new TFile("/home/pku/anying/cms/RunII2018/plj/plj-plot/EleBarrel/plj-hist/cutla-outDEle_hb.root");
TFile* f3 = new TFile("/home/pku/anying/cms/RunII2018/plj/plj-plot/EleBarrel/plj-hist/cutla-outZA_contamination_hb.root");

TH1F* h1 = (TH1F*)f1->Get("h_cutla-outDEle_plj");
TH1F* h2 = (TH1F*)f2->Get("h_cutla-outDEle");
TH1D* h3 = (TH1D*)f3->Get("h_cutla-outZA_contamination");

f4<<"pt"<<"\t"<<"closure"<<"\t\t"<<"sideband"<<"\t"<<"template"<<"\t"<<"total"<<endl;
f5<<"pt"<<"\t"<<"plj"<<"\t\t"<<"plj_up"<<"\t\t"<<"plj_down"<<endl;
cout<<"closure test uncertainty"<<endl;

Double_t bin_data[num],bin_plj[num],bin_za[num];
Double_t weight[num],weight_up[num],weight_down[num];
double uncer_tot,fakefraction_up,fakefraction_down;
int j=0;
for(Int_t i=0;i<num;i++){
	 if(j>=ptnumber-1) j=ptnumber-1;
          if(lowpt[j]==lpt[i] && highpt[j]==hpt[i])
                  run_calculate(j,i);
          if(lowpt[j]==lpt[i] && highpt[j]>hpt[i])
                 { run_calculate(j,i);
                         j = j-1;
                 }
          if(lowpt[j]<lpt[i] && highpt[j]==hpt[i])
                  run_calculate(j,i);
          j++;
	 if(j>=ptnumber-1) j=ptnumber-1;

	 open(lpt[i],hpt[i],"ZA1","ZA2","ZA");
	 open(lpt[i],hpt[i],"EWK","ZA");
//         if(i==num-1) open(lowpt[i],highpt[i],"TTA","ZA");
//         else open(lowpt[i],highpt[i],"EWK","ZA");
	 f4<<fixed<<setprecision(0)<<lpt[i]<<"~"<<hpt[i]<<"\t"<<fixed<<setprecision(2)<<closure_uncer<<"\t\t"<<sideband_uncer<<"\t\t"<<truetemplate_uncer<<"\t\t"<<sqrt(closure_uncer*closure_uncer+sideband_uncer*sideband_uncer+truetemplate_uncer*truetemplate_uncer)<<endl;
         uncer_tot = sqrt(closure_uncer*closure_uncer+sideband_uncer*sideband_uncer+truetemplate_uncer*truetemplate_uncer);
         fakefraction_up = fakefraction*(1+uncer_tot);
         fakefraction_down = fakefraction*(1-uncer_tot);
    bin_data[i]=h2->GetBinContent(i+1);
    bin_plj[i] =h1->GetBinContent(i+1);
    bin_za[i] = 59.97*h3->GetBinContent(i+1);
    weight[i]=bin_data[i]*fakefraction/(bin_plj[i]-bin_za[i]);
    weight_up[i]=bin_data[i]*fakefraction_up/(bin_plj[i]-bin_za[i]);
    weight_down[i]=bin_data[i]*fakefraction_down/(bin_plj[i]-bin_za[i]);
    cout<<fixed<<setprecision(0)<<lpt[i]<<"~"<<hpt[i]<<"\t"<<fixed<<setprecision(3)<<weight[i]<<endl;
    f5<<fixed<<setprecision(0)<<lpt[i]<<"~"<<hpt[i]<<"\t"<<fixed<<setprecision(3)<<weight[i]<<"\t\t"<<weight_up[i]<<"\t\t"<<weight_down[i]<<endl;
    f0<<weight[i]<<endl;
    fup<<weight_up[i]<<endl;
    fdown<<weight_down[i]<<endl;

   }


}
