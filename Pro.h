#include "SettingGame.h"
#include "Menu.h"
#include "Board2.h"

#ifndef PROMODE_H
#define PROMODE_H

struct ProMode{
    /// Khởi tạo bảng
    Board2 B; // 6, 12, 150
    //~Board B;
	
	//Player player;
    
	/// Hàm thực thi
    static void ProPlay(account&);
	
};
#endif // PROMODE_H

