
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

EXPORT  void releaseSimMat(void** data);

EXPORT string openImage(void** frame, char name[], int code);
/*
Open image from file
codes
	IMREAD_GRAYSCALE = 0,  //!< If set, always convert image to the single channel grayscale image (codec internal conversion).
	IMREAD_COLOR = 1,  //!< If set, always convert image to the 3 channel BGR color image.
*/
EXPORT  string showFrame(void* source, int delay, char name[]);

EXPORT  string  openVideoSource(void** source, char address[]);
EXPORT  string  retrieveImage(void* source, void** frame);

EXPORT  int  releaseSourse(void* source);

EXPORT void* createHandledWindow(char name[]);
EXPORT void* getWindowHandle(char name[]);
EXPORT int destroyWindowByName(char name[]);
EXPORT int destroyAllWindows();


//// Perelement operations
EXPORT string bitwiseAND(void* src1, void* src2, void** dst);
EXPORT string bitwiseOR(void* src1, void* src2, void** dst);
EXPORT string bitwiseNO(void* src1, void* src2, void** dst);
EXPORT string bitwiseXOR(void* src1, void* src2, void** dst);

EXPORT string perElementAddWeighted(void* src1, double* alpha, void* src2, double* beta, void** dst);
EXPORT string perElementDIV(double scale, void* src1, void* src2, void** dst);
EXPORT string perElementMUL(double scale, void* src1, void* src2, void** dst);

// TODO
//
EXPORT string perElementADDV(void* src1, float val, void** dst);
EXPORT string perElementMULV(void* src1, float val, void** dst);

//// Matrix operations
EXPORT string matrixMUL(void* src1, void* src2, void** dst);

