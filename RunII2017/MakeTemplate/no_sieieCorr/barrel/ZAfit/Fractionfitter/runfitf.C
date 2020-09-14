#include "fitfraction.C"
void run_fit(){
    float lowchiso[21];
    float highchiso[21];
//	fitf(15,20);
//	fitf(20,25);
	fitf(25,30);
	fitf(30,35);
	fitf(35,40);
	fitf(40,45);
	fitf(45,50);
	fitf(50,60);
	fitf(60,80);
	fitf(80,120);
	fitf(120,400);

}

int runfitf(){
    /*for(Int_t i=10;i<21;i++){*/
	run_fit();
	return 0;
}
