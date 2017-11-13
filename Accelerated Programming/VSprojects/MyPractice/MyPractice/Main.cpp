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
	
	
	//input for discs
	cout << "How many discs?" << endl;
	cin >> discs;

	//declare dynamic arrays
	a = new int[discs];
	b = new int[discs];
	c = new int[discs];
	
	discs = discs - 1;

	//initialize arrays
	int arrayValues = 1;
	for (int i = discs; i >= 0; i--){
		a[i] = arrayValues;
		arrayValues++;
	}
	//put in values for b and c
	for (int i = 0; i <= discs; i++){
		b[i] = 0;
		c[i] = 0;
		
	}

	/*for (int i = 0; i <= discs; i++){
		cout << a[i] << endl;
	}*/
	int aStack = discs;
	int bStack = 0;
	int cStack = 0;	
	bool runA = true;
	bool runB = true;
	bool runC = true;

	bool runLoop = true;
	//to set one tower in b and one in c
	if (discs < 3){
		b[bStack] = a[aStack];
		bStack++;
		aStack--;
		c[bStack] = a[aStack];
		cStack++;
		aStack--;
		runLoop = false;
	}
	else{
		b[bStack] = a[aStack];
		bStack++;
		aStack--;
		c[bStack] = a[aStack];
		cStack++;
		aStack--;
	}

		while (runLoop){

			runA = true;
			while (runA){
				//move form aStack to bStack
				if (a[aStack] < b[bStack]){
					cout << "Moved " << a[aStack] << " from Stack A to B" << endl;
					b[bStack] = a[aStack];
					a[aStack] = 0;
					aStack--;
					bStack++;
				}
				//move form aStack to cStack
				if (a[aStack] < c[cStack]){
					cout << "Moved " << a[aStack] << " from Stack A to c" << endl;
					c[cStack] = a[aStack];
					a[aStack] = 0;
					aStack--;
					cStack++;

				}
				if (a[aStack] > b[bStack] && a[aStack] > c[cStack])
					runA = false;
			}


			runB = true;
			while (runB){
				//move form bStack to cStack
				if (b[bStack] < c[cStack]){
					cout << "Moved " << a[aStack] << " from Stack B to C" << endl;
					c[cStack] = b[bStack];
					b[bStack] = 0;
					bStack--;
					cStack++;
				}

				//move form bStack to aStack
				if (b[bStack] < a[aStack]){
					cout << "Moved " << a[aStack] << " from Stack B to A" << endl;
					a[aStack] = b[bStack];
					b[bStack] = 0;
					bStack--;
					aStack++;

				}

				//exits loop
				if (b[bStack] > c[cStack] && b[bStack] > a[aStack]){
					runA = false;
				}
			}

			runC = true;
			while (runC){
				//move form cStack to bStack
				if (c[cStack] < b[bStack]){
					cout << "Moved " << a[aStack] << " from Stack C to B" << endl;
					b[bStack] = c[cStack];
					c[cStack] = 0;
					cStack--;
					bStack++;
				}
				//move form cStack to aStack
				if (c[cStack] < a[cStack]){
					cout << "Moved " << a[aStack] << " from Stack C to A" << endl;
					a[aStack] = c[cStack];
					c[cStack] = 0;
					cStack--;
					aStack++;

				}
				//exits loop
				if (a[aStack] > b[bStack] && a[aStack] > c[cStack]){
					runA = false;
				}
			}

			//exits overall while loop
			if (c[discs] == discs + 1){
				runLoop = false;

			}
		}
	


	return 0;
}

