
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


EXPORT void releaseSimMat(void** data)
{
	if(*data != 0)
		return
	((simMat*)* data)->data.release();
	*data = NULL;
}

EXPORT string openImage(void** frame, char name[], int code)
{
	try
	{
		simMat* m = 0;
		if (*frame == 0)
		{
			m = new simMat;
			*frame = m;
		}
		else
		{
			m = (simMat*)* frame;
		}
		m->data = imread(name, code);
	}
	catch (Exception& e)
	{
		return e.what();
	}
	return "0";
}

EXPORT string showFrame(void* source, int delay, char name[])
{
	try
	{
		void* pt = cvGetWindowHandle(name);
		if (pt == 0)
			namedWindow(name, WINDOW_NORMAL);
		imshow(name, ((simMat*)source)->data);
		waitKey(delay);

	}
	catch (Exception& e)
	{
		return e.what();
	}
	return "0";
}

EXPORT string openVideoSource(void** source, char address[])
{
	try
	{
		VideoCapture* cam = new VideoCapture;
		*source = cam;

		bool res = false;
		if (isNumber(string(address)))
			res = cam->open(std::stoi(address));
		else
			res = cam->open(address);
	}
	catch (Exception& e)
	{
		return e.what();
	}
	return "0";
}

EXPORT  string  retrieveImage(void* source, void** frame)
{
	try
	{
		VideoCapture* cam = (VideoCapture*)source;
		if (!cam->isOpened())
			return "no image source";

		simMat* m = 0;
		if (*frame == 0)
		{
			m = new simMat;
			*frame = m;
		}
		else
		{
			m = (simMat*)* frame;
		}
		*cam >> m->data;
	}
	catch (Exception& e)
	{
		return e.what();
	}
	return "0";
}

EXPORT  int  releaseSourse(void* source) {
	VideoCapture* cam = (VideoCapture*)source;
	if (cam == 0)
		return -1;
	cam->release();
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
	if ((src1 == 0) || (src2 == 0))
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
	if ((src1 == 0) || (src2 == 0))
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
	if ((src1 == 0) || (src2 == 0))
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
	if ((src1 == 0) || (src2 == 0))
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
	if ((src1 == 0) || (src2 == 0))
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
	if ((src1 == 0) || (src2 == 0))
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
	if ((src1 == 0) || (src2 == 0))
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
	if ((src1 == 0) || (src2 == 0))
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

string perElementADDV(void* src1, float val, void** dst)
{
	if (src1 == 0)
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
		m->data = ((simMat*)src1)->data + val;
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string perElementMULV(void* src1, float val, void** dst)
{
	if (src1 == 0) 
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
		m->data = ((simMat*)src1)->data * val;
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}
