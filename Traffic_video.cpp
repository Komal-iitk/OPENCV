#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat image, gray_image, RGBframe, dst_new, GRAYframe,sub;
int k;
float x=0,y=0;
int main( int , char**  )
{
char key = 'r';

//string imageName("/home/lbehera/Desktop/Nissan/Codes/Test/trafficnew.avi");
string imageName("/home/komal/Desktop/Nissan/DATA/Fundamentals/traffic.avi");
VideoCapture cap(imageName);

//string imageName1("/home/lbehera/Desktop/Nissan/Codes/Test/backgroundnew.png");
string imageName1("/home/komal/Desktop/Nissan/DATA/Fundamentals/background.png");

image = imread(imageName1.c_str());
cvtColor( image, gray_image, CV_BGR2GRAY );

vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

while(1)
{
cap>>RGBframe;

	if(!RGBframe.empty())
	{
		cvtColor(RGBframe, GRAYframe, CV_BGR2GRAY);
		
		sub=GRAYframe-gray_image;
		Canny( sub, dst_new, 70, 210, 3 );
		
		findContours( dst_new, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

		vector<vector<Point> > contours_poly( contours.size() );
		vector<Rect> boundRect( contours.size() );
		vector<Point2f>center( contours.size() );
		vector<float>radius( contours.size() );

		Mat drawing = Mat::zeros( dst_new.size(), CV_8UC3 );

		for( int i = 0; i< contours.size(); i++ )
		{

		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
		
				
		//center[i].
		//center[i] = (float(x),float(y));
		//x=center[0][0];
		//x=center[i];
		
		//if((contourArea(contours[i])>150)&&(contourArea(contours[i])<500))
		if((center[i].y>80)&&(center[i].y<120)&&(contourArea(contours[i])>100)&&(contourArea(contours[i])<250))
		{

		cout<<"Area: "<<contourArea(contours[i]);
		
		cout<<"  center: "<<center[i]<<endl;
		//cout<<center[i].x<<endl;
		k++;
		Scalar color = Scalar(255,255,255);
		circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );		
		}
		}

		namedWindow( "Canny", 1 );
		imshow( "Canny", dst_new );

		namedWindow( "Car Detection", 1 );
		imshow( "Car Detection", drawing );		

		namedWindow( "Original", 1 );
		imshow( "Original", RGBframe );

		namedWindow( "GRAY", 1 );
		imshow( "GRAY", GRAYframe );

		namedWindow( "sub", 1 );
		imshow( "sub", sub );

		waitKey(1000);
		if(key == 'q')
		break;
	}
	else
	break;
}
k=k/2;
cout<<"Number of cars = "<<k<<endl;
return 0;
}

