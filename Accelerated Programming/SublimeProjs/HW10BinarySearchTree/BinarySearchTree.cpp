/****************************
Stanley Lim - Accelerated programming class

Assignment - implement Binary search tree with 
Add function and search

I put in 10 values for a tree. The user can search for those
values. I used 50 40 35 30 33 60 70 65 85 75

Should compile with mobaXterm and run


*********************************/
#include <iostream>
class Node{
	public:
		Node(int value);
		int getValue(){ return value;}
		Node* getLeft(){return left;}
		Node* getRight(){return right;}
		void setRight(Node* newRight);
		void setLeft(Node* newLeft);

	private:
		Node* left;
		Node* right;
		int value;
};
class BinarySearchTree{

	public:
		BinarySearchTree();
		bool add(int newValue);		
		void search(int searchValue);

	private:
		Node* root;
};

//START Node Implementation
Node::Node(int value){
	this->value = value;
	left = 0;
	right = 0;
}

//sets the right pointer
void Node::setRight(Node* newRight){
	right = newRight;
}
//sets the left pointer
void Node::setLeft(Node* newLeft){
	left = newLeft;
}
//END node Implementation

//START BinarySearchTree implementation
BinarySearchTree::BinarySearchTree(){
	root = 0;
}
bool BinarySearchTree::add(int newValue){
	bool success = true;
	Node* newNode = new Node(newValue);
	
	//dynamic memory success check
	if(newNode != 0){

		//iterate with current and previous
		Node* current = root;
		Node* previous = 0;
		while(current != 0){
			previous = current;

			//moves through left and right pointers
			//depending on new value
			if(newValue > current->getValue()){				
				current = current->getRight();
			} else{				
				current = current->getLeft();				
			}
		}

		//checks to see if at Root
		if(previous != 0){

			//Sets the value to left or Right
			if(newValue > previous->getValue()){
				previous->setRight(newNode);			
			} else{
				previous->setLeft(newNode);			
			}
		} else{
			//set Root			
			root = newNode;
		}
		
	}
	return success;
}

void BinarySearchTree::search(int searchValue){

	Node* current = root;
	bool foundValue = false;

	//counts the number of node passes
	int countNumOfMoves = 0;

	while(current != 0 && !foundValue){

		//Runs when value is found
		if(searchValue == current->getValue()){
			std::cout << "Found value " << current->getValue() << " in " <<
				countNumOfMoves << " moves."; 
			foundValue = true;

		}

		//moves right in search if searchValue is greater
		if(searchValue > current->getValue() && !foundValue){
			current = current->getRight();
			std::cout << "Moving Right" << std::endl;
			countNumOfMoves++;
		}

		//Moves left in search if searchValue is less than
		if(searchValue < current->getValue() && !foundValue){
			current = current->getLeft();
			std::cout << "Moving Left" << std::endl;
			countNumOfMoves++;
		}
	}

	if(foundValue == false){
		std::cout << searchValue << " not found, Try again." << std::endl;
	}
}
//End BinarySearchTree Implementation

int main(){
	
	BinarySearchTree myTree;
	int searchValue;
	bool restartLoop = true;
	char restartAnswer;

	//add values to search tree;
	myTree.add(50);	
	myTree.add(40);
	myTree.add(35);
	myTree.add(30);
	myTree.add(33);
	myTree.add(60);
	myTree.add(70);
	myTree.add(65);	
	myTree.add(85);
	myTree.add(75);

	//use while to search more than once
	while(restartLoop){

		std::cout << "What value would you like to search for?" << std::endl;		
		std::cout << "values: 50 40 35 30 33 60 70 65 85 75" << std::endl;
		std::cin >> searchValue;
		myTree.search(searchValue);

		//checks to see if user wants to restart loop
		std::cout << "\n\nSearch again? (Y/N)";
		std::cin >> restartAnswer;
		std::cout << "\n";
		if(restartAnswer == 'Y' || restartAnswer == 'y'){
			restartLoop = true;
		}
		if(restartAnswer == 'N' || restartAnswer == 'n'){
			restartLoop = false;
			std::cout << "Thank you for your time!! See you later! ";
		}
	}//End while loop

	return 0;
}