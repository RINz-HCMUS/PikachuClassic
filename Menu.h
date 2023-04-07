#pragma once

#include "SettingGame.h"
#include "Noob.h"
#include "Pro.h"
#include "Custom.h"
#include "Sound.h"
#include <fstream>
#include <cstring>
using namespace std;
#ifndef MENU_H
#define MENU_H

struct Menu{
	// Các lựa chọn trong Menu
	const static string optionMenu[5];

	// Các lựa chọn độ khó
	const static string optionPlay[4];

	// Các lựa chọn trong CustomMode;
	const static string optionCustom[4];
	// In ô lựa chọn
	void printButton(int, int, int, int, COORD);

	// In ra Menu
	void printMenu();

	// In phần Hướng dẫn chơi
	void printTutorial();

	// In BXH
	void printLeaderBoard();

	// Chỉnh tốc độ thực thi
	void Slow();

	// In Thông tin tác giả
	void printAboutGame();

	// In menu mức độ game
	void printGameMode();
	
	// In ra menu CustomMode
	void printCustomMode();
	// In tên game
	void printLogo();
	
	// In ra màn hình chiến thắng
	void printVictory();

	void Exit();
};

#endif // MENU_H

#ifndef PLAYER_H
#define PLAYER_H

struct Player{
	std::string name;
	std::string password;
	int score;
	int mode; // độ khó
	//std::string atTime; // thời gian lúc hoàn thành trò chơi
};

#endif	// PLAYER_H
