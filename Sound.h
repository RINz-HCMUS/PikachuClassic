#pragma once
#include "SettingGame.h"
#include <MMSystem.h>
#include <stdio.h>
//#pragma comment(lib, "winmm.lib")
#include <iostream>
struct sound{
	static void choose();
	
	static void correct();
	
	static void leaderboard();
	
	static void start();
	
	static void wrong();
	
	static void victory();
	
	static void off();
};