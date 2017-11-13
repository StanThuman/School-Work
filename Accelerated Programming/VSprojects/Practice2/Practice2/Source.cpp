#include<iostream>



int main(){

	int num[5] = { 6, 2, 1, 3, 7 };
	int array_max = 5;
	int current = 0;
	//selection sort
	/*for (int i = 0; i < array_max; i++){
		current = i;

		for (int j = i+1; j < array_max; j++){

			if (num[current] > num[j]){
				current = j;
			}
		}		
		if (current != i){
			int temp = num[i];
			num[i] = num[current];
			num[current] = temp;
		}
	}*/

	//bubble sort
	//for (int i = 0; i < array_max; i++){
	//	current = 0;
	//	for (int j = 1; j < array_max; j++){
	//		if (num[current] > num[j]){
	//			int temp = num[current];
	//			num[current] = j;
	//			num[j] = temp;
	//		}
	//		current++;

	//	}
	//}
	int* num1 = new int[3];
	for (int i = 0; i < 3; i++){

		num1[i] = i;
		std::cout << num1 << std::endl;
		
	}

	/*for (int i = 0; i < array_max; i++){
		current = i;

		for (int j = i -1; j >=0; j--){
			if (num[current] < num[j]){
				int temp = num[current];
				num[current] = num[j];
				num[j] = temp;
				current--;
			}
		}


	}*/


	//for (int i = 0; i < array_max; i++){
	//	std::cout << num[i] << std::endl;
	//}

	return 0;
}