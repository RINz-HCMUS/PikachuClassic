#pragma once
#include <bits/stdc++.h>
#include "SettingGame.h"
#include "BG.h"
#include "Menu.h"
#include "Board.h"
#include "Sound.h"
#include <fstream>
#ifndef NOOBMODE_H
#define NOOBMODE_H

struct NoobMode{
    /// Khởi tạo bảng
    Board A; // 6, 6, 26
    //~Board A;
	
	//Player player;
    
	/// Hàm thực thi
    static void NoobPlay(account&);
	
};
#endif // NOOBMODE_H

