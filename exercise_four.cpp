#include "opencv2/core.hpp"
#include "opencv2/core/hal/interface.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using std::cout;

template <typename... Args>
void print(Args&&... args) {
  (cout << ... << args) << '\n';
}

void displayImg(const std::string& name, const cv::Mat& img) {
  cv::namedWindow(name, cv::WINDOW_NORMAL);
  cv::resizeWindow(name, 400, 260);
  cv::imshow(name, img);
}

/// EX: Test Canny edge detector on your own image (experiment with different parameters)
bool part_three()
{
  print("Part 3: Test canny edge detector on your own image");
  cv::Mat img = cv::imread("lion.jpg", cv::IMREAD_GRAYSCALE);

  cv::Mat canny1;
  cv::Mat canny2;
  cv::Mat canny3;

  // Different threshold values
  cv::Canny(img, canny1, 50, 150);
  cv::Canny(img, canny2, 100, 200);
  cv::Canny(img, canny3, 150, 300);

  displayImg("Input Image (Grayscaled)", img);
  displayImg("Canny 50/150", canny1);
  displayImg("Canny 100/200", canny2);
  displayImg("Canny 150/300", canny3);
  print("Part 3 complete!\n");
  cv::waitKey(0);
  cv::destroyAllWindows();
  return true;
}

/// EX: What are the results of using Sobel kernels on RGB vs grayscale images?
bool part_two()
{
  print("Part 2: Sobel on RGB vs grayscale");

  cv::Mat bgr = cv::imread("lion.jpg", cv::IMREAD_COLOR);
  cv::Mat gray;
  cv::cvtColor(bgr, gray, cv::COLOR_BGR2GRAY);
  
  cv::Mat sobelBGR, sobelGray;
  cv::Sobel(bgr, sobelBGR, CV_64F, 1, 0, 3);
  cv::Sobel(gray, sobelGray, CV_64F, 1, 0, 3);

  cv::Mat sobelBGRAbs, sobelGrayAbs;
  cv::convertScaleAbs(sobelBGR, sobelBGRAbs);
  cv::convertScaleAbs(sobelGray, sobelGrayAbs);

  displayImg("Sobel BGR", sobelBGRAbs);
  displayImg("Sobel Grayscale", sobelGrayAbs);
  print("Part 2 complete!\n");
  cv::waitKey(0);
  cv::destroyAllWindows();

  return true;
}

/// EX: Apply horizontal and vertical Sobel kernels to find edges in an image of your own choice (use the function Sobel) 
bool part_one()
{
  print("Part 1: Apply horizontal and vertical Sobel kernels to find edges in an image of your own choice");
  cv::Mat img = cv::imread("lion.jpg", cv::IMREAD_GRAYSCALE);
  if (img.empty()) {
    print("Error: could not load image");
    return false;
  }

  cv::Mat sobelX;
  cv::Mat sobelY;

  // horizontal edges
  cv::Sobel(img, sobelX, CV_64F, 1, 0, 3);

  // Vertical edges
  cv::Sobel(img, sobelY, CV_64F, 0, 1, 3);

  // absolute values (conversion for better display)
  cv::Mat sobelXAbs;
  cv::Mat sobelYAbs;
  cv::convertScaleAbs(sobelX, sobelXAbs);
  cv::convertScaleAbs(sobelY, sobelYAbs);

  displayImg("Input Image (Grayscaled)", img);
  displayImg("Sobel X", sobelXAbs);
  displayImg("Sobel Y", sobelYAbs);
  print("Part 1 complete!\n");
  cv::waitKey(0);
  cv::destroyAllWindows();
  return true;
}

int main()
{
  print("Starting exercise 4");
  if (!part_one()) { return -1; }
  if (!part_two()) { return -1; }
  if (!part_three()) { return -1; }
  print("Exercise 4 complete!\n");
  return 0;
}
