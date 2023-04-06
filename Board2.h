#pragma once

#include "SettingGame.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <deque>

#ifndef BOARD2_H
#define BOARD2_H

struct Node{
	int data;
	Node* pNext;
	
	int getLength(Node*&);
	int getPos(Node*&, int);
	
	void addPos(Node*&, int, int);// thêm 1 node tại vị trí cho trước
	void setPos(Node*&, int, int);// đặt lại giá trị của node tại vị trí cho trước
	void removePos(Node*&, int);
	void removeAll(Node*&);
};

	
struct Board2{
	
		int n_row, n_column;
		int n_type;
		const int left = 11, top = 5;
		Node** _board2;
		
		// constuctor và destructor	
		Board2(int ,int ,int);
		~Board2();
		
		// Hàm lấy giá trị
		int getCell(int, int);
		int getLengthInRow(int);
		
		// Hàm thực thi
		void removeCell(int, int);
		void initBoard(int, int, int);
		void suffleBoard();
		void suggestBoard(std::pair <int, int> &start, std::pair <int, int> &end);
		void removeBoard(std::pair <int, int> start, std::pair <int, int> end);
		
		// Hàm kiểm tra tính logic của game
		bool canConnect(std::pair<int, int> start, std::pair<int, int> end, std::vector<std::pair<int, int> > &path);
		std::vector <std::pair<int, int> > findPath(std::pair<int, int> start, std::pair<int, int> end);
			// Hàm kiểm tra có 2 ô nào có thể kết nối không checkBoard -> 4 vòng for 
		bool checkBoard();
		
		// Hàm vẽ
		
		void drawCells(int, int, int);
		void drawBoard();
		void drawLine(std::vector<std::pair<int, int> > path);
		
};

#endif // BOARD2_H