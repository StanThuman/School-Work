//#include <iostream>
//using std::cout;
//using std::endl;
//#include <fstream>
//using std::ifstream;
//using std::ofstream;
//#include "DrawPicture.h"
////ifstream is for loadng in files and reading from them
////ofstream is for creating new files and putting info into them
//
//
//const int W = 500;
//const int H = 500;
//
////used to draw the diagnol line
//void setPixel(int x, int y, char image[H][W][3])
//{
//	for (int i = x - 1; i <= x + 1; i++)
//		for (int j = y - 1; j <= y + 1; j++)
//			if (i >= 0 && i <= W - 1 && j >= 0 && j <= H - 1)
//				for (int k = 0; k <= 2; k++)
//					image[i][j][k] = 0;
//}
//
////used to draw pixels
//void setPixel(int p[2], char image[H][W][3])
//{
//	cout << p[0] << ' ' << p[1] << endl;
//	for (int i = p[0] - 1; i <= p[0] + 1; i++)
//		for (int j = p[1] - 1; j <= p[1] + 1; j++)
//			if (i >= 0 && i <= W - 1 && j >= 0 && j <= H - 1)
//				for (int k = 0; k <= 2; k++)
//					image[j][i][k] = 0;
//}


// int main ()
// {
//   if (fabs(a) > 0.001) // (a != 0)  WHY??????
//   x = b / a;
//
//   ifstream example ("500x500.bmp");
//   char header [54];
//   example.read (header, 54);
//   example.close ();
//
//   ofstream outfile ("4413-01.bmp");
//   outfile.write (header, 54);
//
//   char image[H][W][3];
//   for (int x = 0; x <= W-1; x++)
//   for (int y = 0; y <= H-1; y++)
//   for (int c = 0; c <= 2; c++)
//   image[x][y][c] = 255;
//
//   for (int x = 0; x <= W-1; x++)  // diagonal line
//   setPixel (x, x, image);
//
//   int p[4][2] = {{50, 60}, {100, 200}, {300, 350}, {450, 480}};
//
//     for (int i = 0; i <= 3; i++)
//        setPixel (p[i], image);
//
//     //outfile.write (&image[0][0][0], 750000);
//     for (int x = 0; x <= W-1; x++)
//        for (int y = 0; y <= H-1; y++)
//           for (int c = 0; c <= 2; c++)
//              outfile.write (&image[x][y][c], 1);
//     outfile.close ();
//
//     return 0;
// }
