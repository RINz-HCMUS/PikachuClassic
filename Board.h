#pragma once

#include "SettingGame.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <deque>

#ifndef BOARD_H
#define BOARD_H

struct Board
{
		int n_row, n_column; 			// số lượng cột và hàng
		int n_type;			 			// số lượng kiểu hình
		int ** _board;		 			// bảng 2D pointer array
		const int left = 12, top = 6;	// ví trí góc trái trên của bảng

		// constructor và destructor
		Board(int _n_row = 9, int _n_column = 16, int _n_type = 26); // constructor
		~Board();	// destructor

		// Các hàm lấy giá trị
		int getnRow();				// Hàm lấy giá trị của số dòng
		int getnCol();				// Hàm lấy giá trị của số cột
		int getCell(int _x, int _y);// Hàm lấy giá trị của loại tại ô (_x,_y)

		// Các hàm thực thi
		void removeCell(int _x, int _y);						// Hàm xóa ô (_x,_y)
		void setCell(int _x, int _y, int type);					// Hàm gán giá trị ô (_x,_y) = type
		void initBoard(int _n_row, int _n_column, int n_type);	// Hàm khởi tạo mảng giá trị ban đầu
		void suffleBoard();										// Hàm đảo lại bảng
		void suggestBoard(std::pair <int,int> &start, std::pair <int,int> &end);	// Hàm đưa ra gợi ý 2 ô nối được với nhau
		void removeBoard_0(std::pair <int,int> start, std::pair <int,int> end);		// Hàm xóa 2 ô được chọn
		void removeBoard_1(std::pair <int,int> start, std::pair <int,int> end);		// Hàm xóa 2 ô được chọn và thụt qua trái
		void removeBoard_2(std::pair <int,int> start, std::pair <int,int> end);		// Hàm xóa 2 ô được chọn và thụt lên trên
		void removeBoard_3(std::pair <int,int> start, std::pair <int,int> end);		// Hàm xóa 2 ô được chọn và thụt qua phải
		void removeBoard_4(std::pair <int,int> start, std::pair <int,int> end);		// Hàm xóa 2 ô được chọn và thụt xuống dưới

		// Các hàm logic game
		bool canConnect(std::pair<int,int> start, std::pair<int,int> end, std::vector<std::pair<int,int> > &path);	// Hàm kiểm tra 2 ô có thể nối được với nhau không
		std::vector <std::pair<int,int>> findPath(std::pair<int,int> start, std::pair<int,int> end);				// Hàm trả về đường đi của 2 ô
		bool checkBoard();																							// Hàm kiểm tra bảng có 2 ô nào nối được không 

		// Hàm vẽ
        void drawCells(int, int, int, bool);			// Hàm vẽ 1 ô 
        void drawBoard(bool);							// Hàm vẽ bảng
		void drawLine(std::vector<std::pair<int,int>>);	// Hàm vẽ đường đi của 2 ô
};

#endif // BOARD_H