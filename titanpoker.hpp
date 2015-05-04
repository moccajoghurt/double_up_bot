#ifndef TITANPOKER_HPP_
#define TITANPOKER_HPP_

#include <Windows.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "screen_scraper.hpp"

//using namespace std;
//using namespace cv;


class TitanPoker {
public:
  static HWND titan_root_window;
  static void init_titan_poker();
  static void close_login_ads();
private:

};

#endif
