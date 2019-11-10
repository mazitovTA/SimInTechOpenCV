#define EXPORT extern "C" __declspec(dllexport)

#include "core.h"

using namespace cv;
using namespace std;

//// Functions
EXPORT string sim_convertColor(void* src, void** dst, int code);

EXPORT string sim_threshold(void* src, void** dst, double thresh, double maxval, int type);
EXPORT string sim_adaptiveThreshold(void* src, void** dst, double maxValue, int adaptiveMethod,
	int thresholdType, int blockSize, double C);

EXPORT string sim_merge(void* src1, void* src2, void* src3, void** dst);
EXPORT string sim_split(void* src1, void** dst1, void** dst2, void** dst3);
EXPORT string sim_roi(void* src, void** dst, int x, int y, int w, int h);

// TODO
//EXPORT string inRange(void* src, void** dst, void* params);

EXPORT string sim_gaussianBlur(void* src, void** dst, int ksizeX, int ksizeY, double sigmaX, double sigmaY);

EXPORT string sim_bilateralFilter(void* src, void** dst, int d,	double sigmaColor, double sigmaSpace);


EXPORT string sim_boxFilter(void* src, void** dst, int ddepth,
	int ksizeX, int ksizeY, int anchorX = -1, int anchorY = -1,
	bool normalize = true);

EXPORT string sim_blur(void* src, void** dst,
	int ksizeX, int ksizeY, int anchorX = -1, int anchorY = -1);

// TODO
/*
EXPORT string sim_filter2D(void* src, void** dst, int ddepth,
	int ksize, double *kernel, int anchorX = -1, int anchorY = -1,
	double delta = 0);
*/

EXPORT string sim_sobel(void* src, void** dst, int ddepth,
	int dx, int dy, int ksize = 3,
	double scale = 1, double delta = 0);

EXPORT string sim_scharr(void* src, void** dst, int ddepth,
	int dx, int dy, double scale = 1, double delta = 0);

EXPORT string sim_laplacian(void* src, void** dst, int ddepth,
	int ksize = 1, double scale = 1, double delta = 0);


EXPORT string sim_canny(void* src, void** dst, double threshold1, double threshold2,
	int apertureSize = 3, bool L2gradient = false);

EXPORT string sim_cornerHarris(void* src, void** dst, int blockSize,
	int ksize, double k);

EXPORT string sim_dilate(void* src, void** dst, int blockSize, int ksize, int kShape);
EXPORT string sim_erode(void* src, void** dst, int blockSize, int ksize, int kShape);

EXPORT string sim_resizeP(void* src, void** dst, int ksizeX, int ksizeY, double fx = 0, double fy = 0,
	int interpolation = INTER_LINEAR);
EXPORT string sim_resize(void* src, void** dst, int ksizeX, int ksizeY);


// TODO
/*
CV_EXPORTS_W void resize(InputArray src, OutputArray dst,
	Size dsize, double fx = 0, double fy = 0,
	int interpolation = INTER_LINEAR);*/


/*
CV_EXPORTS_W void warpAffine(InputArray src, OutputArray dst,
	InputArray M, Size dsize,
	int flags = INTER_LINEAR,
	int borderMode = BORDER_CONSTANT,
	const Scalar& borderValue = Scalar());*/

/*
CV_EXPORTS_W void warpPerspective(InputArray src, OutputArray dst,
	InputArray M, Size dsize,
	int flags = INTER_LINEAR,
	int borderMode = BORDER_CONSTANT,
	const Scalar& borderValue = Scalar());*/

/*
CV_EXPORTS_W void watershed(InputArray image, InputOutputArray markers);*/

/*
CV_EXPORTS_W void grabCut(InputArray img, InputOutputArray mask, Rect rect,
	InputOutputArray bgdModel, InputOutputArray fgdModel,
	int iterCount, int mode = GC_EVAL);*/

/*
CV_EXPORTS_W void distanceTransform(InputArray src, OutputArray dst,
	int distanceType, int maskSize, int dstType = CV_32F);
*/

/*
CV_EXPORTS int floodFill(InputOutputArray image,
	Point seedPoint, Scalar newVal, CV_OUT Rect* rect = 0,
	Scalar loDiff = Scalar(), Scalar upDiff = Scalar(),
	int flags = 4);
*/