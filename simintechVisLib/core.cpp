
#include <iostream>

#include "pch.h"
#include "framework.h"

#include "core.h"

bool isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;
	return true;
}

void matToVoid(Mat& src, void** dst)
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

EXPORT void releaseSimMat(void** data)
{
	if(*data != 0)
		return
	((simMat*)* data)->data.release();
	*data = NULL;
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



string bitwiseAND(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src1 == 0))
		return "Input data error";

	try
	{
		simMat* m = 0;
		if (*dst == 0)
		{
			m = new simMat;
			*dst = m;
		}
		else
		{
			m = (simMat*)* dst;
		}

		bitwise_and(((simMat*)src1)->data, ((simMat*)src2)->data, m->data);

	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string bitwiseOR(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src1 == 0))
		return "Input data error";

	try
	{
		simMat* m = 0;
		if (*dst == 0)
		{
			m = new simMat;
			*dst = m;
		}
		else
		{
			m = (simMat*)* dst;
		}

		bitwise_or(((simMat*)src1)->data, ((simMat*)src2)->data, m->data);

	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string bitwiseNO(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src1 == 0))
		return "Input data error";

	try
	{
		simMat* m = 0;
		if (*dst == 0)
		{
			m = new simMat;
			*dst = m;
		}
		else
		{
			m = (simMat*)* dst;
		}

		bitwise_not(((simMat*)src1)->data, ((simMat*)src2)->data, m->data);

	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string bitwiseXOR(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src1 == 0))
		return "Input data error";

	try
	{
		simMat* m = 0;
		if (*dst == 0)
		{
			m = new simMat;
			*dst = m;
		}
		else
		{
			m = (simMat*)* dst;
		}

		bitwise_xor(((simMat*)src1)->data, ((simMat*)src2)->data, m->data);

	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string perElementAddWeighted(void* src1, double *alpha, void* src2, double* beta, void** dst)
{
	if ((src1 == 0) || (src1 == 0))
		return "Input data error";

	try
	{
		simMat* m = 0;
		if (*dst == 0)
		{
			m = new simMat;
			*dst = m;
		}
		else
		{
			m = (simMat*)* dst;
		}
		addWeighted(((simMat*)src1)->data, *alpha, ((simMat*)src2)->data, *beta, 0, m->data);

	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string perElementDIV(double scale, void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src1 == 0))
		return "Input data error";

	try
	{
		simMat* m = 0;
		if (*dst == 0)
		{
			m = new simMat;
			*dst = m;
		}
		else
		{
			m = (simMat*)* dst;
		}

		divide(((simMat*)src1)->data,  ((simMat*)src2)->data, m->data, scale, -1);

	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string perElementMUL(double scale, void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src1 == 0))
		return "Input data error";

	try
	{
		simMat* m = 0;
		if (*dst == 0)
		{
			m = new simMat;
			*dst = m;
		}
		else
		{
			m = (simMat*)* dst;
		}

		multiply(((simMat*)src1)->data, ((simMat*)src2)->data, m->data, scale, -1);

	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}
string matrixMUL(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src1 == 0))
		return "Input data error";

	try
	{
		simMat* m = 0;
		if (*dst == 0)
		{
			m = new simMat;
			*dst = m;
		}
		else
		{
			m = (simMat*)* dst;
		}
		m->data = ((simMat*)src1)->data.mul(((simMat*)src2)->data);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string perElementADDV(void* src1, void* val, void** dst)
{
	return string();
}

string perElementMULV(void* src1, void* val, void** dst)
{
	return string();
}
