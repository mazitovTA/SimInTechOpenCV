
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


EXPORT void* createHandledWindow(char name[]);
EXPORT void* getWindowHandle(char name[]);

EXPORT int releaseSimMat(void** data);

/*
Open image from file
codes
	IMREAD_GRAYSCALE = 0,  //!< If set, always convert image to the single channel grayscale image (codec internal conversion).
	IMREAD_COLOR = 1,  //!< If set, always convert image to the 3 channel BGR color image.
*/
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
