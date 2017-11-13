#include "Fraction.h";
#include<iostream>
using std::ostream;
using std::cout;

Fraction::Fraction(int n, int d){
	this->numerator = n;
	this->denominator = d;
}

void Fraction::changeNumerator(int n){

	this->numerator = n;
}

void Fraction::changeDenominator(int d){
	this->denominator = d;
}

void Fraction::print(ostream& out){
	out << numerator << "/" << denominator << std::endl;

}