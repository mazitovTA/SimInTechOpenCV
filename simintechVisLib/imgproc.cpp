
#include "pch.h"
#include "framework.h"
#include "imgproc.h"

int sim_convertColor(void* src, void** dst, int code)
{
	if (src == 0)
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
	cvtColor(((simMat*)src)->data, m->data, code);

	return RES_OK;
}

int sim_threshold(void* src, void** dst, double thresh, double maxval, int type)
{
	if (src == 0)
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

	threshold(((simMat*)src)->data, m->data, thresh, maxval, type);
	return RES_OK;
}

int sim_adaptiveThreshold(void* src, void** dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
{
	if (src == 0)
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

	adaptiveThreshold(((simMat*)src)->data, m->data, maxValue, adaptiveMethod, thresholdType, blockSize, C);

	return RES_OK;
}

int sim_merge(void* src1, void* src2, void* src3, void** dst)
{
	if ((src1 == 0) || (src2 == 0) || (src3 == 0))
	{
		return RES_ERROR;
	}

	vector<Mat> channels;
	channels.push_back(((simMat*)src1)->data);
	channels.push_back(((simMat*)src2)->data);
	channels.push_back(((simMat*)src3)->data);

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
	cv::merge(channels, m->data);

	return RES_OK;
}

int sim_split(void* src, void** dst1, void** dst2, void** dst3)
{
	if (src == 0)
	{
		return RES_ERROR;
	}
	Mat bgr[3];   //destination array

	simMat* ch1 = 0;
	if (*dst1 == 0)
	{
		ch1 = new simMat;
		*dst1 = ch1;
	}
	else
	{
		ch1 = (simMat*)* dst1;
	}

	simMat* ch2 = 0;
	if (*dst2 == 0)
	{
		ch2 = new simMat;
		*dst2 = ch2;
	}
	else
	{
		ch2 = (simMat*)* dst2;
	}

	simMat* ch3 = 0;
	if (*dst3 == 0)
	{
		ch3 = new simMat;
		*dst3 = ch3;
	}
	else
	{
		ch3 = (simMat*)* dst3;
	}

	split(((simMat*)src)->data, bgr);//split source 
	ch1->data = bgr[0];
	ch2->data = bgr[1];
	ch3->data = bgr[2];

	return RES_OK;
}

int sim_roi(void* src, void** dst, int x, int y, int w, int h)
{
	if (src == 0)
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

	m->data = ((simMat*)src)->data(Rect(x, y, w, h));

	return RES_OK;
}

int sim_inRange(void* src, void** dst, double low, double up)
{
	if (src == 0)
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

	int srcChannels = ((simMat*)src)->data.channels();
	if (srcChannels > 3)
	{
		return RES_ERROR;
	}

	Scalar lowB, upB;
	if (srcChannels == 1)
	{
		lowB = Scalar(low);
		upB = Scalar(up);
	}
	else if (srcChannels == 2)
	{
		lowB = Scalar(low, low);
		upB = Scalar(up, up);
	}
	else if (srcChannels == 3)
	{
		lowB = Scalar(low, low, low);
		upB = Scalar(up, up, up);
	}

	inRange(((simMat*)src)->data, lowB, upB, m->data);

	return RES_OK;
}

int sim_gaussianBlur(void* src, void** dst, int ksizeX, int ksizeY, double sigmaX, double sigmaY)
{
	if (src == 0)
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

	int kx;
	int	ky;
	ksizeX < 2 ? kx = 2 : kx = ksizeX;
	ksizeY < 2 ? ky = 2 : ky = ksizeY;

	GaussianBlur(((simMat*)src)->data, m->data, Size(kx, ky), sigmaX, sigmaY, BORDER_DEFAULT);
	return RES_OK;
}

int sim_bilateralFilter(void* src, void** dst, int d, double sigmaColor, double sigmaSpace)
{
	if (src == 0)
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

	bilateralFilter(((simMat*)src)->data, m->data, d, sigmaColor, sigmaSpace, BORDER_DEFAULT);

	return RES_OK;
}

int sim_boxFilter(void* src, void** dst, int ksizeX, int ksizeY, int anchorX, int anchorY, bool normalize)
{
	if (src == 0)
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

	ksizeX < 2 ? ksizeY = 2 : ksizeX;
	ksizeY < 2 ? ksizeY = 2 : ksizeY;
	boxFilter(((simMat*)src)->data, m->data, -1, Size(ksizeX, ksizeY), Point(anchorX, anchorY), normalize, BORDER_DEFAULT);

	return RES_OK;
}

int sim_blur(void* src, void** dst, int ksizeX, int ksizeY)
{
	if (src == 0)
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

	int kx;
	int	ky;
	ksizeX < 2 ? kx = 2 : kx = ksizeX;
	ksizeY < 2 ? ky = 2 : ky = ksizeY;

	blur(((simMat*)src)->data, m->data, Size(kx, ky), Point(-1, -1), BORDER_DEFAULT);

	return RES_OK;
}

int sim_filter2D(void* src, void** dst, int ksize, double* kernel, int anchorX, int anchorY, double delta)
{
	if (src == 0)
	{
		return RES_ERROR;
	}
	Mat kernel_ = Mat::ones(ksize, ksize, CV_32F);
	for (int i = 0; i < ksize * ksize; ++i)
	{
		kernel_.data[i] = kernel[i];
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

	int ddepth = CV_16S;
	filter2D(((simMat*)src)->data, m->data, ddepth, kernel_, Point(anchorX, anchorY), delta, BORDER_DEFAULT);

	return RES_OK;
}

int sim_sobel(void* src, void** dst, int dx, int dy, int ksize, double scale, double delta)
{
	if (src == 0)
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
	dx < 0 ? dx = 0 : dx;
	dy < 0 ? dy = 0 : dy;
	dx > 1 ? dx = 1 : dx;
	dy > 1 ? dy = 1 : dy;	
	if (dx + dx < 0)
	{
		dx = 1;
		dy = 0;
	}
	ksize < 3 ? ksize = 3 : ksize;
	int ddepth = CV_16S;
	Sobel(((simMat*)src)->data, m->data, ddepth, dx, dy, ksize, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(m->data, m->data);

	return RES_OK;
}

int sim_scharr(void* src, void** dst, int dx, int dy, double scale, double delta)
{
	if (src == 0)
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

	dx < 0 ? dx = 0 : dx;
	dy < 0 ? dy = 0 : dy;
	dx > 1 ? dx = 1 : dx;
	dy > 1 ? dy = 1 : dy;
	if (dx + dx < 0)
	{
		dx = 1;
		dy = 0;
	}
	int ddepth = CV_16S;
	Scharr(((simMat*)src)->data, m->data, ddepth, dx, dy, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(m->data, m->data);

	return RES_OK;
}

int sim_laplacian(void* src, void** dst, int ksize, double scale, double delta)
{
	if (src == 0)
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

	ksize < 3 ? ksize = 3 : ksize;
	int ddepth = CV_16S;
	Laplacian(((simMat*)src)->data, m->data, ddepth, ksize, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(m->data, m->data);

	return RES_OK;
}

int sim_canny(void* src, void** dst, double threshold1, double threshold2, int apertureSize, bool L2gradient)
{
	if (src == 0)
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

	if (apertureSize < 3) apertureSize = 3;
	else if (apertureSize > 7) apertureSize = 7;
	else if (apertureSize != 3 && apertureSize != 7) apertureSize = 5;
	Canny(((simMat*)src)->data, m->data, threshold1, threshold2, apertureSize, L2gradient);

	return RES_OK;
}

int sim_cornerHarris(void* src, void** dst, int blockSize, int ksize, double k)
{
	if (src == 0)
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

	cornerHarris(((simMat*)src)->data, m->data, blockSize, ksize, k, BORDER_DEFAULT);
	normalize(m->data, m->data, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(m->data, m->data);

	return RES_OK;
}

int sim_dilate(void* src, void** dst, int ksize, int kShape)
{
	if (src == 0)
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
	if (ksize < 1) ksize = 1;	
	Mat element = getStructuringElement(kShape,
		Size(2 * ksize + 1, 2 * ksize + 1),
		Point(ksize, ksize));
	dilate(((simMat*)src)->data, m->data, element);

	return RES_OK;
}

int sim_erode(void* src, void** dst, int ksize, int kShape)
{
	if (src == 0)
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

	if (ksize < 1) ksize = 1;
	Mat element = getStructuringElement(kShape,
		Size(2 * ksize + 1, 2 * ksize + 1),
		Point(ksize, ksize));
	erode(((simMat*)src)->data, m->data, element);

	return RES_OK;
}

int sim_resize(void* src, void** dst, int ksizeX, int ksizeY, int interpolation)
{
	if (src == 0)
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
	resize(((simMat*)src)->data, m->data, Size(ksizeX, ksizeY), 1, 1, interpolation);

	return RES_OK;
}


int sim_warpAffine(void* src, void** dst,
	double* M, int dsizeX, int dsizeY,
	int flags)
{
	if (src == 0)
	{
		return RES_ERROR;
	}

	Mat warp_matrix(2, 3, CV_32F);
	warp_matrix.data[0] = M[0];
	warp_matrix.data[1] = M[1];
	warp_matrix.data[2] = M[2];
	warp_matrix.data[3] = M[3];
	warp_matrix.data[4] = M[4];
	warp_matrix.data[5] = M[5];

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

	warpAffine(((simMat*)src)->data, m->data, warp_matrix, Size(dsizeX, dsizeY), flags, BORDER_CONSTANT);

	return RES_OK;
}

int sim_flip(void* src, void** dst, int code)
{
	if (src == 0)
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
	flip(((simMat*)src)->data, m->data, code);
	return RES_OK;
}

int sim_rotate(void* src, void** dst, int code)
{
	if (src == 0)
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
	rotate(((simMat*)src)->data, m->data, code);
	return RES_OK;
}

int sim_warpPerspective(void* src, void** dst, double* srcPts, double* dstPts, int dsizeY, int dsizeX)
{
	if (src == 0)
	{
		return RES_ERROR;
	}

	std::vector<cv::Point2f> prev;
	prev.push_back(cv::Point2f(srcPts[0], srcPts[1]));
	prev.push_back(cv::Point2f(srcPts[2], srcPts[3]));
	prev.push_back(cv::Point2f(srcPts[4], srcPts[5]));
	prev.push_back(cv::Point2f(srcPts[6], srcPts[7]));
	std::vector<cv::Point2f> post;
	post.push_back(cv::Point2f(dstPts[0], dstPts[1]));
	post.push_back(cv::Point2f(dstPts[2], dstPts[3]));
	post.push_back(cv::Point2f(dstPts[4], srcPts[5]));
	post.push_back(cv::Point2f(dstPts[6], dstPts[7]));

	cv::Mat warp_mat = getPerspectiveTransform(prev, post);
	//cv::Mat homography = cv::findHomography(prev, post);


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

	//warpPerspective(((simMat*)src)->data, m->data, homography, Size(dsizeX, dsizeY));
	warpPerspective(((simMat*)src)->data, m->data, warp_mat, Size(dsizeX, dsizeY), CV_INTER_LINEAR,	BORDER_CONSTANT, Scalar(0, 0, 0));

	return RES_OK;
}

int sim_floodFill(void* src, void** dst, int pX, int pY, int ch1, int ch2, int ch3)
{
	if (src == 0)
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
	m->data = ((simMat*)src)->data.clone();

	Scalar col;
	int srcChannels = ((simMat*)src)->data.channels();
	if (srcChannels == 1)
		col = Scalar(ch1);
	else if (srcChannels == 3)
		col = Scalar(ch1, ch2, ch3);
	else
		return RES_ERROR;
	floodFill(m->data, cv::Point(pX, pY), col);

	return RES_OK;
}

int sim_findContours(void* src, void** contours)
{
	if (src == 0)
	{
		return RES_ERROR;
	}

	if (((simMat*)src)->data.channels() != 1)
		return RES_ERROR;

	VectorVectorPoint* m = 0;
	if (*contours == 0)
	{
		m = new VectorVectorPoint;
		*contours = m;
	}
	else
	{
		m = (VectorVectorPoint*)* contours;
	}

	vector<Vec4i> hierarchy;
	findContours(((simMat*)src)->data, m->data, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	return RES_OK;
}

// if index  =  -1 draw all contours
int sim_selectContour(void* srcImage, void* contours, int index, int red, int green,  int blue, int width, void** dstItmage, void** result)
{
	//*dstItmage = srcImage;
	//*result = contours;
	//return RES_OK;

	//index = 6;

	if ((contours == 0) || (srcImage == 0))
	{
		return RES_ERROR;
	}


	VectorVectorPoint* input_countours = 0;
	input_countours = (VectorVectorPoint*)contours;
	int s = input_countours->data.size();

	if ((index >= s) || (index < -1))
	{
		return RES_ERROR;
	}

	VectorVectorPoint* res_countours = 0;
	if (*result == 0)
	{
		res_countours = new VectorVectorPoint;
		*result = res_countours;
	}
	else
	{
		res_countours = (VectorVectorPoint*)* result;
	}

	if (index == -1)
	{
		res_countours->data = input_countours->data;
	}
	else
	{
		res_countours->data.clear();
		res_countours->data.push_back(input_countours->data[index]);
	}
	
	//*dstItmage = srcImage;
	   
	simMat* outFrame = 0;
	if (*dstItmage == 0)
	{
		outFrame = new simMat;
		*dstItmage = outFrame;
	}
	else
	{
		outFrame = (simMat*)* dstItmage;
	}

	outFrame->data = ((simMat*)srcImage)->data.clone();

	if (outFrame->data.channels() == 1)
	{
		cvtColor(outFrame->data, outFrame->data, COLOR_GRAY2BGR);
	}
		
	for (int i = 0; i < res_countours->data.size(); i++)
	{
		drawContours(outFrame->data, res_countours->data, i, cv::Scalar(blue, green, red), width);
	}		
		
	return RES_OK;
}

int sim_minMaxAreaContoursFilter(void* src, void** dst, double* min, double* max)
{
	if (src == 0)
	{
		return RES_ERROR;
	}

	VectorVectorPoint* input_countours = 0;
	input_countours = (VectorVectorPoint*)dst;

	VectorVectorPoint* res_countours = 0;
	if (*dst == 0)
	{
		res_countours = new VectorVectorPoint;
		*dst = res_countours;
	}
	else
	{
		res_countours = (VectorVectorPoint*)* dst;
	}

	res_countours->data.clear();

	//(VectorVectorPoint*)contours
	for (int i = 0; i < ((VectorVectorPoint*)src)->data.size(); i++)
	{

		float area = contourArea(((VectorVectorPoint*)src)->data[i]);
		if ((area > * min) && (area < *max))
		{
			res_countours->data.push_back(((VectorVectorPoint*)src)->data[i]);
		}
	}

	return RES_OK;
}


int sim_countContours(void* contours, int* count)
{
	if (contours == 0)
	{
		*count = 0;
		return RES_OK;
	}

	VectorVectorPoint* input_countours = 0;
	input_countours = (VectorVectorPoint*)contours;
	int s = input_countours->data.size();
	*count = s;

	return RES_OK;
}