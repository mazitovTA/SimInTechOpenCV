#define EXPORT extern "C" __declspec(dllexport)

#include "core.h"

using namespace cv;
using namespace std;


EXPORT int sim_detectLanes(void* binaryinput, int numHorHist, int roi_w, int wheel_h, int* rd, int* ld, void* drawinput);
EXPORT int sim_findSign(void* templFrame, void* templContour, void* frame, void* contours,
	int normalizedContourSizeX,
	int normalizedContourSizeY,
	int useHull,
	int draw,
	double minCorrelation,
	int* numFound);

//// Functions

//EXPORT int sim_convertColor(void* src, void** dst, int code);