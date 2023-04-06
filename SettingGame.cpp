#include "SettingGame.h"

/// Thiết lập các con trỏ
HWND SettingGame::consoleWindow = GetConsoleWindow();
HANDLE SettingGame::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void SettingGame::setCenterWindow(){
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int width =1080;
	int height = 780;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void SettingGame::disableMaximize(){
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void SettingGame::setColor(int background, int text){
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}

void SettingGame::gotoXY(short x, short y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SettingGame::disableMouseInput(){
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Lấy handle của console
//
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);       // Lấy thông tin hiện tại của con trỏ chuột

    cursorInfo.bVisible = false;                      // Thiết lập con trỏ chuột không hiển thị
    cursorInfo.dwSize = 1;                            // Thiết lập kích thước con trỏ chuột là 1

    SetConsoleCursorInfo(console, &cursorInfo);        // Thiết lập thông tin con trỏ chuột mới
}


void SettingGame::clearConsole(){
	system("cls");
}
void SettingGame::setUpConsole(){
    setCenterWindow();
    SetConsoleTitle("PIKACHU"); /// Thiết lập tiêu đề console
    disableMaximize();
    disableMouseInput();
}

int SettingGame::getConsoleInput(){
    int c = _getch();

    /// lên
    if(c == KEY_UP || c == 'w' || c == 'w')
        return KEY_UP;

    /// xuống
    else if(c == KEY_DOWN || c == 's' || c == 'S')
        return KEY_DOWN;

    /// trái
    else if(c == KEY_LEFT || c == 'a' || c == 'A')
        return KEY_LEFT;

    /// phải
    else if(c == KEY_RIGHT || c == 'd' || c == 'D')
        return KEY_RIGHT;

    /// thoát
    else if(c == KEY_ESC)
        return KEY_ESC;

    /// chọn
    else if(c == KEY_ENTER || c == KEY_SPACE)
        return KEY_SPACE;

    /// tắt nhạc
    else if(c == 'm' || c == 'M')
        return KEY_MUTE;

    /// xáo trộn lại mảng
    else if(c == 'r' || c == 'R')
        return KEY_SHUFFLE;
	
	/// Gợi ý
	else if(c == 'h' || c == 'H')
		return KEY_SUGGEST;
    /// các phím khác
    else
        return 0;
}

void setCenterConsole(){
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Tính kích thước của console
    int consoleWidth = r.right - r.left;
    int consoleHeight = r.bottom - r.top;

    // Tính kích thước của màn hình
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Tính vị trí để căn giữa
    int posX = (screenWidth - consoleWidth) / 2;
    int posY = (screenHeight - consoleHeight) / 2;

    // Đặt lại vị trí của console
    SetWindowPos(console, 0, posX, posY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
