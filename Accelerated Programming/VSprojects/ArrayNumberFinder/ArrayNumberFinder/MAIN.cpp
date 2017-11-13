#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/***********************************************
Stanley Lim
1 day homework
finds largest number, second largest number,
and smallest number
This program does not work 100%
************************************************/


bool restartProgram();

int main(){

	
	bool repeatProgram = true;

	string stringArray[5] = { "First", "Second","Third","Fourth","Fifth" };

	cout << "Please enter a set of Five numbers: " << endl;
	
	while (repeatProgram){
		int numArray[5];
		int largeNumber = 0;
		int smallNumber = 0;
		int secondLargestNum = 0;

		//intro input loop
		for (int i = 0; i < 5; i++){

			cout << "Enter " << stringArray[i] << " number: ";
			cin >> numArray[i];
		}//end for loop


		//largest number loop
		for (int i = 0; i < 5; i++){
			
			if (numArray[i] > largeNumber){
				largeNumber = numArray[i];
			}
			smallNumber = largeNumber;
		}//end for loop

		
		//smallest number loop
		for (int i = 0; i < 5; i++){
			int tempNumber = 0;
			for (int j = 0; j < 5; j++){
				if (numArray[i] < numArray[j]){
					tempNumber = numArray[i];
					if (smallNumber > numArray[i]){
						smallNumber = numArray[i];
					}
				}
			}
		}//end for loop

		//second largest number loop
		for (int i = 0; i < 5; i++){
			
			if (numArray[i] < largeNumber){
				int tempNumber = numArray[i];
				if (tempNumber > secondLargestNum){
					secondLargestNum = tempNumber;
				}
			}			
		}//end for loop
		
		
		cout << "Largest number is: " << largeNumber << endl;
		cout << "Second largest number is: " << secondLargestNum << endl;
		cout << "Smallest number is: " << smallNumber << endl;

		repeatProgram = restartProgram();

	}


		cout << "Thank you!" << endl;



	return 0;
}//end main

bool restartProgram(){
	bool functionLoop = true;
	char answer;
	while (functionLoop){
		cout << "Would you like to restart program?" << endl;
		cin >> answer;

		if (answer == 'Y' || answer == 'y'){
			functionLoop = false;
			return true;
		}
		if (answer == 'N' || answer == 'n'){
			functionLoop = false;
			return false;
		}
		else{
			cout << "Not a valid answer." << endl;
			functionLoop = true;


		}

	}
	

}



