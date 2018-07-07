#ifndef character_h
#define character_h
#include "stdafx.h"
class character {
	char state;
	int counter;

	Clock speed;
	Clock playfor;
	Sprite image;
	Texture up[37], left[37], right[37], down[37];
	int revolve();
	Texture hold[2];

	const Texture* temp;
	int devilpos;
public:

	void unhold();
	void updateDevilPos(int x);
	void holdProp();
	character(string folder, string proppath1, string proppath2);
	FloatRect getPos();
	Sprite get();
	void stop();
	void setPos(int x, int y);
	void goUp();
	void goDown();
	void goLeft();
	void goRight();
};
#endif
