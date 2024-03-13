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
void print_usage(const char *program_name) {
  std::cerr << "Usage: " << program_name << " path [-w width] [-h height]\n";
  std::cerr << "If only width or height are provided, the original aspect "
               "ratio will be preserved\n";
}

int read_path(int argc, const char **argv) {
  if (argc < 2) {
    print_usage(argv[0]);
    return -1;
  }

  std::string path = argv[1];

  if (!std::filesystem::exists(path)) {
    std::cerr << "Invalid path!\n";
    return -1;
  }

  int width = -1;
  int height = -1;

  for (int i = 2; i < argc; ++i) {
    if (std::string(argv[i]) == "-w") {
      if (i + 1 < argc) {
        width = std::stoi(argv[i + 1]);
        ++i;
      } else {
        std::cerr << "Width value missing after -w\n";
        return -1;
      }
    } else if (std::string(argv[i]) == "-h") {
      if (i + 1 < argc) {
        height = std::stoi(argv[i + 1]);
        ++i;
      } else {
        std::cerr << "Height value missing after -h\n";
        return -1;
      }
    } else {
      std::cerr << "Unknown option: " << argv[i] << std::endl;
      return -1;
    }
  }
  return 0;
}

int process_pixels(cv::Mat image) {
  for (int y = 1; y < image.rows - 1; ++y) {
    for (int x = 1; x < image.cols - 1; ++x) {
      std::cout << scale[std::floor(64 * image.at<uint8_t>(y, x) / 255)];
    }
    std::cout << "\n";
  }
  std::cout << image.rows << "\n" << image.cols << std::endl;
  return 0;
}
void change_size(int height, int width, cv::Mat &im) {
  cv::resize(im, im, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
}

int read_image(const std::string image_path) {

  charImage im;
  cv::Mat img = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
  if (img.empty()) {
    std::cerr << "Error: Unable to read image..." << std::endl;
    return -1;
  }
  int width = img.size().width;
  int height = img.size().height;
  double ratio = static_cast<double>(width) / static_cast<double>(height);
  std::cout << ratio << std::endl;

  change_size(200, std::floor(ratio * 200), img);
  process_pixels(img);

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
