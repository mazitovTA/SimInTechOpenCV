
#include "pch.h"
#include "framework.h"
#include "core.h"

#include <iostream>

using namespace cv;

bool isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;
	return true;
}

EXPORT  int openImage(void** frame, char name[])
{
	if (*frame != 0)
	{
		IplImage* src = (IplImage*)* frame;
		cvReleaseImage(&src);
	}
	IplImage* src = cvLoadImage(name);
	if (src == 0)
		return -1;
	*frame = src;
	return 0;
}

EXPORT  int showFrame(void* source, int delay, char name[])
{
	if (source == 0)
		return -1;
	cv::Mat src = cv::cvarrToMat(source);
	if ((src.type() == CV_8UC1) || (src.type() == CV_8UC3))
	{
		void* pt = cvGetWindowHandle(name);
		if(pt == 0)
			namedWindow(name, WINDOW_NORMAL);
		imshow(name, src);
		waitKey(delay);
		return 0;
	}
	else
		return -1;
}


EXPORT  int  openVideoSource(void** source, char address[], void** frame)
{
	VideoCapture* cam = new VideoCapture;
	*source = cam;

	bool res = false;
	if (isNumber(string(address)))
		res = cam->open(std::stoi(address));
	else
		res = cam->open(address);
	if (!res)
		return -1;

	Mat image;
	cam->grab();
	cam->retrieve(image);
	if (image.empty())
		return -1;
	*frame = cvCloneImage(&(IplImage)image);

	return 0;
}

EXPORT  int  retrieveImage(void* source, void* frame)
{
	VideoCapture* cam = (VideoCapture*)source;
	if ((cam == 0) || (frame == 0))
		return -1;
	Mat image = cv::cvarrToMat(frame);
	*cam >> image;
	if (image.empty())
		return -1;
	frame = (&(IplImage)image);
	return 0;
}

EXPORT  int  releaseSourse(void* source) {
	VideoCapture* cam = (VideoCapture*)source;
	if (cam == 0)
		return -1;
	cam->release();
	return 0;
}

EXPORT  int  releaseFrame(void* source) {
	IplImage* src = (IplImage*)source;
	if (src == 0)
		return -1;
	cvReleaseImage(&src);
	return 0;
}


EXPORT int copyFrame(void* src, void** dst) {
	if (src == 0)
		return -1;
	if (*dst != 0)
	{
		IplImage* s = (IplImage*)* dst;
		cvReleaseImage(&s);
	}
	*dst = cvCloneImage((IplImage*)src);
	return 0;
}

EXPORT int  convertColor(void* src, void** dst, int code) {

	if (src == 0)
		return -1;
	Mat image = cv::cvarrToMat(src);
	Mat res;
	cvtColor(image, res, code);
	*dst = cvCloneImage(&(IplImage)res);
	return 0;
}


EXPORT void* createHandledWindow(char name[]) {
	namedWindow(name, WINDOW_NORMAL);
	return cvGetWindowHandle(name);
}

EXPORT int destroyWindowByName(char name[]) {
	cvDestroyWindow(name);
	return 0;
}

EXPORT int destroyAllWindows() {	
	cvDestroyAllWindows();
	return 0;
}

EXPORT void* getWindowHandle(char name[]) {
	return cvGetWindowHandle(name);
}

void matToVoid(Mat &src, void **dst)
{
	if (*dst == 0)
		* dst = cvCloneImage(&(IplImage)src);
	else
	{
		IplImage* src_ = (IplImage*)* dst;
		cvReleaseImage(&src_);
		*dst = cvCloneImage(&(IplImage)src);
	}
}

string  s_CvtColor(void* src, void** dst) {

	string res = "";
	Mat resImage;

	try {
		Mat image = cv::cvarrToMat(src);
		cvtColor(image, resImage, CV_RGB2GRAY);
	}
	catch (cv::Exception& e)
	{
		return e.what();
	}

	matToVoid(resImage, dst);
	return res;
}

cv::Mat test() {

	Mat res(480, 640, CV_8UC3, Scalar(255, 0, 0));
	return res;
}

void test1(Mat &im) {

	imshow("im", im);
	waitKey(0);
}
