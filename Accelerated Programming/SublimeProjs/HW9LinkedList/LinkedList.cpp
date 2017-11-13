#include <iostream>
#include "Node.h"
#include "LinkedList.h"

LinkedList::LinkedList(){
	head = 0;
}
//Prompt for Linked list options
//Runs after every finished action
void LinkedList::linkedListQuery(){
	int myChoice;
	bool runLoop = true;

	while(runLoop){
		std::cout << "0 - Add" << 
				"\n1 - search" << 
				"\n2 - Remove" <<
				"\n3 - Print Linked List values" << std::endl;
		std::cout << "User Input: ";
		std::cin >> myChoice;

		//case switch used to add, rmove, search, and print linked list
		switch(myChoice){

			case 0:
				std::cout << "\nWhat integer value would you like to add? \nAdd Value: ";
				std::cin >> myChoice;
				add(myChoice);
				std::cout << "\n";
				break;

			case 1:
				std::cout << "\nWhat integer value would you like search for? \nSearch Value: ";
				std::cin >> myChoice;
				search(myChoice);
				std::cout << "\n";
				break;

			case 2:
				if(head != 0){
					std::cout << "\nWhat integer value would you like to remove? \nSearch Value: ";
					std::cin >> myChoice;
					remove(myChoice);
					std::cout << "\n";
				} else{
					std::cout << "\nNothing to delete\n" << std::endl;
				}
				break;

			case 3:
				print();
				break;				

			default:
				std::cout << "And unexpected error has occurred" << std::endl;
		}
	}
}

//adds new Node to linked list
bool LinkedList::add(int newValue){
	//return success to see if the add was successful
	bool success = true;

	//stores new value needed to be added
	Node* newAdd = new Node(newValue);
	
	//returns 0 if error creating dynamic memory allocation
	if(newAdd !=0){
		Node* current = head;
		Node* previous = 0;

		//runs if head has a value
		//increments through linked list
		while(current !=0 && newAdd->getValue() > current->getValue()){
			previous = current;
			current = current->getNext();
		}

		newAdd->setNext(current);

		if(previous != 0){
			previous->setNext(newAdd);
		} else{
			//runs if no nodes are in list
			//first new Node set to head
			head = newAdd;
		}
	} else{
		//error with newAdd condition
		success = false;		
	}

	return success;
}

void LinkedList::search(int searchValue){
	Node* current = head;
	bool hasValue = false;
	bool foundValue = true;
	//checks to see if head has values
	while(current != 0 && foundValue){

		//prints true when found, then exits loop
		if(searchValue == current->getValue()){
			std::cout << "\nTRUE, the linked list has " << searchValue << std::endl;
			hasValue = true;
			foundValue = false;
		}

		//increments the list
		current = current->getNext();
	}
	//prints if not found
	if(hasValue == false){
		std::cout << "FALSE, " << searchValue << " is not in your linked list." << std::endl;
	}	

}
void LinkedList::remove(int removeValue){
	//passes true if succeeded
	bool success = true;

	//create points to iterates and manipulate
	Node* current = head;
	Node* previous = 0;

	//checks for more than on node, else delete head
	if(current->getNext() != 0){
		//iterates through list
		while(removeValue != current->getValue()){
			previous = current;
			current = current->getNext();
		}

		//should be equal
		//deletes inner nodes - not head or tail
		if(current->getNext() != 0 && previous != 0){
			std::cout << previous->getValue() << " " << current->getValue() << std::endl;
			previous->setNext(current->getNext());
			delete current;			
		}

		//delete at tail
		if(current->getNext() == 0){
			
			previous->setNext(0);
			delete current;
		}
		//delete value at head with a list longer than 1 node
		if(previous == 0){
				head = current->getNext();
				delete current;
		}		
	} else{
		//if there's only one node - head
		if(current->getNext() == 0){
			std::cout << "delete 1" << std::endl;
			delete current;
			head = 0;
		}
	}//end main if n else

}//end remove fu nction

//loops through list to print all values contained
void LinkedList::print(){

	Node* current = head;
	std::cout << "\n";
	std::cout << "Linked list current values: ";
	if(current == 0){
		std::cout << "none";
	}

	while(current != 0){
		std::cout << current->getValue() << " ";
		current = current->getNext();
	}
	
	std::cout << "\n\n";
}