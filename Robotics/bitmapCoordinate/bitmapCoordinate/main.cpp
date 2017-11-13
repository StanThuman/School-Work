/***********************************************************
Stanley Lim - 50441072


I cannot compile this is g++
but it should work in visual studio

I had to modify the output.txt because of the way I wrote
my code. I will talk to you about my homework after class
tomorrow.

This assignment calculates trajectories for homework 1a, b, and c.
It will creat a fileOutput.txt that logs some information


***************************************************/

#include <iostream>
   using std::cout;
   using std::endl;

#include "DrawPicture.h"
//ifstream is for loadng in files and reading from them
//ofstream is for creating new files and putting info into them



int main(){

  DrawPicture pic1;
  //pic1.createNewBitmap((char*)"newName.bmp");
  pic1.HW1pointA();
  pic1.HW1pointB();
  pic1.HW1pointC();
  // MathUtility::doMath();


  //pic1.outputLogFile();
  return 0;
}
