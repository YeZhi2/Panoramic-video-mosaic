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
}//ȫ��ƴ�Ӻ���

int main()
{
	VideoCapture cap0("D:\\bishe\\hanjia\\2-10\\test\\1.mp4");
	VideoCapture cap1("D:\\bishe\\hanjia\\2-10\\test\\2.mp4");
	
	string video_name = "out.avi";
	cv::VideoWriter writer;
	int isColor = 1;
	int frame_fps = 30;
	writer = VideoWriter(video_name, -1, frame_fps, Size(320, 240), isColor);//����д�����Ƶ�ļ�

	bool stop = false;
	vector<Mat>imgs;
	Mat resultMat1;
	Mat videoPlay0, videoPlay1;
	int count = 60;//��Ϊstitchƴ��ʵ��̫���������ö�ȡһ����ͼ��	

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

		writer.write(resultMat1);//д��һ֡

		imgs.clear();//��ʵ��vectorȥƵ������ǲ����ʵģ���û���ʹ�����飬clear����Ҳ������ȫ�����
		waitKey(100);
		count--;
	}

	writer.release();
	return 0;
}