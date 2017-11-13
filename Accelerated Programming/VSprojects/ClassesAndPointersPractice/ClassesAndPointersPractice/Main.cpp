#include "Fraction.h";
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include<fstream>

ostream& operator << (ostream& out, Fraction& rhOp){

	rhOp.print(out);
	return out;
}

int main(){	

	//Fraction f1(3,5);
	//std::ofstream fout;
	//fout.open("myFile.txt");

	//if (!fout.is_open()){
	//	cout << "Failed";
	//}

	//fout << f1;
	//fout.close();

	int* p;

	int num = 5;

	p = &num;

	*p = 10;

	cout << num << endl;
	cout << *p << endl;



	

	return 0;
}
