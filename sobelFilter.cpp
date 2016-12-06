#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;
int main (){
Mat var=imread("life.jpg",1);
int A[3][3];
int gx[3][3]={-1,0,1,-2,0,2,-1,0,1};
int gy[3][3]={1,2,1,0,0,0,-1,-2,-1};

int i,j,k,l;
Mat var1(var.rows,var.cols,CV_8UC3,Scalar(0,0,0));
for(int i=1;i<var.rows-1;i++)
	{		
		for(int j=1;j<var.cols-1;j++)

		{	int gx0=0; int gx1=0;int gx2=0;
			int gy0=0;int gy1=0;int gy2=0;
			{	for (k=-1;k<=1;k++)
					{	for(l=-1;l<=1;l++)
						{
						gx0=gx0+var.at<Vec3b>(k+i,l+j)[0]*gx[k+1][l+1];
						gx1=gx1+var.at<Vec3b>(k+i,l+j)[1]*gx[k+1][l+1];
						gx2=gx2+var.at<Vec3b>(k+i,l+j)[2]*gx[k+1][l+1];
						gy0=gy0+var.at<Vec3b>(k+i,l+j)[0]*gy[k+1][l+1];
						gy1=gy1+var.at<Vec3b>(k+i,l+j)[1]*gy[k+1][l+1];
						gy2=gy2+var.at<Vec3b>(k+i,l+j)[2]*gy[k+1][l+1];

						}
					}
			}
int g0,g1,g2;
g0=sqrt(gx0*gx0+gy0*gy0);
g1=sqrt(gx1*gx1+gy1*gy1);
g2=sqrt(gx2*gx2+gy2*gy2);
var1.at<Vec3b>(i,j)[0]=g0;
var1.at<Vec3b>(i,j)[1]=g1;
var1.at<Vec3b>(i,j)[2]=g2;


		}
	}



namedWindow("windows1",WINDOW_AUTOSIZE);
	imshow("windows1",var1);
	waitKey(0);
	return 0;
}
