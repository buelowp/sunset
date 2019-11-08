/*
 * Star.h
 *
 *  Created on: Nov 8, 2019
 *      Author: kiros
 */

#ifndef SRC_STAR_H_
#define SRC_STAR_H_
#define SID_CONST 4.894961212735792
#define SID_COEF 6.300388098984389
#define JD_EPOCH_2000 2451544 //2440587.5
#define JD_UNIX 2440587
enum EVENT{RISE, SET};

class Star {
	  double timeToDeg(double);
	  double degToTime(double);
	  double degToRad(double);
	  double radToDeg(double);
	  double adjustDeg(double);
	  double adjustTime(double);
	  double adjustRad(double);
public:
	double local_sidereal(int ,int ,int ,int ,int );
	  double udaysFromSid(double , double , double );
	  double localSidTime(double , double );
	  double starRiseTimeSidereal(double, double, double );
	  double starSetTimeSidereal(double , double , double );
	  int starRise_SetTime(double , double , double , double, double,int );
	  double starSetTimeSidereal(double , double , double,int );
	Star();
	virtual ~Star();
};

#endif /* SRC_STAR_H_ */
