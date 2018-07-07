#include<iostream>
#include<vector>
#include"character.h"
#include "world2.h"
#include"intia.h"
#include<SFML\Graphics.hpp>
#include "music.h"
#pragma comment (lib,"winmm.lib")
using namespace std;
using namespace sf;
music back2;

intia* getsub();
string str(int x);
Font* getresource();
Text* getsubtitle();
RenderWindow* getwind();
Font* getresource();
Text* getsubtitle();
RenderWindow* getwind();
bool* getEnterBossMode();



int LEVEL2()
{
	
	
	
	
	cout << "World2" << endl;

	getresource()->loadFromFile("astron boy.ttf");

	//mciSendString("play sound.wav", NULL, 0, NULL);


	//PlaySound("sound.wav", NULL, SND_LOOP|SND_ASYNC);
	//PlaySound("aw.wav", NULL, SND_ASYNC|SND_NOSTOP);
	Texture load;
	load.loadFromFile("load.png");
	Sprite wait;
	wait.setTexture(load);
	getwind()->draw(wait);
	getwind()->display();

	character   hello("actor", ".\\actor\\holdsword2.png",".\\actor\\holdsword1.png");
	devil2 hell("actor\\devil2");
	hell.setPos(890, 360);
	level2 lev;
	hello.setPos(lev.SetActor().x, lev.SetActor().y);

	int shortcount = 0;
	int rows = 2;
	int col = 2;
	Texture world,
		chuck[36]
		;
	for (int i = 1; i < 37;i++)
	chuck[i-1].loadFromFile(".\\actor\\right\\actor"+str(i)+".png");
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
	int livecount = 100;
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

	Clock stamina;

	evilbar.setFillColor(Color(255,0,0,125));
	evilbar.setSize(Vector2f(1, 25));
	evilbar.setPosition(10, 768-30-30);
	PlaySound(".\\audio\\music.wav", 0, SND_ASYNC | SND_LOOP);
//	EnterBossMode = true;
	mciSendString("play .\\audio\\intro2.wav", NULL, 0,0);
	getsub()->set("I remember the key I found belongs to this hotel...");
	while (getwind()->isOpen())
	{
		Event poll;

		getwind()->draw(lev.get());
		if (!(*getEnterBossMode())) {
			getLegends = lev.getLegends();
			for (int i = 0; i < getLegends.size(); i++)
				getwind()->draw(getLegends[i]);
			
		
		}
		
		

		if ((*getEnterBossMode()))
		{

			getwind()->draw(hell.get());
			
		}
	
		getwind()->draw(hello.get());
		
		if (!(*getEnterBossMode()))
		{
			getwind()->draw(lev.getMap());
			getwind()->draw(lev.getLocation());
		}
		if ((*getEnterBossMode())) {
			getwind()->draw(hell.getBeam());

			getwind()->draw(herobar);
			getwind()->draw(evilbar);
			getwind()->draw(die);
			if (dragStart)
			{
				if (hell.tryHit(hello)) { devilcount -= 2; }
				if (stamina.getElapsedTime().asSeconds() > 2)
				{
					livecount-= 10;
					stamina.restart();
				}
			}
		}
		getwind()->draw(getsub()->get());
		getwind()->display();
		while (getwind()->pollEvent(poll))
		{
			if (poll.type == Event::KeyPressed)
			{
				if (poll.key.code == Keyboard::Escape)
				{
					back2.pause();
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
					if (!dragStart) {
						dragStart = 1;
						hello.holdProp();
						stamina.restart();
					}
					lev.EnterInto(hello);
					
			
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
		getwind()->clear();

		if ((*getEnterBossMode()))
		{
			
			hello.updateDevilPos(hell.getPos().top);
			if (hell.isStruck(hello)) { livecount -= 2; }
			evilbar.setScale(devilcount, 1);
			herobar.setScale(livecount, 1);
			die.setFillColor(Color(2.55*livecount, 0, 0, 255 - 2.55*(livecount)));
			if (livecount <= 0 || devilcount <= 0) break;

		}
		
		//if (!livecount) break;
	
	
	}

	Text declareResult;
	declareResult.setFont(*getresource());
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
	
	}

	Texture card;
	card.loadFromFile(".\\reallevel1\\levelend.jpg");
	Sprite set;
	set.setTexture(card);
	if (livecount>0)	PlaySound(".\\audio\\finish.wav", 0,SND_ASYNC|SND_LOOP);

	while (true)
	{
		getwind()->draw(set);
		getwind()->draw(declareResult);
		getwind()->display();
		Event poll;
		while (getwind()->pollEvent(poll))
		{
			if (poll.type == Event::KeyReleased)
			{
				if (poll.key.code == Keyboard::Return)
				{
					goto next;
					
				}
			}
		}
		getwind()->clear();
	}
	next:
	if (livecount > 0)
	{
		mciSendString("play .\\audio\\end.wav", 0, 0, 0);
		Clock track;
		cout<<endl<<card.loadFromFile(".\\reallevel2\\gamewin.png");
		set.setTexture(card);
		getsubtitle()->move(-50, -50);
		getsub()->set("Jack: Nights before this night were full of isolation and your endless memories.\nJenny: I am still shocked Jack, I hope that devil never come back\nJack: Never...");
		while (true)
		{
			if (track.getElapsedTime().asSeconds() < 10) {
				getsub()->set("Jack: Nights before this night were full of isolation and your endless memories.\nJenny: I am still shocked Jack, I hope that devil never come back\nJack: Never...");
			}
			else
				getsub()->set("Game Completed! Press Space to return...");
			getwind()->draw(set);
			getwind()->draw(getsub()->get());
			getwind()->display();
			Event poll;
			while (getwind()->pollEvent(poll))
			{
				if (poll.type == Event::KeyReleased)
				{
					if (poll.key.code == Keyboard::Space)
					{
						back2.pause();
						return 1;

					}
				}
			}
			getwind()->clear();
		}
	}
	return 0;
}