#include <iostream>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;

/*************************************
Stanley Lim 1/23/2015
Accelerated programming second assignment
Cubic Formula

This program takes in 4 values for the cubic formula and calculates the aswer

I received the formula from www.math.vanderbilt.edu~schectex/courses/cubic/
*************************************/

//cout some text at the start of the program and when it repeats
	void print(int coutDecider){
		if (coutDecider == 1){
			cout << "This program is for the Cubic formula." << endl;
			cout << "If 0 is the chosen value for a, or, your equation does not equal zero" << endl 
				<< " then your values do not make a third degree polynomial.\n" << endl;

			coutDecider++;
		}

		if (coutDecider == 2){
					
			//cout << "The formula is: ax³ + bx² + cx + d = 0" << endl;
			
			cout << "Please input values for a, b, c, and d." << endl;	
		}
	}

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
				return false;

			}
			else{
				cout << "\"" <<  restartChar << "\"" << " is not a valid answer. " << endl;				
				invalidAnswerLoop = true;
			}
		}

	}
	void calculateCubicFormula(double a, double b, double c, double d){
		
		//part one is the first repeated expression
		double partOne = pow(-b, 3) / (27 * pow(a, 3));
		partOne = partOne + ((b*c) / (6 * (a*a)));
		partOne = partOne - (d / (2 * a));

		//second repeated expression
		double partTwo = partOne*partOne;
		

		//third repeated expression
		double partThree = (c / (3 * a));
		partThree = partThree - ((b*b) / (9 * (a*a)));
		partThree = pow(partThree, 3);

		

		double partTwoAndThree = partTwo + partThree;
		

		if (partTwoAndThree > 0){

			double partOneTotal = partOne + sqrt(partTwoAndThree);			
			partOneTotal = pow(partOneTotal, (1.0 / 3.0));					

			double partTwoTotal = partOne - sqrt(partTwoAndThree);			
			partTwoTotal = pow(partTwoTotal, (1.0 / 3.0));

			double x = (partOneTotal + partTwoTotal) - (b / (3 * a));

			//use x in the equation
			double totalSum = (((a * (x*x*x)) + (b * (x*x)) + (c*x)) + d);
			cout << "\n" << x << endl;
			if (totalSum == 0){
				cout << "The value of x is: " << x << endl;
			}
			else{
				cout << "The equation did not equal zero.\n It must equal zero 4th" << endl;
			}	

		}//end first if
	}//end function

int main(){
	
	double a, b, c, d;
	char restartChar;
	print(1);

	bool repeatLoop = true;

	while (repeatLoop){
		bool aLoop = true;
		
		//while loop for a if it is not positive or negative
		while (aLoop){

			cout << "Please insert a: ";
			cin >> a;
			if (abs(a) > 0.001){
				aLoop = false;
			}
			else{
				cout << "Invalid answer. Please insert a nonzero value for a." << endl;
				aLoop = true;
			}
		}		

		cout << "Please insert b: ";
		cin >> b;

		cout << "Please insert c: ";
		cin >> c;

		cout << "Please insert d: ";
		cin >> d;
				
		calculateCubicFormula(a, b, c, d);		
		
		//prompt user to restart loop or not
		repeatLoop = repeatProgram();

	}//end while loop

	return 0;
} //end main

