#ifndef ANIMAL_H
#define ANIMAL_H

#include<iostream>
using std::ostream;


class Fraction{

	friend
		ostream& operator << (ostream& out, Fraction& rhOp);

	public:
		Fraction(int n, int d);
		void changeNumerator(int n);
		void changeDenominator(int d);
		void print(ostream& out);
		

	private:
		int numerator;
		int denominator;



};


#endif