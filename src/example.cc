#include <chrono>
#include <vector>
#include <opencv2/opencv.hpp>
#include "libcbdetect/config.h"
#include "libcbdetect/boards_from_cornres.h"
#include "libcbdetect/find_corners.h"
#include "libcbdetect/plot_boards.h"
#include "libcbdetect/plot_corners.h"
#include <iostream>
using namespace std;
using namespace std::chrono;

void detect(const char *str, cbdetect::CornerType corner_type) {
  cbdetect::Corner corners;
  std::vector<cbdetect::Board> boards;
  cbdetect::Params params;
  params.corner_type = corner_type;

  cv::Mat img = cv::imread(str, cv::IMREAD_COLOR);

  auto t1 = high_resolution_clock::now();
  cbdetect::find_corners(img, corners, params);

  auto t2 = high_resolution_clock::now();
  cbdetect::plot_corners(img, corners);

  auto t3 = high_resolution_clock::now();
  cbdetect::boards_from_corners(img, corners, boards, params);

  auto t4 = high_resolution_clock::now();
  printf("Find corners took: %.3f ms\n", duration_cast<microseconds>(t2 - t1).count() / 1000.0);
  printf("Find boards took: %.3f ms\n", duration_cast<microseconds>(t4 - t3).count() / 1000.0);
  printf("Total took: %.3f ms\n", duration_cast<microseconds>(t2 - t1).count() / 1000.0
      + duration_cast<microseconds>(t4 - t3).count() / 1000.0);
  cbdetect::plot_boards(img, corners, boards, params);
}

int main(int argc, char *argv[]) {
  printf("chessboards...");
  detect("/home/gu/test3.4/libcbdetect/example_data/c8.png", cbdetect::SaddlePoint);//两种模式

 // printf("deltilles...");
 // detect("/home/gu/test3.4/libcbdetect/example_data/e2.png", cbdetect::MonkeySaddlePoint);
  return 0;
}
