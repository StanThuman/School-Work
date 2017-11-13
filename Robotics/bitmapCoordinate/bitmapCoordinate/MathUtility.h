#ifndef MATHUTILITY_H
#define MATHUTILITY_H

#include <math.h>
#include "Coordinate.h"
#include <iostream>
#include <iomanip>
using std::ofstream;
using std::cout;
using std::endl;
using std::setw;
using std::setprecision;


class MathUtility{


  public:
	//calculate distance formula
	static double distanceFormula(Coordinate point0, Coordinate point1){
		double distance;
		
		double x = point1.x - point0.x;
		double y = point1.y - point0.y;
		x = x * x;
		y = y * y;
		distance = sqrt((x+y));
		
		return distance;
	}



	//2 constraints
	//used for hw 1.a
	//(p1-p0)t + p0
    static Coordinate calculatePosWithTime(Coordinate point0, Coordinate point1, double time, ofstream* outputFile, bool isPrint){
		//(p1-p0)
		double t0 = distanceFormula(point0, point1);
		
		double x = (point1.x - point0.x) / t0;
		double y = (point1.y - point0.y) / t0;

		//(p1-p0)t
		Coordinate position;

		position.x = x/distanceFormula(point0, point1);
		position.y = y/distanceFormula(point0, point1);

		if (isPrint) {
			*outputFile << "Sx(t) = :\t " << setw(9) << setprecision(4) << position.x << 't' << " + \t " << point0.x << '\n';
			*outputFile << "Sy(t) = :\t " << setw(9) << setprecision(4) << position.y << 't' << " + \t " << point0.y << '\n';			
		}
		position.x = x * time;
		position.y = y * time;

		position.x = position.x + point0.x;
		position.y = position.y + point0.y;

		
		return position;
    }

	static void printOutput(){
	
	
	}
	//homework b s0
	static Coordinate calculatePosWIthTimeAndVelocity(Coordinate point0, Coordinate point1, Coordinate point2, double time, ofstream* outputFile, bool isPrint){

		double t0 = distanceFormula(point0, point1);
		double t1 = distanceFormula(point1, point2);

		Coordinate p2p1Difference;
		p2p1Difference.x = ( point2.x - point1.x );
		p2p1Difference.y = ( point2.y - point1.y );

		double productOfCoordAndTimeX1 = p2p1Difference.x * t0;
		double productOfCoordAndTimeY1 = p2p1Difference.y * t0;

		Coordinate p1p0Difference;
		p1p0Difference.x = ( point1.x - point0.x );
		p1p0Difference.y = ( point1.y - point0.y );

		double productOfCoordAndTimeX2 = p1p0Difference.x * t1;
		double productOfCoordAndTimeY2 = p1p0Difference.y * t1;
		
		Coordinate coord2;
		coord2.x = (productOfCoordAndTimeX1 - productOfCoordAndTimeX2) / (t1 * (t0 * t0));
		coord2.y = (productOfCoordAndTimeY1 - productOfCoordAndTimeY2) / (t1 * (t0 * t0));

		Coordinate coord1;
		coord1.x = (p1p0Difference.x * 2) * t1;
		coord1.y = (p1p0Difference.y * 2) * t1;

		coord1.x = coord1.x - (p2p1Difference.x * t0);
		coord1.y = coord1.y - (p2p1Difference.y * t0);

		coord1.x = coord1.x / (t0 * t1);
		coord1.y = coord1.y / (t0 * t1);

		Coordinate coord0;
		coord0.x = point0.x;
		coord0.y = point0.y;

		Coordinate finalCoordinate;
		finalCoordinate.x = ( coord2.x * (time * time) ) + ( coord1.x * time) + coord0.x;
		finalCoordinate.y = (coord2.y * (time * time)) + (coord1.y * time) + coord0.y;

		if (isPrint) {			
			*outputFile << "Sx(t) = :\t " << setw(9) << setprecision(4) << coord2.x << "t^2" << " + \t " << coord1.x << "t + \t" << point0.x << '\n';
			*outputFile << "Sy(t) = :\t " << setw(9) << setprecision(4) << coord2.y << "t^2" << " + \t " << coord1.y << "t + \t" << point0.y << '\n';
			*outputFile << "S'x(t) = :\t " << setw(9) << setprecision(4) << 2*coord2.x << "t + \t" << coord1.x << '\n';
			*outputFile << "S'y(t) = :\t " << setw(9) << setprecision(4) << 2*coord2.y << "t + \t" << coord1.y << '\n';

			*outputFile << "\nsegment\t  p_start\t    v(0)\t  \tp_end\t\tv(t_i)\n";
			*outputFile << 0 << ":     (" << point0.x << "," << point0.y << " ) \t   (" << coord1.x << "," << coord1.y << ")     ";
			*outputFile << "\t (" << point1.x << "," << point1.y << " )\t    (" << (((2 * coord2.x) * (t0/20))+ coord1.x) << "," << (((2 * coord2.y) * (t0 / 20)) + coord1.y) << ")\n\n";
		}

		return finalCoordinate;	
	}
	//homework b s1
	static Coordinate calculatePosWithTime1(Coordinate point0, Coordinate point1, double time, ofstream* outputFile, bool isPrint) {
		//(p1-p0)
		double t0 = distanceFormula(point0, point1);

		double x = (point1.x - point0.x) / t0;
		double y = (point1.y - point0.y) / t0;

		//(p1-p0)t		

		if (isPrint) {
			*outputFile << "Sx(t) = :\t " << setw(9) << setprecision(4) << x << 't' << " + \t " << point0.x << '\n';
			*outputFile << "Sy(t) = :\t " << setw(9) << setprecision(4) << y << 't' << " + \t " << point0.y << '\n';
			*outputFile << "S'x(t) = :\t " << setw(9) << setprecision(4) << x << '\n';
			*outputFile << "S'y(t) = :\t " << setw(9) << setprecision(4) << y << '\n';



			*outputFile << "\nsegment\t  p_start\t    v(0)\t\t\t p_end\t\tv(t_i)\n";
			*outputFile << 1 << ":     (" << point0.x << "," << point0.y << " ) \t   (" << x << "," << y << ")     ";
			*outputFile << "\t (" << point1.x << "," << point1.y << " )\t    (" << (x) << "," << (y) << ")\n\n";
		}		

		Coordinate position;
		position.x = (x * time) + point0.x;
		position.y = (y * time) + point0.y;


		return position;
	}


