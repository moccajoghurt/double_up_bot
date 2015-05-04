
#include "screen_scraper.hpp"

std::vector<HWND> ScreenScraper::open_windows;


BOOL CALLBACK get_windows(HWND hwnd, LPARAM lParam) {
  ScreenScraper::open_windows.push_back(hwnd);
  return true;
}

void ScreenScraper::update_open_windows() {
  ScreenScraper::open_windows.clear();
  EnumWindows(get_windows, false);
}

std::vector<HWND> ScreenScraper::get_windows_by_type(WindowType pm) {
  update_open_windows();

  std::vector<HWND> windows;

  //char class_name[80];
  char title[80];

  for (HWND hwnd : open_windows) {

    //GetClassName(hwnd,class_name, sizeof(class_name));
    GetWindowText(hwnd,title,sizeof(title));
    std::string name(title);
    if (pm == TitanDoubleUpTable) {

      if (name.find("Double Up ") != std::string::npos) { windows.push_back(hwnd); std::cout << windows.size()<< " " << name << std::endl; }

    } else if (pm == TitanLobby) {

      if (name.find("Lobby") != std::string::npos) { windows.push_back(hwnd); }

    } else if (pm == TitanRoot) {

      RECT rect = {0};
      GetWindowRect(hwnd, &rect);
      if (rect.right - rect.left == 1016 && rect.bottom - rect.top == 738 && name.find("Titan Poker") != std::string::npos) { windows.push_back(hwnd); }

    }
  }
  return windows;
}


bool ScreenScraper::window_action(HWND hwnd, WindowAction wa) {

  if (wa == TitanMenuSitAndGo) {
    /*
    if (!SetForegroundWindow(hwnd)) { cout << "didnt get focus" << endl; }
    Sleep(100);

    RECT rect = {0};
    GetWindowRect(hwnd, &rect);
    INPUT input;
    ZeroMemory(&input, sizeof(input));
    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.dx = (100 + rect.left) * (65536./GetSystemMetrics(SM_CXSCREEN));
    input.mi.dy = (360 + rect.top) * (65536./GetSystemMetrics(SM_CYSCREEN));
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
    //SendInput(1, &input, sizeof(input));
    //input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTUP;
    //SendInput(1, &input, sizeof(input));
    */
    

    int x = 100;
    int y = 340;
    PostMessage(hwnd, WM_LBUTTONDOWN, 0, MAKELPARAM(x,y));
    PostMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(x,y));


  } else if (wa == TitanMenuDoubleUp) {

    int x = 100;
    int y = 500;
    PostMessage(hwnd, WM_LBUTTONDOWN, 0, MAKELPARAM(x,y));
    PostMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(x,y));
    
  }  else if (wa == TitanTableGetHistory) {
    
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
    
    //click chat window
    int x = 100;
    int y = 450;
    PostMessage(hwnd, WM_LBUTTONDOWN, 0, MAKELPARAM(x,y));
    PostMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(x,y));
    Sleep(10);
    PostMessage(hwnd, WM_LBUTTONDOWN, 0, MAKELPARAM(x,y));
    PostMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(x,y));
    
    Sleep(50);
    
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    
    
    /********** MARK HISTORY **********/
    //press strg
    input.ki.wVk = VK_CONTROL;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    
    //press A
    input.ki.wVk = 0x41;
    SendInput(1, &input, sizeof(INPUT));
    
    //release A
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
    
    //release strg
    input.ki.wVk = VK_CONTROL;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
    
    
    Sleep(50);
    
    /********** COPY HISTORY **********/
    //press strg
    input.ki.wVk = VK_CONTROL;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    
    //press C
    input.ki.wVk = 0x43;
    SendInput(1, &input, sizeof(INPUT));
    
    //release C
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
    
    //release strg
    input.ki.wVk = VK_CONTROL;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
    
  } else if (wa == TitanTableBigSize) {
    
    RECT rect = {0};
    GetWindowRect(hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    //cout << width << " " << height << endl;
    
    SetWindowPos(hwnd, NULL, rect.left, rect.top, 1004, 757, 0);
    
  }

  return true;
}

