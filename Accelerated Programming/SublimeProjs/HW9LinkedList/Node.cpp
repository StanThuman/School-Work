#include "Node.h"

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