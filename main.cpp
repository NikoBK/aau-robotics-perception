#include <iostream>
#include <opencv2/opencv.hpp>

using std::cout;

template <typename... Args>
void print(Args&&... args)
{
    (cout << ... << args) << '\n';
}

int main()
{
    print("OpenCV version: ", CV_VERSION);
    return 0;
}
