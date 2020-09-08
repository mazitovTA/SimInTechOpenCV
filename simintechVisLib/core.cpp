
#include <iostream>

#include "pch.h"
#include "framework.h"

#include "core.h"
#include <fstream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

bool is_file_exist(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}


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
	//m->data = imread(name, code);
	m->data = imread(name, code);/*
	if (!m->data.data)
		return RES_ERROR;*/

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
	{
		releaseSimMat(frame);
		return RES_ERROR;
	}
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

int sim_fidnCalibrationPoints(void** image_points, void** object_points, void* image, void** dst,
	int numCornersHor, int numCornersVer)
{
	
	if (image == 0)
	{
		return RES_ERROR;
	}


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
	   
	m->data = ((simMat*)image)->data.clone();	
	
	VectorVectorPoint2f* im_points = 0;
	if (*image_points == 0)
	{
		*image_points = new VectorVectorPoint2f;
	}
	im_points = (VectorVectorPoint2f*)* image_points;

	VectorVectorPoint3f* obj_points = 0;
	if (*object_points == 0)
	{
		*object_points = new VectorVectorPoint3f;
	}
	obj_points = (VectorVectorPoint3f*)* object_points;

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
		drawChessboardCorners(m->data, board_sz, corners, found);
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
	if(!is_file_exist(name))
		return RES_ERROR;

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

int um_init(void** server_socket, void** client_socket, void** frame, int port)
{
	WSADATA wsa;
	SOCKET* s = new SOCKET;
	*server_socket = s;
	SOCKET* new_socket = new SOCKET;
	*client_socket = new_socket;
	struct sockaddr_in server, client;
	int c;
	camera_info camera;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return RES_ERROR;
	}

	//Create a socket
	if ((*s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		return RES_ERROR;
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);


	//в неблокирующий режим 
	unsigned long block = 1;
	int res = ioctlsocket(*s, FIONBIO, &block);
	WSAGetLastError();

	//Bind
	int iResult = 0;
	iResult = ::bind(*s, (struct sockaddr*) & server, sizeof(server));
	if (iResult == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		return RES_ERROR;
	}

	listen(*s, 3);

	c = sizeof(struct sockaddr_in);
	for (int i = 0; i < 11; i++)
	{
		*new_socket = accept(*s, (struct sockaddr*) & client, &c);
		if (*new_socket == INVALID_SOCKET)
		{
			printf("accept failed with error code : %d \n", WSAGetLastError());
			Sleep(1000);
			if (i == 10)
				return RES_ERROR;
		}
		else
		{
			break;
		}
	}

	//назад в блокирующий режим
	block = 0;
	res = ioctlsocket(*new_socket, FIONBIO, &block);

	const int info_buf_size = 84;
	char info_buf[info_buf_size];
	int retval;
	{
		retval = recv(*new_socket, info_buf, info_buf_size, MSG_WAITALL);
		for (int i = 0; i < info_buf_size; i += 4)
		{
			int* var = (int*)(&info_buf[i]);
			*var = ntohl(*var);
		}
		memcpy(&camera, &info_buf[0], 84);
	}
	int image_buf_size = camera.ImageResolution_x * camera.ImageResolution_y * 3;
	char* image_buf = new char[image_buf_size];

	{
		retval = recv(*new_socket, info_buf, info_buf_size, MSG_WAITALL);
		for (int i = 0; i < info_buf_size; i += 4)
		{
			int* var = (int*)(&info_buf[i]);
			*var = ntohl(*var);
		}
	}
	
	simMat* m = 0;
	m = new simMat;
	*frame = m;

	if (camera.Colors == 1)
		m->data = cv::Mat(camera.ImageResolution_y, camera.ImageResolution_x, CV_8UC3, cv::Scalar(255, 0, 0));
	else if (camera.Colors == 0)
		m->data = cv::Mat(camera.ImageResolution_y, camera.ImageResolution_x, CV_8UC1, cv::Scalar(255, 0, 0));

	return RES_OK;

}

int um_get_frame(void* socket, void* frame)
{
	SOCKET* s = (SOCKET*)socket;
	cv::Mat img = ((simMat*)frame)->data;
	int size = img.cols * img.rows * img.channels();
	int retval = recv(*s, (char*)img.data, size, MSG_WAITALL);
	if (retval == 0)
		return RES_ERROR;
	cv::flip(img, img, 0);
	return RES_OK;
}

void um_release_socket(void* socket)
{
	SOCKET* s = (SOCKET*)socket;
	closesocket(*s);
	WSACleanup();
}