#ifndef LIINKEDLIST_H
#define LINKEDLIST_H
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


};
#endif