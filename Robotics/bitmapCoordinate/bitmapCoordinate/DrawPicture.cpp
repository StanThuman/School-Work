#include "DrawPicture.h"
DrawPicture::DrawPicture() {
	getBitmapHeader();
	coord[0].x = 50.0;
	coord[0].y = 50.0;
	coord[1].x = 100.0;
	coord[1].y = 400.0;
	coord[2].x = 300.0;
	coord[2].y = 350.0;
	coord[3].x = 450.0;
	coord[3].y = 450.0;
	for(int i = 0; i < 3; i++){
		BLUE[i] = 0;
		RED[i] = 0;
		WHITE[i] = 255;
		BLACK[i] = 0;
	}
	BLUE[0] = 255;
	RED[2] = 255;
	
	
	outputLog = new ofstream("fileOutput.txt");
}

void DrawPicture::getBitmapHeader(){
  cout << "creating bitmap" << endl;

  ifstream templateBitmap("lineGraph.bmp");
  templateBitmap.read(bitmapHeader, 54);
  templateBitmap.close();
}

//sets up the bitmap for writing for each homework iteration
void DrawPicture::createNewBitmap(char* bitmapName){
	bitmapFile = new ofstream(bitmapName);	
	bitmapFile->write(bitmapHeader, 54);
	setAllValues(255);	

	//draw default diagonal
	for(int i = 0; i < 500; i++)
		setPixel(i, i, BLUE);		

	drawCoordinatePixels();
}

//set all rgb for one point
void DrawPicture::setAllValues(int colorValue){
  for( int i = 0; i < 500; i++ )
    for( int j = 0; j < 500; j++ )
      for( int z = 0; z < 3; z++ ){
        bitmapGraph[i][j][z] = colorValue;        
      }
}

//set specific pixels
void DrawPicture::setPixel(int x, int y, int color[3]){
	bitmapGraph[y][x][0] = color[0];
	bitmapGraph[y][x][1] = color[1];
	bitmapGraph[y][x][2] = color[2];

}

//properly close bitmap
void DrawPicture::writeAndClose(){
	int totalSize = 500*500*3;
	bitmapFile->write((char*)bitmapGraph, totalSize);
	bitmapFile->close();
}

//HW 1.A
void DrawPicture::HW1pointA(){

	createNewBitmap("hw1A.bmp");	
	cout << "creating 1a bmp" << endl;
	*outputLog << "1A: POSITIONS ONLY polynomial coefficients\n";
	
	Coordinate trajectoryPoint;
	Coordinate firstPoint;
	double time;
	for (int i = 0; i < 3; i++) {

		*outputLog << "Segment " << i << ": \n";
		time = MathUtility::distanceFormula(coord[i], coord[i+1]);
		for (double t = 0.0; t <= time; t += (time/10)) {
			if (t == 0.0) {
				trajectoryPoint = MathUtility::calculatePosWithTime(coord[i], coord[i + 1], t, outputLog, true);
				firstPoint = trajectoryPoint;
			}
			else
				trajectoryPoint = MathUtility::calculatePosWithTime(coord[i], coord[i + 1], t, outputLog, false);						
			
			setPixel(trajectoryPoint.x, trajectoryPoint.y, BLACK);			
		}

		*outputLog << "\ncheck 1A: positions only\n";
		*outputLog << "\t\tp_start:\t\t\t p_end\n";
		*outputLog << "segment\t  data\t\ts(0)\t\t  data\t\ts(t_i)\n";
		*outputLog << i << ":     (" << coord[i].x << "," << coord[i].y << " )    (" << firstPoint.x << "," << firstPoint.y << ")     ";
		*outputLog << "\t (" << coord[i+1].x << "," << coord[i + 1].y << " )\t(" << trajectoryPoint.x << "," << trajectoryPoint.y << ")\n\n";

	}
	//reprint p1,p2,p3,p4
	for (int i = 0; i < 4; i++) {
		setPixel(coord[i].x, coord[i].y, RED);
	}

	*outputLog << "\n=============================================\n\n";
	writeAndClose();
}

