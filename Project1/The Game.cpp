
#include "commons.cpp"
#include "intia.h"
#include"music.h"
Font* getresource();
Text* getsubtitle();
RenderWindow* getwind();
intia* getsub();
bool* getEnterBossMode();

int LEVEL1();
int LEVEL2();
void Terminate();


DWORD WINAPI menu(LPVOID)
{
	while (true)
	{
		PlaySound(".\\audio\\menu.wav", NULL, SND_SYNC);
		Sleep(1000);

	}
	return 0;
}

int main()
{
	//ShowWindow((*getwind()).getSystemHandle(), SW_MINIMIZE);

	char path[400];
	GetModuleFileName(0, path, 400);
	int count = strlen(path);
	while (path[count--] != '\\');
	path[count+2] = '\0';
	SetCurrentDirectory(path);
	

	(*getwind()).setMouseCursorVisible(false);
	HANDLE ticket;
	music menu;
	getresource()->loadFromFile("astron boy.ttf");
	Texture card;
	Sprite back;


	Text head = *getsubtitle();

	

	Text opt[3];
	//mciSendString("play 'C:\\Endless Memories\\Project1\\audio\\menu.wav' repeat", 0, 0, 0);
	//PlaySound(".\\audio\\menu.wav", 0, SND_ASYNC);
	Texture spark;
	spark.loadFromFile("spark.png");
	Sprite sspark;
	sspark.setTexture(spark);
	sspark.setPosition(901+200, 257+200);
	sspark.setOrigin(400, 400);
	Clock frame;
reset:
	PlaySound(".\\audio\\menu.wav", 0, SND_LOOP | SND_ASYNC);

	
	head = *getsubtitle();
	card.loadFromFile("pro.png");
	back.setTexture(card);
	head.setString("Endless Memories...");
	head.setPosition(450, 57);
	head.setCharacterSize(100);
	for (int i = 0; i < 3; i++)
	{
		opt[i] = *getsubtitle();
		opt[i].setCharacterSize(40);
		opt[i].setPosition(450, 300 + 50 * i);
	}
	opt[0].setString("Play level 1");
	opt[1].setString("Play level 2");
	opt[2].setString("Exit");
	opt[0].setCharacterSize(50);
	int choice = 0;
	while (true)
	{
		Event poll;
		while ((*getwind()).pollEvent(poll))
		{
			if (poll.type == Event::KeyReleased)
			{
				if (poll.key.code == Keyboard::Down)
				{
					for (int i = 0; i < 3; i++)
						opt[i].setCharacterSize(40);
					choice = (choice + 1) % 3;
					opt[choice].setCharacterSize(50);
				}
				if (poll.key.code == Keyboard::Up)
				{
					for (int i = 0; i < 3; i++)
						opt[i].setCharacterSize(40);
					choice = (choice - 1);
					if (choice == -1) choice = 2;
					opt[choice].setCharacterSize(50);
				}
				if (poll.key.code == Keyboard::Return)
				{
					
					if (choice == 2) return 0;
					else if (choice == 0) { (*getEnterBossMode()) = 0; LEVEL1();  goto reset; }
					else if (choice == 1) { 
						//level2locked = false;
						if (!level2locked)
						{
							(* getEnterBossMode()) = 0;
							LEVEL2();
							goto reset;
						}
						else { getsub()->set("Complete level 1 to play level 2!"); menu.resume(); }

					}
				}
			}
		}

		(*getwind()).draw(back);
		
		(*getwind()).draw(head);
		
		for (int i = 0; i < 3; i++)
		{
			(*getwind()).draw(opt[i]);
		}
		(*getwind()).draw(getsub()->get());
		(*getwind()).draw(sspark);
		(*getwind()).display();
		(*getwind()).clear(Color(226,225,225));
		if (frame.getElapsedTime().asMilliseconds() > 100)
		{
			sspark.rotate(-0.01);
		}

	}
}