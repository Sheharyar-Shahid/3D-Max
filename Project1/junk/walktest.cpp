#include"commons.txt"
#include<Windows.h>
#include<iomanip>
#include<sstream>
using namespace sf;
string str(int x)
{
	stringstream xe;
	xe<<setfill('0') << setw(5) << x;
	return xe.str();

}

int main()
{
	SetCurrentDirectory("E:\\chuck");
	RenderWindow win(VideoMode(960, 720), "hello");
	Texture sequence[36]
		, sequenceback[36],
		sequenceright[36]
		, sequenceleft[36]
		,normal
		,backnormal
		,leftnormal
		,rightnormal
		
		;
	leftnormal.loadFromFile("chuckleft.png");
	rightnormal.loadFromFile("chuckright.png");
	backnormal.loadFromFile("chuckback.png");
	normal.loadFromFile("chuckdef.png");
	cout << sizeof(normal);
	
	for (int i = 0; i < 36; i++)
	{
	if (!	sequence[i].loadFromFile(".\\walk\\walk" + str(i + 1) + ".png")) return -1;
	if (!	sequenceback[i].loadFromFile(".\\walkback\\chuck" + str(i + 1) + ".png")) return -1;
	if (!	sequenceright[i].loadFromFile(".\\walkright\\walkright" + str(i + 1) + ".png")) return -1;
	if(!	sequenceleft[i].loadFromFile(".\\walkleft\\walkleft" + str(i + 1) + ".png")) return -1;
	}

	Sprite test1;

	test1.setTexture(normal);
	int counter = 0;
	Clock rate;
	
	while (true)

	{
		Event poll;
		while (win.pollEvent(poll))
		{
			if (poll.type==Event::KeyPressed)
			{
				if (poll.key.code == Keyboard::Up)
				{
					
					if (rate.getElapsedTime().asMilliseconds()>33)
					{
						test1.setTexture(sequence[counter]);
						counter = (counter + 1) % 36;
						rate.restart();
					}
				}

				if (poll.key.code == Keyboard::Down)
				{

					if (rate.getElapsedTime().asMilliseconds()>33)
					{
						test1.setTexture(sequenceback[counter]);
						counter = (counter + 1) % 36;
						rate.restart();
					}
				}

				if (poll.key.code == Keyboard::Right)
				{

					if (rate.getElapsedTime().asMilliseconds()>33)
					{
						test1.setTexture(sequenceright[counter]);
						counter = (counter + 1) % 36;
						rate.restart();
					}
				}

				if (poll.key.code == Keyboard::Left)
				{

					if (rate.getElapsedTime().asMilliseconds()>33)
					{
						test1.setTexture(sequenceleft[counter]);
						counter = (counter + 1) % 36;
						rate.restart();
					}
				}
			}


			if (poll.type == Event::KeyReleased)
			{
				if (poll.key.code == Keyboard::Up)
				{

					test1.setTexture(normal);
				}
				if (poll.key.code == Keyboard::Down)
				{

					test1.setTexture(backnormal);
				}
				if (poll.key.code == Keyboard::Right)
				{

					test1.setTexture(rightnormal);
				}
				if (poll.key.code == Keyboard::Left)
				{

					test1.setTexture(leftnormal);
				}
			}



		}

		
		win.draw(test1);
		win.display();
		win.clear(Color::White);

	}

}