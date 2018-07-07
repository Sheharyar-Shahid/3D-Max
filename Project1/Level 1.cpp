#pragma once

#include<vector>
#include "intia.h"
#include "LEVEL1.h"
#include"character.h"
#include "world.h"
#include "music.h"
#include <Windows.h>

#pragma comment (lib,"winmm.lib")


string str(int x);
bool* getEnterBossMode();
bool *getlevel2locked();

RenderWindow wind(VideoMode(1366, 768), "Hello",Style::Fullscreen);
Font resource;
Text subtitle;

Font* getresource()
{
	return &resource;
}
Text* getsubtitle()
{
	return &subtitle;
}
RenderWindow* getwind()
{
	return &wind;
}

intia sub;

intia* getsub()
{
	return &sub;
}

Sprite sspark;
Texture spark;

Sprite wait;
DWORD WINAPI LOD(LPVOID)
{
	Clock frame;

	while (true)
	{
		if (frame.getElapsedTime().asMilliseconds() > 100)
		{
			wind.draw(wait);
			wind.draw(sspark);
			wind.display();
			wind.clear();
			sspark.rotate(0.5);
			frame.restart();
		}

	}
	return 0;
}

int LEVEL1()
{
	
	 
	
	
	cout << "World1" << endl;
	resource.loadFromFile("astron boy.ttf");
	bool startEffect = 1;
	//mciSendString("play sound.wav", NULL, 0, NULL);


//	PlaySound("", NULL, SND_LOOP|SND_ASYNC);
	//PlaySound("aw.wav", NULL, SND_ASYNC|SND_NOSTOP);
	Texture load;
	load.loadFromFile("load.png");
	
	
	
	wait.setTexture(load);
	wind.draw(wait);
	wind.display();


	character   hello("actor",".\\actor\\holdmirror1.png",".\\actor\\holdmirror2.png");
	devil hell("actor\\devil");
	hell.setPos(890, 360);
	level lev;
	hello.setPos(500, 300);

	int shortcount = 0;
	int rows = 2;
	int col = 2;
	Texture world,
		chuck[36]
		;
	
	for (int i = 1; i < 37; i++)
	{
		chuck[i - 1].loadFromFile(".\\actor\\right\\actor" + str(i) + ".png");
		
	}
	Sprite Background,
		man
		;
	man.setTexture(chuck[0]);
    int colindex=0;
	int rowindex=0;
	//cout<<world.loadFromFile("2.png")<<endl;
	Background.setTexture(world);
	string name = "2.png";
	Clock speed;
	vector<Sprite> getLegends;
	int livecount = 1;
	int devilcount = 100;
	bool dragStart=false;
	RectangleShape herobar;
	RectangleShape evilbar;
	RectangleShape die;
	die.setSize(Vector2f(1366, 768));
	die.setFillColor(Color(2.55*livecount, 0, 0, 255 - 2.55*(livecount)));

	herobar.setFillColor(Color(0,0,255,125));
	herobar.setSize(Vector2f(1, 25));
	herobar.setPosition(10, 768 - 30);

	

	evilbar.setFillColor(Color(255,0,0,125));
	evilbar.setSize(Vector2f(1, 25));
	evilbar.setPosition(10, 768-30-30);
	
	Clock forStart;
	Clock stamina;
	(*getsub()).set("Where am I? Perhaps,I was looking for some key.");
	PlaySound(".\\audio\\music.wav", 0, SND_ASYNC| SND_LOOP);
	mciSendString("play .\\audio\\intro1.wav", NULL, 0, NULL);
	while (wind.isOpen())
	{
		Event poll;

		wind.draw(lev.get());
		if (!(*getEnterBossMode())) {
			getLegends = lev.getLegends();
			for (int i = 0; i < getLegends.size(); i++)
				wind.draw(getLegends[i]);
			
		
		}
		
		

		if ((*getEnterBossMode()))
		{

			wind.draw(hell.get());
			
		}
	
		wind.draw(hello.get());
		
		if (!(*getEnterBossMode())) 
		{
			wind.draw(lev.getMap());
			wind.draw(lev.getLocation());
		}
		if ((*getEnterBossMode())) {
			wind.draw(hell.getBeam());

			wind.draw(herobar);
			wind.draw(evilbar);
			
			if (dragStart)
			{
				if (hell.tryHit(hello)) { devilcount -= 5; }
				if (stamina.getElapsedTime().asSeconds() > 2)
				{
					livecount -= 5;
					stamina.restart();
				}
			}
		}

		if (startEffect == true || (*getEnterBossMode()) == true)
		{
			
			wind.draw(die);
			if (startEffect) {
				if (forStart.getElapsedTime().asSeconds() > 5)
				{
					livecount = 100;
					startEffect = false;
				}
				else {
					if (forStart.getElapsedTime().asMilliseconds() % 50 == 0)
						livecount += 3;
					if (livecount > 100)
						livecount = 100;
				}
			}
		}
		wind.draw((*getsub()).get());
		wind.display();
		while (wind.pollEvent(poll))
		{
			if (poll.type == Event::KeyPressed)
			{
				if (poll.key.code == Keyboard::Escape)
				{
					
					return 9;
				}
				if (poll.key.code == Keyboard::Up)
				{
					lev.moveCharacterUp(hello);
					
		
				}
				if (poll.key.code == Keyboard::Down)
				{
					lev.moveCharacterDown(hello);
					
				}
				if (poll.key.code == Keyboard::Right)
				{
					lev.moveCharacterRight(hello);
			
			
				}
				if (poll.key.code == Keyboard::Left)
				{
					lev.moveCharacterLeft(hello);
					
				}
				if (poll.key.code == Keyboard::Space)
				{
					if (!dragStart)
					{
						dragStart = 1;
						stamina.restart();
					}
					hello.holdProp();
				
			
				}

			}
			else if (poll.type == Event::KeyReleased)
			{
			
				hello.stop();
				if (poll.key.code == Keyboard::Space)
				{
					dragStart = 0;
					hello.unhold();


				}
			}

		

		}
		wind.clear();

		if ((*getEnterBossMode()))
		{
			
			hello.updateDevilPos(hell.getPos().top);
			if (hell.isStruck(hello)) { 
				livecount -= 2;
			}
			evilbar.setScale(devilcount, 1);
			herobar.setScale(livecount, 1);
			die.setFillColor(Color(2.55*livecount, 0, 0, 255 - 2.55*(livecount)));
			if (livecount <= 0 || devilcount <= 0) break;

		}
		if ( startEffect) die.setFillColor(Color(2.55*livecount, 0, 0, 255 - 2.55*(livecount)));
		//if (!livecount) break;
	
	
	}

	Text declareResult;
	declareResult.setFont(resource);
	if (livecount <= 0)
	{

		declareResult.setString("\tYou are dead!\n\tPress Enter to Continue...");
		declareResult.setPosition(0, 768/2);
		declareResult.setFillColor(Color::Black);
		declareResult.setCharacterSize(50);

	}
	else {
		declareResult.setString("\tLevel Completed!\n\tEarned Points : "+str(livecount) +"\n\tPress Enter to Continue...");
		declareResult.setPosition(0, 768 / 2);
		declareResult.setFillColor(Color::Black);
		declareResult.setCharacterSize(40);
		(*getlevel2locked()) = false;
	
	}

	Texture card;
	card.loadFromFile(".\\reallevel1\\levelend.jpg");
	Sprite set;
	set.setTexture(card);
	while (true)
	{
		wind.draw(set);
		wind.draw(declareResult);
		wind.display();
		Event poll;
		while (wind.pollEvent(poll))
		{
			if (poll.type == Event::KeyReleased)
			{
				if (poll.key.code == Keyboard::Return)
				{
					
					return 9;
				}
			}
		}
		wind.clear();
	}
	return 0;
}