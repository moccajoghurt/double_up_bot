#ifndef SCREEN_SCRAPER_HPP_
#define SCREEN_SCRAPER_HPP_


#include <vector>
#include <Windows.h>
#include "table.hpp"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <tesseract/baseapi.h>
//#include <leptonica/allheaders.h>

//using namespace std;
//using namespace cv;


enum WindowType {
  TitanLogin,
  TitanRoot,
  TitanDoubleUpTable,
  TitanLobby,
  TitanLobbyBuyIn
};

enum WindowAction {
  TitanBuyIn,
  TitanJoinLobby,
  TitanMenuSitAndGo,
  TitanMenuDoubleUp,
  TitanTableGetHistory,
  TitanTableBigSize
};


class ScreenScraper {
public:
  
  static void update_table(Table& table);

  static std::vector<HWND> open_windows;
  static std::vector<HWND> get_windows_by_type(WindowType);
  static bool window_action(HWND window, WindowAction action);
  static void update_open_windows();
  static cv::Mat window_to_mat(HWND hwnd);
  

private:
  static std::vector<int> titan_get_player_chips(cv::Mat& mat, std::vector<int> active_players);
  static int titan_get_dealer(cv::Mat& mat);
  static std::vector<int> titan_get_active_players(cv::Mat mat); 
  //static bool
  //static void update_open_windows();

};


#endif
