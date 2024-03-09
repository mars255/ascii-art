#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <opencv2/core/matx.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <ostream>
#include <string>
#include <vector>

const std::string scale =
    "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";

struct charImage {
  std::vector<std::vector<char>> pixels;
};

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

int process_pixels(cv::Mat image) {
  charImage new_im;
  imwrite("output.jpg", image);

  for (int y = 1; y < image.rows - 1; ++y) {
    for (int x = 1; x < image.cols - 1; ++x) {
      std::cout << scale[std::floor(64 * image.at<uint8_t>(y, x) / 255)];
    }
    std::cout << "\n";
  }
  std::cout << image.rows << "\n" << image.cols << std::endl;
  return 0;
}
cv::Mat change_size(int x, int y, cv::Mat &im) {
  cv::Mat result;
  cv::resize(im, result, cv::Size(x, y), 0, 0, cv::INTER_LINEAR);
  return result;
}

int read_image(const std::string image_path) {

  charImage im;
  cv::Mat img = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
  if (img.empty()) {
    std::cerr << "Error: Unable to read image..." << std::endl;
    return -1;
  }
  process_pixels(change_size(100, 100, img));

  return 0;
}

int main(int argc, const char **argv) {
  if (read_path(argc, argv) < 0) {
    return -1;
  }

  if (read_image(argv[1]) < 0) {
    return -1;
  }
  return 0;
}
