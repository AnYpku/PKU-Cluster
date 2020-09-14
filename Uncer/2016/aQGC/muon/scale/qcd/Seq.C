#define num 7
bool myfunction (double i,double j) { return (i>j); }

struct myclass {
  bool operator() (double i,double j) { return (i>j);}
} myobject;

void open(Int_t i);
const int p=5;//the amount of bin
const int histo_number=6;// the number of histo except centeral 
const int number=num;// the number of histo 
Double_t central_value[p],nlo_value[histo_number][p];//[the amount of pdf][the amout of bin]
Double_t BinV[number][p];
ofstream f1("./scale-aQGC_Uncer.txt");
vector<Double_t> vector_nlo,vector_center;
vector<Double_t>:: iterator biggest_nlo;
vector<Double_t>:: iterator smallest_nlo;
Double_t biggest[p],smallest[p];
Double_t biggest_uncer[p],smallest_uncer[p];
TFile*file=new TFile("aa.root");
TH1D*h1[7];
void open(Int_t i){
    h1[i-1]=(TH1D*)file->Get(Form("th2_%i",i-1));
    for(Int_t j=0;j<p;j++){
       if(i==1){
         central_value[j]=h1[i-1]->GetBinContent(j+1);
         cout<<"histo "<<i<<"; bin"<<j+1<<"; central_value = "<<central_value[j]<<endl;  }
       if(i>1){
//          file>>nlo_value[i-2][j];
            nlo_value[i-2][j]=h1[i-1]->GetBinContent(j+1);
            cout<<"hist "<<i<<"; bin"<<j+1<<"; nlo_value = "<<nlo_value[i-2][j]<<endl;
          //nlo_value[i][j]代表第几个histo的第几个bin的值
         }
      }

 }
 
int Seq(){
    gStyle->SetOptStat(0);
for(Int_t i=1;i<=histo_number+1;i++){
   open(i);
   cout<<"*****************************"<<endl;
  }
for(Int_t j=0;j<p;j++){
    BinV[0][j] = central_value[j];
//    cout<<BinV[0][j]<<endl;
     cout<<j+1 <<" bin: ";
    vector_nlo.push_back(central_value[j]);
    for(Int_t i=0;i<histo_number;i++){
        BinV[i+1][j] = nlo_value[i][j];
        vector_nlo.push_back(nlo_value[i][j]);
//        cout<<BinV[i+1][j]<<endl;
       }
   sort (vector_nlo.begin(), vector_nlo.end(), myobject);
   for (std::vector<double>::iterator it=vector_nlo.begin(); it!=vector_nlo.end(); ++it){
       int position = distance( begin(vector_nlo), it);
//       std::cout << *it<<endl;
//       cout<<j+1<<"bin ";
       for(int kk=0;kk<number;kk++ ){
           if(BinV[kk][j] - *it ==0){
              // cout<<kk+1<<" "<<BinV[kk][j]<<" "<<*it<<endl;
               int nn;nn=kk;
               if( (kk+1)==6) nn=6;
               if( (kk+1)==7 )nn=8; 
//               cout<<"scalef"<<nn+1<<"("<<BinV[kk][j]<<")"<<">"<<" ";
               cout<<"scalef"<<nn+1<<">"<<" ";
           }
       }
   }
   cout<<endl;
   biggest_nlo = max_element(begin(vector_nlo),end(vector_nlo));
   smallest_nlo = min_element(begin(vector_nlo),end(vector_nlo));
   biggest[j] = BinV[5][j];smallest[j] = BinV[3][j];
   biggest_uncer[j]=*biggest_nlo;
   smallest_uncer[j]=*smallest_nlo;
//   cout<<"*******************************"<<endl;
//   cout<<j+1 <<" bin "<<"; biggest = "<<biggest[j]<<"; smallest = "<<*smallest_nlo<<"; central value = "<<central_value[j]<<endl;
   vector_nlo.clear();
//   cout<<"***************************************************************************"<<endl;
  }
Double_t single,sum,average,uncertainty[p],mean=0,uncertainty_other[p];
cout<<"bin"<<"\t"<<"down\t"<<"up"<<"\t"<<"uncertainty"<<endl;
f1<<"bin"<<"\t"<<"down\t"<<"up"<<"\t"<<"uncertainty"<<endl;
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
         uncertainty[j]=sqrt(average)/mean;
         }
      }
  uncertainty_other[j]=(biggest_uncer[j]-smallest_uncer[j])/(2*central_value[j]);
//cout<<"bin "<<j+1<<"; mean = "<<mean<<endl;
//cout<<"bin "<<j+1<<"; sum = "<<sum<<endl;
//    cout<<"bin "<<j+1<<"; uncertainty["<<j<<"] = "<<uncertainty_other[j]<<endl;
     cout<<j+1<<"\t"<<fixed<<setprecision(3)<<1-(central_value[j]-smallest[j])/central_value[j]<<" ";
     f1<<j+1<<"\t"<<fixed<<setprecision(3)<<1-(central_value[j]-smallest[j])/central_value[j]<<" ";
     cout<<" "<<1+(biggest[j]-central_value[j])/central_value[j]<<" ";
     f1<<" "<<1+(biggest[j]-central_value[j])/central_value[j]<<" ";
    f1<<" "<<uncertainty_other[j]<<endl;
    cout<<" "<<uncertainty_other[j]<<endl;
  }
const char *name[p]={"ZGmass 150~400","ZGmass 400~600","ZGmass 600~800","ZGmass 800~1000","ZGmass 1000~2000"};//,"Mjj 1200~2000","Mjj 500~1200","Mjj 1200~2000"};
TH1D* h1 =new TH1D("h1","uncertainty",p,0,6);
/*for(Int_t i=0;i<p;i++){
    h1->SetBinContent(i+1,uncertainty_other[i]);
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
    h1->Draw("P");}*/



return 0;
}

