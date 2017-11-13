/******************************************
Stanley Lim - Accelerated Programming class


Assingment - implement a search and remove function
to linked list add, remove and search through the sorted linked list


Note - Should work and compile with mobaXterm
I'm not sure if I implemented the switch the way that you wanted
will ask about it in class so I can change it if needed


******************************************/
#include <iostream>
//Used in Linked list class
class Node{

	public:
		Node(int value);
		int getValue();
		Node* getNext();
		void setNext(Node* newNext);


	private:
		int value;
		Node* next;
}; //end node header
class LinkedList{

	public:
		LinkedList();
		void linkedListQuery();
		void search(int searchValue);
		void remove(int removeValue);
		bool add(int newValue);
		void print();

	private:
		Node* head;		


}; //end linkedlist header

//START Linked list implementation
LinkedList::LinkedList(){
	head = 0;
}
//Prompt for Linked list options
//Runs after every finished action
void LinkedList::linkedListQuery(){
	int myChoice;
	bool runLoop = true;
	int countNumOfMoves = 0;

	while(runLoop){
		std::cout << "0 - Add" << 
				"\n1 - search" << 
				"\n2 - Remove" <<
				"\n3 - Print Linked List values" << std::endl;
		std::cout << "User Input: ";
		std::cin >> myChoice;

		//checks myChoice value to be between 0 and 4
		if(myChoice >= 0 && myChoice < 4){
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
		} else{
			std::cout << "\nInvalid Input - try again\n" << std::endl;
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
//END LinkedList implementation

//START Node implementation
Node::Node(int value){ 
	this->value = value; 
	next = 0;
}
//get and set methods
int Node::getValue(){
	return value;
}
Node* Node::getNext(){
	return next;
}		
void Node::setNext(Node* newNext)
{ 
	next = newNext;
}
//END Node implementation

//START Main
int main(){	
	
	LinkedList myList;

	std::cout << "Welcome to the Linked list Creator/Editor." << std::endl;
	std::cout << "Please use an integer values 0 - 3 to choose an option" << std::endl;

	//runs program
	myList.linkedListQuery();

	return 0;
}