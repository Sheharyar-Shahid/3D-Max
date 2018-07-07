#include<SFML\Graphics.hpp>
#include<iostream>
#pragma comment (lib,"sfml-graphics-d.lib")
#pragma comment (lib,"sfml-system-d.lib")
#pragma comment (lib,"sfml-window-d.lib")
#include<Windows.h>
using namespace sf;
using namespace std;
class point :public RectangleShape
{
public:
	point()
	{
		this->setSize(Vector2f(1, 1));
		this->setFillColor(Color::Black);
		this->setPosition(0, 0);
	}


};
Mouse  input;
Vector2i cur, newc;
int x = 0, y = 0;
DWORD WINAPI update(LPVOID)
{
	while (1) {
		newc = input.getPosition();
		if (newc != cur)
		{
			int xd;
			if (newc.x != cur.x)
			{
				xd = newc.x - cur.x;
				xd = xd / abs(xd);
				x = x + xd;

			}

			if (newc.y != cur.y)
			{
				xd = newc.y - cur.y;
			xd = xd / abs(xd);
				y = y + xd;

			}
			cur = newc;

		}
	}
	return 0;
}
 
int main()
{
	

	point a;
	RenderWindow draw(VideoMode(600, 600), "Draw");
	draw.clear(Color::White);
	Image board;
	board.create(600, 600, Color::White);
	Texture tex;
	tex.loadFromImage(board);
	Sprite me;
	me.setTexture(tex);
	


	
	cur = input.getPosition();
	
cout<<	CreateThread(NULL, 0, update, 0, 0, 0);
	while (draw.isOpen())
	{
	
	
		if (x>=0 && x<600 && y>=0 && y<600)
		board.setPixel(x, y, Color::Black);
		
		tex.loadFromImage(board);

		draw.draw(me);
		draw.display();

		Event retrive;
		while (draw.pollEvent(retrive))
		{
			

			if (retrive.type == Event::KeyPressed)
			{
				if (retrive.key.code == Keyboard::Escape)
					draw.close();

			}
			if (retrive.type == Event::Closed)
			{
			
					draw.close();

			}
		}
		draw.clear(Color::White);

	}



}