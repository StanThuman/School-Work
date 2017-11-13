/**********************************************
Stanley Lim
Accelerated Programming class


Assignment - reads the "input.txt" file into a
Student Struct array, outputs the data, then sorts them
in id order, then sorts in name order

It should work. As long as the input.txt file is in the
same directory

**********************************************/
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::ifstream;

struct Student{
	string name;
	int id;

};

void selectionSort(Student studArray[], int total, int idOrString);
void swap(Student studArray[], int x, int y);

int main(){

	//size for array, 8 comes from how many there are in the txt file "input.txt"
	const int ARRAY_MAX = 8;

	//create student array from struct Student
	Student student_Array[ARRAY_MAX];

	//open file in input stream
	ifstream fin("input.txt");

	//checks to see if the file was successfully opened
	if (!fin.is_open()){
		cout << "Failed to Open file.\n" << endl;
		exit(1);
	}

	//reads in and saves the values to name and id in my array
	for (int i = 0; i < ARRAY_MAX; i++){

		fin >> student_Array[i].name >> student_Array[i].id;
	}

	//close stream
	fin.close();

	//ouputs the order read in from txt file
	for (int i = 0; i < ARRAY_MAX; i++){

		cout << student_Array[i].name << "\t" << student_Array[i].id << endl;
	}

	//sorts the student array by id
	selectionSort(student_Array, ARRAY_MAX, 0);
	cout << endl;
	//outputs array in id order
	for (int i = 0; i < ARRAY_MAX; i++){

		cout << student_Array[i].name << "\t" << student_Array[i].id << endl;
	}

	//re sorts the array in name order
	selectionSort(student_Array, ARRAY_MAX, 1);
	cout << endl;
	//outputs the array in name order
	for (int i = 0; i < ARRAY_MAX; i++){

		cout << student_Array[i].name << "\t" << student_Array[i].id << endl;
	}

	return 0;
}//END MAIN


void selectionSort(Student studArray[], int total, int idOrString){

	//assign first value by default
	int idTemp;
	int j;

	//sorts array by id
	if (idOrString == 0){
		for (int i = 0; i < total; i++){
			j = i + 1;

			for (; j < total; j++){
				//swaps
				if (studArray[j].id < studArray[i].id){
					swap(studArray, i, j);
				}
			}
		}//end for		
	}

	//sorts array by name
	if (idOrString == 1){

		for (int i = 0; i < total; i++){
			j = i + 1;

			for (; j < total; j++){
				//swaps
				if (studArray[j].name < studArray[i].name){
					swap(studArray, i, j);
				}
			}
		}//end for	
	}
}

//used to swap values in to locations of an array
void swap(Student studArray[], int x, int y){
	Student temp = studArray[x];

	studArray[x] = studArray[y];
	studArray[y] = temp;
}