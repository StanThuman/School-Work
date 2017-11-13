/***************************************
Doesn't Work correctly
This was difficult, the recursive way is so much simpler
Basically, what I tried to do was create 3 different stacks, and swap
between each one.
Stanley Lim
******************************************/

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main(){

	int discs;
	int *a, *b, *c;
		
	//reads input for how many discs
	cout << "How many discs?" << endl;
	cin >> discs;
	
	//declare 3 towers of hanoi
	a = new int[discs];
	b = new int[discs];
	c = new int[discs];
	
	discs = discs - 1;
	
	//initialize tower a
	int arrayValues = 1;
	for (int i = 0; i <= discs; i++){
		a[i] = arrayValues;
		arrayValues++;
	}

	//initialize b and c with 0's
	for (int i = 0; i <= discs; i++){
		b[i] = 0;
		c[i] = 0;
		arrayValues++;
	}


	int aStack = discs - 1;
	int bStack = 0;
	int cStack = 0;

	//run loop untill all sorted
	bool runLoop = true;
	while (runLoop){				
		
		
		if (a[aStack] > 0){
			//moves from astack to bstack
			if (a[aStack] > b[bStack]){
				cout << "Moved " << a[aStack] << " from Stack A to B" << endl;
				b[bStack] = a[aStack];
				a[aStack] = 0;
				bStack++;
				aStack--;

			}
			//moves from astack to cstack
			if (a[aStack] > c[cStack]){
				cout << "Moved " << a[aStack] << " from Stack A to C" << endl;
				c[cStack] = a[aStack];
				a[aStack] = 0;
				cStack++;
				aStack--;
			}
		}
		
		if (b[bStack] > 0){
		
			//moves from bstack to cstack
			if (b[bStack] > c[cStack]){
				cout << "Moved " << a[aStack] << " from Stack B to C" << endl;
				c[cStack] = b[bStack];
				b[bStack] = 0;
				bStack--;
				cStack++;
			}
			//moves from bstack to astack
			if (b[bStack] > a[aStack]){
				cout << "Moved " << a[aStack] << " from Stack B to A" << endl;
				a[aStack] = b[bStack];
				b[bStack] = 0;
				bStack--;
				aStack++;
			}
		}
		
		
		if (c[cStack] > 0){
		
			//moves from cstack to bstack			
			if (c[cStack] > b[bStack]){				
				cout << "Moved " << a[aStack] << " from Stack C to B" << endl;
				b[bStack] = c[cStack];
				c[cStack] = 0;
				cStack--;
				bStack++;
			}

			//moves from cstack to astack
			if (c[cStack] > a[aStack]){
				
				cout << "Moved " << a[aStack] << " from Stack C to A" << endl;
				a[aStack] = c[cStack];
				c[cStack] = 0;
				cStack--;
				aStack++;
			}

			if (c[discs] == discs){
				runLoop = false;
			}
		}
		
	}



	return 0;
}

