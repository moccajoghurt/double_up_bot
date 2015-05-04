#include <iostream>
#include "screen_scraper.hpp"
#include "titanpoker.hpp"
#include "table.hpp"


//using namespace std;

/*
int wcount = 0;
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
	if (IsWindow(hwnd)) {
		imshow("test", ScreenScraper::window_to_mat(hwnd));
		waitKey(0);
		cout << wcount << endl;
	}
	wcount++;
}
*/


int main() {
/*
	POINT a;
	a.x = 5;
	a.y = 5;

	RECT rect = {0};
*/

	//imshow("test", ScreenScraper::window_to_mat(ScreenScraper::get_windows_by_type(WindowType::TitanRoot)[0]));
	//waitKey(0);
	//imshow("test", ScreenScraper::window_to_mat(GetLastActivePopup(FindWindow("Titan Poker", NULL))));


	/*
	char title[80];
	char class_name[80];
	char module[80];
	GetClassName(WindowFromPoint(a),class_name, sizeof(class_name));
	GetWindowText(WindowFromPoint(a),title,sizeof(title));
	cout << title << endl;
	cout << class_name << endl;
	//GetWindowModuleFileName(WindowFromPoint(a), module, sizeof(module));
	//cout << module << endl;
*/
	//waitKey(0);

	//vector<HWND> tables = ScreenScraper::get_windows_by_type(WindowType::TitanDoubleUpTable);
	//SetForegroundWindow(tables[0]);
	//ScreenScraper::window_action(tables[0], WindowAction::TitanTableBigSize);
	
	
	//update when table asks for action, tab through tables until then
	Table table;
	ScreenScraper::update_table(table);
	
	
	
	//TitanPoker::close_login_ads();
	//TitanPoker::

	//imshow("test", ScreenScraper::window_to_mat(GetLastActivePopup(ScreenScraper::get_windows_by_type(WindowType::TitanRoot)[0])));
	//waitKey(0);


	//ScreenScraper::window_action(ScreenScraper::get_windows_by_type(WindowType::TitanRoot)[0], WindowAction::TitanMenuSitAndGo);
	//Sleep(500);
	//ScreenScraper::window_action(ScreenScraper::get_windows_by_type(WindowType::TitanRoot)[0], WindowAction::TitanMenuDoubleUp);
	//ScreenScraper::get_windows_by_type(WindowType::TitanDoubleUpTable);


/*
	ScreenScraper::update_open_windows();
	int count = 0;
	for (HWND hwnd : ScreenScraper::open_windows) {
		char title[80];
		char class_name[80];
		GetWindowText(hwnd,title,sizeof(title));
		GetClassName(hwnd,class_name, sizeof(class_name));
		string name(title);
		if (name.find("Titan Poker") != string::npos) {
			//HWND child = FindWindowEx(hwnd, NULL, NULL, NULL);
			//imshow("test", ScreenScraper::window_to_mat(FindWindowEx(child, NULL, NULL, NULL)));
			//waitKey(0);
			//EnumChildWindows(hwnd, EnumChildProc, 0);
			//imshow("test", ScreenScraper::window_to_mat(GetLastActivePopup(hwnd)));
			//waitKey(0);
			count++;
		}
	}
	cout << count << endl;
*/

	//vector<HWND> new_windows = ScreenScraper::open_windows;
	/*
	int i;
	cin >> i;

	ScreenScraper::update_open_windows();
	//cout << new_windows.size() << endl;
	cout << ScreenScraper::open_windows.size() << endl;
	*/

}
