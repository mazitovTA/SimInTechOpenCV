#include "opencv2/opencv.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Size warpedSize(400, 400);

// HSV FILTER RANGES
int hl = 0;
int hh = 255;
int sl = 0;
int sh = 255;
int vl = 180;
int vh = 255;

/// Roi 
float w1 = 520; // расстояние от левой кромки кадра до верхней левой точки Roi по оси Х
float w2 = 305; // расстояние от левой кромки кадра до нижней левой точки Roi по оси Х
float dx = -50; // Смещение Roi по оси Х

float h1 = 560; // Расстояние от верхней кромки кадра до Roi по оси Y
float h2 = 30;  // Расстояние от нижней кромки кадра до Roi по оси Y



std::vector<float> fit_poly(vector<Point>& pts, int K) {

	std::vector<float> a(K + 1);
	std::vector<float> b(K + 1);

	int N = pts.size();
	if (N < K + 1)
		return a;

	std::vector<std::vector<float> > sums(K + 1);
	for (int i = 0; i < K + 1; i++) {
		sums[i].resize(K + 1);
	}

	int i = 0, j = 0, k = 0;

	//init square sums matrix
	for (i = 0; i < K + 1; i++) {
		for (j = 0; j < K + 1; j++) {
			sums[i][j] = 0;
			for (k = 0; k < N; k++) {
				sums[i][j] += pow(pts[k].x, i + j);
			}
		}
	}
	//init free coefficients column
	for (i = 0; i < K + 1; i++) {
		for (k = 0; k < N; k++) {
			b[i] += pow(pts[k].x, i) * pts[k].y;
		}
	}

	float temp = 0;
	for (i = 0; i < K + 1; i++) {
		if (sums[i][i] == 0) {
			for (j = 0; j < K + 1; j++) {
				if (j == i)
					continue;
				if (sums[j][i] != 0 && sums[i][j] != 0) {
					for (k = 0; k < K + 1; k++) {
						temp = sums[j][k];
						sums[j][k] = sums[i][k];
						sums[i][k] = temp;
					}
					temp = b[j];
					b[j] = b[i];
					b[i] = temp;
					break;
				}
			}
		}
	}

	//process rows
	for (k = 0; k < K + 1; k++) {
		for (i = k + 1; i < K + 1; i++) {
			if (sums[k][k] == 0) {
				std::cout << "can't fit curve" << std::endl;
				return a;
			}
			float M = sums[i][k] / sums[k][k];
			for (j = k; j < K + 1; j++) {
				sums[i][j] -= M * sums[k][j];
			}
			b[i] -= M * b[k];
		}
	}
	//printmatrix();
	for (i = (K + 1) - 1; i >= 0; i--) {
		float s = 0;
		for (j = i; j < K + 1; j++) {
			s = s + sums[i][j] * a[j];
		}
		a[i] = (b[i] - s) / sums[i][i];
	}
	return a;
}

std::vector<float> fitLine(vector<Point>& pts) {

	if (pts.size() < 20)
		return std::vector<float>(0);

	int ransacItr = 2000;
	std::vector<std::vector<float>> K;

	std::vector<double> error;
	std::vector<int> size;
	for (int itr = 0; itr < ransacItr; itr++) {
		std::vector<Point> points;

		int ptsNum = 2;

		int p1 = rand() % ((pts.size() - 1));
		int p2 = rand() % ((pts.size() - 1));
		points.push_back(pts[p1]);
		points.push_back(pts[p2]);

		if (cv::norm(pts[p1] - pts[p2]) < 100)
		{
			continue;
		}

		std::vector<float> k(3);
		k[0] = (points[0].y - points[1].y); //A
		k[1] = (points[1].x - points[0].x); //B
		k[2] = (points[0].x * points[1].y) - (points[1].x * points[0].y); //C

		float err = 0;
		int sz = 0;
		for (int i = 0; i < pts.size(); i++) {
			float D = (k[0] * pts[i].x + k[1] * pts[i].y + k[2])
				/ sqrt(k[0] * k[0] + k[1] * k[1]);
			if (D > 5)
				continue;
			err += D * D;
			sz++;
		}
		error.push_back(err);
		size.push_back(sz);
		K.push_back(k);
	}

	if (error.size() == 0)
	{
		std::vector<float> k;
		return k;
	}

	int minIdx = 0;

	double minV = -1;
	int minSize = 200;
	for (int j = 0; j < size.size(); j++) {
		if (size[j] > minSize) {
			minV = error[j]/ size[j];
			break;
		}
	}
	if(minV == -1)
	{
		std::vector<float> k;
		return k;
	}

	for (int j = 1; j < error.size(); j++) {
		if ((minV > error[j] / size[j]) && (size[j] > minSize)) {
			minV = error[j]/ size[j];
			minIdx = j;
		}
	}

	return K[minIdx];
}

