#include <iostream>
#include "Node.h"
#include "LinkedList.h"



int main(){	
	
	LinkedList myList;

	std::cout << "Welcome to the Linked list Creator/Editor." << std::endl;
	std::cout << "Please use an integer values 0 - 3 to choose an option" << std::endl;

	//runs program
	myList.linkedListQuery();

	return 0;
}