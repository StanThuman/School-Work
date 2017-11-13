#include <iostream>

class Node{

	public:
		Node(int newValue){ value = newValue; next = 0; }
		Node* getNext(){ return next; }
		int getValue(){ return value; }
		void setNext(Node* newNext){ next = newNext; }

	private:
		int value;
		Node* next;
};//end Node class

class LinkedList{
	public:
		LinkedList(){ head = 0; }
		bool add(int newValue);

	private:
		Node* head;
};//end LinkedList Class

bool LinkedList::add(int newValue){
	bool success = true;
	Node* newAdd = new Node(newValue);

	//no memory available returns 0
	//0= memory leak or no memory available
	if (newAdd != 0){
		Node* current = head;
		Node* previous = 0;		

		//if current is 0, were at head or tail
		//don't want to run loop if that's the case
		while (current != 0 && newAdd->getValue() > current->getValue()){
			previous = current;
			current = current->getNext();
		} //end loop

		//newAdd should be less than current now
		newAdd->setNext(current);

		if (previous != 0){
			previous->setNext(newAdd);
		} else{
			head = newAdd;
		}
	} else{
		success = false;
	}
	return success;
}



int main(){

	LinkedList list;
	int* num = new int(2);

	std::cout << *num << std::endl;

	int* pointer = num;
	return 0;
}