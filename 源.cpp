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
	namedWindow("����", WINDOW_FREERATIO);
	imshow("����", src);
	namedWindow("output_win", WINDOW_FREERATIO);
	cvtColor(src, src, COLOR_BGR2GRAY);
//1.��������
    //����ͼ��
	//����ȫ��������
	//outputArray,hierachyͼ������˽ṹ
	//int mode �������ص�ģʽ
	//int method ���ַ���
	//Point offset=Point()�������ص�λ�ƣ�Ĭ�ϣ�0��0��û��λ��
	const char* trackbar_title = "thereshold value";
	createTrackbar(trackbar_title, "output_win", &threshold_value, threshold_max, Demo_Contours);
	Demo_Contours(0, 0);
//2.��������
	//����ͼ��
	//����ȫ��������
	//����������
	//������������ɫ
	//�����������߿�
	//�ߵ�����
	//���˽ṹͼ
	//��������0ֻ���Ƶ�ǰ�ģ�1��ʾ���Ƶ�ǰ�Լ���Ƕ������
	//����λ�ƣ���ѡ��
	
	waitKey(0);
	destroyAllWindows;
	return 0;
}
void Demo_Contours(int,void*){
	//ͨ������
	vector<Mat>channels;
	split(src, channels);
	Mat blue = channels.at(0);
	//��ֵ��
	Mat canny_output;
	vector<vector<Point>>contours;
	vector<Vec4i>hierachy;
	Canny(blue, canny_output, threshold_value, threshold_value * 2, 3, false);
	//�ұ߿�
	findContours(canny_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	dst = Mat::zeros(src.size(), CV_8UC3);
	RNG rng(12345);
	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, i, color, 2, 8, hierachy, 0, Point(0, 0));
	}
	imshow("output_win", dst);
}