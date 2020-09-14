#define num 7
ofstream myfile("result.txt");
//Double_t lowpt[num] ={20,25,30,35,40,45,50,60,80,120};
//Double_t highpt[num]={25,30,35,40,45,50,60,80,120,400};
  Double_t lowpt[num]= {20,25,30,40,50,65,100};
  Double_t highpt[num]={25,30,40,50,65,100,400};
void get(Double_t lowpt,Double_t highpt){
//TString dir = "./result_endcap/";
TString dir = "./";
ifstream f1,f2;
f2.open(Form("closure-test_pt%0.f-%0.f.txt",lowpt,highpt));
if(!f2.is_open()) cout<< "can't open the file"<<endl;
Double_t value[22];
for(Int_t i=0;i<22;i++){
   f2>>value[i+1];
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
 void run(Int_t a){
     cout<<"pt: "<<lowpt[a]<<" ~ "<<highpt[a]<<endl; 
     get(lowpt[a],highpt[a]);
    }

int draw_closuretest(){
  for(Int_t i=0;i<num;i++){
     myfile<<fixed<<setprecision(0)<<"pt: "<<lowpt[i]<<" ~ "<<highpt[i]<<endl; 
     run(i);
     myfile<<"############################################################"<<endl;
     }
  return 0;
 }