//HW 1.B
void DrawPicture::HW1pointB(){
	cout << "creating 1b bmp" << endl;
	createNewBitmap("hw1B.bmp");
	Coordinate trajectoryPoint;
	Coordinate firstPoint;
	*outputLog << "1B: POSITIONS & INTERIOR VELOCITIES polynomial coefficients\n";
	*outputLog << "Segment " << 0 << ": \n";

	double time = MathUtility::distanceFormula(coord[0], coord[1]);

	for (double t = 0.0; t <= time; t += (time / 10)) {
		if (t == 0.0) {
			trajectoryPoint = MathUtility::calculatePosWIthTimeAndVelocity(coord[0], coord[1], coord[2], t, outputLog, true);
			firstPoint = trajectoryPoint;
		}
		else
			trajectoryPoint = MathUtility::calculatePosWIthTimeAndVelocity(coord[0], coord[1], coord[2], t, outputLog, false);		
		
		setPixel(trajectoryPoint.x, trajectoryPoint.y, BLACK);
	}
	
	*outputLog << "\t\tp_start:\t\t\t p_end\n";
	*outputLog << "segment\t  data\t\ts(0)\t\t  data\t\ts(t_i)\n";
	*outputLog << 0 << ":     (" << coord[0].x << "," << coord[0].y << " )    (" << firstPoint.x << "," << firstPoint.y << ")     ";
	*outputLog << "\t (" << coord[1].x << "," << coord[1].y << " )\t(" << trajectoryPoint.x << "," << trajectoryPoint.y << ")\n\n";


	time = MathUtility::distanceFormula(coord[1], coord[2]);
	*outputLog << "Segment " << 1 << ": \n";
	for (double t = 0.0; t <= time; t += time/10) {
		if(t == 0.0){
			trajectoryPoint = MathUtility::calculatePosWithTime1(coord[1], coord[2], t, outputLog, true);
			firstPoint = trajectoryPoint;
		}
		else
			trajectoryPoint = MathUtility::calculatePosWithTime1(coord[1], coord[2], t, outputLog, false);

		setPixel(trajectoryPoint.x, trajectoryPoint.y, BLACK);
	}	

	*outputLog << "\t\tp_start:\t\t\t p_end\n";
	*outputLog << "segment\t  data\t\ts(0)\t\t  data\t\ts(t_i)\n";
	*outputLog << 1 << ":     (" << coord[1].x << "," << coord[1].y << " )    (" << firstPoint.x << "," << firstPoint.y << ")     ";
	*outputLog << "\t (" << coord[2].x << "," << coord[2].y << " )\t(" << trajectoryPoint.x << "," << trajectoryPoint.y << ")\n\n";	
		
	*outputLog << "Segment " << 2 << ": \n";
	time = MathUtility::distanceFormula(coord[2], coord[3]);
	for (double t = 0.0; t <= time; t += (time / 10)) {	
		if(t == 0.0){
			trajectoryPoint = MathUtility::calculatePosWIthTimeAndVelocity2(coord[1], coord[2], coord[3], t, outputLog, true);
			firstPoint = trajectoryPoint;
		}
		else
			trajectoryPoint = MathUtility::calculatePosWIthTimeAndVelocity2(coord[1], coord[2], coord[3], t, outputLog, false);
		
		setPixel(trajectoryPoint.x, trajectoryPoint.y, BLACK);
	}		

	*outputLog << "\t\tp_start:\t\t\t p_end\n";
	*outputLog << "segment\t  data\t\ts(0)\t\t  data\t\ts(t_i)\n";
	*outputLog << 2 << ":     (" << coord[2].x << "," << coord[2].y << " )    (" << firstPoint.x << "," << firstPoint.y << ")     ";
	*outputLog << "\t (" << coord[3].x << "," << coord[3].y << " )\t(" << trajectoryPoint.x << "," << trajectoryPoint.y << ")\n\n";
	
	writeAndClose();

	*outputLog << "====================================\n\n";	
}

