/************************************************
Stanley Lim
2/15/2015

Homework on the char conversion to int

I'm pretty sure it works. I'm not even sure if I 
did it the way you wanted me to. But this does output
the value that is put in at the beginning

*************************************************/


#include <iostream>

using std::cout;
using std::cin;
using std::endl;



int main(){
	int arraySize;
	int totalSum;
	int charToNum;
	
	
	bool restartLoop = true;

	//cont a char into interger by substractice the value of 0, 48, in char type
	char one = '1';
	int num1 = one - 48;


	cout << "Welcome to the Stanely lim\'s number sequence binary converter 2000" << endl;

	//while controls the loop to restart if wanted
	while (restartLoop){
		bool digitLoop = true;
		
		//controls how many digits the user enters
		//I put a threshhold on the amount of digits just becuase
		while (digitLoop){
			cout << "How many digits is your integer?(1 - 10) ";
			cin >> arraySize;

			if (arraySize > 10){
				cout << "That number is to big. Please use someting smaller." << endl;
			}
			else{
				digitLoop = false;
			}
		}

		//char array holds the inputs, then I transfer inputes to int array
		char *myArray = new char[arraySize];
		int *myNumArray = new int[arraySize];

		cout << "Please input your " << arraySize << " digit number: ";

		//read inputs for char array
		for (int i = 0; i < arraySize; i++){

			cin >> myArray[i];
		}

		//sets the value for int array, according to the values in char array
		for (int i = 0; i < arraySize; i++){

			myNumArray[i] = myArray[i];

			//subtract 48(the value of 0) to get the int value from char
			myNumArray[i] = myNumArray[i] - 48;
		}		

		//calculates the integer value of the char
		for (int i = 0; i < arraySize; i++){
			if (i == 0){

				totalSum = (myNumArray[i] * 10) + myNumArray[i + 1];				
			}
			if (i > 1){

				totalSum = totalSum * 10 + myNumArray[i];				
			}

		}

		//couts the answer and answer + 1		
		cout << "\nThe number is: " << totalSum << endl;
		cout << "The number plus 1 is: " << totalSum + num1 << endl;

		//restarts Loop
		char restartChoice;
		cout << "\nWould you like to run this agai? (Y/N)? ";
		cin >> restartChoice;

		if (restartChoice == 'Y' || restartChoice == 'y')
			restartLoop = true;
		
		if (restartChoice == 'N' || restartChoice == 'N')
			restartLoop = false;

	}

	return 0;
}