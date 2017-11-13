/*****************************************
Stanley Lim
Accelerated programming - raf file


Should run. I first make a txt file, then I read it in,
then i put it in a raf file


*****************************************/

#include <iostream>
#include <fstream>


using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::cin;


struct Student{

	int studentID;
	double gpa;

	Student(int id, double newGpa){

		studentID = id; 
		gpa = newGpa;
	}
	Student(){}
};



int main(){

	//size of my array
	const int CLASS_SIZE = 10;

	//create an array of ten students
	Student myStudents[CLASS_SIZE];
	Student myNewStudent[CLASS_SIZE];

	//open output stream
	//create my initial txt file
	ofstream fout("studentsInClass.txt");

	//make sure it's open
	if(!fout.is_open()){
		cout << "Error outputting to studentsInClass.txt\n";
	}

	//assign values to all the students in the array
	for(int i = 0; i < CLASS_SIZE; i++){		
	
		//creates different student IDs	
		//make all the gpa s the same since they don't matter for this
		myStudents[i].studentID = 11220 + i;
		myStudents[i].gpa = 3.5;

		//write to file
		fout << myStudents[i].studentID << "\t"
			 << myStudents[i].gpa << "\r\n";

	}

	//close output stream
	fout.close();

	//read in the txt file i just made
	ifstream fin("studentsInClass.txt");

	//check to make sure it's open
	if(!fin.is_open()){
		cout << "Error loading file.";
	}

	
	//assign the data from the studentsInClass.txt to a new array
	int num = 0;
	//read the file and assign values
	while(!fin.eof()){

		fin >> myNewStudent[num].studentID >> myNewStudent[num].gpa;		
		num++;
	}
	//close stream
	fin.close();


	//reuse the output stream object
	//output my studen array to raf file
	fout.open("student.raf");

	//check for errors
	if(!fout.is_open()){
		cout << "Couldn't open raf file";
	}

	//use this variable to store last two digits of student id
	int twoDigitID;
	
	//write in each student in array
	for(int i = 0; i < CLASS_SIZE; i++){

		twoDigitID = myNewStudent[i].studentID % 100;
		fout.write((char*) &twoDigitID, sizeof(Student));
	}

	//close the stream
	fout.close();







	return 0;
}