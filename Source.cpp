#include <opencv2/opencv.hpp>
#include "iostream"
#include <cstdlib>
#include <ctime>
#include <iomanip>

#ifdef _WIN32
#include <io.h>
#elif __linux__
#include <dirent.h>
#endif

using namespace std;
using namespace cv;

int pic2video();
int video2pic(std::string videoPath, std::string picPath, int step = 1);

int main(int argc, char* argv[])
{
	if (argc<3)
	{
		std::cout<<"Lacks arguments!\n";
		return -1;
	}	
	video2pic(argv[0], argv[1], 5);
}

int video2pic(std::string videoPath, std::string picPath, int step)
{
	VideoCapture videoIn(videoPath);
	cv::Mat img;
	std::stringstream strstream;
	int frameNum = videoIn.get(cv::CAP_PROP_FRAME_COUNT);
	std::cout <<"frameNum = "<< frameNum << endl;

	for (size_t i = 0; i< frameNum; i++)
	{
		videoIn >> img;
		if (i%step)
		{			
			continue;
		}		
		strstream << picPath <<setw(6)<<setfill('0')<< i/step << ".jpg";
		cv::imwrite(strstream.str(),img);
		strstream.str("");
		if (i%10==0)
		{
			std::cout << i << endl;
		}
	}
	return 0;
}

int pic2video()
{
	// 设定文件路径
	string path = "D:\\[PCL] pedestrianlights\\download\\imagesequences\\01\\";
	
	// 初始化视频写入器
	bool isColor = true;
	int frameW = 640;
	int frameH = 480;
	VideoWriter writer("D:\\[PCL] pedestrianlights\\download\\imagesequences\\01\\out.avi", cv::VideoWriter::fourcc('D', 'I', 'V', 'X'), 25, Size(240, 320), isColor);
	if (!writer.isOpened())
	{
		cout << "Could not establish Videowriter." << endl;
		getchar();
		return -1;
	}
	
	// 查找jpg文件
#ifdef _WIN32
	struct _finddata_t fileinfo;
	Mat pic;
	intptr_t hFile;
	string pathjpg = path + "*.png";
	hFile = _findfirst(pathjpg.c_str(), &fileinfo);
	if ((hFile) == -1)
	{
		cout << "No JPG File!";
		getchar();
		return -1;
	}
	cout << endl << "NOW JPG ......" << endl;
	do {
		pic = imread(path + fileinfo.name);
		writer.write(pic);
		imshow("Video Preview", pic);
		waitKey(1);		
	} while (_findnext(hFile, &fileinfo) == 0);
	_findclose(hFile);
#elif __linux__
	DIR* dir = opendir((path).c_str());  //打开指定目录
	dirent* p = nullptr;  //定义遍历指针
	int counter = 0;
	while((p = readdir(dir)) != NULL)  //开始逐个遍历
	{
		cout << endl << "NOW JPG ......" << endl;
		// 过滤"."和".."隐藏文件
		if(p->d_name[0] != '.')  //d_name是一个char数组，存放当前遍历到的文件名  
		{
			string strName = p->d_name;
			if (strName.substr(strName.length()-3, 3)=="png")
			{
				cv::Mat pic = imread(path+strName);
				writer.write(pic);
				imshow("Video Preview", pic);
				waitKey(1);	
			}
			
		}
	}
	closedir(dir);  //关闭指定目录 
#endif

	cout << "OK" << endl;
	getchar();
	return 0;
}