	//homework b s2 
	static Coordinate calculatePosWIthTimeAndVelocity2(Coordinate point0, Coordinate point1, Coordinate point2, double time, ofstream* outputFile, bool isPrint) {

		double tSub1 = distanceFormula(point0, point1);
		double tSub2 = distanceFormula(point1, point2);

		Coordinate p2p1Difference;
		p2p1Difference.x = (point2.x - point1.x);
		p2p1Difference.y = (point2.y - point1.y);

		double productOfCoordAndTimeX1 = p2p1Difference.x * tSub1;
		double productOfCoordAndTimeY1 = p2p1Difference.y * tSub1;

		Coordinate p1p0Difference;
		p1p0Difference.x = (point1.x - point0.x);
		p1p0Difference.y = (point1.y - point0.y);

		double productOfCoordAndTimeX2 = p1p0Difference.x * tSub2;
		double productOfCoordAndTimeY2 = p1p0Difference.y * tSub2;

		Coordinate coord22;
		coord22.x = (productOfCoordAndTimeX1 - productOfCoordAndTimeX2) / (tSub1 * (tSub2 * tSub2));
		coord22.y = (productOfCoordAndTimeY1 - productOfCoordAndTimeY2) / (tSub1 * (tSub2 * tSub2));

		Coordinate coord21;
		coord21.x = p1p0Difference.x / tSub1;
		coord21.y = p1p0Difference.y / tSub1;
		

		Coordinate coord20;
		coord20.x = point1.x;
		coord20.y = point1.y;

		Coordinate finalCoordinate;
		finalCoordinate.x = (coord22.x * (time * time)) + (coord21.x * time) + coord20.x;
		finalCoordinate.y = (coord22.y * (time * time)) + (coord21.y * time) + coord20.y;

		if (isPrint) {
			*outputFile << "Sx(t) = :\t " << setw(9) << setprecision(4) << coord22.x << "t^2" << " + \t " << coord21.x << "t + \t" << coord20.x << '\n';
			*outputFile << "Sy(t) = :\t " << setw(9) << setprecision(4) << coord22.y << "t^2" << " + \t " << coord21.y << "t + \t" << coord20.y << '\n';
			*outputFile << "S'x(t) = :\t " << setw(9) << setprecision(4) << 2 * coord22.x << "t + \t" << coord21.x << '\n';
			*outputFile << "S'y(t) = :\t " << setw(9) << setprecision(4) << 2 * coord22.y << "t + \t" << coord21.y << '\n';


			*outputFile << "\nsegment\t  p_start\t    v(0)\t\t\t  p_end\t\tv(t_i)\n";
			*outputFile << 2 << ":     (" << point0.x << "," << point0.y << " ) \t   (" << coord21.x << "," << coord21.y << ")     ";
			*outputFile << "\t (" << point1.x << "," << point1.y << " )\t    (" << (((2 * coord22.x) * (tSub1 / 20)) + coord21.x) << "," << (((2 * coord22.y) * (tSub1 / 20)) + coord21.y) << ")\n\n";
		
		}

		return finalCoordinate;
	}



