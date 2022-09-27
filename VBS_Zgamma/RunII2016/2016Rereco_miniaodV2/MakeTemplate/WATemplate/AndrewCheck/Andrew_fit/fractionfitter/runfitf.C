#include "fitfraction.C"
void run_fit(){
    float lowchiso[21];
    float highchiso[21];
//	fitf(15,20);
//	fitf(20,25);
	fitf(25,30);
	fitf(30,40);
	fitf(40,50);
	fitf(50,70);
	fitf(70,100);
	fitf(100,135);
	fitf(135,400);

}

int runfitf(){
    /*for(Int_t i=10;i<21;i++){*/
	run_fit();
	return 0;
}
