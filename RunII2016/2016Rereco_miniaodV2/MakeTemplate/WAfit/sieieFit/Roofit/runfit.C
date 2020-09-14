#include "fit.C"
void run_fit(){
    float lowchiso[21];
    float highchiso[21];
//	fit(15,20);
//	fit(20,25);
	fit(25,30);
	fit(30,35);
	fit(35,40);
	fit(40,45);
	fit(45,50);
	fit(50,60);
	fit(60,80);
	fit(80,120);
	fit(120,400);

}

int runfit(){
    /*for(Int_t i=10;i<21;i++){*/
	run_fit();
	return 0;
}