	//homework c s0
	static Coordinate calculatePosWithTimeAndVelocityAndTerminalVelocity(Coordinate point0, Coordinate point1, double time, ofstream* outputFile, bool isPrint){
		Coordinate finalPoint;
		
		double t0 = distanceFormula(point0, point1);


		double c02x = (point1.x - point0.x) / (t0 * t0);		
		double c02y = (point1.y - point0.y) / (t0 * t0);		
	
		finalPoint.x = (c02x * (time * time)) + point0.x;
		finalPoint.y = (c02y * (time * time)) + point0.y;

		if (isPrint) {
			*outputFile << "Sx(t) = :\t " << setw(9) << setprecision(4) << c02x << "t^2" << " + \t " << 0 << "t + \t" << point0.x << '\n';
			*outputFile << "Sy(t) = :\t " << setw(9) << setprecision(4) << c02y << "t^2" << " + \t " << 0 << "t + \t" << point0.y << '\n';
			*outputFile << "S'x(t) = :\t " << setw(9) << setprecision(4) << 2 * c02x << "t + \t" << 0 << '\n';
			*outputFile << "S'y(t) = :\t " << setw(9) << setprecision(4) << 2 * c02y << "t + \t" << 0 << '\n';

			*outputFile << "\nsegment\t  p_start\t    v(0)\t  p_end\t\tv(t_i)\n";
			*outputFile << 0 << ":     (" << point0.x << "," << point0.y << " ) \t   (" << 0 << "," << 0 << ")     ";
			*outputFile << "\t (" << point1.x << "," << point1.y << " )\t    (" << (((2 * c02x) * time)) << "," << ((2 * c02y) * (time)) << ")\n\n";

		}

		return finalPoint;		
	}

	//homework c s1
	//static Coordinate calculatePosWithTimeAndVelocityAndTerminalVelocity2(Coordinate point0, Coordinate point1, Coordinate point2, Coordinate point3, double time) {
	//	Coordinate finalPoint;

	//	double t0 = distanceFormula(point0, point1);
	//	double t1 = distanceFormula(point1, point2);
	//	double t2 = distanceFormula(point2, point3);

	//	double c13x = (-2 * (((point2.x - point1.x) / t1) -2 * ((point1.x - point2.x)/ (t0 * t0))));
	//	c13x = (c13x - (2 * ((point1.x - point0.x)/(t0 * t0))) + (2 * ((point3.x - point2.x) / t2)))/ (t1 * t1);
	//			
	//	double c12x = ( 3 * (((point2.x - point1.x)/(t1)) -2 * ((point1.x-point0.x)/(t0 * t0))));
	//	c12x = ( c12x + (2 * ((point1.x - point0.x)/ (t0 * t0))) -2 * ((point3.x - point2.x) / (t2))) / t1;
	//	
	//	double c11x = 2 * ((point1.x - point0.x) / ( t0 * t0));

	//	double c13y = (-2 * (((point2.y - point1.y) / t1) - 2 * ((point1.y - point2.y) / (t0 * t0))));
	//	c13y = (c13y - (2 * ((point1.y - point0.y) / (t0 * t0))) + (2 * ((point3.y - point2.y) / t2))) / (t1 * t1);

	//	double c12y = (3 * (((point2.y - point1.y) / (t1)) - 2 * ((point1.y - point0.y) / (t0 * t0))));
	//	c12y = (c12y + (2 * ((point1.y - point0.y) / (t0 * t0))) - 2 * ((point3.y - point2.y) / (t2))) / t1;

	//	double c11y = 2 * ((point1.y - point0.y) / (t0 * t0));

	//	finalPoint.x = ((c13x) * (time * time * time)) + ((c12x) * (time * time)) + (c11x * time) + point1.x;
	//	finalPoint.y = ((c13y) * (time * time * time)) + ((c12y) * (time * time)) + (c11y * time) + point1.y;


	//	return finalPoint;
	//}

