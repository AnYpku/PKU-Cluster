#include "RoccoR.C"

double get_rochester_scale(bool isdata, double charge_temp, double pt, double eta, double phi, int nl, double genPt, double r1){
	RoccoR  rc;
	rc.init(edm::FileInPath("./RoccoR2017.txt").fullPath());
	int charge = int(charge_temp/fabs(charge_temp));

	// data correction
	if(isdata) return rc.kScaleDT(charge, pt, eta, phi, 0, 0);

	// MC with genPt avalible
	if((!isdata) && genPt>0)
	return rc.kScaleFromGenMC(charge, pt, eta, phi, genPt, 0, 0);

	// MC without genPT avalible
	if((!isdata) && genPt<0)
	return rc.kScaleAndSmearMC(charge, pt, eta, phi, nl, r1, 0, 0);
	
}
