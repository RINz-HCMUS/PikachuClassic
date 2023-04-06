#pragma once
//#pragma comment(lib, "Winmm.lib")

#include <iostream>
#include <time.h>
#include <vector>
#include <deque>
#include "SettingGame.h"
//using namespace std;

#ifndef BOARD_H
#define BOARD_H

struct Board
{
		int n_row, n_column;
		int n_type;
		int ** _board;
		const int left = 12, top = 6;

		// constructor và destructor
		Board() {
			Board(9, 16, 26);
		}
		Board(int _n_row = 9, int _n_column = 16, int _n_type = 26);
		~Board();

		// Các hàm lấy giá trị
		int getnRow();
		int getnCol();
		int getCell(int _x, int _y);

		// Các hàm thực thi
		void removeCell(int _x, int _y);
		void setCell(int _x, int _y, int type);
		void initBoard(int _n_row, int _n_column, int n_type);
			// Hàm suffleBoard -> tương tự initBoard()
		void suffleBoard();
			// Hàm đưa ra suggestion -> trả về vector chứa 2 cái pair hoặc pair<pair,pair>
		void suggestBoard(std::pair <int,int> &start, std::pair <int,int> &end);
			// Hàm xóa 2 ô khi chọn được theo kiểu bình thường
		void removeBoard_0(std::pair <int,int> start, std::pair <int,int> end);
			// Hàm xóa 2 ô khi chọn được, sau đó thụt qua trái
		void removeBoard_1(std::pair <int,int> start, std::pair <int,int> end);
			// Hàm xóa 2 ô khi chọn được, sau đó thụt lên trên
		void removeBoard_2(std::pair <int,int> start, std::pair <int,int> end);
			// Hàm xóa 2 ô khi chọn được, sau đó thụt qua phải
		void removeBoard_3(std::pair <int,int> start, std::pair <int,int> end);
			// Hàm xóa 2 ô khi chọn được, sau đó thụt xuống dưới
		void removeBoard_4(std::pair <int,int> start, std::pair <int,int> end);


		// Hàm kiểm tra tính logic của game7
		bool canConnect(std::pair<int,int> start, std::pair<int,int> end, std::vector<std::pair<int,int> > &path);
		std::vector <std::pair<int,int>> findPath(std::pair<int,int> start, std::pair<int,int> end);
			// Hàm kiểm tra có 2 ô nào có thể kết nối không checkBoard -> 4 vòng for
		bool checkBoard();

		// Hàm vẽ
        void drawCells(int, int, int);
        void drawBoard();
		void drawLine(std::vector<std::pair<int,int>>);

};

#endif // BOARD_H
