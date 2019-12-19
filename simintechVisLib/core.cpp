
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

int openImage(void** frame, char name[], int code)
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
	if (!m->data.data)
		return RES_ERROR;

	return RES_OK;
}

int showFrame(void* source, int delay, char name[])
{
	if ((source == 0) || (!((simMat*)source)->data.data))
		return RES_ERROR;
	void* pt = cvGetWindowHandle(name);
	if (pt == 0)
		namedWindow(name, WINDOW_NORMAL);
	imshow(name, ((simMat*)source)->data);
	waitKey(delay);

	return RES_OK;
}

int openVideoSource(void** source, char address[])
{
	VideoCapture* cam = new VideoCapture;
	*source = cam;

	bool res = false;
	if (isNumber(string(address)))
		res = cam->open(std::stoi(address));
	else
		res = cam->open(address);
	if (!res)
		return RES_ERROR;

	return RES_OK;
}


int retrieveImage(void* source, void** frame)
{
	VideoCapture* cam = (VideoCapture*)source;
	if (!cam->isOpened() || source == 0)
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
	if (!m->data.data)
		return RES_ERROR;
	return RES_OK;
}

int releaseSourse(void* source)
{
	VideoCapture* cam = (VideoCapture*)source;
	if (cam == 0)
		return RES_ERROR;
	cam->release();
	return RES_OK;
}


int destroyWindowByName(char name[])
{
	cvDestroyWindow(name);
	return RES_OK;
}

int destroyAllWindows()
{
	cvDestroyAllWindows();
	return RES_OK;
}

int  bitwiseAND(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src2 == 0) || (!((simMat*)src1)->data.data) || (!((simMat*)src2)->data.data))
		return RES_ERROR;

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
	return RES_OK;
}

int  bitwiseOR(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src2 == 0) || (!((simMat*)src1)->data.data) || (!((simMat*)src2)->data.data))
		return RES_ERROR;
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
	return RES_OK;
}

int bitwiseNO(void* src, void** dst)
{
	if ((src == 0) || (!((simMat*)src)->data.data))
		return RES_ERROR;

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
	return RES_OK;
}

int bitwiseXOR(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src2 == 0) || (!((simMat*)src1)->data.data) || (!((simMat*)src2)->data.data))
		return RES_ERROR;

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
	return RES_OK;
}

int perElementAddWeighted(void* src1, double alpha, void* src2, double beta, void** dst)
{
	if ((src1 == 0) || (src2 == 0) || (!((simMat*)src1)->data.data) || (!((simMat*)src2)->data.data))
		return RES_ERROR;

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
	addWeighted(((simMat*)src1)->data, alpha, ((simMat*)src2)->data, beta, 0, m->data);
	return RES_OK;
}

int absDiff(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src2 == 0) || (!((simMat*)src1)->data.data) || (!((simMat*)src2)->data.data))
		return RES_ERROR;

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

	absdiff(((simMat*)src1)->data, ((simMat*)src2)->data, m->data);
	return RES_OK;
}

int perElementMUL(double scale, void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src2 == 0) || (!((simMat*)src1)->data.data) || (!((simMat*)src2)->data.data))
		return RES_ERROR;

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

	return RES_OK;
}

int perElementADD(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src2 == 0) || (!((simMat*)src1)->data.data) || (!((simMat*)src2)->data.data))
		return RES_ERROR;

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

	add(((simMat*)src1)->data, ((simMat*)src2)->data, m->data);

	return RES_OK;
}

int perElementADDV(void* src, double val, void** dst)
{
	if ((src == 0) || (!((simMat*)src)->data.data))
		return RES_ERROR;
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
	m->data = ((simMat*)src)->data + val;

	return RES_OK;
}

int perElementMULV(void* src, double val, void** dst)
{
	if ((src == 0) || (!((simMat*)src)->data.data))
		return RES_ERROR;

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
	m->data = ((simMat*)src)->data * val;

	return RES_OK;
}

int matrixMUL(void* src1, void* src2, void** dst)
{
	if ((src1 == 0) || (src2 == 0) || (!((simMat*)src1)->data.data) || (!((simMat*)src2)->data.data))
		return RES_ERROR;

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
	return RES_OK;
}

