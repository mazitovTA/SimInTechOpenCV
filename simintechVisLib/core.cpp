
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

int fidnCalibrationPoints(void** image_points, void** object_points, void* image, int numCornersHor, int numCornersVer)
{
	if (image == 0)
	{
		return RES_ERROR;
	}

	VectorVectorPoint2f* im_points = 0;
	{
		im_points = new VectorVectorPoint2f;
	}
	if (*image_points != 0)
	{
		for (int i = 0; i < ((VectorVectorPoint2f*)* image_points)->data.size(); i++)
			im_points->data.push_back(((VectorVectorPoint2f*)* image_points)->data[i]);
	}
	*image_points = im_points;

	VectorVectorPoint3f* obj_points = 0;
	{
		obj_points = new VectorVectorPoint3f;
	}
	if (*object_points != 0)
	{
		for (int i = 0; i < ((VectorVectorPoint3f*)* object_points)->data.size(); i++)
			obj_points->data.push_back(((VectorVectorPoint3f*)* object_points)->data[i]);
	}
	*object_points = obj_points;


	Size board_sz = Size(numCornersHor, numCornersVer);
	int numSquares = numCornersHor * numCornersVer;
	vector<Point3f> obj;
	for (int j = 0; j < numSquares; j++)
		obj.push_back(Point3d(j / numCornersHor, j % numCornersHor, 0.0f));

	Mat gray_image;
	vector<Point2f> corners;

	cvtColor(((simMat*)image)->data, gray_image, CV_BGR2GRAY);
	bool found = findChessboardCorners(((simMat*)image)->data, board_sz, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
	if (found)
	{
		cornerSubPix(gray_image, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
		drawChessboardCorners(((simMat*)image)->data, board_sz, corners, found);
		im_points->data.push_back(corners);
		obj_points->data.push_back(obj);
	}
	return RES_OK;
}

int sim_undistort(void* image, void** imageUndistorted, void* intrinsic, void* distCoeffs)
{
	if (image == 0)
	{
		return RES_ERROR;
	}

	simMat* u_im = 0;
	if (*imageUndistorted == 0)
	{
		u_im = new simMat;
		*imageUndistorted = u_im;
	}
	else
	{
		u_im = (simMat*)* imageUndistorted;
	}

	simMat* intrinsicCoefficients = 0;
	if (intrinsic == 0)
	{
		return RES_ERROR;
	}
	else
	{
		intrinsicCoefficients = (simMat*)intrinsic;
	}

	simMat* distCoeffsCoefficients = 0;
	if (distCoeffs == 0)
	{
		return RES_ERROR;
	}
	else
	{
		distCoeffsCoefficients = (simMat*)distCoeffs;
	}

	undistort(((simMat*)image)->data, u_im->data, intrinsicCoefficients->data, distCoeffsCoefficients->data);
	return RES_OK;
}

int sim_calibrateCamera(void* image_points, void* object_points, void* image, void** intrinsic, void** distCoeffs)
{
	if (image == 0)
	{
		return RES_ERROR;
	}

	VectorVectorPoint2f* im_points = 0;
	if (image_points == 0)
	{
		return RES_ERROR;
	}
	else
	{
		im_points = (VectorVectorPoint2f*)image_points;
	}

	VectorVectorPoint3f* obj_points = 0;
	if (object_points == 0)
	{
		return RES_ERROR;
	}
	else
	{
		obj_points = (VectorVectorPoint3f*)object_points;
	}

	simMat* intrinsicCoefficients = 0;
	if (*intrinsic == 0)
	{
		intrinsicCoefficients = new simMat;
		*intrinsic = intrinsicCoefficients;
	}
	else
	{
		intrinsicCoefficients = (simMat*)* intrinsic;
	}

	simMat* distCoeffsCoefficients = 0;
	if (*distCoeffs == 0)
	{
		distCoeffsCoefficients = new simMat;
		*distCoeffs = distCoeffsCoefficients;
	}
	else
	{
		distCoeffsCoefficients = (simMat*)* distCoeffs;
	}

	intrinsicCoefficients->data = cv::Mat(3, 3, CV_32FC1);

	vector<Mat> rvecs;
	vector<Mat> tvecs;
	intrinsicCoefficients->data.ptr<float>(0)[0] = 1;
	intrinsicCoefficients->data.ptr<float>(1)[1] = 1;

	cv::calibrateCamera(obj_points->data,
		im_points->data,
		((simMat*)image)->data.size(),
		intrinsicCoefficients->data,
		distCoeffsCoefficients->data,
		rvecs,
		tvecs);
	return RES_OK;
}

int sim_saveCalibrationParameters(char name[], void* intrinsic, void* distCoeffs)
{
	simMat* intrinsic_ = 0;
	if (intrinsic == 0)
	{
		return RES_ERROR;
	}
	else
	{
		intrinsic_ = (simMat*)intrinsic;
	}

	simMat* distCoeffs_ = 0;
	if (distCoeffs == 0)
	{
		return RES_ERROR;
	}
	else
	{
		distCoeffs_ = (simMat*)distCoeffs;
	}

	FileStorage fs(name, FileStorage::WRITE);
	fs << "intrinsic" << intrinsic_->data;
	fs << "distCoeffs" << distCoeffs_->data;
	fs.release();

	return RES_OK;
}

int sim_loadCalibrationParameters(char name[], void** intrinsic, void** distCoeffs)
{
	simMat* intrinsic_ = 0;
	intrinsic_ = new simMat;
	*intrinsic = intrinsic_;

	simMat* distCoeffs_ = 0;
	distCoeffs_ = new simMat;
	*distCoeffs = distCoeffs_;

	cv::FileStorage fs2(name, cv::FileStorage::READ);
	fs2["intrinsic"] >> intrinsic_->data;
	fs2["distCoeffs"] >> distCoeffs_->data;

	return RES_OK;
}
