#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/stitching.hpp>
#include <vector>
using namespace std;
using namespace cv;

void stitch(vector<Mat> imgs, Mat& resultMat)
{
	bool flag = true;
	Stitcher stitcher = Stitcher::createDefault(flag);
	Stitcher::Status status = stitcher.stitch(imgs, resultMat);
}//全景拼接函数

int main()
{
	VideoCapture cap0("D:\\bishe\\hanjia\\2-10\\test\\1.mp4");
	VideoCapture cap1("D:\\bishe\\hanjia\\2-10\\test\\2.mp4");
	
	string video_name = "out.avi";
	cv::VideoWriter writer;
	int isColor = 1;
	int frame_fps = 30;
	writer = VideoWriter(video_name, -1, frame_fps, Size(320, 240), isColor);//定义写入的视频文件

	bool stop = false;
	vector<Mat>imgs;
	Mat resultMat1;
	Mat videoPlay0, videoPlay1;
	int count = 60;//因为stitch拼接实在太卡，想设置读取一部分图像	

	namedWindow("videoplay0", WINDOW_AUTOSIZE);
	namedWindow("videoplay1", WINDOW_AUTOSIZE);
	namedWindow("stitch", WINDOW_AUTOSIZE);

	while (count)
	{
		cap0 >> videoPlay0;
		cap0.read(videoPlay0);
		imshow("videoplay0", videoPlay0);

		cap1 >> videoPlay1;
		cap1.read(videoPlay1);
		imshow("videoplay1", videoPlay1);

		imgs.push_back(videoPlay0);
		imgs.push_back(videoPlay1);

		stitch(imgs, resultMat1);
		resize(resultMat1, resultMat1, Size(320,240), 0, 0, INTER_AREA);
		imshow("stitch", resultMat1);

		writer.write(resultMat1);//写入一帧

		imgs.clear();//其实用vector去频繁清除是不合适的，最好还是使用数组，clear（）也不是完全清除，
		waitKey(100);
		count--;
	}

	writer.release();
	return 0;
}