#ifndef WORLD_H
#define WORLD_H
#include "SFML\Graphics\Rect.hpp"
#include "intia.h"
#include<iostream>
#include<windows.h>
using namespace std;

#include "character.h"

class devil {
	bool consider;
	CircleShape redbeam;
	Clock fireRate;
	char state;
	int counter;
	const  char  *seq = "lllllllllrrrrrrrrr";
	int num;

	Clock speed;
	Clock playfor;
	Sprite image;
	Texture left[49], right[49];
	bool hit;

	int revolve();

public:

	bool tryHit(character& actor);
	bool isStruck(character& actor);

	CircleShape  getBeam();
	devil(string folder);
	FloatRect getPos();
	Sprite get();
	void stop();
	void setPos(int x, int y);

	void goLeft();
	void goRight();
};

class level {


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
	float getFactor();
	bool shouldMove(int top, int left, int height, int width);
	bool valid(int pos);
	void updateLocation();

	void actorGetsLegend(character& actor);
public:
	RectangleShape getLocation();
	Sprite getMap();
	vector<Sprite> getLegends();
	level();
	void moveCharacterUp(character& actor);
	void moveCharacterDown(character& actor);
	void moveCharacterRight(character& actor);
	void moveCharacterLeft(character& actor);
	Sprite get();

};

#endif
