#include "Pro.h"

void ProMode::ProPlay(){
	int Score = 0;
	int row = 6, col = 12;
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
    B.drawBoard();

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
						Score += 200;
						CompleteCells += 2;
						B.drawLine(Path);
						Sleep(20);
						B.removeBoard({X, Y}, {Xchoose, Ychoose});
//                      B.removeCell(X, Y);
//                      B.removeCell(Xchoose, Ychoose);
                        choose = false;
                    }
                    else{
//                        SettingGame::setColor(BLACK, WHITE);
//                        A.drawCells(A._board[X][Y], X, Y);
//                        A.drawCells(A._board[Xchoose][Ychoose], Xchoose, Ychoose);
                        choose = false;
                    }
                    while(CompleteCells <= row * col - 2 && !B.checkBoard())
                    	B.suffleBoard();
                    	
                    SettingGame::setColor(BLACK, WHITE);
                    SettingGame::clearConsole();
                    SettingGame::setColor(BLACK, WHITE);
                   
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
            	B.~Board2();
                return;
                break;
            }
            
            case KEY_SUGGEST:{
            	B.Board2::suggestBoard(p, q);
            	
            	SettingGame::setColor(BLACK, YELLOW);
            	B.drawCells(B.getCell(p.first, p.second), p.first, p.second);
            	
            	SettingGame::setColor(BLACK, YELLOW);
				B.drawCells(B.getCell(q.first, q.second), q.first, q.second);
				
				SettingGame::setColor(BLACK, WHITE);
				break;
			}
			
			case KEY_SHUFFLE:{
				B.Board2::suffleBoard();
				B.drawBoard();
				break;
			}
        }   
        /// Hiển thị vị trí con trỏ thay đổi
    	if(X != oldX || Y != oldY){
            SettingGame::setColor(BLACK, WHITE);
            SettingGame::clearConsole();
            SettingGame::setColor(BLACK, WHITE);
            
			B.drawBoard();
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
    
    //player.score = Score;
    //Menu::printVictory();
	SettingGame::clearConsole();
    //Menu::printMenu();
    B.~Board2();
	return;
}

