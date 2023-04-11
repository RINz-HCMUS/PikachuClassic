#include "SettingGame.h"
#include "Menu.h"
#include "Board.h"

#ifndef CUSTOMMODE_H
#define CUSTOMMODE_H

struct CustomMode{
    /// Khởi tạo bảng
    Board A; // row, col, 150
    //~Board A;
	
	//Player player;
    
	/// Hàm thực thi
    static void CustomPlay(int, int, account&m, int, int);
	
};
#endif // CUSTOMMODE_H

