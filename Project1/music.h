#ifndef MUSIC_H
#define MUSIC_H
#include<iostream>
#include<string>
#include<Windows.h>
using namespace std;

class music {
	bool *fire;
	string name;

public:
	bool ongoing;
	music();
	void loop(string name,int dur);
	void pause();
	void resume();

};
struct info
{
	int secs;
	 string name;
	bool *flag;

};
#endif