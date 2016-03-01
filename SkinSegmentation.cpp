/*
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 60;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void*);

 //@function main 
int main()
{
	/// Load source image and convert it to gray
	src = imread("C:/Users/Nitin/Documents/Visual Studio 2013/files/test/img30.jpg", 1);

	/// Convert image to gray and blur it
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	/// Create Window
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	createTrackbar(" Threshold:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

// @function thresh_callback
void thresh_callback(int, void*)
{
	Mat threshold_output;
vector<vector<Point> > contours;

	vector<Vec4i> hierarchy;

	/// Detect edges using Threshold
	threshold(src_gray, threshold_output, thresh, 255, THRESH_BINARY);
	/// Find contours
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Approximate contours to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);
	}


	/// Draw polygonal contour + bonding rects + circles
	cout << contours.size() << endl;
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	int jp = 0;
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		
		double pq = contourArea(contours[i], 0);
		
		
		if (pq > 1000)
		{
			jp++;
			cout << pq << endl;
			drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
			rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
			cout << boundRect[i].tl() << endl;
			cout << boundRect[i].br() << endl;
			int width = boundRect[i].br().x - boundRect[i].tl().x;
			cout << width << endl;
			int height = -boundRect[i].tl().y + boundRect[i].br().y;
			cout << height << endl;
		//	Rect roi(boundRect[i].tl().x, boundRect[i].tl().y, width, height);

		}
		
		
//		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
*/