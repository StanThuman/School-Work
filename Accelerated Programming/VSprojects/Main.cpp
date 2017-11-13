#include <iostream>
#include <cmath>
#include <stdlib.h>


using std::cout;
using std::cin;
using std::endl;


/*************************************************
**************************************************
Stanley Lim 1/14/2015
Accelerated Programming class
This program takes in 3 inputs and calculates the two x intercepts

Professor,
I could not remember the run command code after compiling with g++ in mobaXterm
This will run in Visual Studio, but im not 100% sure about mobaXterm

************************************************
************************************************/

int main(){

	bool runLoop = true;
	char restart;
	

	cout << "Quadratic equation calculator" << endl;
	cout << "Please insert a, b, and c as prompted." << endl;
	cout << "Do not use 0 for the value of a" << endl;

	//runs until end or user decides to stop
	while (runLoop){

		double a, b, c;	//variables for parabola inputs

		cout << "Please insert a: ";
		cin >> a;

		cout << "Please insert b: ";
		cin >> b;

		cout << "Please insert c: ";
		cin >> c;

		if (abs(a) > 0.001){
			//quadratic formula
			int parabola = sqrt((b*b) - (4 * a*c));

			

			if (parabola == 0){
				float x = -b / 2 / a;
				cout << "Only touches the x coordinate one time at: " << x;

			}
			if (parabola > 0){
				double x1 = (-b - parabola) / (2 * a);
				double x2 = (-b + parabola) / (2 * a);

				//outputs x1 and x2
				cout << "\nX coordinate one: " << x1 << endl;
				cout << "X coordinate two: " << x2 << endl;
			}
			else{
				cout << "x never touches the x axis" << endl;
			}
		}

		//conditional to restart program
		bool restartProgram = true;
		while (restartProgram){
			cout << "Would you like to restart?(Y/N)" << endl;
			cin >> restart;

			if (restart == 'y' || restart == 'Y'){
				runLoop = true;
				restartProgram = false;
			}
			else{
				if (restart == 'n' || restart == 'N'){
					runLoop = false;
					restartProgram = false;
					cout << "\nGoodbye!!!!" << endl;
				}
				else{
					cout << "Not a valid entry, try again." << endl;
					restartProgram = true;
				}
			}
			
		}
		
	}//end program loop

	return 0;
}