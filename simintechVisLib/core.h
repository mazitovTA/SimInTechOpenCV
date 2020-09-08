
#define EXPORT extern "C" __declspec(dllexport)


#include <winsock2.h>  
#include <stdio.h>
#include <windows.h>
#include <string>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>


#pragma comment(lib,"ws2_32.lib") 

using namespace cv;
using namespace std;

struct camera_info
{
	int CameraPosition_x, CameraPosition_y, CameraPosition_z;
	int CarBodySize_x, CarBodySize_y, CarBodySize_z;
	int FrameRate;
	int Channels;
	int Colors;
	int seR, seG, seB;
	int StereoBase;
	int FocalLength;
	int SensorType;
	int SensorSize_x, SensorSize_y;
	int ImageResolution_x, ImageResolution_y;
	int FieldOfViewDeg_x, FieldOfViewDeg_y;
};

struct simMat
{
	Mat data;

	~simMat()
	{
		data.release();
	}
};

struct VectorMat {
	std::vector<Mat> data;
	~VectorMat()
	{
		data.clear();
	}
};

struct VectorPoint {
	std::vector<cv::Point> data;
	~VectorPoint()
	{
		data.clear();
	}
};

struct VectorPoint2f {
	std::vector<cv::Point> data;
	~VectorPoint2f()
	{
		data.clear();
	}
};

struct VectorVectorPoint {
	std::vector < std::vector<cv::Point>> data;
	~VectorVectorPoint()
	{
		data.clear();
	}
}; 

struct VectorVectorPoint2f {
	std::vector < std::vector<cv::Point2f>> data;
	~VectorVectorPoint2f()
	{
		data.clear();
	}
};

struct VectorVectorPoint3f {
	std::vector< std::vector<cv::Point3f>> data;
	~VectorVectorPoint3f()
	{
		data.clear();
	}
};
enum f_result
{
	RES_ERROR = -1, 
	RES_OK = 0
};

EXPORT void* createHandledWindow(char name[]);
EXPORT void* getWindowHandle(char name[]);

EXPORT int releaseSimMat(void** data);

EXPORT int openImage(void** frame, char name[], int code);
EXPORT int showFrame(void* source, int delay, char name[]);
EXPORT int openVideoSource(void** source, char address[]);
EXPORT int retrieveImage(void* source, void** frame);
EXPORT int releaseSourse(void* source);
EXPORT int destroyWindowByName(char name[]);
EXPORT int destroyAllWindows();

//// Perelement operations
EXPORT int bitwiseAND(void* src1, void* src2, void** dst);
EXPORT int bitwiseOR(void* src1, void* src2, void** dst);
EXPORT int bitwiseNO(void* src, void** dst);
EXPORT int bitwiseXOR(void* src1, void* src2, void** dst);

EXPORT int perElementAddWeighted(void* src1, double alpha, void* src2, double beta, void** dst);
EXPORT int perElementMUL(double scale, void* src1, void* src2, void** dst);

EXPORT int absDiff(void* src1, void* src2, void** dst);

EXPORT int perElementADD(void* src1, void* src2, void** dst);
EXPORT int perElementADDV(void* src1, double val, void** dst);
EXPORT int perElementMULV(void* src1, double val, void** dst);

//// Matrix operations
EXPORT int matrixMUL(void* src1, void* src2, void** dst);

//// Camera calibration functions
EXPORT int sim_fidnCalibrationPoints(void** image_points, void** object_points, void* image, void** dst,
	int numCornersHor, int numCornersVer);
EXPORT int sim_undistort(void* image, void** imageUndistorted, void* intrinsic, void* distCoeffs);
EXPORT int sim_calibrateCamera(void* image_points, void* object_points, void* image, void** intrinsic, void** distCoeffs);
EXPORT int sim_saveCalibrationParameters(char name[], void* intrinsic, void* distCoeffs);
EXPORT int sim_loadCalibrationParameters(char name[], void** intrinsic, void** distCoeffs);

EXPORT int um_init(void** server_socket, void** client_socket, void** frame, int port);
EXPORT int um_get_frame(void* socket, void* frame);
EXPORT void um_release_socket(void* socket);
