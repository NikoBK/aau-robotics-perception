#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>

using std::cout;
using std::sqrt;
using std::exp;
using std::pow;
using std::round;

template <typename... Args>
void print(Args&&... args) {
  (cout << ... << args) << '\n';
}

/// pass the image by reference without allowing displayImg to modify it.
/// also keeps every displayed image same size.
void displayImg(const std::string& name, const cv::Mat& img) {
  cv::namedWindow(name, cv::WINDOW_NORMAL);
  cv::resizeWindow(name, 400, 260);
  cv::imshow(name, img);
}

cv::Mat convolve(const cv::Mat& img, const cv::Mat& kernel)
{
  int kernelSize = kernel.rows;
  double kernelSum = cv::sum(kernel)[0];

  cv::Mat output(
      img.rows - kernelSize,
      img.cols - kernelSize,
      img.type()
  );

  for (int y = 0; y < output.rows; y++)
  {
    for (int x = 0; x < output.cols; x++)
    {
      double sum = 0.0;

      for (int ky = 0; ky < kernelSize; ky++)
      {
        for (int kx = 0; kx < kernelSize; kx++)
        {
          sum += img.at<uchar>(y + ky, x + kx) * kernel.at<double>(ky,kx);
        }
      }
      output.at<uchar>(y,x) = sum / kernelSum;
    }
  }
  return output;
}

/// sD: Standard Deviation (sigma)
cv::Mat gaussianKernel(int kernelSize, double sD)
{
  int radius = kernelSize / 2;
  cv::Mat kernel(kernelSize, kernelSize, CV_64F);

  // Create one dimensional Gaussian value
  std::vector<double> kernel1D(kernelSize);

  // crate one dimensional kernel
  for (int x = -radius; x <= radius; x++) {
    kernel1D[x + radius] = 1.0 / (sD * sqrt(2.0 * M_PI)) * exp(-0.5 * pow(x / sD, 2));
  }

  // create two dimensional kernel (multiplying the 1d values)
  for (int y = 0; y < kernelSize; y++) {
    for (int x = 0; x < kernelSize; x++) {
      kernel.at<double>(y, x) = kernel1D[y] * kernel1D[x];
    }
  }

  // scale so that the corner is 1 
  double sF = 1.0 / kernel.at<double>(0, 0); // scale factor, pivot: bottom left
  for (int y = 0; y < kernelSize; y++) {
    for (int x = 0; x < kernelSize; x++) {
      kernel.at<double>(y, x) = round(kernel.at<double>(y, x) * sF);
    }
  }

  return kernel;
}

/// EX. Implement a Gaussian blur filter with configurable kernel size
bool part_three()
{
  print("part 3: implement a Gaussian blur filter with configurable kernel size");

  // (implementation is based on the provided python solutions)
  cv::Mat img = cv::imread("lion.jpg", cv::IMREAD_GRAYSCALE);
  cv::Mat kernel = gaussianKernel(7, 2.2);
  cv::Mat gaussianImg = convolve(img, kernel);

  displayImg("Input Image (Grayscaled)", img);
  displayImg("Gaussian Blur (k. size: 7, sigma: 2.2)", gaussianImg);
  print("part 3 complete!\n");
  cv::waitKey(0);
  return true;
}

cv::Mat meanFilter(const cv::Mat& img, int kernelSize)
{
  int kernelArea = kernelSize * kernelSize;

  cv::Mat output(
      img.rows - kernelSize,
      img.cols - kernelSize,
      img.type()
  );

  for (int y = 0; y < output.rows; y++)
  {
    for (int x = 0; x < output.cols; x++)
    {
      int sum = 0;
      for (int ky = 0; ky < kernelSize; ky++)
      {
        for (int kx = 0; kx < kernelSize; kx++)
        {
          sum += img.at<uchar>(y + ky, x + kx);
        }
      }
      output.at<uchar>(y,x) = sum / kernelArea;
    }
  }
  return output;
}

/// EX: Implement a mean filter with configurable kernel size
bool part_two()
{
  print("part 2: implement a meant filter with configurable kernel size");
  // the provided solutions for Python operate on a grayscale image. Each pixel is one value instead of BGR, I will therefore read the image as grayscale here too
  cv::Mat img = cv::imread("lion.jpg", cv::IMREAD_GRAYSCALE);
  cv::Mat meanImg = meanFilter(img, 7);

  displayImg("Input Image (Grayscaled)", img);
  displayImg("Mean Filter", meanImg);
  print("part 2 complete!\n");
  cv::waitKey(0);
  return true;
}

/// EX: Use OpenCV to load and display lion.jpg
bool part_one()
{
  print("Part 1: Use OpenCV to load and display lion.jpg");
  cv::Mat img = cv::imread("lion.jpg");
  if (img.empty()) { // check whether or not the image is loaded
    print("Error: Image 'lion.jpg' is empty");
    return false;
  }
  displayImg("Input Image (BGR)", img);
  print("Part 1 complete!\n");
  cv::waitKey(0);
  return true;
}

int main()
{
  print("Starting exercise 3");
  if (!part_one()) { return -1; }
  if (!part_two()) { return -1; }
  if (!part_three()) { return -1; }
  print("Exercise 3 complete!\n");
  return 0;
}
