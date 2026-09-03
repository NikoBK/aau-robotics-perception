#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using std::cout;

template <typename... Args>
void print(Args&&... args)
{
    (std::cout << ... << args) << '\n';
}

int main()
{
    print("OpenCV version: ", CV_VERSION);
    return 0;
}
