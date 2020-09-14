#include "math.h"

int thesubsector( double phi, double eta){
	int side = (eta>0)? 1:-1;
	double phiindegree = phi*180/3.1415926;
	if(fabs(eta)<1.25) return 0;
	else if(fabs(eta)<1.8){
		//Code is: 1=> first 50 degrees of the sector, 11=> last 10 deg of previous sector
		if(phiindegree>=5&& phiindegree<15) return 11*side;
		if(phiindegree>=15&& phiindegree<65) return 1*side;
		if(phiindegree>=65&& phiindegree<75) return 12*side;
		if(phiindegree>=75&& phiindegree<125) return 2*side;
		if(phiindegree>=125&& phiindegree<135) return 13*side;
		if(phiindegree>=135&& phiindegree<185) return 3*side;
		if(phiindegree>=185&& phiindegree<195) return 14*side;
		if(phiindegree>=195&& phiindegree<245) return 4*side;
		if(phiindegree>=245&& phiindegree<255) return 15*side;
		if(phiindegree>=255&& phiindegree<305) return 5*side;
		if(phiindegree>=305&& phiindegree<315) return 16*side;
		if(phiindegree>=315 || phiindegree < 5) return 6*side;
	}
	else {
		//Code is: 1=> first 40 degrees of the sector, 11=> last 20 deg of previous sector
		if(phiindegree>=355 || phiindegree<15) return 11*side;
		if(phiindegree>=15&& phiindegree<55) return 1*side;
		if(phiindegree>=55&& phiindegree<75) return 12*side;
		if(phiindegree>=75&& phiindegree<115) return 2*side;
		if(phiindegree>=115&& phiindegree<135) return 13*side;
		if(phiindegree>=135&& phiindegree<175) return 3*side;
		if(phiindegree>=175&& phiindegree<195) return 14*side;
		if(phiindegree>=195&& phiindegree<235) return 4*side;
		if(phiindegree>=235&& phiindegree<255) return 15*side;
		if(phiindegree>=255&& phiindegree<295) return 5*side;
		if(phiindegree>=295&& phiindegree<315) return 16*side;
		if(phiindegree>=315 &&phiindegree < 355) return 6*side;
	}
		return 0;
} 

double L1_weight(double phiext1, double phiext2, double eta1, double eta2) {

	if(fabs(eta1)<1.25 || fabs(eta2)<1.25) return 1;

	int theCSCsubsector1 = thesubsector(phiext1,eta1);
	int theCSCsubsector2 = thesubsector(phiext2,eta2);

	if (theCSCsubsector1 * theCSCsubsector2 <=0) return 1;
	if (theCSCsubsector1 == theCSCsubsector2 ) return 0;
	if ( fabs(theCSCsubsector1 - theCSCsubsector2) ==10 ) return 0.5;
	return 1;
}

