
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
std::vector<float> fitLine(vector<Point>& pts, Mat& mask) {

	int ransacItr = 200;
	std::vector<std::vector<float>> K;

	std::vector<int> size;


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

	int maxSize = -1;
	int minIdx = -1;

	for (int j = 0; j < size.size(); j++) {
		if (size[j] > maxSize) {
			maxSize = size[j];
			minIdx = j;
		}
	}
	if (minIdx == -1)
	{
		std::vector<float> k;
		return k;
	}

	return K[minIdx];
}

void detectLanes(cv::Mat& binaryinput, cv::Mat& drawinput, int roi_w, int wheel_h, int* rd, int* ld, int numHorHist)
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

	*rd = featurePointsRight.size();
	*ld = featurePointsLeft.size();
	
	std::vector<float> leftLine = fitLine(featurePointsLeft, binaryinput);
	std::vector<float> rightLine = fitLine(featurePointsRight, binaryinput);

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

int sim_detectLanes(void* binaryinput, int numHorHist, int roi_w, int wheel_h, int* rd, int* ld, void* drawinput)
{
	if ((binaryinput == 0) || (drawinput == 0))
		return RES_ERROR;

	if (((simMat*)binaryinput)->data.cols < roi_w *2)
		return RES_ERROR;
	
	detectLanes(((simMat*)binaryinput)->data, ((simMat*)drawinput)->data, roi_w, wheel_h, rd, ld, numHorHist);
	return RES_OK;

}