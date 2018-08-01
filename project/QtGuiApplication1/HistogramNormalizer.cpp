#include "HistogramNormalizer.h"

HistogramNormalizer::HistogramNormalizer()
{
}

HistogramNormalizer::~HistogramNormalizer()
{
}

void HistogramNormalizer::run(cv::Mat& input)
{
	std::vector<float> histogram;
	calculateHistogram(input, histogram);
	cv::MatIterator_<short> it = input.begin<short>(), it_end = input.end<short>();
	for (; it != it_end; ++it) {
		*it = histogram[*it];
	}
}

void HistogramNormalizer::calculateHistogram(const cv::Mat& depth, std::vector<float>& histogram)
{
	int depthTypeSize = CV_ELEM_SIZE(depth.type());
	int histogramSize = pow(2., 8 * depthTypeSize);
	histogram.resize(histogramSize, 0.0f);

	unsigned int nNumberOfPoints = 0;
	cv::MatConstIterator_<short> it = depth.begin<short>(), it_end = depth.end<short>();
	for (; it != it_end; ++it) {
		if (*it != 0) {
			++histogram[*it];
			++nNumberOfPoints;
		}
	}

	for (int nIndex = 1; nIndex < histogramSize; ++nIndex)
	{
		histogram[nIndex] += histogram[nIndex - 1];
	}

	if (nNumberOfPoints != 0)
	{
		for (int nIndex = 1; nIndex < histogramSize; ++nIndex)
		{
			histogram[nIndex] = (256.0 * (1.0f - (histogram[nIndex] / nNumberOfPoints)));
		}
	}
}