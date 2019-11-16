
#include "pch.h"
#include "framework.h"
#include "imgproc.h"

EXPORT string sim_convertColor(void* src, void** dst, int code) {
	if (src == 0)
		return "Input data error";

	try
	{
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

	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";

}

string sim_threshold(void* src, void** dst, double thresh, double maxval, int type)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_adaptiveThreshold(void* src, void** dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_merge(void* src1, void* src2, void* src3, void** dst)
{
	if ((src1 == 0) || (src2 == 0) || (src3 == 0))
		return "Input data error";
	try
	{
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
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_split(void* src, void** dst1, void** dst2, void** dst3)
{
	if (src == 0)
		return "Input data error";
	try
	{

		Mat bgr[3];   //destination array
		split(((simMat*)src)->data, bgr);//split source 
		simMat* ch1 = 0;
		simMat* ch2 = 0;
		simMat* ch3 = 0;

		if (*dst1 == 0) { ch1 = new simMat; }
		if (*dst2 == 0) { ch2 = new simMat; }
		if (*dst3 == 0) { ch3 = new simMat; }

		ch1->data = bgr[0];
		ch2->data = bgr[1];
		ch3->data = bgr[2];

		*dst1 = ch1;
		*dst2 = ch2;
		*dst3 = ch3;
	}
	catch (Exception& e)
	{
		releaseSimMat(dst1);
		releaseSimMat(dst2);
		releaseSimMat(dst3);
		return e.what();
	}
	return "0";
}

string sim_roi(void* src, void** dst, int x, int y, int w, int h)
{
	if (src == 0)
		return "Input data error";

	try
	{
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
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_inRange(void* src, void** dst, float* low, float* up)
{
	if (src == 0)
		return "Input data error";

	try
	{
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
			return "0";

		Scalar low, up;
		if (srcChannels == 1)
		{
			low = Scalar(low[0]);
			low = Scalar(up[0]);
		}
		else if (srcChannels == 2)
		{
			low = Scalar(low[0], low[1]);
			low = Scalar(up[0], up[1]);
		}
		else if (srcChannels == 3)
		{
			low = Scalar(low[0], low[1], low[2]);
			low = Scalar(up[0], up[1], up[2]);
		}
		else
			return "0";

		inRange(((simMat*)src)->data, low, up, m->data);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_gaussianBlur(void* src, void** dst, int ksizeX, int ksizeY, double sigmaX, double sigmaY)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

		GaussianBlur(((simMat*)src)->data, m->data, Size(ksizeX, ksizeY), sigmaX, sigmaY, BORDER_DEFAULT);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_bilateralFilter(void* src, void** dst, int d, double sigmaColor, double sigmaSpace)
{
	if (src == 0)
		return "Input data error";

	try
	{
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
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}
string sim_boxFilter(void* src, void** dst, int ddepth, int ksizeX, int ksizeY, int anchorX, int anchorY, bool normalize)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

		boxFilter(((simMat*)src)->data, m->data, ddepth, Size(ksizeX, ksizeY), Point(anchorX, anchorY), normalize, BORDER_DEFAULT);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_blur(void* src, void** dst, int ksizeX, int ksizeY, int anchorX, int anchorY)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

		blur(((simMat*)src)->data, m->data, Size(ksizeX, ksizeY), Point(anchorX, anchorY), BORDER_DEFAULT);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_filter2D(void* src, void** dst, int ddepth, int ksize, float* kernel, int anchorX, int anchorY, double delta)
{
	if (src == 0)
		return "Input data error";
	try
	{
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

		filter2D(((simMat*)src)->data, m->data, ddepth, kernel_, Point(anchorX, anchorY), delta, BORDER_DEFAULT);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_sobel(void* src, void** dst, int ddepth, int dx, int dy, int ksize, double scale, double delta)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

		Sobel(((simMat*)src)->data, m->data, ddepth, dx, dy, ksize, scale, delta, BORDER_DEFAULT);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_scharr(void* src, void** dst, int ddepth, int dx, int dy, double scale, double delta)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

		Scharr(((simMat*)src)->data, m->data, ddepth, dx, dy, scale, delta, BORDER_DEFAULT);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_laplacian(void* src, void** dst, int ddepth, int ksize, double scale, double delta)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

		Laplacian(((simMat*)src)->data, m->data, ddepth, ksize, scale, delta, BORDER_DEFAULT);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_canny(void* src, void** dst, double threshold1, double threshold2, int apertureSize, bool L2gradient)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

		Canny(((simMat*)src)->data, m->data, threshold1, threshold2, apertureSize, L2gradient);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_cornerHarris(void* src, void** dst, int blockSize, int ksize, double k)
{
	if (src == 0)
		return "Input data error";

	try
	{
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
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
	return "0";
}

string sim_dilate(void* src, void** dst, int blockSize, int ksize, int kShape)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

		Mat element = getStructuringElement(kShape,
			Size(2 * blockSize + 1, 2 * blockSize + 1),
			Point(ksize, ksize));
		dilate(((simMat*)src)->data, m->data, element);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}

	return "0";
}

string sim_erode(void* src, void** dst, int blockSize, int ksize, int kShape)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

		Mat element = getStructuringElement(kShape,
			Size(2 * blockSize + 1, 2 * blockSize + 1),
			Point(ksize, ksize));
		erode(((simMat*)src)->data, m->data, element);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}

	return "0";
}

string sim_resizeP(void* src, void** dst, int ksizeX, int ksizeY, double fx, double fy, int interpolation)
{
	if (src == 0)
		return "Input data error";

	try
	{
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
		resize(((simMat*)src)->data, m->data, Size(ksizeX, ksizeY), fx, fy, interpolation);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}

	return "0";
}

string sim_resize(void* src, void** dst, int ksizeX, int ksizeY)
{
	if (src == 0)
		return "Input data error";

	try
	{
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
		resize(((simMat*)src)->data, m->data, Size(ksizeX, ksizeY));
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}

	return "0";
}

string sim_warpAffine(void* src, void** dst,
	double* M, int dsizeX, int dsizeY,
	int flags,
	int borderMode)
{
	if (src == 0)
		return "Input data error";

	try
	{
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

		warpAffine(((simMat*)src)->data, m->data, warp_matrix, Size(dsizeX, dsizeY), flags, borderMode);
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}

	return "0";
}


string sim_warpPerspective(void* src, void** dst, float* srcPts, float* dstPts, int dsizeY, int dsizeX)
{
	if (src == 0)
		return "Input data error";

	try
	{
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
		cv::Mat homography = cv::findHomography(prev, post);

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

		warpPerspective(((simMat*)src)->data, m->data, homography, Size(dsizeX, dsizeY));
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}

	return "0";
}

string sim_floodFill(void* src, void** dst, int pX, int pY, uchar color)
{
	if (src == 0)
		return "Input data error";

	try
	{
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
		floodFill(m->data, cv::Point(pX, pY), Scalar(color));
	}
	catch (Exception& e)
	{
		releaseSimMat(dst);
		return e.what();
	}
}