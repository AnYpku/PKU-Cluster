#include "RoccoR.cc"
double get_rochester_scale(bool isdata, double charge_temp, double pt, double eta, double phi, int nl, double genPt, double r1,TString tag){
	RoccoR  rc; 
	double scale=1;
	if(tag.Contains("16")) {rc.init("RoccoR2016.txt"); }
	if(tag.Contains("17")) {rc.init("RoccoR2017.txt"); }
	if(tag.Contains("18")) {rc.init("RoccoR2018.txt"); }
	int charge = int(charge_temp/fabs(charge_temp));
	// data correction
	if(isdata) 
		scale=rc.kScaleDT(charge, pt, eta, phi, 0, 0);
	
	// MC with genPt avalible
	if((!isdata) && genPt>0&&fabs(genPt-pt)/pt<0.1)
		scale=rc.kSpreadMC(charge, pt, eta, phi, genPt, 0, 0);

	// MC without genPT avalible
	if((!isdata) && !(genPt>0&&fabs(genPt-pt)/pt<0.1))
		scale=rc.kSmearMC(charge, pt, eta, phi, nl, r1, 0, 0);
	return scale;
}