void DrawPicture::HW1pointC(){
	cout << "creating 1c bmp" << endl;
	createNewBitmap("hw1C.bmp");
	Coordinate trajectoryPoint;
	Coordinate firstPoint;
	*outputLog << "1C: POSITIONS & ALL VELOCITIES polynomial coefficients\n";
	*outputLog << "Segment " << 0 << ": \n";
	
	double time = MathUtility::distanceFormula(coord[0], coord[1]);
	for (double t = 0.0; t <= time; t += (time / 20)) {
	
		if(t == 0.0){
			trajectoryPoint = MathUtility::calculatePosWithTimeAndVelocityAndTerminalVelocity(coord[0], coord[1], t, outputLog, true);
			firstPoint = trajectoryPoint;
		}
		else
			trajectoryPoint = MathUtility::calculatePosWithTimeAndVelocityAndTerminalVelocity(coord[0], coord[1], t, outputLog, false);
	
		setPixel(trajectoryPoint.x, trajectoryPoint.y, BLACK);
	}	
	*outputLog << "segment\t  p_start\t    v(0)\t  p_end\t\tv(t_i)\n";
	*outputLog << 0 << ":     (" << coord[0].x << "," << coord[0].y << " )    (" << firstPoint.x << "," << firstPoint.y << ")     ";
	*outputLog << "\t (" << coord[1].x << "," << coord[1].y << " )\t(" << trajectoryPoint.x << "," << trajectoryPoint.y << ")\n\n";


	*outputLog << "Segment " << 1 << ": \n";
	time = MathUtility::distanceFormula(coord[1], coord[2]);
	for (double t = 0.0; t <= time; t += (time / 10)) {
		if (t == 0.0) {
			trajectoryPoint = MathUtility::calculatePosWithTimeAndVelocityAndTerminalVelocity2(coord[0], coord[1], coord[2], coord[3], t, outputLog, true);
			firstPoint = trajectoryPoint;
		}
		else
			trajectoryPoint = MathUtility::calculatePosWithTimeAndVelocityAndTerminalVelocity2(coord[0], coord[1], coord[2], coord[3], t, outputLog, false);

		setPixel(trajectoryPoint.x, trajectoryPoint.y, BLACK);
	}	
	*outputLog << "segment\t  p_start\t    v(0)\t  p_end\t\tv(t_i)\n";
	*outputLog << 1 << ":     (" << coord[1].x << "," << coord[1].y << " )    (" << firstPoint.x << "," << firstPoint.y << ")     ";
	*outputLog << "\t (" << coord[2].x << "," << coord[2].y << " )\t(" << trajectoryPoint.x << "," << trajectoryPoint.y << ")\n\n";

	*outputLog << "Segment " << 2 << ": \n";
	time = MathUtility::distanceFormula(coord[2], coord[3]);
	for (double t = 0.0; t < time; t += (time / 20)) {		
		if (t == 0.0) {
			trajectoryPoint = MathUtility::calculatePosWithTimeAndVelocityAndTerminalVelocity3(coord[2], coord[3], t, outputLog, true);
			firstPoint = trajectoryPoint;
		}
		else
			trajectoryPoint = MathUtility::calculatePosWithTimeAndVelocityAndTerminalVelocity3(coord[2], coord[3], t, outputLog, false);

		setPixel(trajectoryPoint.x, trajectoryPoint.y, BLACK);
	}	
	*outputLog << "segment\t  p_start\t    v(0)\t  p_end\t\tv(t_i)\n";
	*outputLog << 2 << ":     (" << coord[2].x << "," << coord[2].y << " )    (" << firstPoint.x << "," << firstPoint.y << ")     ";
	*outputLog << "\t (" << coord[3].x << "," << coord[3].y << " )\t(" << trajectoryPoint.x << "," << trajectoryPoint.y << ")\n\n";

	//redraw coordinate pixels
	
	writeAndClose();
	outputLog->close();

}

//make main points bigger
void DrawPicture::drawCoordinatePixels(){
	for (int i = 0; i < 4; i++) {
		setPixel(coord[i].x, coord[i].y, RED);
		setPixel(coord[i].x - 1, coord[i].y + 1, RED);
		setPixel(coord[i].x, coord[i].y + 1, RED);
		setPixel(coord[i].x + 1, coord[i].y + 1, RED);
		setPixel(coord[i].x - 1, coord[i].y, RED);
		setPixel(coord[i].x + 1, coord[i].y, RED);
		setPixel(coord[i].x - 1, coord[i].y - 1, RED);
		setPixel(coord[i].x, coord[i].y - 1, RED);
		setPixel(coord[i].x + 1, coord[i].y - 1, RED);
	}
}


DrawPicture::~DrawPicture(){
	
	delete bitmapFile;
}
