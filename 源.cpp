#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int threshold_value = 100;
int threshold_max = 255;
Mat src, dst;
void Demo_Contours(int, void*);
int main(int argv, char** argc) {
	src = imread("D:/1.jpg");
	if (src.empty()) {
		cout << "can not be loaded..." << endl;
	}
	namedWindow("输入", WINDOW_FREERATIO);
	imshow("输入", src);
	namedWindow("output_win", WINDOW_FREERATIO);
	cvtColor(src, src, COLOR_BGR2GRAY);
//1.发现轮廓
    //输入图像
	//发现全部的轮廓
	//outputArray,hierachy图像的拓扑结构
	//int mode 轮廓返回的模式
	//int method 发现方法
	//Point offset=Point()轮廓像素的位移，默认（0，0）没有位移
	const char* trackbar_title = "thereshold value";
	createTrackbar(trackbar_title, "output_win", &threshold_value, threshold_max, Demo_Contours);
	Demo_Contours(0, 0);
//2.绘制轮廓
	//输入图像
	//发现全部的轮廓
	//轮廓索引号
	//绘制轮廓的颜色
	//绘制轮廓的线宽
	//线的类型
	//拓扑结构图
	//最大层数，0只绘制当前的，1表示绘制当前以及内嵌的轮廓
	//轮廓位移（可选）
	
	waitKey(0);
	destroyAllWindows;
	return 0;
}
void Demo_Contours(int,void*){
	//通道分离
	vector<Mat>channels;
	split(src, channels);
	Mat blue = channels.at(0);
	//二值化
	Mat canny_output;
	vector<vector<Point>>contours;
	vector<Vec4i>hierachy;
	Canny(blue, canny_output, threshold_value, threshold_value * 2, 3, false);
	//找边框
	findContours(canny_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	dst = Mat::zeros(src.size(), CV_8UC3);
	RNG rng(12345);
	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, i, color, 2, 8, hierachy, 0, Point(0, 0));
	}
	imshow("output_win", dst);
}