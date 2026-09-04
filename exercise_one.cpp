/**
 * file: main.cpp
 * date: sep 4 2026
 * author: nikobk
 */

#include "opencv2/core/version.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using std::cout;
using std::string;

template <typename... Args>
void print(Args&&... args)
{
    (cout << ... << args) << '\n';
}

/// EX: Install OpenCV
/// Not really a whole lot to this, we will print the OpenCV version to prove it is installed.
bool part_one() {
    print("Part 1: Install OpenCV");
    print("OpenCV version: ", CV_VERSION, " (OpenCV is installed)\n");
    return true;
}

/// EX: Make a program which loads and displays a grayscale image using OpenCV.
/// To do this we simply load the image without any flags (default is BGR), convert the source to grayscale and display that using imshow.
bool part_two() {
    print("Part 2: Make a program which loads and displays a grayscale image using OpenCV.");
    cv::Mat img = cv::imread("lion.jpg");
    if (img.empty()) { // check whether or not the image is loaded
      print("Error: Image 'lion.jpg' is empty");
      return false;
    }
    // define the grayscale image
    cv::Mat imgGs;
    cv::cvtColor(img, imgGs, cv::COLOR_BGR2GRAY);
    cv::imshow("Input Image (BGR)", img);
    cv::imshow("Grayscale Image", imgGs);
    print("Part 2 complete!\n");
    cv::waitKey(0);
    return true;
}

/// EX: Make a program which loops over each pixel and prints its value, row by row.
/// Here we assume this is for the default BGR lion and not the grayscaled one!
bool part_three() {
  print("Part 3: Make a program which loops over each pixel and prints its value, row by row.");
  cv::Mat img = cv::imread("lion.jpg");
  int w = img.cols;
  int h = img.rows;

  print("image width: ", w, ", height: ", h);

  int pixelCount = 0;
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
      pixelCount++;
      uchar pixel = img.at<uchar>(y,x);
      string value = std::to_string(static_cast<int>(pixel));
      print("Pixel: ", pixelCount, "(x:", x, ",y:", y, ")", " value: ", value);
    }
  }
  print("Part 3 complete!\n");
  return true;
}

bool exercise_one() {
    print("Starting exercise 1");
    if (!part_one()) { return false; }
    if (!part_two()) { return false; }
    if (!part_three()) { return false; }
    print("Exercise 1 complete!\n");
    return true;
}

int main()
{
    if (!exercise_one()) {
      return -1;
    }
    return 0;
}

