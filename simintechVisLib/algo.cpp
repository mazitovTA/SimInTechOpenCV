
#include "algo.h"

std::vector<cv::Point> findLocalMaxima(std::vector<float> in, int eps)
{
	std::vector<cv::Point> tmp;
	if (in.size() < 3)
		return tmp;
	if (in[0] > in[1])
		tmp.push_back(Point(0, in[0]));

	if (in[in.size() - 1] > in[in.size() - 2])
		tmp.push_back(Point(in.size() - 1, in[in.size() - 1]));


	for (int i = 1; i < in.size() - 1; ++i)
	{
		if ((in[i] > in[i - 1]) && (in[i] >= in[i + 1]) && (in[i] > 1))
		{
			tmp.push_back(Point(i, in[i]));
		}
	}

	if (tmp.size() < 2)
		return tmp;

	std::vector<cv::Point> res;
	for (int i = 0; i < tmp.size() - 1; ++i)
	{
		if (abs(tmp[i].x - tmp[i + 1].x) <= eps)
		{
			std::vector<cv::Point> temp;
			temp.push_back(tmp[i]);

			if (i + 1 == tmp.size() - 1)
				temp.push_back(tmp[i + 1]);

			for (int j = i + 1; j < tmp.size() - 1; ++j)
			{
				i++;
				temp.push_back(tmp[j]);
				if (abs(tmp[j].x - tmp[j + 1].x) > eps)
					break;

				if (j + 1 == tmp.size() - 1)
					temp.push_back(tmp[j + 1]);
			}

			float x = 0;
			float y = 0;
			for (int j = 0; j < temp.size(); ++j)
			{
				x += temp[j].x;
				y += temp[j].y;
			}
			x /= temp.size();
			y /= temp.size();
			res.push_back(Point(x, y));
		}
		else
		{
			res.push_back(tmp[i]);
			if (i + 1 == tmp.size() - 1)
				res.push_back(tmp[i + 1]);
		}

	}
	return res;
}

Point getCentroid(vector<Point>& locations)
{
	Point Coord(0, 0);
	for (int i = 0; i < locations.size(); ++i)
	{
		Coord += locations[i];
	}
	Coord.x /= locations.size();
	Coord.y /= locations.size();
	return Coord;
}

