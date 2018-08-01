#pragma once

#include <opencv2/opencv.hpp>

class HistogramNormalizer
{
public:
	HistogramNormalizer();
	~HistogramNormalizer();
	static void run(cv::Mat& input);
private:
	static void calculateHistogram(const cv::Mat& depth, std::vector<float>& histogram);
};

