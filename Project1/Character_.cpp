#include"character.h"

string str(int x);
void Terminate();
int character::revolve()
{
	counter = (counter + 1) % 36;
	return counter + 1;
}

void character::unhold()
{
	image.setTexture(*temp);
	image.setTextureRect(IntRect(0, 0, (*temp).getSize().x, (*temp).getSize().y));
	state = 'i';

}
void character::updateDevilPos(int x)
{
	devilpos = x;
	if (state == 'h')
	{
		short num = (bool)(devilpos <  this->image.getGlobalBounds().top);


		image.setTexture(hold[num]);
		image.setTextureRect(IntRect(0, 0, hold[num].getSize().x, hold[num].getSize().y));
	}
}

void character::holdProp()
{

	if (state != 'h') temp = image.getTexture();

	state = 'h';
}
character::character(string folder, string proppath1, string proppath2)
{

	hold[0].loadFromFile(proppath1);
	hold[1].loadFromFile(proppath2);
	counter = 0;

	string path = ".\\" + folder + "\\";
	for (int i = 0; i < 37; i++)
	{
		if (!up[i].loadFromFile(path + "up\\actor" + str(i) + ".png")) Terminate();
		if (!down[i].loadFromFile(path + "down\\actor" + str(i) + ".png")) Terminate();
		if (!left[i].loadFromFile(path + "left\\actor" + str(i) + ".png")) Terminate();
		if (!right[i].loadFromFile(path + "right\\actor" + str(i) + ".png")) Terminate();
	}
	image.setTexture(up[0]);
	image.setColor(Color::White);
}

FloatRect character::getPos()
{
	FloatRect  rect = image.getGlobalBounds();
	rect.width = up[0].getSize().x;
	rect.height = up[0].getSize().y;
	return rect;
}
Sprite character::get()
{
	if (state != 'i' && state != 'h'  && speed.getElapsedTime().asMilliseconds()>25)
	{
		switch (state)
		{
		case 'u':
			image.setTexture(up[revolve()]);
			image.move(0, -5);
			break;
		case 'd':
			image.setTexture(down[revolve()]);
			image.move(0, 5);
			break;
		case 'l':
			image.setTexture(left[revolve()]);
			image.move(-5, 0);
			break;
		case 'r':
			image.setTexture(right[revolve()]);
			image.move(5, 0);
			break;
		default:
			break;
		}


		speed.restart();
	}
	////	if (playfor.getElapsedTime().asSeconds()>0.5 && state!='i')
	//	{ 
	//		stop();
	//                   
	//	}
	return image;
}
void character::stop()
{
	switch (state)
	{
	case 'u':
		image.setTexture(up[0]);
		image.setTextureRect(IntRect(0, 0, up[0].getSize().x, up[0].getSize().y));
		break;
	case 'd':
		image.setTexture(down[0]);
		image.setTextureRect(IntRect(0, 0, down[0].getSize().x, down[0].getSize().y));
		break;
	case 'l':
		image.setTexture(left[0]);
		image.setTextureRect(IntRect(0, 0, left[0].getSize().x, left[0].getSize().y));
		break;
	case 'r':
		image.setTexture(right[0]);
		image.setTextureRect(IntRect(0, 0, right[0].getSize().x, right[0].getSize().y));
		break;
	default:
		break;
	}
	state = 'i';
}
void character::setPos(int x, int y)
{
	image.setPosition(x, y);
}
void character::goUp()
{
	state = 'u';
	playfor.restart();
	image.setTextureRect(IntRect(0, 0, up[1].getSize().x, up[1].getSize().y));

}
void character::goDown()
{
	state = 'd';
	playfor.restart();
	image.setTextureRect(IntRect(0, 0, down[1].getSize().x, down[1].getSize().y));
}
void character::goLeft()
{
	state = 'l';
	playfor.restart();
	image.setTextureRect(IntRect(0, 0, left[1].getSize().x, left[1].getSize().y));
}

void character::goRight()
{
	state = 'r';
	playfor.restart();
	image.setTextureRect(IntRect(0, 0, right[1].getSize().x, right[1].getSize().y));
}