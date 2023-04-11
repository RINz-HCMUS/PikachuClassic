#include "Sound.h"

void sound::choose(){
	PlaySound(TEXT("sounds\\choose.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void sound::correct(){
	PlaySound(TEXT("sounds\\correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void sound::leaderboard(){
	PlaySound(TEXT("sounds\\leaderboard.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void sound::start(){
	PlaySound(TEXT("sounds\\pikapipikachu.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void sound::wrong(){
	PlaySound(TEXT("sounds\\wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void sound::victory(){
	PlaySound(TEXT("sounds\\win.wav"), NULL, SND_FILENAME | SND_SYNC);
}

void sound::off(){
	PlaySound(NULL, NULL, 0);	
}