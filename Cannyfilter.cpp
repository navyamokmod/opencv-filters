#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
using namespace std;
using namespace cv;

void displayimage(Mat image, String windowname)
{
	imshow(windowname, image);
}

int main()
{

	Mat var1 = imread("pic.jpg", 1);
	Mat vs(var1.rows, var1.cols, CV_8UC1, Scalar(0)); //grayscaled 1d image
	Mat ed(var1.rows, var1.cols, CV_8UC1, Scalar(0)); //Edge detected 1d image
	Mat th(var1.rows, var1.cols, CV_8UC1, Scalar(0)); //Theta matrix

	namedWindow("Original", WINDOW_AUTOSIZE);
	displayimage(var1, "Original");

	//Converting colour to gray
	for (int i = 1; i < var1.rows; i++)
	{
		for (int j = 1; j < var1.cols; j++)
		{
			int R = var1.at<Vec3b>(i, j)[0];
			int G = var1.at<Vec3b>(i, j)[1];
			int B = var1.at<Vec3b>(i, j)[2];
			int a = (R + G + B) / 3;
			vs.at<uchar>(i, j) = a;
		}
	}

	//Copy gray scale to edge detect matrix
	for (int i = 0; i < var1.rows; i++)
	{
		for (int j = 0; j < var1.cols; j++)
		{
			ed.at<uchar>(i, j) = vs.at<uchar>(i, j);
		}
	}

	Mat gscale(var1.rows, var1.cols, CV_8UC1, Scalar(0)); //Theta matrix
	for (int i = 0; i < var1.rows; i++)
	{
		for (int j = 0; j < var1.cols; j++)
		{
			gscale.at<uchar>(i, j) = vs.at<uchar>(i, j);
		}
	}
	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	displayimage(gscale, "Grayscale");
	//Compute Gaussian of edge detect matrix
	int Gauss;
	for (int i = 1; i < var1.rows - 1; i++)
	{
		for (int j = 1; j < var1.cols - 1; j++)
		{
			Gauss = (1 * ed.at<uchar>(i - 1, j - 1)) + (2 * ed.at<uchar>(i - 1, j)) + (1 * ed.at<uchar>(i - 1, j + 1)) + (2 * ed.at<uchar>(i, j - 1)) + (4 * ed.at<uchar>(i, j)) + (2 * ed.at<uchar>(i, j + 1))+(1 * ed.at<uchar>(i + 1, j - 1)) + (2 * ed.at<uchar>(i + 1, j)) + (1 * ed.at<uchar>(i + 1, j + 1));
			Gauss = Gauss / 16;
			vs.at<uchar>(i, j) = Gauss;
		}
	}


	//Copy gaussian in vs to ed matrix
	for (int i = 0; i < var1.rows; i++)
	{
		for (int j = 0; j < var1.cols; j++)
		{
			ed.at<uchar>(i, j) = vs.at<uchar>(i, j);
		}
	}

	for (int i = 1; i < var1.rows - 1; i++)
	{
		for (int j = 1; j < var1.cols - 1; j++)
		{
			Gauss = (1 * ed.at<uchar>(i - 1, j - 1)) + (2 * ed.at<uchar>(i - 1, j)) + (1 * ed.at<uchar>(i - 1, j + 1)) + (2 * ed.at<uchar>(i, j - 1)) + (4 * ed.at<uchar>(i, j)) + (2 * ed.at<uchar>(i, j + 1)) + (1 * ed.at<uchar>(i + 1, j - 1)) + (2 * ed.at<uchar>(i + 1, j)) + (1 * ed.at<uchar>(i + 1, j + 1));
			Gauss = Gauss / 16;
			vs.at<uchar>(i, j) = Gauss;
		}
	}

	Mat Gaussian(var1.rows, var1.cols, CV_8UC1, Scalar(0)); //grayscaled 1d image

	for (int i = 0; i < var1.rows; i++)
	{
		for (int j = 0; j < var1.cols; j++)
		{
			Gaussian.at<uchar>(i, j) = vs.at<uchar>(i, j);
		}
	}

	namedWindow("Gaussian", WINDOW_AUTOSIZE);
	displayimage(Gaussian, "Gaussian");
	//vs contains the gausian of the gray scale matrix

	//compute Sobel using ed and update vs
	uint64 Lx = 0; uint64 Ly = 0; uint64 L = 0; uint64 theta = 0;
	uint64 Tx = 0; uint64 Ty = 0;
	for (int i = 1; i < var1.rows - 1; i++)
	{
		for (int j = 1; j < var1.cols - 1; j++)
		{
			Lx = (-1 * ed.at<uchar>(i - 1, j - 1)) + (0 * ed.at<uchar>(i - 1, j)) + (1 * ed.at<uchar>(i - 1, j + 1)) + (-2 * ed.at<uchar>(i, j - 1)) + (0 * ed.at<uchar>(i, j)) + (2 * ed.at<uchar>(i, j + 1)) + (-1 * ed.at<uchar>(i + 1, j - 1)) + (0 * ed.at<uchar>(i + 1, j)) + (1 * ed.at<uchar>(i + 1, j + 1));
			Ly = (1 * ed.at<uchar>(i - 1, j - 1)) + (2 * ed.at<uchar>(i - 1, j)) + (1 * ed.at<uchar>(i - 1, j + 1)) + (0 * ed.at<uchar>(i, j - 1)) + (0 * ed.at<uchar>(i, j)) + (0 * ed.at<uchar>(i, j + 1)) + (-1 * ed.at<uchar>(i + 1, j - 1)) + (-2 * ed.at<uchar>(i + 1, j)) + (-1 * ed.at<uchar>(i + 1, j + 1));
			Tx = Lx;
			Ty = Ly;
			if (Tx == 0)
			{
				Tx = 1;
			}
			theta = atan(Ty / Tx);

			if (theta >= 135){ theta = 135; }
			else if (theta >= 90){ theta = 90; }
			else if (theta >= 45){ theta = 45; }
			else{ theta = 0; }

			Lx = Lx*Lx;
			Ly = Ly*Ly;

			L = sqrt(Lx + Ly);

			vs.at<uchar>(i, j) = L;
			th.at<uchar>(i, j) = theta;
		}
	}
	namedWindow("Sobel", WINDOW_AUTOSIZE);
	displayimage(vs, "Sobel");
	//Non Maximum suppression
	for (int i = 1; i < var1.rows - 1; i++)
	{
		for (int j = 1; j < var1.cols - 1; j++)
		{

			//learn generic sorting code
			theta = th.at<uchar>(i, j);
			if (theta == 0)
			{
				if ((vs.at<uchar>(i, j)>vs.at<uchar>(i, j+1)) && (vs.at<uchar>(i, j)>vs.at<uchar>(i, j-1)))
				{
					ed.at<uchar>(i, j) = vs.at<uchar>(i, j);
				//	ed.at<uchar>(i, j) = 255;
				}
				else
				{
					ed.at<uchar>(i, j) = 0;
				}
			}
			else if (theta == 45)
			{
				if ((vs.at<uchar>(i, j)>vs.at<uchar>(i + 1, j-1)) && (vs.at<uchar>(i, j)>vs.at<uchar>(i - 1, j+1)))
				{
					ed.at<uchar>(i, j) = vs.at<uchar>(i, j);
				//	ed.at<uchar>(i, j) = 255;
				}
				else
				{
					ed.at<uchar>(i, j) = 0;
				}
			}
			else if (theta == 90)
			{
				if ((vs.at<uchar>(i, j)>vs.at<uchar>(i+1 , j)) && (vs.at<uchar>(i, j)>vs.at<uchar>(i-1 , j)))
				{
					ed.at<uchar>(i, j) = vs.at<uchar>(i, j);
				//	ed.at<uchar>(i, j) = 255;
				}
				else
				{
					ed.at<uchar>(i, j) = 0;
				}
			}
			else
			{
				if ((vs.at<uchar>(i, j)>vs.at<uchar>(i - 1, j-1)) && (vs.at<uchar>(i, j)>vs.at<uchar>(i + 1, j+1)))
				{
					ed.at<uchar>(i, j) = vs.at<uchar>(i, j);
				//	ed.at<uchar>(i, j) = 255;
				}
				else
				{
					ed.at<uchar>(i, j) = 0;
				}
			}
		}
		
	}
	namedWindow("Canny", WINDOW_AUTOSIZE);
	int l = 0; int u = 0;
	createTrackbar("LowerThreshold", "Canny", &l, 255);
	createTrackbar("UpperThreshold", "Canny", &u, 255);

	while (1)
	{
		for (int i = 1; i < var1.rows - 1; i++)
		{
			for (int j = 1; j < var1.cols - 1; j++)
			{

				if ((ed.at<uchar>(i, j) > l) && (ed.at<uchar>(i, j) < u))
				{
					vs.at<uchar>(i, j) = 255;
				}
				else
				{
					vs.at<uchar>(i, j) = 0;
				}
			}
		}
		displayimage(vs, "Canny");
		char ch = waitKey(5);
		if (ch == '32')
		{
			break;
		}
	}

	
	char ch = waitKey(0);
	//imshow("windows1", var2);
	return (0);
}

