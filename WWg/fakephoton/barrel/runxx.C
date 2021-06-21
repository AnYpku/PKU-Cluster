#include "WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
	TString dir ="/home/pku/anying/cms/rootfiles/WWg/";
	ifstream infile("file");
	string buffer; 
	TString infilename;

	int k=1;
        vector<bool> isBarrel={1,0};
        vector<int>  channel_number={1,2,3};

	while (k>0){
		getline (infile, buffer) ;
		infilename = buffer;
		if(infilename.Contains("root")==0) {k=-2; continue;}
		if(infilename.Contains("end")==1) {k=-2; break;}
		infilename = infilename;
		TString outname=infilename;

		cout<<dir<<infilename<<" -> "<<outname<<endl;

		TFile *file1 =new TFile(dir+infilename);
		TTree *tree1 = (TTree*) file1->Get("Events");
		WWg m1(tree1,outname);
		cout<<outname<<endl;
		for(int i=0;i<isBarrel.size()-1;i++){
			for(int j=1;j<channel_number.size();j++){
                                if(outname.Contains("DMuon") && channel_number[j] == 2) 
					continue;
                                if( (outname.Contains("EGamma") || outname.Contains("Ele")) && channel_number[j] == 3) 
					continue;
                                cout<<"isBarrel "<<isBarrel[i]<<" channel "<<channel_number[j]<<endl;
				m1.Loop(outname,isBarrel[i],channel_number[j]);
			}
		}
		m1.endJob();

	}
}

int main(){
	runxx();
	return 1;
}

