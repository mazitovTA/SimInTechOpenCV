
#define EXPORT extern "C" __declspec(dllexport)

#include <stdio.h>
#include <windows.h>
#include <string>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

EXPORT  int openImage(void** frame, char name[]);
EXPORT  int showFrame(void* source, int delay, char name[]);

EXPORT  int  openVideoSource(void** source, char address[], void** frame);
EXPORT  int  retrieveImage(void* source, void* frame);

EXPORT  int  releaseSourse(void* source);
EXPORT  int  releaseFrame(void* source);

EXPORT int  copyFrame(void* src, void** dst);
EXPORT int  convertColor(void* src, void** dst, int code);

EXPORT void* createHandledWindow(char name[]);
EXPORT void* getWindowHandle(char name[]);
EXPORT int destroyWindowByName(char name[]);
EXPORT int destroyAllWindows();

EXPORT cv::Mat test();
EXPORT void test1(Mat& im);