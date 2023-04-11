#include "Noob.h"

void NoobMode::NoobPlay(account& newAccount){
	srand(time(0));
	sound::start();
	int Type = rand() % 50;
	if(!Type)
		Type++;
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
    BG::drawBG(Type);
    A.drawBoard(1);
	
    SettingGame::setColor(BLACK, LIGHTYELLOW);
	SettingGame::gotoXY(100, 14);
	std::cout << "Hi, ";
	SettingGame::setColor(BLACK, YELLOW);
	std::cout << newAccount.Name;
	SettingGame::setColor(BLACK, LIGHTYELLOW);
	SettingGame::gotoXY(100, 16);
	std::cout << "Your score: " << Score;
	SettingGame::gotoXY(100, 18);
	std::cout << "Press 'H' to get suggestion (-50 points)";
	
	SettingGame::gotoXY(100, 20);
	std::cout << "Press 'R' to shuffe board (-100 points)";
	
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
						choose = false;
					}
                    else{
                        sound::wrong();
						
						choose = false;
                    }
                    
					while(CompleteCells != row * col && !A.checkBoard())
                    	A.suffleBoard();
                    	
                    SettingGame::setColor(BLACK, WHITE);
                    SettingGame::clearConsole();
                    SettingGame::setColor(BLACK, WHITE);
                    BG::drawBG(Type);
                    A.drawBoard(1);
                    
    SettingGame::setColor(BLACK, LIGHTYELLOW);
	SettingGame::gotoXY(100, 14);
	std::cout << "Hi, " << newAccount.Name;
	SettingGame::gotoXY(100, 16);
	std::cout << "Your score: " << Score;
	SettingGame::gotoXY(100, 18);
	std::cout << "Press 'H' to get suggestion (-50 points)";
	
	SettingGame::gotoXY(100, 20);
	std::cout << "Press 'R' to shuffe board (-100 points)";
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
//            	A.~Board();
                return;
            }
            
            case KEY_SUGGEST:{
            	A.Board::suggestBoard(p, q);
            	SettingGame::setColor(BLACK, YELLOW);
            	A.drawCells(A._board[p.first][p.second], p.first, p.second, 1);
            	SettingGame::setColor(BLACK, YELLOW);
				A.drawCells(A._board[q.first][q.second], q.first, q.second, 1);
				SettingGame::setColor(BLACK, WHITE);
				Score -= 50;
				break;
			}
			
			case KEY_SHUFFLE:{
				A.Board::suffleBoard();
				BG::drawBG(Type);
				A.drawBoard(1);
				Score -= 100;
				break;
			}
        }
		sound::choose();
		if(Score < -9999999)
			Score = -9999999;
		SettingGame::setColor(BLACK, BLACK);
		SettingGame::gotoXY(100, 16);
		std::cout << "                                   ";		
		SettingGame::setColor(BLACK, LIGHTYELLOW);
		SettingGame::gotoXY(100, 16);
		std::cout << "Your score: " << Score;

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
    
    SettingGame::clearConsole();
    BG::drawBG(Type);
    sound::victory();
    newAccount.Score = Score;
    newAccount.Mode = 1;
    
    for(int i = 0; i < 152; i++)
    	newAccount.pokemon[i] = 0;
    newAccount.pokemon[Type]++;
	
	
	account a[100];
	int stt = 0;
	bool saved = 0;
    //	Truyen du lieu tu file
	std::ifstream ifs("rank.txt", std::ios::in);
    while(!ifs.eof()){
        ifs >> a[stt].Name;
        ifs.ignore();
        ifs >> a[stt].Pass;
        ifs.ignore();
        ifs >> a[stt].Mode;
        ifs.ignore();
        ifs >> a[stt].Score;
        ifs.ignore();
        for(int i = 0; i < 152; i++)
            ifs >> a[stt].pokemon[i];
        ifs.ignore();
        stt++;
    }
    stt--;
    ifs.close();
    
    for(int i = 0; i < stt; i++){
        if(strcmp(newAccount.Name, a[i].Name) == 0){
            saved = 1;
            a[i].pokemon[Type]++;
            if(newAccount.Score > a[i].Score){
                a[i].Mode = newAccount.Mode;
                a[i].Score = newAccount.Score;
            }
            break;
        }
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
	
	std::ofstream ofs1("rank.txt", std::ios::out);
        for(int i = 0; i < stt; i++){
			ofs1 << a[i].Name << std::endl;
        	ofs1 << a[i].Pass << std::endl;
        	ofs1 << a[i].Mode << std::endl;
        	ofs1 << a[i].Score << std::endl;
        	for(int j = 0; j < 152; j++)
                ofs1 << a[i].pokemon[j] << " ";
            ofs1 << std::endl;
        }
	ofs1.close();

	//Menu::printVictory();
    SettingGame::clearConsole();
    
}