void ScreenScraper::update_table(Table& table) {
  
  HWND table_window;
  std::vector<HWND> tables = get_windows_by_type(WindowType::TitanDoubleUpTable);
  //find window with id
  for (HWND hwnd : tables) {
    
    //find our table by id
    
  }
  
  table_window = tables[0];
  cv::Mat table_mat = window_to_mat(table_window);
  
  //
  //int dealer_pos = titan_get_dealer(table_mat, table);
  //std::cout << dealer_pos << std::endl;
  
  std::vector<int> active_players = titan_get_active_players(table_mat);
  std::vector<int> chips = titan_get_player_chips(table_mat, active_players);
  table.active_players.clear();
  
  if (active_players.size() != chips.size()) std::cout << "active player count != chip count" << std::endl;
  
  for (int i = 0; i < active_players.size(); i++) {
    Player p;
    p.position = active_players[i];
    p.chipcount = chips[i];
    std::cout << p.position << ": "<< p.chipcount << std::endl;
    table.active_players.push_back(p);
  }
  
  table.current_dealer = titan_get_dealer(table_mat);
  
  
}

std::vector<int> ScreenScraper::titan_get_active_players(cv::Mat mat) {
  
  std::vector<int> active_players;
  int player_count = 1;
  std::vector<cv::Mat> player_positions;
  player_positions.push_back( cv::Mat(mat, cv::Rect(701, 467, 65, 65)) );
  player_positions.push_back( cv::Mat(mat, cv::Rect(220, 470, 65, 65)) );
  player_positions.push_back( cv::Mat(mat, cv::Rect(68, 277, 65, 65)) );
  player_positions.push_back( cv::Mat(mat, cv::Rect(220, 93, 65, 65)) );
  player_positions.push_back( cv::Mat(mat, cv::Rect(705, 93, 65, 65)) );
  player_positions.push_back( cv::Mat(mat, cv::Rect(855, 277, 65, 65)) );
  
  cv::Mat titan_empty_seat = cv::imread("res/empty.png", CV_LOAD_IMAGE_UNCHANGED);
  //std::cout << titan_empty_seat.channels() << std::endl;
  
  for (cv::Mat mats : player_positions) {
    double dist = norm(mats, titan_empty_seat, cv::NORM_L2);
    //std::cout << dist << std::endl;
    if (dist > 7000) active_players.push_back(player_count);
    player_count++;
  }
  
  return active_players;
}

int ScreenScraper::titan_get_dealer(cv::Mat& mat) {
  
  // check:
  // http://stackoverflow.com/questions/4196453/simple-and-fast-method-to-compare-images-for-similarity
  
  int dealer_pos = 1;
  
  std::vector<cv::Mat> dealer_positions;
  dealer_positions.push_back( cv::Mat(mat, cv::Rect(655, 455, 27, 21)) );
  dealer_positions.push_back( cv::Mat(mat, cv::Rect(305, 455, 27, 21)) );
  dealer_positions.push_back( cv::Mat(mat, cv::Rect(170, 350, 27, 21)) );
  dealer_positions.push_back( cv::Mat(mat, cv::Rect(239, 177, 27, 21)) );
  dealer_positions.push_back( cv::Mat(mat, cv::Rect(721, 175, 27, 21)) );
  dealer_positions.push_back( cv::Mat(mat, cv::Rect(794, 350, 27, 21)) );
  
  cv::Mat titan_dealer_pic = cv::imread("res/dealer.png", CV_LOAD_IMAGE_UNCHANGED);
  
  for (cv::Mat mats : dealer_positions) {
    
    double dist = norm(mats, titan_dealer_pic, cv::NORM_L2);
    if (dist < 1000) break;
    dealer_pos++;
  }
  
  return dealer_pos;
  
}


