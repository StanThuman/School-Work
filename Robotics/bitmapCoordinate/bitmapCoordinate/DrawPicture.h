#ifndef DRAWPICTURE_H
#define DRAWPICTURE_H

#include <iostream>
#include <string.h>
#include <fstream>
#include "MathUtility.h"
#include "Coordinate.h"
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;


class DrawPicture{
  //make bitmap
  //calculate lines
  //draw lines on bitmap
  private:
	int BLUE[3];
	int RED[3];
	int WHITE[3];
	int BLACK[3];
    char bitmapHeader[54];
    char bitmapGraph[500][500][3];

	//bitmap pointer
	ofstream* bitmapFile;

	//txt pointer
	ofstream* outputLog;

	//holds all main points
	Coordinate coord[4];
  public:
    DrawPicture();
    void getBitmapHeader();
    void createNewBitmap(char* bitmapName);
    void setAllValues(int colorValue);
	void setPixel(int x, int y, int color[3]);
	void writeAndClose();
	void HW1pointA();
	void HW1pointB();
	void HW1pointC();
	void drawCoordinatePixels();


	~DrawPicture();
};
#endif
