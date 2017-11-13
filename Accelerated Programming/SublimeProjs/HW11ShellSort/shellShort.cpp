/*******************************
Shell sort assignment

I didn't use 3n+1 to iterate through with shell sort
since i wasn't making huge arrays, instead, I just divided by two

It should sort the array multiple times. I didn't have any problems.
should work

Stanley Lim
********************************/


#include <iostream>
#include <iterator>

using std::cout;
using std::cin;
using std::endl;

//prototypes
void shellSort(int* unsortedArray, int arraySize);

//calculates the number used to iterate through array(for the shell sort)
int calculatePattern(int pattern);
void swap(int& posOne, int& posTwo);
void printArray(int* intArray, const int& arraySize);

int main(){
	//holds max arraySize
	int arrayMax;	
	int* shellArray;

	cout << "Welcome to the shell sorter Ver. 50.007" << endl;
	
	bool inputCheck = true;
	//checks to make sure input is <= 50
	while (inputCheck){
		cout << "How many numbers would you like to use(1-50)? ";
		cin >> arrayMax;

		if (arrayMax > 0 && arrayMax <= 50){
			inputCheck = false;
		} else{
			cout << "\nInvalid value. Please input a value between 1 - 50\n" << endl;
		}
	}
	

	//initialize dynamic array with user value for arraySize
	shellArray = new int[arrayMax];
	
	cout << "Please input " << arrayMax << " numbers" << endl;

	//user input for array values
	for (int i = 0; i < arrayMax; i++){
		cout << "Please enter number for position " << i + 1 << ": ";
		cin >> shellArray[i];
	}	
	
	//need to do it twice before sorting the first time
	shellSort(shellArray, arrayMax);
	delete[] shellArray;
	
	return 0;
}

void shellSort(int* unsortedArray, int arraySize){		

	//used to hold the value to sort by
	int sortPattern = arraySize;	

	//controls the loop to continue sorting
	bool loopControl = true;

	//used to exit loop when no values are swapped
	bool noValueChanged = true;
	

	//output array before modifying
	cout << "\nOriginal array before changes  : ";
	for (int i = 0; i < arraySize; i++){
		cout << unsortedArray[i] << " ";
	}
	cout << "\n" << endl;

	//causes the pattern to run twice if there are a lot of values in the array	
	if (arraySize >= 40){
		sortPattern = calculatePattern(sortPattern);
	}

	//sorts the array via shell sort
	while (loopControl){
		int arrayIncrementer = 0;
		
		//if no value is changed,
		//this will remain true and exit sorting
		noValueChanged = true;
		
		//recalculate pattern		
		if (sortPattern > 1){
			sortPattern = calculatePattern(sortPattern);			
		} else
			//used to make sure sortPattern is at least one, so it can do
			//normal bubble sorts at the end	
			sortPattern = 1;	
		
		//for loop to interate through array once, sorting the locations	
		cout << "Using array location iterator " << sortPattern << ": ";
		for (int i = sortPattern; i < arraySize; i += sortPattern){

			if (unsortedArray[arrayIncrementer] > unsortedArray[i]){				
				noValueChanged = false;
				//swap if 'i' value is les than 'sortPattern' location
				swap(unsortedArray[arrayIncrementer], unsortedArray[i]);				
			}			

			//applies pattern to first incrementer
			arrayIncrementer += sortPattern;

		}//end for

		//prints each pass of the array
		printArray(unsortedArray, arraySize);		

		//exits while loop when no value is changed
		//and makes sure the loop doesn't exit early
		//in case of high number iteration with no swapping
		if (noValueChanged == true && sortPattern == 1){			
			loopControl = false;
		}
	}//end while loop
}

//function implementation
//returns the value to iterate array with
int calculatePattern(int pattern){		
	//this formula is used for the reverse of 3n + 1(optimal)
	//pattern = (pattern - 1) / 3;		

	//Im not making arrays big enough to utilize this efficient value
	//so Im just goint to divied by 3
	pattern = pattern / 2;
	return pattern;
}

//swaps values in array positions
void swap(int& posOne, int& posTwo){
	int temp = posOne;
	posOne = posTwo;
	posTwo = temp;
}

//prints array
void printArray(int* intArray, const int& arraySize){
	for (int i = 0; i < arraySize; i++){
		cout << intArray[i] << " ";
	}
	cout << endl;
}