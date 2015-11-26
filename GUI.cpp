#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>

using namespace cv;
using namespace std;

Mat rgb1,rgb2,rgb3,rgb4,rgb5;
Mat targetROI;

VideoCapture grab1(0);
VideoCapture grab2(1);
VideoCapture grab3(2);
VideoCapture grab4(3);

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{

if( event == EVENT_LBUTTONDOWN )
{

if((x>0 && x<320) && (y>0 && y<240))			// Top left
{

pyrUp( rgb1, rgb5, Size( rgb1.cols*2, rgb1.rows*2 ) );

namedWindow("img1",1);
imshow("img1", rgb5);

}

else if((x>319 && x<640) && (y>0 && y<240))		// Top right
{

pyrUp( rgb2, rgb5, Size( rgb2.cols*2, rgb2.rows*2 ) );

namedWindow("img1",1);
imshow("img1", rgb5);

}

else if((x>0 && x<320) && (y>239 && y<480))		//Bottom left
{

pyrUp( rgb3, rgb5, Size( rgb3.cols*2, rgb3.rows*2 ) );

namedWindow("img1",1);
imshow("img1", rgb5);

}

else if((x>319 && x<640) && (y>239 && y<480))		//Bottom right
{

pyrUp( rgb4, rgb5, Size( rgb4.cols*2, rgb4.rows*2 ) );

namedWindow("img1",1);
imshow("img1", rgb5);

}

}
}

int main(int argc, char *argv[])
{
char key = 'r';

grab1.set(3,320);
grab1.set(4,240);

grab2.set(3,320);
grab2.set(4,240);

grab3.set(3,320);
grab3.set(4,240);

grab4.set(3,320);
grab4.set(4,240);

grab1.grab();

grab1.retrieve(rgb1);

int dstWidth = rgb1.cols*2;
int dstHeight = rgb1.rows*2;

Mat dst = Mat(dstHeight, dstWidth, CV_8UC3, Scalar(0,0,0));

while(1)
{

grab1.grab();
grab2.grab();
grab3.grab();
grab4.grab();

grab1.retrieve(rgb1);
grab2.retrieve(rgb2);
grab3.retrieve(rgb3);
grab4.retrieve(rgb4);

setMouseCallback("OpenCV Window", CallBackFunc, NULL);

Rect roi(Rect(0,0,rgb1.cols, rgb1.rows));
targetROI = dst(roi);
rgb1.copyTo(targetROI);

targetROI = dst(Rect(rgb1.cols,0,rgb1.cols, rgb1.rows));
rgb2.copyTo(targetROI);

targetROI = dst(Rect(0,rgb1.rows,rgb1.cols, rgb1.rows));
rgb3.copyTo(targetROI);

targetROI = dst(Rect(rgb1.cols,rgb1.rows,rgb1.cols, rgb1.rows));
rgb4.copyTo(targetROI);

namedWindow("OpenCV Window");
imshow("OpenCV Window", dst);

key=waitKey(1);

if(key == 'q')
break;
}

return 0;
}

//if  ( event == EVENT_LBUTTONDBLCLK )
//if  ( event == EVENT_LBUTTONUP )
//if  ( event == EVENT_LBUTTONDOWN )
//if ( event == EVENT_MOUSEMOVE )

