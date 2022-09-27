void open(Int_t i);
const int p=9;//the amount of bin
const int histo_number=8;// the number of histo except centeral 
Double_t central_value[p],nlo_value[histo_number][p];//[the amount of pdf][the amout of bin]
ofstream f1("./scale-uncertainty.txt");
void open(Int_t i){
    ifstream file(Form("./scale-txt/content-hist_%d",i));
    if(!file.is_open()){cout<<"can not open the "<<i<<" file"<<endl;   }
    for(Int_t j=0;j<p;j++){
       if(i==1){
         file>>central_value[j];
         cout<<"histo "<<i<<"; bin"<<j+1<<"; central_value = "<<central_value[j]<<endl;  }
       if(i>1){
          file>>nlo_value[i-2][j];
          cout<<"hist "<<i<<"; bin"<<j<<"; nlo_value = "<<nlo_value[i-2][j]<<endl;
          //nlo_value[i][j]代表第几个histo的第几个bin的值
         }
      }

 }
 
int calculate_uncertainty(){
    gStyle->SetOptStat(0);
for(Int_t i=1;i<=histo_number+1;i++){
   open(i);
   //对于第j个bin，把每个histo的bincontent输出
   cout<<"*****************************"<<endl;
  }
Double_t single,sum,average,uncertainty[p],mean=0;
for(Int_t j=0;j<p;j++){
  sum=0;
  mean=0;
  for(Int_t i=0;i<histo_number;i++){
      single = pow(nlo_value[i][j]-central_value[j],2);
      sum = sum+single;
      mean = (mean + nlo_value[i][j]);
      if(i==histo_number-1){
         mean = (mean + central_value[j])/(histo_number+1);
         average = sum/histo_number;
         uncertainty[j]=sqrt(sum/8)/mean;
         }
      }
//    cout<<"bin "<<j+1<<"; mean = "<<mean<<endl;
//    cout<<"bin "<<j+1<<"; sum = "<<sum<<endl;
    cout<<"bin "<<j+1<<"; uncertainty["<<j<<"] = "<<uncertainty[j]<<endl;
    f1<<"bin "<<j+1<<"; uncertainty["<<j<<"] = "<<uncertainty[j]<<endl;
  }
const char *name[9]={"Mjj 500~750","Mjj 750~1000","Mjj 1000~2000","Mjj 500~750","Mjj 750~1000","Mjj 1000~2000","Mjj 500~750","Mjj 750~1000","Mjj 1000~2000"};
TH1D* h1 =new TH1D("h1","uncertainty",9,0,0.5);
for(Int_t i=0;i<9;i++){
    h1->SetBinContent(i+1,uncertainty[i]);
    h1->SetTitle("uncertainty;;uncertainty");
    h1->GetXaxis()->SetBinLabel(i+1,name[i]);
    h1->GetYaxis()->CenterTitle();
    h1->GetYaxis()->SetTitleFont(32);
    h1->GetYaxis()->SetLabelFont(22);
    h1->GetYaxis()->SetLabelSize(0.05);
    h1->GetYaxis()->SetTitleSize(0.06);
    h1->GetYaxis()->SetTitleOffset(0.85);
    h1->GetXaxis()->SetLabelFont(22);
    h1->GetXaxis()->SetLabelSize(0.05);
    h1->SetMarkerStyle(29);
    h1->SetMarkerSize(1.5);
    h1->Draw("P");}



return 0;
}

