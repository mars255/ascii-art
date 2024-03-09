#include <filesystem>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

int read_path(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Please provide an image path\n";
    return -1;
  }
  if (!std::filesystem::exists(argv[1])) {
    std::cerr << "Invalid path!\n";
    return -1;
  }
  return 0;
}

int read_image(std::string image_path) { return -1; }

int main(int argc, char **argv) {
  if (read_path(argc, argv) < 0)
    return -1;
  cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);

  if (img.empty()) {
    std::cerr << "Error: Unable to read image..." << std::endl;
    return 1;
  }

  cv::imshow("Display window", img);
  int k = cv::waitKey(0); // Wait for a keystroke in the window
  return 0;
}
