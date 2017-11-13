#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <string.h>

using std::string;
using std::cout;


int main(){

	string timeHolder[50];
	time_t t;
	struct tm *tmp;

	t = time(&t);
	tmp = localtime(&t);

	strftime(timeHolder, 50,"%A %B  %d %H:%M:%S %Z %Y\n", tmp);

	cout << timeHolder;

	

	return 0;
}