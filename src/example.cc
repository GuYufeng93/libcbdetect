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
  cbdetect::Corner corners; //角点对象
  std::vector<cbdetect::Board> boards; //棋盘格对象
  cbdetect::Params params; //棋盘格类型
  params.corner_type = corner_type;

  cv::Mat img = cv::imread(str, cv::IMREAD_COLOR);

  auto t1 = high_resolution_clock::now();
  cbdetect::find_corners(img, corners, params); //1 得到角点

  auto t2 = high_resolution_clock::now();
  cbdetect::plot_corners(img, corners); //2 可视化棋盘格角点

  auto t3 = high_resolution_clock::now();
  cbdetect::boards_from_corners(img, corners, boards, params); //3 得到棋盘格
  // 还需要对点进行重排列
  auto t4 = high_resolution_clock::now(); 
  printf("Find corners took: %.3f ms\n", duration_cast<microseconds>(t2 - t1).count() / 1000.0);
  printf("Find boards took: %.3f ms\n", duration_cast<microseconds>(t4 - t3).count() / 1000.0);
  printf("Total took: %.3f ms\n", duration_cast<microseconds>(t2 - t1).count() / 1000.0
      + duration_cast<microseconds>(t4 - t3).count() / 1000.0);

  cbdetect::plot_boards(img, corners, boards, params);//4 可视化棋盘格
}

int main(int argc, char *argv[]) {
  printf("chessboards...");
  detect("/home/gu/test3.4/libcbdetect/example_data/r6.png", cbdetect::SaddlePoint);//两种模式

 // printf("deltilles...");
 // detect("/home/gu/test3.4/libcbdetect/example_data/e2.png", cbdetect::MonkeySaddlePoint);
  return 0;
}