std::vector<int> ScreenScraper::titan_get_player_chips(cv::Mat& mat, std::vector<int> active_players) {
  
  
  std::vector<int> chips;
  
  std::vector<cv::Mat> mats;
  if(std::find(active_players.begin(), active_players.end(), 1) != active_players.end()) mats.push_back( cv::Mat(mat, cv::Rect(595, 513, 70, 20)) );
  if(std::find(active_players.begin(), active_players.end(), 2) != active_players.end()) mats.push_back( cv::Mat(mat, cv::Rect(322, 516, 70, 20)) );
  if(std::find(active_players.begin(), active_players.end(), 3) != active_players.end()) mats.push_back( cv::Mat(mat, cv::Rect(55, 374, 70, 20)) );
  if(std::find(active_players.begin(), active_players.end(), 4) != active_players.end()) mats.push_back( cv::Mat(mat, cv::Rect(321, 80, 70, 20)) );
  if(std::find(active_players.begin(), active_players.end(), 5) != active_players.end()) mats.push_back( cv::Mat(mat, cv::Rect(594, 77, 70, 20)) );
  if(std::find(active_players.begin(), active_players.end(), 6) != active_players.end()) mats.push_back( cv::Mat(mat, cv::Rect(865, 374, 70, 20)) );
  //cv::imshow("test", mat1);
  //cv::waitKey(0);
  
  char *txt;
  tesseract::TessBaseAPI api;
  if (api.Init("res/tessdata", "eng")) { std::cout << "tesseract couldn't init" << std::endl; exit(0); };
  api.SetVariable("tessedit_char_whitelist", "0123456789,");
  
  
  for (cv::Mat num_mat : mats) {
    //cv::imshow("test", num_mat);
    //cv::waitKey(0);
    cv::cvtColor(num_mat, num_mat, CV_BGR2GRAY);
    api.SetImage((uchar*)num_mat.data, num_mat.cols, num_mat.rows, 1, num_mat.cols);
    txt = api.GetUTF8Text();
    
    std::string str(txt);
    str.erase(std::remove(str.begin(), str.end(), ','), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    if (str.size() > 0) chips.push_back( std::atoi(str.c_str()) );
  }
  return chips;
}


// thanks to: http://stackoverflow.com/questions/14148758/how-to-capture-the-desktop-in-opencv-ie-turn-a-bitmap-into-a-cv::Mat
cv::Mat ScreenScraper::window_to_mat(HWND hwnd) {
  HDC hwindowDC,hwindowCompatibleDC;

  int height,width,srcheight,srcwidth;
  HBITMAP hbwindow;
  cv::Mat src;
  BITMAPINFOHEADER  bi;

  hwindowDC=GetDC(hwnd);
  hwindowCompatibleDC=CreateCompatibleDC(hwindowDC);
  SetStretchBltMode(hwindowCompatibleDC,COLORONCOLOR);

  RECT windowsize;    // get the height and width of the screen
  GetClientRect(hwnd, &windowsize);

  srcheight = windowsize.bottom;
  srcwidth = windowsize.right;
  height = windowsize.bottom;  //change this to whatever size you want to resize to
  width = windowsize.right;

  src.create(height,width,CV_8UC4);

  // create a bitmap
  hbwindow = CreateCompatibleBitmap( hwindowDC, width, height);
  bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
  bi.biWidth = width;
  bi.biHeight = -height;  //this is the line that makes it draw upside down or not
  bi.biPlanes = 1;
  bi.biBitCount = 32;
  bi.biCompression = BI_RGB;
  bi.biSizeImage = 0;
  bi.biXPelsPerMeter = 0;
  bi.biYPelsPerMeter = 0;
  bi.biClrUsed = 0;
  bi.biClrImportant = 0;

  // use the previously created device context with the bitmap
  SelectObject(hwindowCompatibleDC, hbwindow);
  // copy from the window device context to the bitmap device context
  StretchBlt( hwindowCompatibleDC, 0,0, width, height, hwindowDC, 0, 0,srcwidth,srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
  GetDIBits(hwindowCompatibleDC,hbwindow,0,height,src.data,(BITMAPINFO *)&bi,DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

  // avoid memory leak
  DeleteObject (hbwindow); DeleteDC(hwindowCompatibleDC); ReleaseDC(hwnd, hwindowDC);

  return src;
}
