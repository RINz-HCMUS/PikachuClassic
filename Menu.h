#pragma once

#include "SettingGame.h"

#include "Sound.h"
#include <fstream>
#include <cstring>

using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H

struct account{
    char Name[16];
    char Pass[16];
    int Mode;
    int Score;
    int pokemon[152];
    // Ham gan struct
    account& operator=(const account& other) {
        strcpy(Name, other.Name);
        strcpy(Pass, other.Pass);
        Mode = other.Mode;
        Score = other.Score;
        for(int i = 0; i < 152; i++)
        	pokemon[i] = other.pokemon[i];
        return *this;
    }
};

#endif	// ACCOUNT_H


#include "Noob.h"
#include "Pro.h"
#include "Custom.h"






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
	void printMenu(account&);

	// In phần Hướng dẫn chơi
	void printTutorial();

	// In BXH
	void printLeaderBoard();

	// Chỉnh tốc độ thực thi
	void Slow();

	// In Thông tin tác giả
	void printAboutGame();

	// In menu mức độ game
	void printGameMode(account&);
	
	void printLOGIN();
	
	// In ra menu CustomMode
	void printCustomMode(account&);

	// In tên game
	void printLogo();
	
	// In ra màn hình chiến thắng
	void printVictory();

	void Exit();
};

#endif // MENU_H