void findHistogrammMaximums(cv::Mat& filter_res, std::vector<cv::Point>& featurePointsLeft, std::vector<cv::Point>& featurePointsRight, int hist_step_y = 30)
{
	for (int i = filter_res.rows, u = 0; i > filter_res.rows * 1 / 8; i -= hist_step_y, ++u)
	{
		std::vector<float> vec(filter_res.cols);
		std::vector<float> vec1(filter_res.cols);
		Rect region_of_interest = Rect(0, i - hist_step_y - 1, filter_res.cols - 1, hist_step_y);
		Mat image_roi = filter_res(region_of_interest);

		uchar* data = image_roi.data;
		std::vector<float> av(filter_res.cols);
		std::vector<float> an(filter_res.cols);
		for (int i = 0; i < hist_step_y * filter_res.cols - 1; i++)
		{
			int y = i / filter_res.cols;
			int x = i - y * filter_res.cols;
			//operations using *data
			data++;
			if (int(*data))
			{
				av[x] += y;
				an[x] ++;
			}
		}

		// сглаживание скользящим средним
		int win_w = 5;
		std::vector<float> av_an(filter_res.cols);
		av_an[0] = an[0];
		av_an[filter_res.cols - 1] = an[filter_res.cols - 1];
		for (int i = 1; i < av_an.size() - 2; i++)
		{
			int cnt = 1;
			av_an[i] = 0;
			for (int j = i - win_w; j < i + win_w; j++)
			{
				if ((j > 0) && (j < av_an.size() - 1) && (an[j] != 0))
				{
					av_an[i] += an[j];
					cnt++;
				}

			}

			if (cnt > 0)
				av_an[i] /= cnt;
			else
				av_an[i] = 0;
		}

		std::vector<cv::Point> maximums = findLocalMaxima(av_an, hist_step_y);

		for (int r = 0; r < maximums.size(); r++) {
			//circle(image_roi, maximums[r], 0, Scalar(0, 0, 255), 6, 8, 0);
			if (maximums[r].x < filter_res.cols / 2)
				featurePointsLeft.push_back(Point(maximums[r].x, i - hist_step_y));
			else
				featurePointsRight.push_back(Point(maximums[r].x, i - hist_step_y));
		}
	}

	// уточнить положение по среднему значеиню
	for (int r = 0; r < featurePointsLeft.size(); r++) {

		int xCoord = featurePointsLeft[r].x - hist_step_y / 2;
		int width = hist_step_y;
		if (xCoord < 0)
		{
			xCoord = 0;
			width = featurePointsLeft[r].x * 2;
		}
		if ((xCoord + width) > (filter_res.cols - 1))
			width = (filter_res.cols - 1) - xCoord;

		Rect region_of_interest = Rect(xCoord, featurePointsLeft[r].y, width, hist_step_y);
		Mat v = filter_res(region_of_interest);
		vector<Point>  nonzeropixels;
		findNonZero(v, nonzeropixels);
		if (nonzeropixels.size() == 0)
			continue;
		Point pt = getCentroid(nonzeropixels);
		featurePointsLeft[r].x += pt.x - hist_step_y / 2;
		featurePointsLeft[r].y += pt.y;
	}

	for (int r = 0; r < featurePointsRight.size(); r++) {

		int xCoord = featurePointsRight[r].x - hist_step_y / 2;
		int width = hist_step_y;
		if (xCoord < 0)
		{
			xCoord = 0;
			width = featurePointsRight[r].x * 2;
		}
		if ((xCoord + width) > (filter_res.cols - 1))
			width = (filter_res.cols - 1) - xCoord;

		Rect region_of_interest = Rect(xCoord, featurePointsRight[r].y, width, hist_step_y);
		Mat v = filter_res(region_of_interest);
		vector<Point>  nonzeropixels;
		findNonZero(v, nonzeropixels);
		if (nonzeropixels.size() == 0)
			continue;
		Point pt = getCentroid(nonzeropixels);
		featurePointsRight[r].x += pt.x - hist_step_y / 2;
		featurePointsRight[r].y += pt.y;
	}
}

std::vector<float> fitLine(vector<Point>& pts, Mat& mask, int* pointNumber) {

	int ransacItr = 200;
	std::vector<std::vector<float>> K;

	std::vector<int> size;

	*pointNumber = 0;

	for (int itr = 0; itr < ransacItr; itr++) {
		std::vector<Point> points;

		int ptsNum = 2;

		if (pts.size() < 3)
			return std::vector<float>(0);

		int p1 = rand() % ((pts.size() - 1));
		int p2 = rand() % ((pts.size() - 1));
		points.push_back(pts[p1]);
		points.push_back(pts[p2]);


		std::vector<float> k(3);
		k[0] = (points[0].y - points[1].y); //A
		k[1] = (points[1].x - points[0].x); //B
		k[2] = (points[0].x * points[1].y) - (points[1].x * points[0].y); //C


		float A = k[0];
		float B = k[1];
		float C = k[2];

		if (B == 0)
			continue;
		if (abs(A / B) < 0.4)
			continue;

		Point top(0, -C / B);
		Point bot(mask.cols, (A * mask.cols + C) / (-B + 0.000000001));

		LineIterator it(mask, top, bot, 8);
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

		size.push_back(whiteCounter);
		K.push_back(k);
	}

	int maxSize = 0;
	int minIdx = -1;

	for (int j = 0; j < size.size(); j++) {
		if (size[j] > maxSize) {
			maxSize = size[j];
			minIdx = j;
		}
	}
	*pointNumber = maxSize;

	if (minIdx == -1)
	{
		std::vector<float> k;
		return k;
	}
	return K[minIdx];
}

