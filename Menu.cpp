#include <fstream>
#include "SettingGame.h"
#include "Board2.h"
#include "Menu.h"

int main()
{
	SettingGame::setUpConsole();
	Menu MainMenu;
	
	//	Khoi tao
	account newAccount;
	account a[100];
	int stt = 0;
    int loginComplete = 0;

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
    
	// Bat con tro	
while(loginComplete != 1){
	loginComplete = 0;
	MainMenu.printLOGIN();
	SettingGame::setCursorInput(1);
	
	string s = "";
	///	Input account name
	
	// The first time
	SettingGame::gotoXY(85, 26);
//	cin >> newAccount.Name;
	SettingGame::setColor(BLACK, WHITE);
	cin >> s;
    while(s.size() > 15 || s == ""){
        SettingGame::clearConsole();
        MainMenu.printLOGIN();
        SettingGame::setColor(BLACK, RED);
        SettingGame::gotoXY(85, 24);
		cout << "The account name must not be empty and must not exceed 15 English characters.";
		SettingGame::gotoXY(85, 26);
		SettingGame::setColor(BLACK, WHITE);
	    cin.ignore();
		cin >> s;
    }
    
	SettingGame::setColor(BLACK, BLACK);
    SettingGame::gotoXY(85, 24);
	cout << "                                                                              ";
	
	strcpy(newAccount.Name, s.c_str());
	
	
	SettingGame::gotoXY(85, 30);
	SettingGame::setColor(BLACK, WHITE);
    cin.ignore(); 
	cin >> s;
	while(s.size() > 15 || s == ""){
        SettingGame::clearConsole();
        MainMenu.printLOGIN();
        SettingGame::setColor(BLACK, RED);
        SettingGame::gotoXY(85, 24);
        cout << "The account password must not be empty and must not exceed 15 character.";
        SettingGame::setColor(BLACK, WHITE);
        SettingGame::gotoXY(85, 30);
        cin.ignore();
		cin >> s;
        }
    SettingGame::setColor(BLACK, BLACK);
    SettingGame::gotoXY(85, 24);
		cout << "                                                                         ";
    strcpy(newAccount.Pass, s.c_str());    
    
	for(int i = 0; i < stt; i++){
		if(loginComplete == 1)
			break;
		// Neu tai khoan ton tai
        if(strcmp(a[i].Name, newAccount.Name) == 0){
        	// check password
            if(strcmp(a[i].Pass, newAccount.Pass) == 0){
			SettingGame::setColor(BLACK, RED);
            SettingGame::gotoXY(85, 24);
				cout << "LOGIN COMPLETE!";
				loginComplete = 1;
            }

            else{
                int tmp = 3;
                while(tmp){
					SettingGame::setColor(BLACK, RED);
           			SettingGame::gotoXY(85, 24);
					cout << "Wrong password. Try agian." << tmp << " times left.\n";
                    SettingGame::gotoXY(85, 30);
					cin.ignore();
                    cin >> s;
                    if(strcmp(a[i].Pass, s.c_str()) == 0){
                    	strcpy(newAccount.Pass, a[i].Pass);
						break; 
					}
                     else
                        tmp--;
                }
                if(tmp == 0){
                    SettingGame::setColor(BLACK, BLACK);
    	    		SettingGame::gotoXY(85, 24);
					cout << "   				                             		";
					SettingGame::setColor(BLACK, RED);
           			SettingGame::gotoXY(85, 24);
					cout << "You have entered the wrong password too many times!";
					//SettingGame::clearConsole();
                    loginComplete = 2;
                }
                else{
				
	                SettingGame::setColor(BLACK, BLACK);
    		    	SettingGame::gotoXY(85, 24);
					cout << "   		                         				";
					SettingGame::setColor(BLACK, RED);
           			SettingGame::gotoXY(85, 24);
            	    cout << "LOGIN COMPLETE!";
                	loginComplete = 1;
                }
            }
        }
    }
    if(loginComplete == 0){
    SettingGame::setColor(BLACK, RED);
	SettingGame::gotoXY(75, 24);	
    cout << "Don't have this accound. Do you want sign in it? (YES or NO)\n";
    SettingGame::gotoXY(75, 25);
	cin >> s;
	while(true)
        if(s == "YES"){
        	SettingGame::gotoXY(75, 25);
            cout << "Your account was created! Have fun.";
			loginComplete = 1;
			newAccount.Mode = 0;
			newAccount.Score = 0;
//			std::ofstream ofs("rank.txt", std::ios::app);
//        	ofs << newAccount.Name << std::endl;
//        	ofs << newAccount.Pass << std::endl;
//        	ofs << newAccount.Mode << std::endl;
//        	ofs << newAccount.Score << std::endl;
//       	ofs.close();
        	Sleep(500);
            break;
        }
        else if(s == "NO"){
        	SettingGame::gotoXY(75, 25);
            cout << "Please login again!";
            Sleep(500);
            break;
        }
        else{
			MainMenu.printLOGIN();
			SettingGame::setColor(BLACK, WHITE);
        	SettingGame::gotoXY(85, 26);
        	cout << newAccount.Name;
			
			SettingGame::gotoXY(85, 30);
        	cout << newAccount.Pass;

   			SettingGame::setColor(BLACK, RED);
			SettingGame::gotoXY(75, 24);	
    		cout << "Don't have this accound. Do you want sign in it? (YES or NO)";        	
    		
        	SettingGame::gotoXY(75, 25);
            cin >> s;
        }
  	}
}
	SettingGame::setCursorInput(0);
//	MainMenu.printVictory();
	while(true)
		MainMenu.printMenu(newAccount);


}
