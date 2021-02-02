#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat drawhistogram(Mat image)
{
	int histogram[256];

    for(int i = 0; i < 255; i++)
    {
	histogram[i]=0;
    }

for(int y = 0; y < image.rows; y++)
{
for(int x = 0; x < image.cols; x++)
{
histogram[(int)image.at<uchar>(y,x)]++;
}}



    // draw the histograms
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double) hist_w/256);
 
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

    int max = histogram[0];
    for(int i = 1; i < 256; i++){
        if(max < histogram[i]){
            max = histogram[i];
        }
    }
 
   // normalize the histogram between 0 and histImage.rows
 
    for(int i = 0; i < 255; i++){
        histogram[i] = ((double)histogram[i]/max)*histImage.rows;
    }
 
 
    // draw the intensity line for histogram
    for(int i = 0; i < 255; i++)
    {
        line(histImage, Point(bin_w*(i), hist_h),
                              Point(bin_w*(i), hist_h - histogram[i]),
             Scalar(0,0,0), 1, 8, 0);
    }
 
    // display histogram
    //namedWindow("Intensity Histogram", CV_WINDOW_AUTOSIZE);
    //imshow("Intensity Histogram", histImage);
 
    //namedWindow("Image", CV_WINDOW_AUTOSIZE);
    //imshow("Image", image);
//imwrite("histogram.bmp", histImage);

return histImage;

}


int main(void)
{
	Mat originalImage = imread("House_width_times4.bmp");
	//Mat modifiedImage = imread("House_width_times4.bmp");
	Mat *image = &originalImage;

	if (originalImage.empty())
	{
		cout << "fail to load image !" << endl;
		return -1;
	}

	Mat negativeImage = Mat::zeros(image->rows, image->cols, CV_8UC1);
	image = &negativeImage;


	for (int i=0; i<originalImage.cols ; i++)
	{
	for (int j=0 ; j<originalImage.rows ; j++)
 	{     
 	negativeImage.at<uchar>(Point(i,j)) = 255-originalImage.at<uchar>(Point(i,j)); 
 	}
 	}

	imwrite("output.bmp", negativeImage);
//drawhistogram(originalImage);
//drawhistogram(negativeImage);
imwrite("inputHistogram.bmp", drawhistogram(originalImage));
imwrite("modifiedHistogram.bmp", drawhistogram(negativeImage));
	//namedWindow("opencv sample", CV_WINDOW_AUTOSIZE);
	//imshow("opencv sample", negativeImage);	
}