Mat filtration(Mat& input)
{
	Mat hsv_img;
	cvtColor(input, hsv_img, CV_RGB2HSV);

	Mat gray_img;
	cvtColor(input, gray_img, CV_BGR2GRAY);

	Mat filter_hsv, filter_thresh, filter_res;

	// Threshold filter
	Mat grad_x, abs_grad_x;
	Sobel(gray_img, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	threshold(abs_grad_x, filter_thresh, 240, 255, 0);

	// Color filter
	inRange(hsv_img, Scalar(hl, sl, vl), Scalar(hh, sh, vh), filter_hsv);

	int size = 4;
	Mat element = getStructuringElement(cv::MORPH_RECT,
		cv::Size(3 * size + 1, 3 * size + 1),
		cv::Point(size, size));

	dilate(filter_thresh, filter_thresh, element);
	bitwise_and(filter_hsv, filter_thresh, filter_res);


	imshow("Threshold filter", filter_thresh);
	imshow("Color filter", filter_hsv);

	return filter_res;
}

int main() {

	VideoCapture cap("v1.mp4");

	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	while (1) {
		Mat frame;
		cap >> frame;

		if (frame.empty())
			break;
		
		///Roi
		Point2f srcTri[4];
		srcTri[0] = Point2f(w1 + dx, h1);
		srcTri[1] = Point2f(frame.cols + dx - w1, h1);
		srcTri[2] = Point2f(frame.cols + dx - w2, frame.rows - h2);
		srcTri[3] = Point2f(w2 + dx, frame.rows - h2);

		Point2f dstTri[4];
		dstTri[0] = Point2f(0.f, 0.f);
		dstTri[1] = Point2f(warpedSize.width, 0);
		dstTri[2] = Point2f(warpedSize.width, warpedSize.height);
		dstTri[3] = Point2f(0, warpedSize.height);

		Mat warp_mat = getPerspectiveTransform(srcTri, dstTri);
		Mat warp_dst = Mat::zeros(warpedSize, frame.type());

		warpPerspective(frame, warp_dst, warp_mat, warpedSize, CV_INTER_LINEAR,
			BORDER_CONSTANT, Scalar(0, 0, 0));


		/// Image filtration
		Mat filter_res = filtration(warp_dst);
		
		/// Line Fitting
		vector<Point> leftLine, rightLine;
		cv::findNonZero(
			filter_res(Rect(0, 0, warpedSize.width / 2, warpedSize.height)),
			leftLine);
		cv::findNonZero(
			filter_res(
				Rect(warpedSize.width / 2, 0, warpedSize.width / 2,
					warpedSize.height)), rightLine);

		std::vector<float> leftK = fitLine(leftLine);
		std::vector<float> rightK = fitLine(rightLine);

		int leftType = -1;
		int rightType = -1;
		/// Line Classification
		/// Left
		if (leftK.size() > 1) {
			float A = leftK[0];
			float B = leftK[1];
			float C = leftK[2];
			Point top(0, -C / B);
			Point bot(400, (A * 400 + C) / (-B + 0.000000001));

			LineIterator it(filter_res, top, bot, 8);
			LineIterator it2 = it;
			vector<uchar> buf(it.count);
			int Length = 0;
			int whiteCounter = 0;
			for (int i = 0; i < it.count; i++, ++it)
			{
				buf[i] = *(const uchar*)* it;
				if (buf[i] != 0)
					whiteCounter++;
				Length++;
			}
			if ((whiteCounter > 50) && (whiteCounter < 260))
				leftType = 0;
			else if (whiteCounter > 259)
				leftType = 1;
		}
		/// Right
		if (rightK.size() > 1) {
			float A = rightK[0];
			float B = rightK[1];
			float C = rightK[2];
			Point top(200, -C / B);
			Point bot(600, (A * 400 + C) / (-B + 0.000000001));

			LineIterator it(filter_res, top, bot, 8);
			LineIterator it2 = it;
			vector<uchar> buf(it.count);
			int Length = 0;
			int whiteCounter = 0;
			for (int i = 0; i < it.count; i++, ++it)
			{
				buf[i] = *(const uchar*)* it;
				if (buf[i] != 0)
					whiteCounter++;
				Length++;
			}
			if ((whiteCounter > 50) && (whiteCounter < 300))
				rightType = 0;
			else if (whiteCounter > 299)
				rightType = 1;
		}  		 	  


		/// Draw results
		if (leftK.size() > 1) {
			float A = leftK[0];
			float B = leftK[1];
			float C = leftK[2];
			Point top(0, -C/B);
			Point bot(400, (A*400+C)/(-B+ 0.000000001));
			line(warp_dst, top, bot, Scalar(255, 0, 0), 2, 8, 0);
		}

		if (rightK.size() > 1) {
			float A = rightK[0];
			float B = rightK[1];
			float C = rightK[2];
			Point top(200, -C / B);
			Point bot(600, (A * 400 + C) / (-B + 0.000000001));
			line(warp_dst, top, bot, Scalar(0, 255, 0), 2, 8, 0);
		}		
		
		line(frame, srcTri[0], srcTri[1], Scalar(0, 255, 0), 1, 8, 0);
		line(frame, srcTri[1], srcTri[2], Scalar(0, 255, 0), 1, 8, 0);
		line(frame, srcTri[2], srcTri[3], Scalar(0, 255, 0), 1, 8, 0);
		line(frame, srcTri[3], srcTri[0], Scalar(0, 255, 0), 1, 8, 0);


		if (leftType == -1)
			putText(warp_dst, "No line", cv::Point(50, 25), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(0, 0, 255), 1, CV_AA);
		else if (leftType == 0)
			putText(warp_dst, "discontinuous", cv::Point(50, 25), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255, 0, 0), 1, CV_AA);
		else if (leftType == 1)
			putText(warp_dst, "solid", cv::Point(50, 25), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(0, 255, 0), 1, CV_AA);

		if (rightType == -1)
			putText(warp_dst, "No line", cv::Point(250, 25), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(0, 0, 255), 1, CV_AA);
		else if (rightType == 0)
			putText(warp_dst, "discontinuous", cv::Point(250, 25), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255, 0, 0), 1, CV_AA);
		else if (rightType == 1)
			putText(warp_dst, "solid", cv::Point(250, 25), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(0, 255, 0), 1, CV_AA);


		imshow("Res filter", filter_res);				
		imshow("frame", frame);
		imshow("ROI", warp_dst);

		char c = (char)waitKey(0);
		if (c == 27)
			break;
		else if (c == 's')
			waitKey(0);
	}

	cap.release();

	destroyAllWindows();

	return 0;
}
