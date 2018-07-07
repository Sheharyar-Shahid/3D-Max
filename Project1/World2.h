#ifndef WORLD2_H
#define WORLD2_H

#include "SFML\Graphics\Rect.hpp"
#include "intia.h"
#include<iostream>
#include<windows.h>
using namespace std;

#include "character.h"


string str(int x);
bool* getEnterBossMode();
void Terminate();

int * getpush();
intia* getsub();

class devil2 {
	bool consider;
	CircleShape redbeam;
	Clock fireRate;
	char state;
	int counter;
	const  char  *seq = "lrllrllrllrllrllrlrrrrrr";
	int num;

	Clock speed;
	Clock playfor;
	Sprite image;
	Texture left[49], right[49];
	int revolve();
	bool hit;
public:

	bool tryHit(character& actor);
	bool isStruck(character& actor);
	CircleShape  getBeam();
	devil2(string folder);
	FloatRect getPos();
	Sprite get();
	void stop();
	void setPos(int x, int y);
	void goLeft();
	void goRight();
};

class level2 {

	bool LockAcquired;
	POINT bosslocation;

	const float seq[8] = { 0.88f,0.9f,0.92f,0.96f,1,0.96f,0.92f,0.9f };

	struct legend {
		bool obtained;
		Sprite show;
		POINT gridlocation;
	};
	int grow;


	vector<legend> achieve;
	Clock legendTimer;
	vector<int> forbiden;
	POINT max;
	POINT cur;
	Texture current;
	Sprite image;
	Image boundary;
	int limx;
	int limy;
	int tolerate;
	Sprite map;
	RectangleShape mentionlocation;
	POINT defaulter[2];
	float getFactor();
	bool shouldMove(int top, int left, int height, int width);
	bool valid(int pos);
	void updateLocation();
	void actorGetsLegend(character& actor);
	void checkForBoss();

public:
	RectangleShape getLocation();

	void EnterInto(character& actor);
	Sprite getMap();
	vector<Sprite> getLegends();
	POINT SetActor();
	level2();
	void moveCharacterUp(character& actor);
	void moveCharacterDown(character& actor);
	void moveCharacterRight(character& actor);
	void moveCharacterLeft(character& actor);
	Sprite get();

};
#endif