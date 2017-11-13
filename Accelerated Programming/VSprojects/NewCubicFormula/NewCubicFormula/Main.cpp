#include <iostream>
#include <stdlib.h>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;

/*************************************
Stanley Lim 1/28/2015
Accelerated programming second assignment
Cubic Formula

This program takes in 4 values for the cubic formula and calculates the aswer.
It will run but may or may not do everything correctly, though I think it does

I received the formula from http://www.1728.org/cubic2.htm
*************************************/

bool repeatProgram(){

	bool invalidAnswerLoop = true;
	while (invalidAnswerLoop){

		char restartChar;

		cout << "Would you like to do another one? (Y/N)" << endl;
		cin >> restartChar;

		if (restartChar == 'Y' || restartChar == 'y'){
			invalidAnswerLoop = false;			
			return true;

		}
		else if (restartChar == 'N' || restartChar == 'n'){
			invalidAnswerLoop = false;

			cout << "Goodbye!!" << endl;
			return false;

		}
		else{
			cout << "\"" << restartChar << "\"" << " is not a valid answer.\n" << endl;
			invalidAnswerLoop = true;
		}
	}
}// end repeatProgram function

void calculateCubicFormula(double a, double b, double c, double d){

	double f = (((3 * c) / a) - ((b*b) / (a*a)))/3;	
	double g = (((2 * (b*b*b) / (a*a*a)) - ((9 * b*c) / (a*a)) + ((27 * d) / a)))/27;
	double h = ((g*g) / 4) + ((f*f*f) / 27);	
	double i = sqrt(((g*g) / 4) - h);

	double oneThirdPower = 1.0 / 3.0;

	double x1, x2, x3;

	//only 1 root
	if (h > 0){
		
		
		double r = (-(g / 2.0)) + (sqrt(h));
		double s = pow(r, oneThirdPower);
		double t = (-(g / 2.0)) - (sqrt(h));

		//had to run loop, cant take cubed root of a negative in program code
		double u;
		if (t < 0){
			u= pow(-t, oneThirdPower) * (-1);
		}
		else{
			u = pow(t, oneThirdPower);
		}	

		x1 = ((s + u) - (b / (3.0 * a)));		
		cout << "One 1 root is real\nX: " << x1 << endl;		
	}//end if for 1 root

	//if all 3 roots are real
	if (h <= 0){

		//if all roots are equal
		if (f == 0 && g == 0 && h == 0){

			x1 = pow((d / a), oneThirdPower) * (-1);

			x1 = x1 + x1;
			cout << "All roots are equal" << endl;

			cout << "x = " << x1 << endl;


		}//end if for all equal roots

		double j = pow(i, (1.0 / 3.0));	
		double k = acos(-(g / (2 * i)));		
		double l = j * (-1.0);
		double m = cos(k / 3.0);
		double n = sqrt(3.0) * sin(k / 3.0);
		double p = (b / (3*a)) * (-1.0);		

		

		x1 = ((2 * j) * (cos(k / 3.0))) - (b / (3 * a));
		x2 = (l * (m + n)) + p;
		x3 = (l * (m - n)) + p;

		cout << "x1 = " << x1 << endl;
		cout << "x2 = " << x2 << endl;
		cout << "x3 = " << x3 << endl;
	}//end if for 3 roots

	
}//end function



int main(){


	double a, b, c, d;
	
	

	bool repeatLoop = true;
	
	cout << "This program is for the Cubic formula." << endl;

	while (repeatLoop){
		//loop is repeated if the input is not an integer
		//the loop is done for each integer

		cout << "Please input number values for a, b, c, and d as prompted." << endl;
		
			cout << "Please insert a: ";
			cin >> a;		

			cout << "Please insert b: ";
			cin >> b;
			
			cout << "Please insert c: ";
			cin >> c;
		
			cout << "Please insert d: ";
			cin >> d;
	
		calculateCubicFormula(a, b, c, d);

		//prompt user to restart loop or not
		repeatLoop = repeatProgram();

	}

	

	return 0;
} //end main

