#include <filesystem>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

const std::string scale =
    "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";

int read_path(int argc, const char **argv) {
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

int read_image(const std::string image_path) {

  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

  if (img.empty()) {
    std::cerr << "Error: Unable to read image..." << std::endl;
    return -1;
  }

  return 0;
}

int main(int argc, const char **argv) {
  std::cout << scale << "\n";
  if (read_path(argc, argv) < 0) {
    return -1;
  }

  if (read_image(argv[1]) < 0) {
    return -1;
  }
  return 0;
}
