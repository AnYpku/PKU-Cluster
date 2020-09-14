#include "RoccoR.C"

double get_rochester_scale(bool isdata, double charge_temp, double pt, double eta, double phi, int nl, double genPt, double r1, double r2){
	
	RoccoR  rc("rcdata.2016.v3");
	int charge = int(charge_temp/fabs(charge_temp));

	// data correction
	if(isdata) return rc.kScaleDT(charge, pt, eta, phi, 0, 0);

	// MC with genPt avalible
	if((!isdata) && genPt>0)
	return rc.kScaleFromGenMC(charge, pt, eta, phi, nl, genPt, r1, 0, 0);

	// MC without genPT avalible
	if((!isdata) && genPt<0)
	return rc.kScaleAndSmearMC(charge, pt, eta, phi, nl, r1, r2, 0, 0);
	
}
