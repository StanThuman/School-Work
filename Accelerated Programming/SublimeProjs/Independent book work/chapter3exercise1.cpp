#include<iostream>


using namespace std;
class Node{

public:
	int getValue(){return value;}	
	void setNext(Node* newNext){next = newNext;}
	Node* getNext(){return next;}
	Node(int newValue){value = newValue;}

private:
	int value;
	Node* next;

};

class LinkedList{

public:
	bool add(int value);
	LinkedList(){head = 0;}

private:
	Node* head;



};

bool LinkedList::add(int value){
	bool success = true;

	Node* newAdd = new Node(value);

	if(newAdd != 0){

		Node* current = head;
		Node* previous = 0;

		while(current != 0 && current->getValue() > newAdd->getValue()){
			
				previous = current;
				current = current->getNext();
			}

			if(previous != 0){
				previous->setNext(newAdd);
			} else{
				head->setNext(newAdd);
			}
	} else{
		success = false;
	}
	
	return success;
}


int main(){


	return 0;
}