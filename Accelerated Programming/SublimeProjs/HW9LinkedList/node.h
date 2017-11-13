#ifndef NODE_H
#define NODE_H
class Node{

	public:
		Node(int value);
		int getValue();
		Node* getNext();
		void setNext(Node* newNext);


	private:
		int value;
		Node* next;
};
#endif