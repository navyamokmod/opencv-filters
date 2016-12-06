#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main( int argc, char** argv )
{
 
 namedWindow( "Original Image" , CV_WINDOW_AUTOSIZE );
 namedWindow( "Smoothed Image" , CV_WINDOW_AUTOSIZE );

 
 Mat src = imread( "light.jpg", 1 );
 imshow( "Original Image", src );

 Mat dst;
 char zBuffer[35];

 for ( int i = 1; i < 31; i = i + 2 )
 { 
       blur( src, dst, Size( i, i ) );
     
      imshow( "Smoothed Image", dst );

      
      int c = waitKey(0);

      
      
 }

 
 dst = Mat::zeros( src.size(), src.type() );

 imshow( "Smoothed Image", dst );
 

 waitKey(0);
     
 return 0;

}

