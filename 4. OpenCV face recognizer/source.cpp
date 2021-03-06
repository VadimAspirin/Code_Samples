#include "stdafx.h"

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/types_c.h"
#include "opencv2/face.hpp"
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;
using namespace cv;
using namespace cv::face;

string seconds_to_time(int seconds);

double number_in_percent(double value_100_percent, double number);

void read_csv_dir(const string& filename, vector<Mat>& images,
	vector<int>& labels, vector<string>& labelsName,
	char separator = ';');

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	Ptr<FaceRecognizer> model,
	double scale = 1.3,
	bool detection = true,
	bool log = false);

Ptr<FaceRecognizer> recognition_learning(string fileName,
	double threshold = 100.0);

const int faceSavedFreq = 20;
int faceSavedCur = 0;
const int logSavedFreq = 20;
int logSavedCur = 0;
vector<int> labelsRecogn;
vector<string> labelsNameRecogn;
double threshold;
int framerate;
int timer = 0;

int main(int argc, const char** argv)
{
	VideoCapture capture;
	Mat frame, image;
	CascadeClassifier cascade;
	Ptr<FaceRecognizer> model;

	string cascadeName = "haarcascade/haarcascade_frontalface_alt.xml";
	string inputName = "mak.mp4";
	string recognitionDataName = "rec.csv";
	double threshold = 100.0;
	double scale = 1.3;
	bool detection = true;
	bool log = true;

	::threshold = threshold;

	if (!cascade.load(cascadeName))
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return -1;
	}

	if (inputName.size())
	{
		image = imread(inputName, 1);
		if (image.empty())
		{
			if (!capture.open(inputName))
				cout << "Could not read " << inputName << endl;
		}
	}

	framerate = capture.get(CAP_PROP_FPS);

	if (detection)
		model = recognition_learning(recognitionDataName, threshold);

	if (capture.isOpened())
	{
		cout << "Video capturing has been started ..." << endl;

		int t = 0;
		for (;;)
		{
			capture >> frame;
			if (frame.empty())
				break;

			Mat frame1 = frame.clone();
			detectAndDraw(frame1, cascade, model, scale, detection, log);

			char c = (char)waitKey(10);
			if (c == 27 || c == 'q' || c == 'Q')
				break;

			++t;
			if (t == framerate)
			{
				timer++;
				t = 0;
			}

			if (faceSavedCur == faceSavedFreq)
				faceSavedCur = 0;
			else
				++faceSavedCur;

			if (logSavedCur == logSavedFreq)
				logSavedCur = 0;
			else
				++logSavedCur;
		}
	}
	else if (!image.empty())
	{
		cout << "Detecting face(s) in " << inputName << endl;
		detectAndDraw(image, cascade, model, scale, detection, log);
		waitKey(0);
	}
	else
		return -1;

	return 0;
}

Ptr<FaceRecognizer> recognition_learning(string fileName, double threshold)
{
	vector<Mat> imagRecogn;

	try {
		read_csv_dir(fileName, imagRecogn, labelsRecogn, labelsNameRecogn);
	}
	catch (cv::Exception& e) {
		cerr << "Error opening file \"" << fileName << "\". Reason: " << e.msg << endl;
		exit(1);
	}

	Ptr<FaceRecognizer> model = LBPHFaceRecognizer::create(1, 8, 8, 8, 180.0);

	cout << "Learning recognition start..." << endl;
	try {
		model->train(imagRecogn, labelsRecogn);
	}
	catch (cv::Exception& e) {
		cerr << "Error: " << e.msg << endl;
		exit(1);
	}
	cout << "Learning recognition completed!" << endl;

	model->setThreshold(threshold);

	return model;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade, Ptr<FaceRecognizer> model,
	double scale, bool detection, bool log)
{
	Mat gray, smallImg;
	bool flag1 = true, flag2 = true;

	cvtColor(img, gray, COLOR_BGR2GRAY);
	double fx = 1 / scale;
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	double t = 0;
	vector<Rect_<int>> faces;
	t = (double)getTickCount();
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		//|CASCADE_FIND_BIGGEST_OBJECT
		//|CASCADE_DO_ROUGH_SEARCH
		| CASCADE_SCALE_IMAGE,
		Size(30, 30));
	t = (double)getTickCount() - t;
	printf("detection time = %g ms\n", t * 1000 / getTickFrequency());

	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Mat smallImgROI = smallImg(r);

		int prediction = -1;
		double confidence;
		if (detection)
			model->predict(smallImgROI, prediction, confidence);
		else
		{
			if (faceSavedCur == 0 && flag1)
			{
				imwrite("test/" + to_string(getTickCount()) + ".jpg", smallImgROI);
				cout << "Face saved!" << endl;
				flag1 = false;
			}
		}

		if (prediction != -1)
		{
			string box_text = format("%s (%.1f%%)", labelsNameRecogn[prediction].c_str(), 100 - number_in_percent(::threshold * 2, confidence));
			putText(img, box_text, Point(r.x*scale, r.y*scale - 10), 1, 1.0, Scalar(0, 255, 0), INTER_NEAREST);

			rectangle(img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
				cvPoint(cvRound((r.x + r.width - 1)*scale), cvRound((r.y + r.height - 1)*scale)),
				Scalar(0, 255, 0), 1.0, 1.0, INTER_NEAREST);
			if (log)
			{
				if (logSavedCur == 0 && flag2)
				{
					ofstream fout("log.txt", ios_base::app);
					fout << "h:m:s/" << seconds_to_time(timer) << " - " << labelsNameRecogn[prediction] << " - " << 100 - number_in_percent(::threshold * 2, confidence) << "%" << endl;
					fout.close();
					flag2 = false;
				}
			}
		}
		else
		{
			rectangle(img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
			cvPoint(cvRound((r.x + r.width - 1)*scale), cvRound((r.y + r.height - 1)*scale)),
			Scalar(0, 0, 255), 1.0, 1.0, INTER_NEAREST);
		}

	}
	imshow("result", img);
}

void read_csv_dir(const string& filename, vector<Mat>& images,
	vector<int>& labels, vector<string>& labelsName, char separator)
{
	ifstream file(filename.c_str(), ifstream::in);
	if (!file)
	{
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	for (int i = 0; getline(file, line); ++i)
	{
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty())
		{
			for (auto & p : std::experimental::filesystem::directory_iterator(path))
			{
				images.push_back(imread(p.path().string(), 0));
				labels.push_back(i);
			}
			labelsName.push_back(classlabel.c_str());
		}
	}
}

double number_in_percent(double value_100_percent, double number)
{
	if (value_100_percent == 0)
		return 0;
	return (number * 100) / value_100_percent;
}

string seconds_to_time(int seconds)
{
	const int SECS_MIN = 60;
	const int SECS_HR = 60 * 60;
	const int SECS_DAY = SECS_HR * 24;

	int rsecs = 0;  // remaining seconds
	int days, hours, mins;

	if (seconds >= SECS_HR) {
		hours = seconds / SECS_HR;
		rsecs = seconds % SECS_HR;
		mins = rsecs / SECS_MIN;
		rsecs = rsecs % SECS_MIN;
		return to_string(hours) + ":" + to_string(mins) + ":" + to_string(seconds);
	}
	else if (seconds >= SECS_MIN) {
		mins = seconds / SECS_MIN;
		seconds = seconds % SECS_MIN;
		return "0:" + to_string(mins) + ":" + to_string(seconds);
	}
	else
		return "0:0:" + to_string(seconds);
}