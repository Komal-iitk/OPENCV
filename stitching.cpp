#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/stitching/stitcher.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace cv;

bool try_use_gpu = false;
vector<Mat> imgs;
string result_name = "result.jpg";

Mat RGBframe1,RGBframe2,GRAYframe1,GRAYframe2;
long c=0;

///////////// This loop is used to calculate process time /////////////////////
double tt_tic=0;
void tic()
{
tt_tic = getTickCount();
}

void toc()
{
double tt_toc = (getTickCount() - tt_tic)/(getTickFrequency());
cout<<tt_toc<<endl;
}
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{

char key = 'r';

VideoCapture grab1(0);
VideoCapture grab2(1);

while(1)
{
tic();
c++;

grab1.grab();
grab2.grab();

if((c%15)==0)
{
cout<<"Grabbing frame"<<endl;
grab1.retrieve(RGBframe1);
grab2.retrieve(RGBframe2);
c=0;

cvtColor(RGBframe1, GRAYframe1, COLOR_BGR2GRAY);
cvtColor(RGBframe2, GRAYframe2, COLOR_BGR2GRAY);

namedWindow("RGB1",1);
imshow("RGB1",GRAYframe1);
imwrite("out3.jpg",GRAYframe1);

namedWindow("RGB2",1);
imshow("RGB2",GRAYframe2);
imwrite("out4.jpg",GRAYframe2);

Mat img1 = imread("out1.jpg");
imgs.push_back(img1);
Mat img2 = imread("out2.jpg");
imgs.push_back(img2);

Mat pano;
Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
Stitcher::Status status = stitcher.stitch(imgs, pano);

if (status != Stitcher::OK)
{
    cout << "Can't stitch images, error code = " << int(status) << endl;
    //return -1;
}

imwrite(result_name, pano);
imshow(result_name,pano);

}

key=waitKey(1);

grab1.release();
grab2.release();

if(key == 'q')
break;
toc();
}

//waitKey(0);    
return 0;
}


