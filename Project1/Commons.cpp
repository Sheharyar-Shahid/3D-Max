#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<iomanip>
#include<sstream>
#include<windows.h>

#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
using namespace sf;
using namespace std;

int push;
bool level2locked = true;
bool EnterBossMode = 0;

bool *getlevel2locked()
{
	return &level2locked;
}
int * getpush()
{
	return &push;
}
bool* getEnterBossMode()
{
	return &EnterBossMode;
}
string str(int x)
{
	stringstream xe;
	xe << setfill('0') << setw(5) << x;
	return xe.str();

}
void Terminate()
{
	MessageBox(NULL, "Failed to initiallize", "Error", MB_OK);
	exit(-1);

}




