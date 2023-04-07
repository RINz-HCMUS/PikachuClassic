#include "SettingGame.h"
#include "Board.h"
#include "Menu.h"

int main()
{
	SettingGame::setUpConsole();
	Menu MainMenu;
//	MainMenu.printVictory();
	while(true)
		MainMenu.printMenu();

//	Board A(4, 4, 26);
//	A.Board::drawBoard();

}
