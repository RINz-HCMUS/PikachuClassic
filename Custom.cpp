#include "Custom.h"

//#include "Noob.h"

void CustomMode::CustomPlay(int row, int col, account& newAccount, int mode, int RemoveType){
	
	sound::start();
	int Type = rand() % 150;
	if(!Type)
		Type++;
	//int row = 6, col = 6;
	Board A(row, col, 150);
	while(!A.checkBoard())
		A.suffleBoard();
		
	int Score = 0;
    int X = 0, Y = 0, oldX = 0, oldY = 0;
    int CompleteCells = 0;
    bool choose = false;
    int Xchoose, Ychoose;
	
	std::pair<int, int> p, q;
	p = {0, 0};
    q = {0, 0};
            	
    SettingGame::clearConsole();
    
    //sound::start();
    
	SettingGame::setColor(BLACK, WHITE);
	BG::drawBG(Type);
    A.drawBoard(mode);
	
	SettingGame::setColor(BLACK, LIGHTYELLOW);
	SettingGame::gotoXY(150, 14);
	std::cout << "Hi, ";
	SettingGame::setColor(BLACK, YELLOW);
	std::cout << newAccount.Name;
	SettingGame::setColor(BLACK, LIGHTYELLOW);
	SettingGame::gotoXY(150, 16);
	std::cout << "Your score: " << Score;
	SettingGame::gotoXY(150, 18);
	std::cout << "Press 'H' to get suggestion";
	
	SettingGame::gotoXY(155, 20);
	std::cout << "(-700 points)";
	
	SettingGame::gotoXY(150, 22);
	std::cout << "Press 'R' to shuffe board";
	
	SettingGame::gotoXY(155, 24);
	std::cout << "(-200 points)";
    SettingGame::setColor(BLACK, GREEN);
    A.drawCells(A._board[0][0], 0, 0, mode);
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
					
					if(A._board[X][Y] != -1)
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
					
					if(A._board[X][Y] != -1)
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
                	
                	if(A._board[X][Y] != -1)
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
					
					if(A._board[X][Y] != -1)
						break;	
				}
                break;
            }

            case KEY_SPACE:{
                if(!choose && A._board[X][Y] != -1){
                    Xchoose = X;
                    Ychoose = Y;
                    choose = true;

                }
                else if(choose && A._board[X][Y] != -1){
                    SettingGame::setColor(BLACK, RED);
                    A.drawCells(A._board[X][Y], X, Y, 1);
                    std::vector<std::pair<int,int>> Path;
                    if((Xchoose != X || Ychoose != Y) && A.Board::canConnect(std::make_pair(X, Y), std::make_pair(Xchoose, Ychoose), Path)){
						Score += 400;
						CompleteCells += 2;
						A.drawLine(Path);
						Sleep(20);
						switch(RemoveType){
							case 0:{
								A.removeBoard_0({X, Y}, {Xchoose, Ychoose});
								break;
							}
							case 1:{
								A.removeBoard_1({X, Y}, {Xchoose, Ychoose});
								break;
							}
							case 2:{
								A.removeBoard_2({X, Y}, {Xchoose, Ychoose});
								break;
							}
							case 3:{
								A.removeBoard_3({X, Y}, {Xchoose, Ychoose});
								break;
							}
							case 4:{
								A.removeBoard_4({X, Y}, {Xchoose, Ychoose});
								break;
							}
							default:{
								int tmp = rand() % 5;
								switch(tmp){
									case 0:{
										A.removeBoard_0({X, Y}, {Xchoose, Ychoose});
										break;
									}
									case 1:{
										A.removeBoard_1({X, Y}, {Xchoose, Ychoose});
										break;
									}
									case 2:{
										A.removeBoard_2({X, Y}, {Xchoose, Ychoose});
										break;
									}
									case 3:{
										A.removeBoard_3({X, Y}, {Xchoose, Ychoose});
										break;
									}
									case 4:{
										A.removeBoard_4({X, Y}, {Xchoose, Ychoose});
										break;
									}
								}
								break;
							}
                        	choose = false;
                   		}
                    }
                    else{
                        choose = false;
                    }
                    
                    while(CompleteCells <= row * col - 2 && !A.checkBoard())
                    	A.suffleBoard();
                    	
                    SettingGame::setColor(BLACK, WHITE);
                    SettingGame::clearConsole();
                    SettingGame::setColor(BLACK, WHITE);
                    A.drawBoard(mode);
                    SettingGame::setColor(BLACK, WHITE);
                    A.drawCells(A._board[oldX][oldY], oldX, oldY, mode);
                    SettingGame::setColor(BLACK, GREEN);				// Ô đang tr
                    A.drawCells(A._board[X][Y], X, Y, 1);
                    oldX = X;
                    oldY = Y;
                }
                break;
            }

            case KEY_ESC:{
                //A.~Board();
                return;
            }
            
            case KEY_SUGGEST:{
            	A.Board::suggestBoard(p, q);
            	SettingGame::setColor(BLACK, YELLOW);
            	A.drawCells(A._board[p.first][p.second], p.first, p.second, 1);
            	SettingGame::setColor(BLACK, YELLOW);
				A.drawCells(A._board[q.first][q.second], q.first, q.second, 1);
				SettingGame::setColor(BLACK, WHITE);
				break;
			}
			
			case KEY_SHUFFLE:{
				A.Board::suffleBoard();
				A.drawBoard(mode);
				break;
			}
        }
		
//
        if(X != oldX || Y != oldY){
            SettingGame::setColor(BLACK, WHITE);
            //SettingGame::clearConsole();
            SettingGame::setColor(BLACK, WHITE);
            A.drawBoard(mode);
            SettingGame::setColor(BLACK, WHITE);
            A.drawCells(A._board[oldX][oldY], oldX, oldY, mode);
            SettingGame::setColor(BLACK, GREEN);				// Ô đang trỏ vào
            A.drawCells(A._board[X][Y], X, Y, 1);
            oldX = X;
            oldY = Y;
        }

        if(choose){
            SettingGame::setColor(BLACK, RED);				// Ô đang được chọn
            A.drawCells(A._board[Xchoose][Ychoose], Xchoose, Ychoose, 1);
            SettingGame::setColor(BLACK, WHITE);
        }
        Sleep(50);
        
    }
    
    //player.score = Score;
    //Menu::printVictory();
    A.~Board();
    SettingGame::clearConsole();
    
}

