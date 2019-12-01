
#define EXPORT extern "C" __declspec(dllexport)

#include <stdio.h>
#include <windows.h>
#include <string>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/calib3d/calib3d.hpp"

using namespace cv;
using namespace std;

struct simMat
{
	Mat data;

	~simMat()
	{
		data.release();
	}
};

enum f_result
{
	RES_ERROR = -1, 
	RES_OK = 0
};

EXPORT void sim_err(char*** err, string& e);

EXPORT void* createHandledWindow(char name[]);
EXPORT void* getWindowHandle(char name[]);

EXPORT int releaseSimMat(void** data);

/*
Open image from file
codes
	IMREAD_GRAYSCALE = 0,  //!< If set, always convert image to the single channel grayscale image (codec internal conversion).
	IMREAD_COLOR = 1,  //!< If set, always convert image to the 3 channel BGR color image.
*/
EXPORT int openImage(void** frame, char name[], int code, char** err);
EXPORT int showFrame(void* source, int delay, char name[], char** err);
EXPORT int openVideoSource(void** source, char address[], char** err);
EXPORT int retrieveImage(void* source, void** frame, char** err);
EXPORT int releaseSourse(void* source, char** err);
EXPORT int destroyWindowByName(char name[], char** err);
EXPORT int destroyAllWindows(char** err);

//// Perelement operations
EXPORT int bitwiseAND(void* src1, void* src2, void** dst, char** err);
EXPORT int bitwiseOR(void* src1, void* src2, void** dst, char** err);
EXPORT int bitwiseNO(void* src, void** dst, char** err);
EXPORT int bitwiseXOR(void* src1, void* src2, void** dst, char** err);

EXPORT int perElementAddWeighted(void* src1, double* alpha, void* src2, double* beta, void** dst, char** err);
EXPORT int perElementDIV(double scale, void* src1, void* src2, void** dst, char** err);
EXPORT int perElementMUL(double scale, void* src1, void* src2, void** dst, char** err);

EXPORT int perElementADDV(void* src1, float val, void** dst, char** err);
EXPORT int perElementMULV(void* src1, float val, void** dst, char** err);

//// Matrix operations
EXPORT int matrixMUL(void* src1, void* src2, void** dst, char** err);