void detectLanes(cv::Mat& binaryinput, cv::Mat& drawinput, int roi_w, int wheel_h, int* rd, int* ld, int numHorHist, int* leftPointNumber, int* rightPointNumber)
{		
	std::vector<cv::Point> featurePointsLeft;
	std::vector<cv::Point> featurePointsRight;

	std::vector<cv::Point> leftTriangle;

	leftTriangle.push_back(cv::Point(0, 0));
	leftTriangle.push_back(cv::Point(roi_w, 0));
	leftTriangle.push_back(cv::Point(0, binaryinput.cols));

	std::vector<cv::Point> rightTriangle;
	rightTriangle.push_back(cv::Point(binaryinput.rows, 0));
	rightTriangle.push_back(cv::Point(binaryinput.rows - roi_w, 0));
	rightTriangle.push_back(cv::Point(binaryinput.rows, binaryinput.cols));

	std::vector<std::vector<cv::Point> > fillContAll;
	fillContAll.push_back(leftTriangle);
	fillContAll.push_back(rightTriangle);
	cv::fillPoly(binaryinput, fillContAll, cv::Scalar(0));

	
	findHistogrammMaximums(binaryinput, featurePointsLeft, featurePointsRight, numHorHist);
		
	std::vector<float> leftLine = fitLine(featurePointsLeft, binaryinput, leftPointNumber);
	std::vector<float> rightLine = fitLine(featurePointsRight, binaryinput, rightPointNumber);

	int cx = binaryinput.cols / 2;
	int cy = binaryinput.rows - wheel_h;

	Point r(cx, cy);
	Point l(cx, cy);
	Point m(cx, cy);
	
	/// Draw results		
	
	if ((leftLine.size() > 1) && (leftLine[0] != 0) && (leftLine[1] != 0) && (leftLine[2] != 0)) {
		float A = leftLine[0];
		float B = leftLine[1];
		float C = leftLine[2];
		Point top(0, -C / B);
		Point bot((-B * cy - C) / (A + 0.000000001), cy);
		//Point bot(binaryinput.cols, (A * binaryinput.cols + C) / (-B + 0.000000001));
		l.x = (B * cy + C) / (-A + 0.000000001);
		*ld = abs(cx - l.x);
		line(drawinput, top, bot, Scalar(255, 0, 0), 2, 8, 0);
	}

	if ((rightLine.size() > 1) && (rightLine[0] != 0) && (rightLine[1] != 0) && (rightLine[2] != 0)) {
		float A = rightLine[0];
		float B = rightLine[1];
		float C = rightLine[2];
		//Point top(0, -C / B);
		Point top((-B * cy - C) / (A + 0.000000001), cy);
		Point bot(binaryinput.cols, (A * binaryinput.cols + C) / (-B + 0.000001));
		r.x = (B * cy + C) / (-A + 0.000000001);
		*rd = abs(r.x - cx);
		line(drawinput, top, bot, Scalar(0, 255, 0), 2, 8, 0);
	}

	line(drawinput, m, r, Scalar(255, 0, 255), 2, 8, 0);
	line(drawinput, m, l, Scalar(255, 255, 0), 2, 8, 0);
	line(drawinput, m, Point(m.x, drawinput.rows), Scalar(0, 255, 0), 1, 8, 0);
}

vector<cv::Point> toPoint(vector<cv::Point2f>& in)
{
	vector<cv::Point> pts;

	for (int i = 0; i < in.size(); ++i)
	{
		pts.push_back(Point(in[i].x, in[i].y));
	}
	return pts;
}

float correlation(cv::Mat& image1, cv::Mat& image2)
{
	cv::Mat corr;
	cv::matchTemplate(image1, image2, corr, cv::TM_CCORR_NORMED);
	return corr.at<float>(0, 0);  // corr only has one pixel
}
int sim_detectLanes(void* binaryinput, int numHorHist, int roi_w, int wheel_h, int* rd, int* ld, void* drawinput, int* leftPointNumber, int* rightPointNumber)
{
	
	if ((binaryinput == 0) || (drawinput == 0))
		return RES_ERROR;

	if (((simMat*)binaryinput)->data.cols < roi_w *2)
		return RES_ERROR;
	
	detectLanes(((simMat*)binaryinput)->data, ((simMat*)drawinput)->data, roi_w, wheel_h, rd, ld, numHorHist, leftPointNumber, rightPointNumber);
	return RES_OK;

}

