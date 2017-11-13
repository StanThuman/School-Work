/**Stanley Lim


When I run this "correctly", I don't have any problems


Output homework - enter student numbers and names and sorts by id number

*/

#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::string;
using std::cin;
using std::endl;



struct Student{
	
	int id;
	string name;
	

};


void selectionSort(Student studArray[], int total, int idOrString);
void swap(Student studArray[], int x, int y);

int main(){

	int totalStudents;
	
	//intro prompt
	cout << "Hello! This program will take in your student\'s names and Id\'s and \noutput them in a text file." << endl;

	cout << "\nHow many Students would you like to enter information for?";

	cin >> totalStudents;

	//array to hold in all students entered
	Student* studentArray = new Student[totalStudents];


	//loop to enter the total Students
	for (int i = 0; i < totalStudents; i++){

		cout << "Please input a 2 digit ID for student #" << i + 1 << ": ";
		cin >> studentArray[i].id;


		cout << "Please input first name for student #" << i + 1 << ": ";
		cin >> studentArray[i].name;
		cout << "\n";

	}//end for

	


	//sort ids
	selectionSort(studentArray, totalStudents, 0);	

	//open outputStream
	std::ofstream fout("studentList.txt");

	//write to output
	for (int i = 0; i < totalStudents; i++){

		fout << studentArray[i].name << " " << studentArray[i].id << endl;
	}


	//re sorts in alphabetical order
	selectionSort(studentArray, totalStudents, 1);
	//write to output
	fout << "\n\n";
	for (int i = 0; i < totalStudents; i++){

		fout << studentArray[i].name << " " << studentArray[i].id << endl;
	}

	fout.close();


	


	return 0;
}



void selectionSort(Student studArray[], int total, int idOrString){

	//assign first value by default
	int idTemp;
	int j;

	//sorts array
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


void swap(Student studArray[], int x, int y){
	Student temp = studArray[x];

	studArray[x] = studArray[y];
	studArray[y] = temp;
}