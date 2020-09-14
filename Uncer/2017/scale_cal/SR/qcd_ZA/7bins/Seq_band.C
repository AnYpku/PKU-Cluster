#define num 7
bool myfunction (double i,double j) { return (i>j); }

struct myclass {
  bool operator() (double i,double j) { return (i>j);}
} myobject;

void open(Int_t i);
const int p=7;//the amount of bin
const int histo_number=num-1;// the number of histo except centeral 
const int number=num;// the number of histo  
Double_t central_value[p],nlo_value[histo_number][p];//[the amount of pdf][the amout of bin]
Double_t BinV[number][p];
ofstream f1("./scale-uncertainty.txt");
vector<Double_t> vector_nlo,vector_center,vec;
vector<Double_t>:: iterator biggest_nlo;
vector<Double_t>:: iterator smallest_nlo;
Double_t biggest_band1[p],smallest_band1[p];
Double_t biggest_band2[p],smallest_band2[p];
Double_t biggest_band3[p],smallest_band3[p];
Double_t uncertainty[p];
Double_t maximum[p],minimum[p];
void open(Int_t i){
    ifstream file(Form("./uncer-txt/content-hist_no%d",i));
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
 
int Seq_band(){
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
              else if(kk==5) cout<<"scalef"<<7<<">"<<" ";
              else cout<<"scalef"<<9<<">"<<" ";
           }
       }
   }
   biggest_band1[j] = BinV[5][j];smallest_band1[j] = BinV[3][j];//scale7 and scale4
   biggest_band2[j] = BinV[2][j];smallest_band2[j] = BinV[1][j];//scale3 and scale2
   biggest_band3[j] = BinV[6][j];smallest_band3[j] = BinV[4][j];//scale9 and scale5
   cout<<endl;
   biggest_nlo = max_element(begin(vec),end(vec));
   smallest_nlo = min_element(begin(vec),end(vec));
   uncertainty[j]=(*biggest_nlo - *smallest_nlo)/(2*central_value[j]);
//   cout<<"bin "<<j+1<<" biggest "<<*biggest_nlo<<" smallest "<<*smallest_nlo<<endl;
//   uncertainty[j]=(vector_nlo[0] - vector_nlo[8])/(2*central_value[j]);
   vector_nlo.clear();
   vec.clear();
//   cout<<"***************************************************************************"<<endl;
  }
cout<<"bin"<<"\t"<<"down\t"<<"up"<<"\t"<<"uncertainty"<<endl;
/*for(Int_t j=0;j<p;j++){
     cout<<j+1<<"\t"<<fixed<<setprecision(3)<<1-(central_value[j]-smallest[j])/central_value[j]<<" ";
     cout<<" "<<1+(biggest[j]-central_value[j])/central_value[j];
     cout<<" "<<uncertainty[j]<<endl;
    f1<<" "<<uncertainty[j]<<endl;
  }*/
     cout<<"uncertaninty band1: ";
for(Int_t j=0;j<p;j++){
//     cout<<fixed<<setprecision(3)<<1+fabs(biggest_band1[j]-smallest_band1[j])/(2*central_value[j])<<",";
     cout<<fixed<<setprecision(3)<<100*fabs(biggest_band1[j]-smallest_band1[j])/(2*central_value[j])<<"%,";
}
cout<<endl;
cout<<"uncertaninty band2: ";
for(Int_t j=0;j<p;j++){
     cout<<fixed<<setprecision(3)<<100*fabs(biggest_band2[j]-smallest_band2[j])/(2*central_value[j])<<"%,";
}
cout<<endl;
cout<<"uncertaninty band3: ";
for(Int_t j=0;j<p;j++){
     cout<<fixed<<setprecision(3)<<100*fabs(biggest_band3[j]-smallest_band3[j])/(2*central_value[j])<<"%,";
}
cout<<endl;

return 0;
}