	//homework c s1
	static Coordinate calculatePosWithTimeAndVelocityAndTerminalVelocity2(Coordinate point0, Coordinate point1, Coordinate point2, Coordinate point3, double time, ofstream* outputFile, bool isPrint) {
		double t0 = distanceFormula(point0, point1);
		double t1 = distanceFormula(point1, point2);
		double t2 = distanceFormula(point2, point3);
		Coordinate finalPoint;

		double c13x = (((2 * (point3.x - point2.x)) * (t0 * t1)) - ((2 * (point2.x - point1.x)) * (t0 * t2)) + (( 2 * (point1.x - point0.x)) * (t1 * t2))) / (t0 * (t1 * t1 * t1) * t2);
		double c12x = (((-2 * (point3.x - point2.x)) * (t0 * t1)) + ((3 * (point2.x - point1.x)) * (t0 * t2)) - ((4 * (point1.x - point0.x)) * (t1 * t2))) / (t0 * (t1 * t1) * t2);
		double c11x = (2 * (point1.x - point0.x)) / t0;

		double c13y = (((2 * (point3.y - point2.y)) * (t0 * t1)) - ((2 * (point2.y - point1.y)) * (t0 * t2)) + ((2 * (point1.y - point0.y)) * (t1 * t2))) / (t0 * (t1 * t1 * t1) * t2);
		double c12y = (((-2 * (point3.y - point2.y)) * (t0 * t1)) + ((3 * (point2.y - point1.y)) * (t0 * t2)) - ((4 * (point1.y - point0.y)) * (t1 * t2))) / (t0 * (t1 * t1) * t2);
		double c11y = (2 * (point1.y - point0.y)) / t0;

		finalPoint.x = ((c13x) * (time * time * time)) + ((c12x) * (time * time)) + (c11x * time) + point1.x;
		finalPoint.y = ((c13y) * (time * time * time)) + ((c12y) * (time * time)) + (c11y * time) + point1.y;

		if (isPrint) {
			*outputFile << "Sx(t) = :\t " << setw(9) << setprecision(4) << c13x << "t^3" << " + \t " << c12x << "t^2" << " + \t " << c11x << "t + \t" << point0.x << '\n';
			*outputFile << "Sy(t) = :\t " << setw(9) << setprecision(4) << c13y << "t^3" << " + \t " << c12y << "t^2" << " + \t " << c11y << "t + \t" << point0.y << '\n';
			*outputFile << "S'x(t) = :\t " << setw(9) << setprecision(4) << 3 * c13x << "t^2 + \t" << 2*c12x << "t + \t" << c11x << '\n';
			*outputFile << "S'y(t) = :\t " << setw(9) << setprecision(4) << 3 * c13y << "t^2 + \t" << 2*c12y << "t + \t" << c11y << '\n';


			*outputFile << "\nsegment\t  p_start\t    v(0)\t  p_end\t\tv(t_i)\n";
			*outputFile << 1 << ":     (" << point1.x << "," << point1.y << " ) \t   (" << (c11x) << "," << (c11y) << ")     ";
			*outputFile << "\t (" << point2.x << "," << point2.y << " )\t    (" << (((3 * c13x) * (time*time)) + ((2 * c12x) * time) + c11x) << "," << (((3 * c13y) * (time*time)) + ((2 * c12y) * time) + c11y) << ")\n\n";
		}

		return finalPoint;
	}

	//homework c s2
	static Coordinate calculatePosWithTimeAndVelocityAndTerminalVelocity3(Coordinate point2, Coordinate point3, double time, ofstream* outputFile, bool isPrint) {
		Coordinate finalPoint;

		
		double t2 = distanceFormula(point2, point3);

		double c22x = -((point3.x - point2.x) / (t2 * t2));
		double c21x = 2 * ((point3.x - point2.x) / t2);

		double c22y = -((point3.y - point2.y) / (t2 * t2));
		double c21y = 2 * ((point3.y - point2.y) / t2);

		finalPoint.x = ((c22x) * (time * time)) + ((c21x) * time) + point2.x;
		finalPoint.y = ((c22y) * (time * time)) + ((c21y)* time) + point2.y;		
		
		if (isPrint) {
			*outputFile << "Sx(t) = :\t " << setw(9) << setprecision(4) << c22x << "t^2" << " + \t " << c21x << "t + \t" << point2.x << '\n';
			*outputFile << "Sy(t) = :\t " << setw(9) << setprecision(4) << c22y << "t^2" << " + \t " << c21y << "t + \t" << point2.y << '\n';
			*outputFile << "S'x(t) = :\t " << setw(9) << setprecision(4) << 2 * c22x << "t + \t" << c21x << '\n';
			*outputFile << "S'y(t) = :\t " << setw(9) << setprecision(4) << 2 * c22y << "t + \t" << c21y << '\n';

			*outputFile << "\nsegment\t  p_start\t    v(0)\t  p_end\t\tv(t_i)\n";
			*outputFile << 2 << ":     (" << point2.x << "," << point2.y << " ) \t   (" << c21x << "," << c21x << ")     ";
			*outputFile << "\t (" << point3.x << "," << point3.y << " )\t    (" << ((((2 * c22x) * time)) + c21x) << "," << (((2 * c22y) * (time))) + c21y << ")\n\n";
		}

		return finalPoint;
	}


};




#endif
