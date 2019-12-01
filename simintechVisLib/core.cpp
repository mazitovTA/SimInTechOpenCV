
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

int releaseSimMat(void** data)
{
	if (*data != 0)
		return RES_ERROR;
	((simMat*)* data)->data.release();
	*data = NULL;
	return RES_OK;

}

////////////////////////////////////////////////////

int openImage(void** frame, char name[], int code, char** err)
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int showFrame(void* source, int delay, char name[], char** err)
{
	try
	{
		if (source == 0)
			return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int openVideoSource(void** source, char address[], char** err)
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int retrieveImage(void* source, void** frame, char** err)
{
	try
	{
		VideoCapture* cam = (VideoCapture*)source;
		if (!cam->isOpened())
			return RES_ERROR;

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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int releaseSourse(void* source, char** err)
 {
	try
	{
		VideoCapture* cam = (VideoCapture*)source;
		if (cam == 0)
			return RES_ERROR;
		cam->release();
	}
	catch (Exception& e)
	{
		string exeption = e.what();
		sim_err(&err, exeption);
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}


int destroyWindowByName(char name[], char** err)
{
	try
	{
		cvDestroyWindow(name);
	}
	catch (Exception& e)
	{
		string exeption = e.what();
		sim_err(&err, exeption);
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int destroyAllWindows(char** err)
{
	try
	{
		cvDestroyAllWindows();
	}
	catch (Exception& e)
	{
		string exeption = e.what();
		sim_err(&err, exeption);
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int  bitwiseAND(void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{	
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int  bitwiseOR(void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int bitwiseNO(void* src, void** dst, char** err)
{
	if ((src == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int bitwiseXOR(void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int perElementAddWeighted(void* src1, double *alpha, void* src2, double* beta, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int perElementDIV(double scale, void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int perElementMUL(double scale, void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}


int perElementADDV(void* src1, float val, void** dst, char** err)
{
	if (src1 == 0)
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int perElementMULV(void* src1, float val, void** dst, char** err)
{
	if (src1 == 0)
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}

int matrixMUL(void* src1, void* src2, void** dst, char** err)
{
	if ((src1 == 0) || (src2 == 0))
	{
		string exeption = "Input data error";
		sim_err(&err, exeption);
		return RES_ERROR;
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
		return RES_ERROR;
	}

	string exeption = "0";
	sim_err(&err, exeption);
	return RES_OK;
}