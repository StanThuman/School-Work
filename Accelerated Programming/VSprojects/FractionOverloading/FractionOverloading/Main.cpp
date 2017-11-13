/**********************************
Stanley Lim

Accelerated Programming -
Assignment was to overload operators: +, -, *, / , <, >, ==
I have overloaded each operator and provided cout statements to show that
each overload implemented was successful

This should run
************************************/

#include<iostream>
#include <ostream>
#include <fstream>

class Fraction{
	public:		
		Fraction(int numerator, int denominator);		
		void setNumerator(int numerator);
		void setDenominator(int denominator);
		int getNumerator() const;
		int getDenominator() const;	
		void print();		
		void print(std::ostream& myOut) const;
		
	private:
		int numerator;
		int denominator;
}; //END class

//constructor
Fraction::Fraction(int numerator, int denominator){
	this->numerator = numerator;
	this->denominator = denominator;
}

//set and get methods
void Fraction::setNumerator(int numerator){
	this->numerator = numerator;
}
int Fraction::getNumerator() const{
	return this->numerator;
}
void Fraction::setDenominator(int denominator){
	this->denominator = denominator;
}
int Fraction::getDenominator() const{
	return this->denominator;
}

//print methods
void Fraction::print(){	
	std::cout << this->numerator << "/" << this->denominator << std::endl;
}

//used in the ostream overload <<
void Fraction::print(std::ostream& myOut) const{
	myOut << this->numerator << "/" << this->denominator;
}

//operator overloads - Methods(nonclass functions)
//Add operator + overload
Fraction operator + (const Fraction& f1,  const Fraction& f2){

	//stores the value of the fraction after the denominators are equal
	Fraction fractionSum1(1,1);
	Fraction fractionSum2(1, 1);

	//stores sum of fractions
	Fraction totalSum(1, 1);

	//find common denominator
	fractionSum1.setNumerator(f1.getNumerator() * f2.getDenominator());
	fractionSum1.setDenominator(f1.getDenominator() * f2.getDenominator());
	fractionSum2.setNumerator(f2.getNumerator() * f1.getDenominator());
	fractionSum2.setDenominator(f1.getDenominator());

	//Add fractions and store into fractionSum
	totalSum.setNumerator(fractionSum1.getNumerator() + fractionSum2.getNumerator());
	totalSum.setDenominator(fractionSum1.getDenominator());

	return totalSum;
}

//Subtraction operator - overload
Fraction operator - (const Fraction& f1, const Fraction& f2){

	//stores the value of the fraction after the denominators are equal
	Fraction fractionSum1(1, 1);
	Fraction fractionSum2(1, 1);
	Fraction totalDifference(1, 1);

	//find common denominator
	fractionSum1.setNumerator(f1.getNumerator() * f2.getDenominator());
	fractionSum1.setDenominator(f1.getDenominator() * f2.getDenominator());
	fractionSum2.setNumerator(f2.getNumerator() * f1.getDenominator());
	fractionSum2.setDenominator(f1.getDenominator());

	//Subtracts fractions and stores into fractionDifference
	totalDifference.setNumerator(fractionSum1.getNumerator() - fractionSum2.getNumerator());
	totalDifference.setDenominator(fractionSum1.getDenominator());

	return totalDifference;
}

//Multiplication operator * overload
Fraction operator * (const Fraction& f1, const Fraction& f2){	

	//stores the final fraction after they have been multiplied
	Fraction fractionProduct(1, 1);

	//Multiply and set values to fractionProduct
	fractionProduct.setNumerator(f1.getNumerator() * f2.getNumerator());
	fractionProduct.setDenominator(f1.getDenominator() * f2.getDenominator());

	return fractionProduct;
}

//Division operator overload
Fraction operator / (const Fraction& f1, const Fraction& f2){
	
	//holds the qutient of fractions
	Fraction fractionQuotient(1, 1);

	//use fraction reciprical and store into fractionQuotient
	fractionQuotient.setNumerator(f1.getNumerator() * f2.getDenominator());
	fractionQuotient.setDenominator(f1.getDenominator() * f2.getNumerator());

	return fractionQuotient;
}

//Overload the << operator to cout or fout fractions when needed
std::ostream& operator << (std::ostream& myOut, const Fraction& frac) {	
	frac.print(myOut);

	return myOut;
}

//Less than < overload
bool operator < (const Fraction& f1, const Fraction& f2){
	
	//stores the bool of the comparison of the double conversions
	bool conditional;

	//used to hold the converted value of fractions into a decimal
	double f1ToDouble;
	double f2ToDouble;
	//convert fractions to decimals
	f1ToDouble = static_cast<double>(f1.getNumerator())/static_cast<double>(f1.getDenominator());
	f2ToDouble = static_cast<double>(f2.getNumerator()) / static_cast<double>(f2.getDenominator());

	//decimal comparison to determin the boolean conditional
	if (f1ToDouble < f2ToDouble){
		conditional = true;
	}else{
		conditional = false;
	}

	return conditional;
}

//Greater than >> overload
bool operator > (const Fraction& f1, const Fraction& f2){

	//stores the bool of the comparison of the double conversions
	bool conditional;
	double f1ToDouble;
	double f2ToDouble;

	//conver fractions to decimals
	f1ToDouble = static_cast<double>(f1.getNumerator()) /static_cast<double>(f1.getDenominator());
	f2ToDouble = static_cast<double>(f2.getNumerator()) /static_cast<double>(f2.getDenominator());

	//decimal comparison to determine the boolean conditional
	if (f1ToDouble > f2ToDouble){
		conditional = true;
	}
	else{
		conditional = false;
	}

	return conditional;
}

//Equal to == overload
bool operator == (const Fraction& f1, const Fraction& f2){

	//store bool conditional when compared with if
	bool conditional;	
	
	//store the converted value of fractions
	double f1ToDouble;
	double f2ToDouble;

	//conver fractions to decimals
	f1ToDouble = static_cast<double>(f1.getNumerator()) / static_cast<double>(f1.getDenominator());
	f2ToDouble = static_cast<double>(f2.getNumerator()) / static_cast<double>(f2.getDenominator());

	//determines the value of conditional using the converted fractions
	if (f1ToDouble == f2ToDouble){
		conditional = true;
	}else{
		conditional = false;
	}

	return true;
}
int main(){

	//create two fractions
	Fraction f1(2, 7);
	Fraction f2(1, 5);		

	std::cout << "Welcome to the operator Overload Program\n" << std::endl;
	std::cout << "The following fractions will be used to test each operator overload:" << std::endl;
		
	//Performing all the operator overload tests
	std::cout << "Fraction one: " << f1 << std::endl;
	std::cout << "Fraction two: " << f2 << std::endl;
		
	std::cout << "\nAdding Fractions" << std::endl;
	std::cout << f1 + f2 << std::endl;
		
	std::cout << "Subtracting fractions" << std::endl;
	std::cout << f1-f2 << "\n" << std::endl;

	std::cout << "Multiplying fractions" << std::endl;
	std::cout << f1*f2 << "\n" << std::endl;

	std::cout << "Dividing fractions" << std::endl;
	std::cout << f1/f2 << "\n" << std::endl;
		
	std::cout << "Greater than (>) test" << std::endl;
	std::cout << (f1 > f2) << "\n" << std::endl;

	std::cout << "Less than (<) test" << std::endl;
	std::cout << (f1 < f2) << "\n" << std::endl;
	 
	std::cout << "Equl to (==) test" << std::endl;
	std::cout << (f1 == f2) << std::endl;
	

	
	return 0;
}