#include "SettingGame.h"
#include "Menu.h"
#include "Board.h"
#include "Sound.h"
#ifndef NOOBMODE_H
#define NOOBMODE_H

struct NoobMode{
    /// Khởi tạo bảng
    Board A; // 6, 6, 26
    //~Board A;
	
	//Player player;
    
	/// Hàm thực thi
    static void NoobPlay();
	
};
#endif // NOOBMODE_H

