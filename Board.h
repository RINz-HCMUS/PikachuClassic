#pragma once
//#pragma comment(lib, "Winmm.lib")

#include <iostream>
#include <time.h>
#include <vector>
#include <deque>
//using namespace std;

#ifndef BOARD_H
#define BOARD_H

struct Board
{
		int n_row, n_column;
		int ** _board;		
		
		// constructor và destructor
		Board(int _n_row, int _n_column, int n_type);
		~Board();
		
		// Các hàm lấy giá trị
		int getnRow();
		int getnCol();
		int getCell(int _x, int _y);
		
		// Các hàm thực thi
		void removeCell(int _x, int _y); 
		void setCell(int _x, int _y, int type);
		void initBoard(int _n_row, int _n_column, int n_type);
		
		
		// Hàm kiểm tra tính logic của game
		bool canConnect(std::pair<int,int> start, std::pair<int,int> end);
		std::vector <std::pair<int,int>> findPath(std::pair<int,int> start, std::pair<int,int> end);
		
};

#endif // BOARD_H