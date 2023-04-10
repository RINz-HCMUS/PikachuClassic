#include "Noob.h"

void NoobMode::NoobPlay(){
	sound::start();
	int row = 6, col = 6;
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
    sound::start();
	 	
    SettingGame::clearConsole();
    SettingGame::setColor(BLACK, WHITE);
    A.drawBoard(1);

    SettingGame::setColor(BLACK, GREEN);
    A.drawCells(A._board[0][0], 0, 0, 1);
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
						sound::correct();
						Score += 200;
						CompleteCells += 2;
						A.drawLine(Path);
						Sleep(20);
						A.removeBoard_0({X, Y}, {Xchoose, Ychoose});
//                        A.removeCell(X, Y);
//                        A.removeCell(Xchoose, Ychoose);
//                        A._board[X][Y] = -1;
//                        A._board[Xchoose][Ychoose] = -1;
                        choose = false;
                    }
                    else{
//                        SettingGame::setColor(BLACK, WHITE);
//                        A.drawCells(A._board[X][Y], X, Y);
//                        A.drawCells(A._board[Xchoose][Ychoose], Xchoose, Ychoose);
                        sound::wrong();
						choose = false;
                    }
                    while(CompleteCells <= row * col - 2 && !A.checkBoard())
                    	A.suffleBoard();
                    	
                    SettingGame::setColor(BLACK, WHITE);
                    SettingGame::clearConsole();
                    SettingGame::setColor(BLACK, WHITE);
                    A.drawBoard(1);
                    SettingGame::setColor(BLACK, WHITE);
                    A.drawCells(A._board[oldX][oldY], oldX, oldY, 1);
                    SettingGame::setColor(BLACK, GREEN);				// Ô đang tr
                    A.drawCells(A._board[X][Y], X, Y, 1);
                    oldX = X;
                    oldY = Y;
                }
                break;
            }

            case KEY_ESC:{
            	A.~Board();
                return;
                break;
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
				A.drawBoard(1);
				break;
			}
        }
		sound::choose();
//
        if(X != oldX || Y != oldY){
            SettingGame::setColor(BLACK, WHITE);
            //SettingGame::clearConsole();
            SettingGame::setColor(BLACK, WHITE);
            A.drawBoard(1);
            SettingGame::setColor(BLACK, WHITE);
            A.drawCells(A._board[oldX][oldY], oldX, oldY, 1);
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
    sound::victory();
    //player.score = Score;
    //Menu::printVictory();
    A.~Board();
    SettingGame::clearConsole();
    
}

