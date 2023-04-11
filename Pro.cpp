#include "Pro.h"

void ProMode::ProPlay(account& newAccount){
	sound::start();
	int Type = rand() % 150;
	if(!Type)
		Type++;
	int Score = 0;
	int row = 6, col = 8;
	Board2 B(row, col, 150);
	
	while(!B.checkBoard())
		B.suffleBoard();
		
	int X = 0, Y = 0, oldX = 0, oldY = 0;
    int CompleteCells = 0;
    bool choose = false;
    int Xchoose, Ychoose;
	
	std::pair<int, int> p, q;
	p = {0, 0};
    q = {0, 0};
            	
    SettingGame::clearConsole();
    SettingGame::setColor(BLACK, WHITE);
    
	BG::drawBG(Type);
	B.drawBoard();
	
    SettingGame::setColor(BLACK, LIGHTYELLOW);
	SettingGame::gotoXY(120, 14);
	std::cout << "Hi, ";
	SettingGame::setColor(BLACK, YELLOW);
	std::cout << newAccount.Name;
	SettingGame::setColor(BLACK, LIGHTYELLOW);
	SettingGame::gotoXY(120, 16);
	std::cout << "Your score: " << Score;
	SettingGame::gotoXY(120, 18);
	std::cout << "Press 'H' to get suggestion (-100 points)";
	
	SettingGame::gotoXY(120, 20);
	std::cout << "Press 'R' to shuffe board (-200 points)";
    SettingGame::setColor(BLACK, GREEN);
    B.drawCells(B.getCell(0,0), 0, 0);
    SettingGame::setColor(BLACK, WHITE);	
    
  	while(CompleteCells != row * col){
        switch(SettingGame::getConsoleInput()){
            case KEY_UP:{
               while(true){
               		if(X == 0){
               			if(Y == 0){
               				X = row - 1;
               				Y = col - 1;
						   }
						else{
							X = row - 1;
							Y--;
						}
					}
					else 
						X--;
					
					if(B.getCell(X, Y) != -1)
						break;
			   }
               break;
            }

            case KEY_DOWN:{
                while(true){
                	if(X == row - 1){
                		if(Y == col - 1){
                			X = 0;
                			Y = 0;
						}
						else{
							X = 0;
							Y++;
						}
					}
					else
						X++;
					
					if(B.getCell(X, Y) != -1)
						break;
				}
                break;
            }

            case KEY_LEFT:{
                while(true){
                	if(Y == 0){
                		if(X == 0){
                			X = row - 1;
                			Y = col - 1;
						}
						else{
							X--;
							Y = col - 1;							
						}
					}
					else
						Y--;
                	
                	if(B.getCell(X, Y) != -1)
						break;
				}
                break;
            }

            case KEY_RIGHT:{
                while(true){
					if(Y == col - 1){
						if(X == row - 1){
							X = 0;
							Y = 0;
						}
						else{
							X++;
							Y = 0;
						}
					}
					else
						Y++;
					
					if(B.getCell(X, Y) != -1)
						break;	
				}
                break;
            }

            case KEY_SPACE:{
                if(!choose && B.getCell(X, Y) != -1){
                    Xchoose = X;
                    Ychoose = Y;
                    choose = true;

                }
                else if(choose && B.getCell(X, Y) != -1){
                    SettingGame::setColor(BLACK, RED);
                    B.drawCells(B.getCell(X, Y), X, Y);
                    std::vector<std::pair<int,int>> Path;
                    if((Xchoose != X || Ychoose != Y) && B.Board2::canConnect(std::make_pair(X, Y), std::make_pair(Xchoose, Ychoose), Path)){
						Score += 220;
						CompleteCells += 2;
						B.drawLine(Path);
						Sleep(20);
						B.removeBoard({X, Y}, {Xchoose, Ychoose});
                        choose = false;
                    }
                    else{
                        choose = false;
                    }
                    while(CompleteCells <= row * col - 2 && !B.checkBoard())
                    	B.suffleBoard();
                    	
                    SettingGame::setColor(BLACK, WHITE);
                    SettingGame::clearConsole();
                    SettingGame::setColor(BLACK, WHITE);
                   	
				    SettingGame::setColor(BLACK, LIGHTYELLOW);
					SettingGame::gotoXY(120, 14);
					std::cout << "Hi, ";
					SettingGame::setColor(BLACK, YELLOW);
					std::cout << newAccount.Name;
					SettingGame::setColor(BLACK, LIGHTYELLOW);
					SettingGame::gotoXY(120, 16);
					std::cout << "Your score: " << Score;
					SettingGame::gotoXY(120, 18);
					std::cout << "Press 'H' to get suggestion (-100 points)";
	
					SettingGame::gotoXY(120, 20);
					std::cout << "Press 'R' to shuffe board (-200 points)";
					SettingGame::setColor(BLACK, WHITE);
					BG::drawBG(Type);
				    B.drawBoard();
                    SettingGame::setColor(BLACK, WHITE);
                    B.drawCells(B.getCell(oldX, oldY), oldX, oldY);
                    SettingGame::setColor(BLACK, GREEN);				// Ô đang tr
                    B.drawCells(B.getCell(X, Y), X, Y);
                    oldX = X;
                    oldY = Y;
                }
                break;
            }

            case KEY_ESC:{
                return;
            }
            
            case KEY_SUGGEST:{
            	B.Board2::suggestBoard(p, q);
            	
            	SettingGame::setColor(BLACK, YELLOW);
            	B.drawCells(B.getCell(p.first, p.second), p.first, p.second);
            	
            	SettingGame::setColor(BLACK, YELLOW);
				B.drawCells(B.getCell(q.first, q.second), q.first, q.second);
				
				SettingGame::setColor(BLACK, WHITE);
				Score -= 100;
				break;
			}
			
			case KEY_SHUFFLE:{
				B.Board2::suffleBoard();
				BG::drawBG(Type);
				B.drawBoard();
				Score -= 200;
				break;
			}
        } 
		
		if(Score < -9999999)
			Score = -9999999;
		SettingGame::setColor(BLACK, BLACK);
		SettingGame::gotoXY(120, 16);
		std::cout << "                                   ";		
		SettingGame::setColor(BLACK, LIGHTYELLOW);
		SettingGame::gotoXY(120, 16);
		std::cout << "Your score: " << Score;

		
		 
        /// Hiển thị vị trí con trỏ thay đổi
    	if(X != oldX || Y != oldY){
          //  SettingGame::setColor(BLACK, WHITE);
          //  SettingGame::clearConsole();
          //  SettingGame::setColor(BLACK, WHITE);
            
		//	B.drawBoard();
            SettingGame::setColor(BLACK, WHITE);
            B.drawCells(B.getCell(oldX, oldY), oldX, oldY);
            SettingGame::setColor(BLACK, GREEN);				// Ô đang trỏ vào
            B.drawCells(B.getCell(X, Y), X, Y);
            oldX = X;
            oldY = Y;
        }
		
		/// Hiển thị ô được chọn
        if(choose){
            SettingGame::setColor(BLACK, RED);				// Ô đang được chọn
            B.drawCells(B.getCell(Xchoose, Ychoose), Xchoose, Ychoose);
            SettingGame::setColor(BLACK, WHITE);
        }
        Sleep(50);
        
    }
    SettingGame::clearConsole();
    				    SettingGame::setColor(BLACK, LIGHTYELLOW);
					SettingGame::gotoXY(120, 14);
					std::cout << "Hi, ";
					SettingGame::setColor(BLACK, YELLOW);
					std::cout << newAccount.Name;
					SettingGame::setColor(BLACK, LIGHTYELLOW);
					SettingGame::gotoXY(120, 16);
					std::cout << "Your score: " << Score;
					SettingGame::gotoXY(120, 18);
					std::cout << "Press 'H' to get suggestion (-100 points)";
	
					SettingGame::gotoXY(120, 20);
					std::cout << "Press 'R' to shuffe board (-200 points)";
					SettingGame::setColor(BLACK, WHITE);
					BG::drawBG(Type);
    newAccount.Score = Score;
    newAccount.Mode = 2;
	sound::victory();
	
	account a[100];
	int stt = 0;
	bool saved = 0;
    //	Truyen du lieu tu file
	ifstream ifs("rank.txt", ios::in);
    while(!ifs.eof()){
        ifs >> a[stt].Name;
        ifs.ignore();
        ifs >> a[stt].Pass;
        ifs.ignore();
        ifs >> a[stt].Mode;
        ifs.ignore();
        ifs >> a[stt].Score;
        ifs.ignore();
        stt++;
    }
    ifs.close();
    stt--;
    for(int i = 0; i < stt; i++)
    	if(strcmp(newAccount.Name,a[i].Name) == 0){
    		if(a[i].Score < newAccount.Score)
				a[i] = newAccount;
			saved = 1;
    		break;
    	}
    if(!saved){
    	a[stt] = newAccount;
    	stt++;
	}
    for(int i = 0; i < stt - 1; i++)
		for(int j = i + 1; j < stt; j++)
			if(a[i].Score < a[j].Score){
					std::swap(a[i], a[j]);
			}
	
	std::ofstream ofs1("rank.txt", ios::out | ios::trunc);
        for(int i = 0; i < stt; i++){
			ofs1 << a[i].Name << std::endl;
        	ofs1 << a[i].Pass << std::endl;
        	ofs1 << a[i].Mode << std::endl;
        	ofs1 << a[i].Score << std::endl;
        }
	ofs1.close();


    //Menu::printVictory();
	SettingGame::clearConsole();
	return;
}

