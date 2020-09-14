#include "fit.C"
void run_fit(){
    float lowchiso[21];
    float highchiso[21];
//	fit(15,20);
//	fit(20,25);
	fit(25,30);
	fit(30,40);
	fit(40,50);
	fit(50,70);
	fit(70,100);
	fit(100,135);
	fit(135,400);

}

int runfit(){
    /*for(Int_t i=10;i<21;i++){*/
	run_fit();
	return 0;
}