void normalize_contour(vector<Point>& inpit, vector<Point>& normalize, Size sz)
{
	Rect2f boundRect = boundingRect(inpit);
	float x_ratio = (float)sz.width / boundRect.width;
	float y_ratio = (float)sz.height / boundRect.height;

	
	normalize.resize(inpit.size());
	Moments m = moments(inpit, true);
	Point p(m.m10 / m.m00, m.m01 / m.m00);
	
	for (int j = 0; j < inpit.size(); ++j)
	{
		normalize[j].x = inpit[j].x - boundRect.x - p.x;
		normalize[j].y = inpit[j].y - boundRect.y - p.y;
		normalize[j].x *= x_ratio;
		normalize[j].y *= y_ratio;
	}
}
void normalizeAndPopulateTemplate(Mat input, vector<Point>& contour, Size sz, float alphaStep, int rotationsNum, vector<Mat>& templates, vector<Mat>& masks)
{
	int min_morm = 80;
	int max_morm = 255;
	
	templates.clear();
	masks.clear();

	Rect2f boundRect = boundingRect(contour);
	Mat templ = input(boundRect);
	
	Mat templMask(boundRect.size(), CV_8U, Scalar(0));
	Mat templMasked(boundRect.size(), CV_8U, Scalar(0));
	
	Moments m = moments(contour, true);
	Point p(m.m10 / m.m00 - boundRect.x, m.m01 / m.m00 - boundRect.y);
	vector<Point2f> normContour(contour.size());
	for (int j = 0; j < contour.size(); ++j)
	{
		normContour[j].x = contour[j].x - boundRect.x;
		normContour[j].y = contour[j].y - boundRect.y;
	}

	vector<cv::Point> pts = toPoint(normContour);
	fillConvexPoly(templMask, &pts[0], pts.size(), Scalar(255));
	templ.copyTo(templMasked, templMask);

	
	Mat s;
	resize(templMask, s, sz);
	masks.push_back(s);

	Mat t;
	resize(templMasked, t, sz);
	normalize(t, t, min_morm, max_morm, NORM_MINMAX, -1, s);
	//imshow("normalize templ", t);
	templates.push_back(t);

	for (int i = 1; i < rotationsNum + 1; ++i)
	{
		//////////////////////// rotation
		float angle = alphaStep * i;
		float w = templMasked.size().width;
		float h = templMasked.size().height;
		Point2d center = Point2d(w / 2, h / 2);

		Rect bounds = RotatedRect(center, templMasked.size(), angle).boundingRect();
		Mat rot = getRotationMatrix2D(center, angle, 1.0);
		Mat warped;
		rot.at<double>(0, 2) += bounds.width / 2.0 - center.x;
		rot.at<double>(1, 2) += bounds.height / 2.0 - center.y;
		warpAffine(templMasked, warped, rot, bounds.size());

		cv::Mat tr = rot.clone();
		cv::Mat row = cv::Mat::ones(1, 3, CV_64F);  // 3 cols, 1 row
		tr.push_back(row);
		tr.at<double>(2, 0) = 0.0;
		tr.at<double>(2, 1) = 0.0;
		tr.at<double>(2, 2) = 1.0;
		vector<Point2f> warpedContour;
		perspectiveTransform(normContour, warpedContour, tr);


		/////////////////////////////////////////////
		Rect2f boundRect = boundingRect(warpedContour);
		Mat templ = warped(boundRect);
		Mat templMask(boundRect.size(), CV_8U, Scalar(0));
		Mat templMasked(boundRect.size(), CV_8U, Scalar(0));

		Moments m = moments(warpedContour, true);
		Point p(m.m10 / m.m00 - boundRect.x, m.m01 / m.m00 - boundRect.y);
		vector<Point2f> normContour(warpedContour.size());
		for (int j = 0; j < warpedContour.size(); ++j)
		{
			normContour[j].x = warpedContour[j].x - boundRect.x;
			normContour[j].y = warpedContour[j].y - boundRect.y;
		}

		vector<cv::Point> pts = toPoint(normContour);
		fillConvexPoly(templMask, &pts[0], pts.size(), Scalar(255));
		templ.copyTo(templMasked, templMask);
		//////////////////////////////////////////

		Mat s;
		resize(templMask, s, sz);
		masks.push_back(s);

		Mat t;
		resize(templMasked, t, sz);
		normalize(t, t, min_morm, max_morm, NORM_MINMAX, -1, s);
		templates.push_back(t);
	}

	for (int i = 1; i < rotationsNum + 1; ++i)
	{
		//////////////////////// rotation
		float angle = -alphaStep * i;
		float w = templMasked.size().width;
		float h = templMasked.size().height;
		Point2d center = Point2d(w / 2, h / 2);

		Rect bounds = RotatedRect(center, templMasked.size(), angle).boundingRect();
		Mat rot = getRotationMatrix2D(center, angle, 1.0);
		Mat warped;
		rot.at<double>(0, 2) += bounds.width / 2.0 - center.x;
		rot.at<double>(1, 2) += bounds.height / 2.0 - center.y;
		warpAffine(templMasked, warped, rot, bounds.size());

		cv::Mat tr = rot.clone();
		cv::Mat row = cv::Mat::ones(1, 3, CV_64F);  // 3 cols, 1 row
		tr.push_back(row);
		tr.at<double>(2, 0) = 0.0;
		tr.at<double>(2, 1) = 0.0;
		tr.at<double>(2, 2) = 1.0;
		vector<Point2f> warpedContour;
		perspectiveTransform(normContour, warpedContour, tr);

		/////////////////////////////////////////////
		Rect2f boundRect = boundingRect(warpedContour);
		Mat templ = warped(boundRect);
		Mat templMask(boundRect.size(), CV_8U, Scalar(0));
		Mat templMasked(boundRect.size(), CV_8U, Scalar(0));

		Moments m = moments(warpedContour, true);
		Point p(m.m10 / m.m00 - boundRect.x, m.m01 / m.m00 - boundRect.y);
		vector<Point2f> normContour(warpedContour.size());
		for (int j = 0; j < warpedContour.size(); ++j)
		{
			normContour[j].x = warpedContour[j].x - boundRect.x;
			normContour[j].y = warpedContour[j].y - boundRect.y;
		}

		vector<cv::Point> pts = toPoint(normContour);
		fillConvexPoly(templMask, &pts[0], pts.size(), Scalar(255));
		templ.copyTo(templMasked, templMask);
		//////////////////////////////////////////

		Mat s;
		resize(templMask, s, sz);
		masks.push_back(s);

		Mat t;
		resize(templMasked, t, sz);
		normalize(t, t, min_morm, max_morm, NORM_MINMAX, -1, s);
		templates.push_back(t);
	}
}

