/**********************************************
Stanley Lim
Accelerated Programming Class
2/10/2015
Sorts IDs or GPA with bubble sort, insertion sort, and selection sort

Professor Hammerand: Pretty sure it works. At least it does when I run it but that coud change
when you run it.
No gurantees 80%sure
***********************************************/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

struct Student{
	long int id;
	double gpa;
};

//prototypes
int getStudentSize();
bool checkForRepeat(Student dbName[], int inputValue, int currentStudentMax);
void insertionSort(Student dbName[], int max, int IDorGPA);
void selectSort(Student dbName[], int max, int IDorGPA);
void bubbleSort(Student dbName[], int max, int IDorGPA);
void swap(Student dbName[], int swapX, int swapY);
void runSort(Student dbName[], int max);
void print(Student dbName[], int max);




int main(){	

	//introduction prompt
	cout << "Welcome to the Student ID and GPA input program!" << endl;
	cout << "After inputing all information, you can\nsort your data by insertion, selection, or bubble sort\n" << endl;

	
	int studentSize = getStudentSize();
	bool idCheck = true;
	bool gpaCheck = true;	

	Student  *studentDB = new Student[studentSize];

	//input id and gpa based off of studentSize
	for (int i = 0; i < studentSize; i++){

		//used to start at 1 instead of 0 from the i variable		
		int userInteger = 1;

		idCheck = true;
		gpaCheck = true;

		//make sure there's no duplicate data and the id is a 5 digits
		while (idCheck){
			bool fiveDigitCheck = true;
			while (fiveDigitCheck){
				cout << "Please input a 5 digit student #" << userInteger << "\'s id: ";
				//stores id input
				cin >> studentDB[i].id;
				if (studentDB[i].id < 0 || studentDB[i].id > 99999){
					cout << "not a 5 digit value" << endl;
					fiveDigitCheck = true;
				} else{
					fiveDigitCheck = false;
				}
			}//end fiveDigitCheck while

			//check for duplicate IDs
			if (i >= 1){				
				idCheck = checkForRepeat(studentDB, studentDB[i].id, i);
			}
			else{
				idCheck = false;
			}
		}//end idCheck while

		//checks gpa to be between 1.0 and 4.0
		while (gpaCheck){
			cout << "Please input student #" << userInteger << "\'s gpa: ";
			cin >> studentDB[i].gpa;
			cout << endl;
			
			if (studentDB[i].gpa < 1.0 || studentDB[i].gpa > 4.0){
				cout << "\nNot a valid gpa number." << endl;
				cout << "\nPlease input a value betwwen 1.0 - 4.0" << endl;
				gpaCheck = true;
			}else
				gpaCheck = false;
		}

		userInteger++;
	}//end for

	//chooses the sort to run and calls the chosen sort
	runSort(studentDB, studentSize);

	return 0;

}//END MAIN





//gets the arraySize for total students
int getStudentSize(){
	int studSize;
	bool isTrue = true;	
	
	//loops until a correct value is assigned to studentSize
	while (isTrue == true){
		//20 is the limit or input at one time
		cout << "How many students would you like to input?(1 - 20) ";
		cin >> studSize;		
		if (studSize > 0 && studSize <= 20){
			isTrue = false;			
		}
		else{
			cout << "\nThat\'s way to many. Try again" << endl;
			isTrue = true;
		}//end if
	}//end while
	return studSize;
}//end getStudentSize function

//checks to see if an id has been previously entered
bool checkForRepeat(Student dbName[], int inputValue, int currentStudentMax){

	bool isRepeat = true;
	
	//checks the previous id inputs to determine if loop needs repeating
	for (int j = 0; j < currentStudentMax; j++){
		
		if (dbName[j].id == inputValue){
			cout << "You have already entered a Student with an id of " << inputValue << endl;
			isRepeat = true;			
		}
		else{
			isRepeat = false;
		}
	}//end for

	return isRepeat;
}//end checkForRepeat Function

