#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <cstring>
#include <vector>
#include <cstdlib>

/// Định dạng color
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTAQUA 11
#define LIGHTRED 12
#define LIGHTPURPLE 13
#define LIGHTYELLOW 14
#define BRIGHTWHITE 15

/// Định dạng Keyboard
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_ENTER 13
#define KEY_MUTE 'm'
#define KEY_SHUFFLE 'r'
#define KEY_SUGGEST 'h'

//using namespace std;


#ifndef SETTINGGAME_H
#define SETTINGGAME_H

struct SettingGame{
    // SettingGame() {};
    // ~SettingGame() {};
    
    /// Con trỏ xử lí console
    static HWND consoleWindow;

    /// Con trỏ xử lí trong console
	static HANDLE consoleOutput;

    /// Hàm thiết lập cửa sổ console
    static void setUpConsole();

    /// Hàm căn giữa cho console
    static void setCenterWindow();

    /// Hàm chỉnh màu
    static void setColor(int, int);
//    /// Hàm thiết lập tiêu đề console
//    static void setUp

    /// Hàm di chuyển con trỏ đến vị trí (x, y)
    static void gotoXY(short, short);

    /// Hàm vô hiệu hóa phóng to màn hình
    static void disableMaximize();

    /// Hàm vô hiệu hóa con trỏ chuột
    static void setCursorInput(bool);

    /// Hàm lấy giá trị từ bàn phím
    static int getConsoleInput();

    /// Hàm xóa màn hình console
    static void clearConsole();
	
	/// Hàm căn giữa màn hình
	static void setCenterConsole();
	
	/// Hàm căn chỉnh font chữ
	static void setFontInfo();
	
	/// Hàm giảm tốc độ xử lý
	static void Slow(int);
};
#endif
