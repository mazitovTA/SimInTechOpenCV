
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

EXPORT  void sim_err(char*** err, string& e);

EXPORT void* createHandledWindow(char name[]);
EXPORT void* getWindowHandle(char name[]);
EXPORT void releaseSimMat(void** data);


/*
Open image from file
codes
	IMREAD_GRAYSCALE = 0,  //!< If set, always convert image to the single channel grayscale image (codec internal conversion).
	IMREAD_COLOR = 1,  //!< If set, always convert image to the 3 channel BGR color image.
*/
EXPORT void openImage(void** frame, char name[], int code, char** err);
EXPORT void showFrame(void* source, int delay, char name[], char** err);
EXPORT void openVideoSource(void** source, char address[], char** err);
EXPORT void retrieveImage(void* source, void** frame, char** err);
EXPORT void releaseSourse(void* source, char** err);
EXPORT void destroyWindowByName(char name[], char** err);
EXPORT void destroyAllWindows(char** err);

//// Perelement operations
EXPORT void bitwiseAND(void* src1, void* src2, void** dst, char** err);
EXPORT void bitwiseOR(void* src1, void* src2, void** dst, char** err);
EXPORT void bitwiseNO(void* src, void** dst, char** err);
EXPORT void bitwiseXOR(void* src1, void* src2, void** dst, char** err);

EXPORT void perElementAddWeighted(void* src1, double* alpha, void* src2, double* beta, void** dst, char** err);
EXPORT void perElementDIV(double scale, void* src1, void* src2, void** dst, char** err);
EXPORT void perElementMUL(double scale, void* src1, void* src2, void** dst, char** err);

EXPORT void perElementADDV(void* src1, float val, void** dst, char** err);
EXPORT void perElementMULV(void* src1, float val, void** dst, char** err);

//// Matrix operations
EXPORT void matrixMUL(void* src1, void* src2, void** dst, char** err);

