
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

void sim_err(char*** err, string& e)
{
	if (**err != 0)
		free(**err);
	**err = _strdup(e.c_str());
}

void* createHandledWindow(char name[]) {
	namedWindow(name, WINDOW_NORMAL);
	return cvGetWindowHandle(name);
}

void* getWindowHandle(char name[]) {
	return cvGetWindowHandle(name);
}

void releaseSimMat(void** data)
{
	if(*data != 0)
		return
	((simMat*)* data)->data.release();
	*data = NULL;
}

////////////////////////////////////////////////////

void openImage(void** frame, char name[], int code, char** err)
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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void showFrame(void* source, int delay, char name[], char** err)
{
	try
	{
		if (source == 0)
			return;
		void* pt = cvGetWindowHandle(name);
		if (pt == 0)
			namedWindow(name, WINDOW_NORMAL);
		imshow(name, ((simMat*)source)->data);
		waitKey(delay);

	}
	catch (Exception& e)
	{
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void openVideoSource(void** source, char address[], char** err)
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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void retrieveImage(void* source, void** frame, char** err)
{
	try
	{
		VideoCapture* cam = (VideoCapture*)source;
		if (!cam->isOpened())
			return;

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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void releaseSourse(void* source, char** err)
 {
	try
	{
		VideoCapture* cam = (VideoCapture*)source;
		if (cam == 0)
			return;
		cam->release();
	}
	catch (Exception& e)
	{
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}


void destroyWindowByName(char name[], char** err)
{
	try
	{
		cvDestroyWindow(name);
	}
	catch (Exception& e)
	{
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void destroyAllWindows(char** err)
{
	try
	{
		cvDestroyAllWindows();
	}
	catch (Exception& e)
	{
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void  bitwiseAND(void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{	
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return;
	}

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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void  bitwiseOR(void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return;
	}

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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void bitwiseNO(void* src, void** dst, char** err)
{
	if ((src == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return;
	}

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

		bitwise_not(((simMat*)src)->data, m->data);

	}
	catch (Exception& e)
	{
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void bitwiseXOR(void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return;
	}

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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void perElementAddWeighted(void* src1, double *alpha, void* src2, double* beta, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return;
	}

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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void perElementDIV(double scale, void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return;
	}

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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void perElementMUL(double scale, void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return;
	}

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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}


void perElementADDV(void* src1, float val, void** dst, char** err)
{
	if (src1 == 0)
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return;
	}

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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void perElementMULV(void* src1, float val, void** dst, char** err)
{
	if (src1 == 0)
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return;
	}

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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}

void matrixMUL(void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return;
	}

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
		string exeption = e.what();
		sim_err(&err, exeption);
		return;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return;
}