int findShapes(Mat& templFrame, vector<vector<Point>>& templContour, Mat& frame, vector<vector<Point>>& contours, int normalizedContourSizeX, int normalizedContourSizeY, bool useHull,
	bool draw, double minCorrelation, int* numFound)
{	
	if (templContour.size() < 1)
		return RES_ERROR;
	if (!frame.data || !templFrame.data)
		return RES_ERROR;

	Size normalizedContourSize(normalizedContourSizeX, normalizedContourSizeY);
	Mat grayTempl, grayFrame;

	if (templFrame.channels() == 3)
		cvtColor(templFrame, grayTempl, COLOR_BGR2GRAY);
	else
		grayTempl = templFrame;

	if (frame.channels() == 3)
		cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
	else
		grayFrame = frame;

	
	//////////////////////////////////////////////
	vector<Point> templ_contour = templContour[0];
	vector<Mat> templates;
	vector<Mat> masks;
	vector<vector<Point>> templ_hull_contour(1);
	vector<vector<Point>> norm_templ_contour(1);
	vector<vector<Point>> norm_templ_contours;
	
	{
		if (useHull)
			convexHull((templ_contour), templ_hull_contour[0], false);
		else
			templ_hull_contour[0] = templ_contour;
		normalizeAndPopulateTemplate(grayTempl, templ_hull_contour[0], normalizedContourSize, 1, 3, templates, masks);
		normalize_contour(templ_hull_contour[0], norm_templ_contour[0], normalizedContourSize);
	}
	
	//////////////////////////////////////////////	
	vector<vector<Point>> contours_hull;
	//vector<vector<Point>> contours_normalize;
	contours_hull.resize(contours.size());
	if (useHull)
	{
		for (int i = 0; i < contours.size(); i++)
		{
			convexHull((contours[i]), contours_hull[i], false);
		}
	}
	else
		contours_hull = contours;
	
	vector<Point> res_center;
	*numFound = 0;
	for (int i = 0; i < contours_hull.size(); i++)
	{
		if (contours_hull[i].size() > 3)
		{
			Mat norm_patch;
			Rect2f boundRect = boundingRect(contours_hull[i]);
			Mat templ = grayFrame(boundRect);

			Mat templMask(boundRect.size(), CV_8U, Scalar(0));
			Mat templMasked(boundRect.size(), CV_8U, Scalar(0));

			Moments m = moments(contours_hull[i], true);
			Point p(m.m10 / m.m00 - boundRect.x, m.m01 / m.m00 - boundRect.y);
			vector<Point2f> normContour(contours_hull[i].size());
			for (int j = 0; j < contours_hull[i].size(); ++j)
			{
				normContour[j].x = contours_hull[i][j].x - boundRect.x;
				normContour[j].y = contours_hull[i][j].y - boundRect.y;
			}

			vector<cv::Point> pts = toPoint(normContour);
			fillConvexPoly(templMask, &pts[0], pts.size(), Scalar(255));
			templ.copyTo(templMasked, templMask);

			Mat s;
			resize(templMask, s, normalizedContourSize);
			Mat t;
			resize(templMasked, t, normalizedContourSize);
			normalize(t, norm_patch, 0, 255, NORM_MINMAX, -1, s);

			for (int j = 0; j < templates.size(); ++j)
			{
				float corr = correlation(templates[j], norm_patch);
				if (corr > minCorrelation)
				{

					Point cx(boundRect.x + boundRect.width / 2, boundRect.y + boundRect.height / 2);
					bool is_same = 0;
					for (int k = 0; k < res_center.size(); ++k)
					{
						if (sqrt((res_center[k].x - cx.x) * (res_center[k].x - cx.x) + (res_center[k].y - cx.y) * (res_center[k].y - cx.y)) < 20)
						{
							is_same = 1;
							break;
						}
					}
					if (is_same)
						continue;
					(*numFound)++;
					res_center.push_back(cx);
					drawContours(frame, contours_hull, i, Scalar(0, 255, 0), 4, 8, 0, 0, Point());
					break;
				}
			}

		}
	}
	return RES_OK;
}

int sim_findSign(void* templFrame, void* templContour, void* frame, void* contours, int normalizedContourSizeX, 
	int normalizedContourSizeY, int useHull, int draw, double minCorrelation, int* numFound)
{	
	if (templFrame == 0 || templContour == 0 || frame == 0 || contours == 0)
		return RES_ERROR;	

	int res = findShapes(((simMat*)templFrame)->data,
		    ((VectorVectorPoint*)templContour)->data,
			((simMat*)frame)->data,
			((VectorVectorPoint*)contours)->data,
			normalizedContourSizeX,
			normalizedContourSizeY, 
			useHull,
			draw, minCorrelation, numFound);

	return res;
}