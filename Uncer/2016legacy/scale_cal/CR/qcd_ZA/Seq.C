#define num 7
bool myfunction (double i,double j) { return (i>j); }

struct myclass {
  bool operator() (double i,double j) { return (i>j);}
} myobject;

void open(Int_t i);
const int p=1;//the amount of bin
const int histo_number=num-1;// the number of histo except centeral 
const int number=num;// the number of histo  
Double_t central_value[p],nlo_value[histo_number][p];//[the amount of pdf][the amout of bin]
Double_t BinV[number][p];
ofstream f1("./scale-uncertainty.txt");
vector<Double_t> vector_nlo,vector_center,vec;
vector<Double_t>:: iterator biggest_nlo;
vector<Double_t>:: iterator smallest_nlo;
Double_t biggest[p],smallest[p];
Double_t uncertainty[p];
Double_t maximum[p],minimum[p];
void open(Int_t i){
    ifstream file(Form("./scale-txt/content-hist_no%d",i));
    if(!file.is_open()){cout<<"can not open the "<<i<<" file"<<endl;   }
    for(Int_t j=0;j<p;j++){
       if(i==1){
         file>>central_value[j];
         cout<<"histo "<<i<<"; bin"<<j+1<<"; central_value = "<<central_value[j]<<endl;  }
       if(i>1){
          file>>nlo_value[i-2][j];
          cout<<"hist "<<i<<"; bin"<<j+1<<"; nlo_value = "<<nlo_value[i-2][j]<<endl;
          //nlo_value[i][j]代表第几个histo的第几个bin的值
         }
      }

 }
 
int Seq(){
    gStyle->SetOptStat(0);
for(Int_t i=1;i<=histo_number+1;i++){
   open(i);
   //把每个histo的bincontent输出
   cout<<"*****************************"<<endl;
  }
for(Int_t j=0;j<p;j++){
    BinV[0][j] = central_value[j];
//    cout<<BinV[0][j]<<endl;
     cout<<j+1 <<" bin: ";
    vector_nlo.push_back(central_value[j]);
    vec.push_back(central_value[j]);
    for(Int_t i=0;i<histo_number;i++){
        BinV[i+1][j] = nlo_value[i][j];
        vector_nlo.push_back(nlo_value[i][j]);
        vec.push_back(nlo_value[i][j]);
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
              if(kk<5) cout<<"scalef"<<kk+1<<">"<<" ";
              else if(kk==5) cout<<"scalef"<<kk+2<<">"<<" ";
              else cout<<"scalef"<<kk+3<<">"<<" ";
           }
       }
   }
   biggest[j] = BinV[5][j];smallest[j] = BinV[3][j];
   cout<<"OK"<<endl;
   biggest_nlo = max_element(begin(vec),end(vec));
   smallest_nlo = min_element(begin(vec),end(vec));
   uncertainty[j]=(*biggest_nlo - *smallest_nlo)/(2*central_value[j]);
   cout<<"OK"<<endl;
//   cout<<"bin "<<j+1<<" biggest "<<*biggest_nlo<<" smallest "<<*smallest_nlo<<endl;
//   uncertainty[j]=(vector_nlo[0] - vector_nlo[8])/(2*central_value[j]);
   vector_nlo.clear();
   vec.clear();
//   cout<<"***************************************************************************"<<endl;
  }
cout<<"bin"<<"\t"<<"down\t"<<"up"<<"\t"<<"uncertainty"<<endl;
for(Int_t j=0;j<p;j++){
     cout<<j+1<<"\t"<<fixed<<setprecision(3)<<1-(central_value[j]-smallest[j])/central_value[j]<<" ";
     cout<<" "<<1+(biggest[j]-central_value[j])/central_value[j];
     cout<<" "<<uncertainty[j]<<endl;
    f1<<" "<<uncertainty[j]<<endl;
  }
     cout<<"down: ";
for(Int_t j=0;j<p;j++){
     cout<<fixed<<setprecision(3)<<1-(central_value[j]-smallest[j])/central_value[j]<<",";
}
cout<<endl;
 cout<<"up: ";
for(Int_t j=0;j<p;j++){
     cout<<fixed<<setprecision(3)<<1+(biggest[j]-central_value[j])/central_value[j]<<",";
}
cout<<endl;
cout<<"uncer ";
for(Int_t j=0;j<p;j++){
     cout<<fixed<<setprecision(2)<<1+uncertainty[j]<<",";
}
cout<<endl;

return 0;
}