//handles what and how to sort
void runSort(Student dbName[], int max){
	int sortChoose;
	bool sortValueCheck = true;
	bool idOrGpaCheck = true;
	int idOrGpa;
	

	cout << "Great! Would you like to swort by ID or gpa?" << endl;

	//sorts by id or gpa
	while (idOrGpaCheck){
		cout << "1 - sort by ID\n2 - sort by gpa" << endl;
		cout << "Choose: ";

		cin >> idOrGpa;

		//makes sure the input is a 1 or 2
		if (idOrGpa < 1 || idOrGpa > 2){
			cout << "Not valid. Try again" << endl;
			idOrGpaCheck = true;
		}else{
			idOrGpaCheck = false;
		}
	}

	cout << "Now how would you like them sorted ? " << endl;

	//sort is chosen and checked to be a valid value
	while (sortValueCheck){
		cout << "1 - Insertion Sort\n2 - Selection Sort\n3 - Bubble Sort" << endl;
		cout << "Choose: ";
		cin >> sortChoose;
		cout << endl;
		if (sortChoose < 1 || sortChoose > 3){
			cout << "Not a correct value" << endl;
			cout << "Please choose a sort." << endl;
			sortValueCheck = true;
		}else{
				sortValueCheck = false;
		}
	}

	//goes to the sort chosen
	if (sortChoose == 1){
		insertionSort(dbName, max, idOrGpa);
		print(dbName, max);
	}

	if (sortChoose == 2){
		selectSort(dbName, max, idOrGpa);
		print(dbName, max);
	}

	if (sortChoose == 3){
		bubbleSort(dbName, max, idOrGpa);
		print(dbName, max);
	}



}//end runSort()


void insertionSort(Student dbName[], int max, int IDorGPA){
	int j;

	//sort loop for id
	if (IDorGPA == 1){
		for (int i = 0; i < max; i++){
			j = i;
			j--;
			//continuously checks the "sorted portion" with the unsorted
			//and swaps accordingly
			while (j >= 0){
				if (dbName[i].id < dbName[j].id){
					swap(dbName, i, j);
					j--;
				}
				else{
					j--;
				}
			}//end while
		}//end for
	}// end if
	
	//sort loop for gpa
	if (IDorGPA == 2){
		for (int i = 0; i < max; i++){
			j = i;
			j--;
			//continuously checks the "sorted portion" with the unsorted
			//and swaps accordingly
			while (j >= 0){
				if (dbName[i].gpa < dbName[j].gpa){
					swap(dbName, i, j);
					j--;
				}else{
					j--;
				}
			}//end while
		}//end for
	}//end if
}//end insertionsort

void selectSort(Student dbName[], int max, int IDorGPA){
	int j = 0;
	int placeHolder;
	//sort loop for id
	if (IDorGPA == 1){	
		for (int i = 0; i < max; i++){			
			placeHolder = 0;
			j = i + 1;			
			//sorts throught he rest of the Student array
			//and compares it with the first and swaps if <
			for (; j < max; j++){				
				if (dbName[j].id < dbName[i].id){
					placeHolder = i;
				}
			}
			if (dbName[i].id < dbName[placeHolder].id){				
				swap(dbName, placeHolder, i);
			}
		}
	}//end iff


	//sort loop for gpa
	if (IDorGPA == 2){
		for (int i = 0; i < max; i++){
			placeHolder = 0;
			j = i + 1;
			//sorts throught he rest of the Student array
			//and compares it with the first and swaps if <
			for (; j < max; j++){

				if (dbName[j].gpa < dbName[i].gpa){
					placeHolder = j;
				}
			}//end for

			if (dbName[i].gpa < dbName[placeHolder].gpa){
				swap(dbName, placeHolder, i);
			}
		}//end for
	}//end if
}//end selectsort function


void bubbleSort(Student dbName[], int max, int IDorGPA){
	int dbCounter;
	if (IDorGPA == 1){
		dbCounter = 1;
		for (int i = 0; i < max; i++){	

			//swaps the next adjacent array index if less than
			for (int j = 0; j < max; j++){				
				if (dbName[j].id > dbName[dbCounter].id){					
					if (dbCounter < max){						
						swap(dbName, dbCounter, j);
					}
				}
				dbCounter++;			
			}
		}//end forloop
	}//end if

	if (IDorGPA == 2){
		dbCounter = 1;
		for (int i = 0; i < max; i++){
			//swaps the next adjacent array index if less than
			for (int j = 0; j < max; j++){
				if (dbName[j].gpa > dbName[dbCounter].gpa){
					if (dbCounter < max){
						swap(dbName, dbCounter, j);
					}
				}
				dbCounter++;
			}
		}//end forloop
	}//end if
}//End bubblesort


//switches the values for swapX and swapY from Student struct
void swap(Student dbName[], int swapX, int swapY){	
	Student tempStudent = dbName[swapY];
	
	dbName[swapY] = dbName[swapX];
	dbName[swapX] = tempStudent;
}

//outputs the finished sort
void print(Student dbName[], int max){
	cout << "PRINT" << endl;
	for (int i = 0; i < max; i++){

		cout << "ID: " << dbName[i].id << endl;
		cout << "gpa: " << dbName[i].gpa << endl;
		cout << endl;
	}
}




