#include "Menu.h"

const string Menu::optionMenu[5] = {"PLAY", "TUTORIAL", "LEADERBOARD", "ABOUT GAME", "EXIT"};

const string Menu::optionPlay[4] = {"NOOB", "PRO ", "CUSTOM", "BACK"};

const string Menu::optionCustom[4] = {"ROW", "COLUNM", "PLAY", "BACK"};

void Menu::printLogo(){
	//SettingGame::clearConsole();

	SettingGame::setColor(BLACK, YELLOW);
	// pokemon 44x 5;
	std::cout << R"(
				                                  ,'\
				    _.----.        ____         ,'  _\   ___    ___     ____
				_,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.
				\      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
				 \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |
				   \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |
				    \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |
				     \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |
				      \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
				       \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |
				        \_.-'       |__|    `-._ |              '-.|     '-.| |   |
				                                `'                            '-._|
)" << "\n";

}

void Menu::printLeaderBoard(){
    Player Toprank[100];
	int cnt = 0;
	std::ifstream fs;
	fs.open("toprank.txt", ios::in);
	//if(!ifs) std::cout << " NOt read" ;
	while(!fs.eof()){
		std::cout << "Loading";
		getline(fs, Toprank[cnt].name);
		getline(fs, Toprank[cnt].password);
		fs >> Toprank[cnt].mode;
		fs >> Toprank[cnt].score;
		fs.ignore();
		std::cout << Toprank[cnt].name << std::endl;
		cnt++;
		//std::cout << cnt << endl;
	}
//	if(!ifs) std::cout << " NOt read" ;
	fs.close();

	//SettingGame::clearConsole();

//    SettingGame::setColor(BLACK, YELLOW);
//	cout << R"(
//	  _      ______          _____  ______ _____  ____   ____          _____  _____
//	 | |    |  ____|   /\   |  __ \|  ____|  __ \|  _ \ / __ \   /\   |  __ \|  __ \
//	 | |    | |__     /  \  | |  | | |__  | |__) | |_) | |  | | /  \  | |__) | |  | |
//	 | |    |  __|   / /\ \ | |  | |  __| |  _  /|  _ <| |  | |/ /\ \ |  _  /| |  | |
//	 | |____| |____ / ____ \| |__| | |____| | \ \| |_) | |__| / ____ \| | \ \| |__| |
//	 |______|______/_/    \_\_____/|______|_|  \_\____/ \____/_/    \_\_|  \_\_____/
//	)";
//
//    SettingGame::setColor(BLACK, WHITE);
//    SettingGame::gotoXY(5, 10);
//    std::cout << "No.";
//
//	SettingGame::gotoXY(10, 10);
//	std::cout << "NAME";
//
//	SettingGame::gotoXY(30, 10);
//	std::cout << "MODE";
//
//	SettingGame::gotoXY(40, 10);
//	std::cout << "SCORE";
//
//	for(int i = 0; i < 10; i++){
//		SettingGame::gotoXY(30, 12 + i * 2);
//		switch(Toprank[i].mode){
//			case 1:{
//			    SettingGame::gotoXY(30, 12 + i * 2);
//				SettingGame::setColor(BLACK, WHITE);
//				std::cout << "NOOB";
//				break;
//			}
//			case 2:{
//			    SettingGame::gotoXY(30, 12 + i * 2);
//				SettingGame::setColor(BLACK, YELLOW);
//				std::cout << "PRO";
//				break;
//			}
//			case 3:{
//				SettingGame::setColor(BLACK, RED);
//				SettingGame::gotoXY(30, 12 + i * 2);
//				std::cout << "CUSTOM";
//				break;
//			}
//		}
//        SettingGame::gotoXY(5 , 12 + i * 2);
//        std::cout << (i + 1);
//
//		SettingGame::gotoXY(10, 12 + i * 2);
//		std::cout << Toprank[i].name;
//
//		SettingGame::gotoXY(40, 12 + i * 2);
//		std::cout << Toprank[i].score;
//	}
//
//    SettingGame::gotoXY(60, 80);
	std::cout << "Press ESC to back.";
	while(SettingGame::getConsoleInput() != KEY_ESC);
}

void Menu::printAboutGame(){
	SettingGame::clearConsole();

	SettingGame::gotoXY(50, 10);
	std::cout << "2212050 - Ho Minh Dang\n";

	SettingGame::gotoXY(50, 12);
	std::cout << " 22127439 - Vo Huu Tuan\n";

	SettingGame::gotoXY(60, 50);
	std::cout << "Press ESC to back.";

	while(SettingGame::getConsoleInput() != KEY_ESC);
}

void Menu::printButton(int _x, int _y, int Cells, int type, COORD Pos){
	SettingGame::setColor(BLACK, WHITE);
	for(int manyCells = 0; manyCells < Cells; manyCells++){
		for(int i = 0; i < 5; i++){
			_y ++;
			if(_y == Pos.Y)
				SettingGame::setColor(WHITE, BLACK);

			int tmp = _x - 1;
			for(int j = 0; j < 21; j++){
				tmp++;
				SettingGame::gotoXY(tmp, _y);
				if(i == 0 || i == 4 || j == 0 || j == 20)
//					std::cout << "*";
					putchar('*');
				else
//					std::cout << " ";
					putchar(' ');
			}
			if(i == 2 ){
				if(type == 1){
					SettingGame::gotoXY(_x + 11 - optionMenu[manyCells].size() / 2, _y);
					std::cout << optionMenu[manyCells];
				}
				else if(type == 2){
					SettingGame::gotoXY(_x + 11 - optionPlay[manyCells].size() / 2, _y);
					std::cout << optionPlay[manyCells];
				}
				else if(type == 3){
					SettingGame::gotoXY(_x + 11 - optionCustom[manyCells].size() / 2, _y);
					std::cout << optionPlay[manyCells];
				}
			}
		}
		SettingGame::setColor(BLACK, WHITE);
		_y++;
	}
}

void Menu::printMenu(){
	SettingGame::clearConsole();
	int Row = 21, Col = 12; // kích thước ô
	short _x = 66 - Row / 2, _y = 20 - Col / 2;
	//Kẻ ô
	COORD Pos = {56, 15};
	COORD oldPos = {0, 0};
	while(true){
		if(oldPos.X != Pos.X || oldPos.Y != Pos.Y){
			SettingGame::clearConsole();
			Menu::printLogo();
			Menu::printButton(_x, _y, 5, 1, Pos);
		}
		else
			oldPos = Pos;

		switch(SettingGame::getConsoleInput()){
			case KEY_UP:{
				if(0 <= Pos.Y - 1)
					Pos.Y = max(15, Pos.Y - 6);
				break;
			}
			case KEY_DOWN:{
					Pos.Y = min(Pos.Y + 6, 39);
				break;
			}

			case KEY_SPACE:{
				if(Pos.Y == 0) break;
				SettingGame::clearConsole();
					switch(Pos.Y){
						case 15:{
							Menu::printGameMode();
							break;
						}
						case 21:{
							Menu::printTutorial();
							break;
						}
						case 27:{
							Menu::printLeaderBoard();
							break;
						}
						case 33:{
							Menu::printAboutGame();
							break;
						}
						case 39:{
							exit(0);
						}
					}

				break;
			}
			default:
				break;
		}
	Menu::Slow();
	}
}

void Menu::printTutorial(){

	SettingGame::gotoXY(50, 10);
	std::cout << "Use WASD or ARROWBUTTON to MOVE, ok?";

	SettingGame::gotoXY(50, 14);
	std::cout << R"(

                                        :^^^^^^^^^^^^^^^^^^:
                                      !P5JJJJJJJJJJJJJJJJJJ5P!
                                     :#?                    ?#:
                                     ^&!                    !&^
                                     ^&!        .55.        !&^
                                     ^&!       :G&&G:       !&^
                                     ^&!      ~B&##&B~      !&^
                                     ^&!     !BBBBBBBB!     !&^
                                     ^&!     ..........     !&^
                                     ^&!                    !&^
                                     ^&7                    7&^
                                      JG?!!!!!!!!!!!!!!!!!!?GJ
              :!!7777777777777777!!:   ~YPPPPPPPPPPPPPPPPPPY~   :!!7777777777777777!!:
             JGJ777777777777777777JGJ JG?!!!!!!!!!!!!!!!!!!?GJ JGJ777777777777777777JGJ
            ^&7                    7&!&7                    7&!&7                    7&^
            ^&!                    !#7#!                  . !#7#!                    !&^
            ^&!         :!Y5    .  !B7#!  . .........::.    !#7B! ..    5Y!:         !&^
            ^&!     .~?P#&&G       !#7#!     !GBGBGGBB!     !#7#!       G&&#P?~.     !&^
            ^&!    :YB&&&#&G       !#7#!      ~B&##&B~      !#7#!       G&#&&&BY:    !&^
            ^&!      .~JP#&B       !#7#!       :G&&G:       !#7#!       B&#PJ~.      !&^
            ^&!          :!J       !#7#!        .55.        !#7#!       ?!:          !&^
            ^&!                    !#7#!                    !#7#!                    !&^
            :#?                    ?#~#?                    ?#~#?                    ?&:
             !P5JJJJJJJJJJJJJJJJJJ5P! !P5JJJJJJJJJJJJJJJJJJ5P! !P5JJJJJJJJJJJJJJJJJJ5P!
               :^^^^^^^^^^^^^^^^^^:     :^^^^^^^^^^^^^^^^^^:     :^^^^^^^^^^^^^^^^^^:
			      )";


	SettingGame::gotoXY(60, 50);
	std::cout << "Press ESC to back.";

	while(SettingGame::getConsoleInput() != KEY_ESC);
}

void Menu::printGameMode(){
	COORD Pos = {56, 15};
	COORD oldPos = {0, 0};
	int Row = 21, Col = 12;
	short _x = 66 - Row / 2, _y = 20 - Col / 2;

	SettingGame::clearConsole();
	Menu::printLogo();
	Menu::printButton(_x, _y, 4, 2, Pos);
	bool out = false;
	while(!out){
		if(oldPos.X != Pos.X || oldPos.Y != Pos.Y){
			SettingGame::clearConsole();
			Menu::printLogo();
			Menu::printButton(_x, _y, 4, 2, Pos);
		}
		else
			oldPos = Pos;

		switch(SettingGame::getConsoleInput()){
			case KEY_UP:{
				Pos.Y = max(15, Pos.Y - 6);
				break;
			}

			case KEY_DOWN:{
				Pos.Y = min(Pos.Y + 6, 33);
				break;
			}

			case KEY_SPACE:{
				if(Pos.Y == 0) break;
				SettingGame::clearConsole();
					switch(Pos.Y){
						case 15:{
							NoobMode::NoobPlay();
							break;
						}
						case 21:{
							ProMode::ProPlay();
							break;
						}
						case 27:{
//							Menu::printCustomMode();
							int row, col;
							std::cout << "Input Row: ";
							cin >> row;
							std::cout << "Input Col: ";
							cin >> col;
							CustomMode::CustomPlay(row, col);
							break;
						}
						case 33:{
							out = true;
							break;
						}
					}
//
//				break;
			}
			default:
				break;
		}
	Menu::Slow();
	}
}

void Menu::printCustomMode(){
	COORD Pos = {56, 15};
	COORD oldPos = {0, 0};
	int Row = 21, Col = 12;
	int row = -22127439, col = -22127050;
	short _x = 66 - Row / 2, _y = 20 - Col / 2;

	SettingGame::clearConsole();
	Menu::printLogo();
	Menu::printButton(_x, _y, 4, 3, Pos);
	
	bool out = false;
	while(!out){
		if(oldPos.X != Pos.X || oldPos.Y != Pos.Y){
			SettingGame::clearConsole();
			Menu::printLogo();
			Menu::printButton(_x, _y, 4, 3, Pos);
			if(0 < row && row < 8){
				SettingGame::gotoXY(66, 15);
				std::cout << row;
			}
			if(0 < col && col < 14){
				SettingGame::gotoXY(66, 21);
				std::cout << col;
			}	
		}
		else
			oldPos = Pos;

		switch(SettingGame::getConsoleInput()){
			case KEY_UP:{
				Pos.Y = max(15, Pos.Y - 6);
				break;
			}

			case KEY_DOWN:{
				Pos.Y = min(Pos.Y + 6, 33);
				break;
			}

			case KEY_SPACE:{
				if(Pos.Y == 0) break;
				SettingGame::clearConsole();
					switch(Pos.Y){
						case 15:{
							std::cin >> row;
							SettingGame::gotoXY(66, 15);
							std::cout << row;
							break;
						}
						case 21:{
							std::cin >> col;
							SettingGame::gotoXY(66, 21);
							std::cout << col;
							break;
						}
						case 27:{
//							Menu::printCustomMode();
							if(0 < row && row < 8 && 0 < col && col < 14 && col != -22127050 && row != -22127439)
								CustomMode::CustomPlay(row, col);
							else{
								SettingGame::setColor(BLACK, RED);
								SettingGame::gotoXY(50, 60);
								std::cout << "the value of column or row is invalid, again.";
								SettingGame::gotoXY(50, 61);
								std::cout << "remind: row is not less than 1 and greater than 8";
								SettingGame::gotoXY(50, 62);
								std::cout << "remind: column is not less than 1 and greater than 14";
								SettingGame::setColor(BLACK, RED);
							}
							break;
						}
						case 33:{
							out = true;
							break;
						}
					}
//
//				break;
			}
			default:
				break;
		}
	Menu::Slow();
	}	
	
}

void Menu::printVictory(){
    SettingGame::gotoXY(80, 8);
    SettingGame::setColor(BLACK, RED);
	std::cout << R"(
					       _      _
					__   ___  ___| |_ ___  _ __ _   _
					\ \ / / |/ __| __/ _ \| '__| | | |
					 \ V /| | (__| || (_) | |  | |_| |
					  \_/ |_|\___|\__\___/|_|   \__, |
					                             __/ |
					                            |___/ 
	)" << "\n";
	
	SettingGame::gotoXY(50, 20);
	SettingGame::setColor(BLACK, YELLOW);
	std::cout << "YOUR SCORE: ";
    SettingGame::gotoXY(60, 60);
    std::cout << "Press ESC to exit.";
    
    while(SettingGame::getConsoleInput() != KEY_ESC);
}

void Menu::Slow(){
	Sleep(100);
}

void Menu::Exit(){
	exit(0);
}
