#define num 9
bool myfunction (double i,double j) { return (i>j); }

struct myclass {
	bool operator() (double i,double j) { return (i>j);}
} myobject;

void open(Int_t i,TString tag);
const int p=7;//the amount of bin
const int histo_number=num-1;// the number of histo except centeral 
const int number=num;// the number of histo  
Double_t central_value[p],nlo_value[histo_number][p];//[the amount of pdf][the amout of bin]
Double_t BinV[number][p];
vector<Double_t> vector_nlo,vector_center,vec;
vector<Double_t>:: iterator biggest_nlo;
vector<Double_t>:: iterator smallest_nlo;
Double_t biggest[p],smallest[p];
Double_t uncertainty[p];
Double_t maximum[p],minimum[p];
TH1D*h1[num];
void open(Int_t i,TString tag){
	TFile*f1=new TFile("hist_qcd_scale"+tag+".root");
	if( (i!=6&&i!=8) ){ 
		h1[i]=(TH1D*)f1->Get(Form("hist_%i",i-1)); 
		for(Int_t j=0;j<p;j++){
			if(i==1){
				central_value[j]=h1[i]->GetBinContent(j+1);
				cout<<"histo "<<i<<"; bin"<<j+1<<"; central_value = "<<central_value[j]<<endl;  }
			if(i>1){
				nlo_value[i-2][j]=h1[i]->GetBinContent(j+1);
				cout<<"hist "<<i<<"; bin"<<j+1<<"; nlo_value = "<<nlo_value[i-2][j]<<endl;
				//Print the bincontent for histos expect the central histo
			}
		}
	}
}

void Seq_run(TString tag){
	gStyle->SetOptStat(0);
	for(Int_t i=1;i<=histo_number+1;i++){
//		if(i==6||i==8)continue;
		open(i,tag);
		//Print the bincontent for every histos
		cout<<"*****************************"<<endl;
	}
	for(Int_t j=0;j<p;j++){
		BinV[0][j] = central_value[j];
		cout<<j+1 <<" bin: ";
		vector_nlo.push_back(central_value[j]);
		vec.push_back(central_value[j]);
		for(Int_t i=0;i<histo_number;i++){
			BinV[i+1][j] = nlo_value[i][j];
			if( (i+1)==5||(i+1)==7 )continue;
			vector_nlo.push_back(nlo_value[i][j]);
			vec.push_back(nlo_value[i][j]);
		}
		sort (vector_nlo.begin(), vector_nlo.end(), myobject);
		for (std::vector<double>::iterator it=vector_nlo.begin(); it!=vector_nlo.end(); ++it){
			int position = distance( begin(vector_nlo), it);
			for(int kk=0;kk<number;kk++ ){
                                if(kk==5||kk==7)continue;
				if(BinV[kk][j] - *it ==0){
				      cout<<"scalef"<<kk+1<<">"<<" ";
				}
			}
		}
		biggest[j] = BinV[6][j];smallest[j] = BinV[3][j];
		cout<<endl;
		biggest_nlo = max_element(begin(vec),end(vec));
		smallest_nlo = min_element(begin(vec),end(vec));
		uncertainty[j]=(*biggest_nlo - *smallest_nlo)/(2*central_value[j]);
		vector_nlo.clear();
		vec.clear();
		//   cout<<"***************************************************************************"<<endl;
	}
	cout<<"bin"<<"\t"<<"down\t"<<"up"<<"\t"<<"uncertainty"<<endl;
	for(Int_t j=0;j<p;j++){
		cout<<j+1<<"\t"<<fixed<<setprecision(3)<<1-(central_value[j]-smallest[j])/central_value[j]<<" ";
		cout<<" "<<1+(biggest[j]-central_value[j])/central_value[j];
		cout<<" "<<uncertainty[j]<<endl;
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
}
int Seq(){
	Seq_run("16");
	Seq_run("17");
	Seq_run("18");
	return 0;
}

