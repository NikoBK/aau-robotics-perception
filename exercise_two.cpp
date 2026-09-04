#include "opencv2/core/matx.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using std::cout;

template <typename... Args>
void print(Args&&... args) {
  (cout << ... << args) << '\n';
}

/// EX: Convert it to grayscale
/// 1. Using nested loops
/// 2. Using matrix operations with numpy (Python) <- we will do a C++ equivalent
/// 3. Using the built-in OpenCV function
bool part_two()
{
  print("Part 2: Convert it to grayscale");
  cv::Mat img = cv::imread("lion.jpg");

  // Subpart 1: Grayscale with nested loops
  print("Subpart 1: Using nested loops");
  int w = img.cols; // width
  int h = img.rows; // height

  // create the nested loop based grayscale material
  cv::Mat imgGsNL(h, w, CV_8UC1);
  
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
      cv::Vec3b pixel = img.at<cv::Vec3b>(y,x);
      uchar valB = pixel[0]; // blue
      uchar valG = pixel[1]; // green
      uchar valR = pixel[2]; // red
    
      // use common grayscale formula
      uchar valGs = 0.114*valB + 0.587*valG + 0.299*valR; // gray
      imgGsNL.at<uchar>(y, x) = valGs;
    }
  }

  print("(press any key to continue)");
  cv::imshow("Input Image (BGR)", img);
  cv::imshow("Grayscale (Nested Loops)", imgGsNL);
  print("subpart 1 complete!\n");
  cv::waitKey(0);

  // subpart 2: grayscale using matrix operations
  print("subpart 2: using matrix operations");


  // we obviously can not use NumPy here so we are using a C++ alternative
  cv::Mat channels[3]; // 0 -> 2 = B,G,R
  cv::split(img, channels);

  // create the matrix based grayscale material using a common grayscale formula
  cv::Mat imgGsMO = 0.114 * channels[0]
                  + 0.587 * channels[1]
                  + 0.299 * channels[2];

  print("(press any key to continue");
  // cv::imshow("Input Image (BGR)", img);
  cv::imshow("Grayscale (Matrix Operations)", imgGsMO);
  print("subpart 2 complete!\n");
  cv::waitKey(0);

  // subpart 3: grayscale using the built-in function
  print("subpart 3: using the built-in OpenCV function");
  cv::Mat imgGsBI;
  cv::cvtColor(img, imgGsBI, cv::COLOR_BGR2GRAY);

  print("(press any key to continue)");
  cv::imshow("Grayscale (Built-In)", imgGsBI);
  print("subpart 3 complete!\n");
  cv::waitKey(0);
  return true;
}

/// EX: Use OpenCV to load and display a color image
/// This is the same as half of exercise 1, part 2.
bool part_one()
{
  print("Part 1: Use OpenCV to load and display a color image");
  cv::Mat img = cv::imread("lion.jpg");
  if (img.empty()) { // check whether or not the image is loaded
    print("Error: Image 'lion.jpg' is empty");
    return false;
  }
  cv::imshow("Input Image (BGR)", img);
  print("Part 1 complete!\n");
  cv::waitKey(0);
  return true;
}

int main()
{
  print("Starting exercise 2");
  if (!part_one()) { return -1; }
  if (!part_two()) { return -1; }
  print("Exercise 2 complete!\n");
  return 0;
}
