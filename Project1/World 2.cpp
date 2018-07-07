#include "world2.h"

//#include "intia.h"


int devil2::revolve()
{
	counter = (counter + 1) % 48;
	return counter + 1;
}
bool devil2::tryHit(character& actor)
{

	if (actor.getPos().intersects(redbeam.getGlobalBounds()))
	{
		if (!hit)
		{
			hit = true;
			return true;
		}
	}
	return false;
}

bool devil2::isStruck(character& actor)
{
	if (hit) return false;

	if (consider && actor.getPos().intersects(redbeam.getGlobalBounds()))
	{
		consider = false;
		redbeam.setRadius(1);
		return true;

	}
	else return false;
}
CircleShape  devil2::getBeam()
{
	redbeam.setPosition(image.getPosition().x + image.getLocalBounds().width / 2 - redbeam.getGlobalBounds().width / 2, image.getPosition().y + image.getLocalBounds().height / 2 - redbeam.getGlobalBounds().height / 2);
	return redbeam;
}
devil2::devil2(string folder)
{
	consider = false;
	hit = false;
	redbeam.setRadius(10);


	redbeam.setFillColor(Color(0, 0, 0, 125));
	redbeam.setOutlineColor(Color::Yellow);
	redbeam.setOutlineThickness(2);
	num = 0;
	counter = 0;

	string path = ".\\" + folder + "\\";
	for (int i = 0; i < 49; i++)
	{

		if (!left[i].loadFromFile(path + "left\\actor" + str(i) + ".png")) Terminate();
		if (!right[i].loadFromFile(path + "right\\actor" + str(i) + ".png")) Terminate();
	}

	image.setTexture(left[0]);

}

FloatRect devil2::getPos()
{
	FloatRect  rect = image.getGlobalBounds();
	rect.width = left[0].getSize().x;
	rect.height = left[0].getSize().y;
	return rect;
}
Sprite devil2::get()
{
	if (state != 'i' && speed.getElapsedTime().asMilliseconds()>33)
	{
		if (!hit) {
			if (fireRate.getElapsedTime().asSeconds() > 5)
			{
				redbeam.setRadius(1);
				consider = false;
				if (fireRate.getElapsedTime().asSeconds() > 10)
				{

					redbeam.setRadius(1);
					fireRate.restart();
				}
			}
			else {
				consider = true;
				redbeam.setRadius(redbeam.getRadius() + 15);
				if (redbeam.getRadius() > 10000)
				{
					redbeam.setRadius(1);
				}

			}
		}
		else
		{
			if ((redbeam.getRadius() - 10) > 0) {
				redbeam.setRadius(redbeam.getRadius() - 10);
				redbeam.setFillColor(Color(0, 0, 255, 125));
			}
			else { hit = false; redbeam.setFillColor(Color(0, 0, 0, 125)); }

		}
		switch (state)
		{


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
	if (playfor.getElapsedTime().asSeconds()>0.5)
	{
		num++;
		if (num == strlen(seq))
		{
			num = 0;

		}
		switch (seq[num])

		{
		case 'l':goLeft(); break;
		case 'r': goRight(); break;
		case 'i':stop(); break;

		default:
			break;
		}

	}
	return image;
}
void devil2::stop()
{
	switch (state)
	{

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
void devil2::setPos(int x, int y)
{
	image.setPosition(x, y);
}
void devil2::goLeft()
{
	state = 'l';
	playfor.restart();
	image.setTextureRect(IntRect(0, 0, left[1].getSize().x, left[1].getSize().y));
}
void devil2::goRight()
{
	state = 'r';
	playfor.restart();
	image.setTextureRect(IntRect(0, 0, right[1].getSize().x, right[1].getSize().y));
}




float level2::getFactor()
{
	grow = (grow + 1) % 8;
	return seq[grow];

}
bool level2::shouldMove(int top, int left, int height, int width)
{
	//forbiden.push_back(1);
	Image temp(boundary);


	for (int i = left; i < left + width; i++)
	{

		for (int j = top; j < top + height; j++)
		{
			if (i < limx && j < limy) {
				temp.setPixel(i, j, Color::Yellow);
				if (boundary.getPixel(i, j).a < tolerate) return false;
			}
		}
	}
	//current.loadFromImage(temp);
	//image.setTexture(current);
	//wind.draw(image);
	//wind.display();

	return true;

}
bool level2::valid(int pos)
{
	for (size_t i = 0; i < forbiden.size(); i++)
	{
		if (forbiden[i] == pos) return false;
	}
	return true;
}
void level2::updateLocation()
{
	checkForBoss();
	mentionlocation.setPosition(Vector2f(map.getGlobalBounds().left + cur.x*mentionlocation.getSize().x, map.getGlobalBounds().top + cur.y*mentionlocation.getSize().y));

}
void level2::actorGetsLegend(character& actor)
{
	for (int i = 0; i < achieve.size(); i++)
	{
		if (achieve[i].gridlocation.x == cur.x && achieve[i].gridlocation.y == cur.y)
		{
			if (achieve[i].obtained == false) {
				achieve[i].obtained = actor.getPos().intersects(achieve[i].show.getGlobalBounds());
				if (achieve[i].obtained) {
					mciSendString("play .\\audio\\collect.wav", NULL, 0, NULL);

					switch (i)
					{
					case 2:
						this->LockAcquired = true;
						(*getsub()).set("The door's locked. Why not I use the key...");
						break;

					case 4:
						(*getsub()).set("Oh no! This is the room where I and Jenny lived...\nI just got from the photo");
						break;
					case 3:
						(*getsub()).set("There's another one. I miss you Jenny...");
						break;

					}

				}
			}
		}
	}


}
void level2::checkForBoss()
{

	if (bosslocation.x == cur.x && bosslocation.y == cur.y)
	{
		for (int i = 0; i < achieve.size(); i++)
		{
			if (achieve[i].obtained == false) return;

		}
		if (!(*getEnterBossMode()))
		{
			PlaySound(".\\audio\\boss.wav", 0, SND_ASYNC | SND_LOOP);
			*getEnterBossMode() = true;
			(*getsub()).set("Devil: Hahaha... You little pimp I gonna sequeeze you and your wife\nJack: Fuck off! I've come here to get my wife and I'll");

		}
		//else sub.set("Devil: Is that the best you got!\nJack: Eat This!");

	}

}

RectangleShape level2::getLocation()
{
	return mentionlocation;
}
void level2::EnterInto(character& actor)
{
	if (LockAcquired)
	{
		(*getsub()).set("Ah the key worked! I have been here before...");
		cur.x = 0;
		cur.y = 0;

		current.loadFromFile(".\\reallevel2\\" + str(cur.y*max.x + cur.x) + ".png");
		boundary = current.copyToImage();
		actor.setPos(defaulter[cur.y].x, defaulter[cur.y].y);
		updateLocation();
		LockAcquired = false;
	}

}
Sprite level2::getMap()
{

	return map;
}
vector<Sprite> level2::getLegends()
{
	vector <Sprite> get;
	for (int i = 0; i < achieve.size(); i++)
	{
		if (achieve[i].gridlocation.x == cur.x && achieve[i].gridlocation.y == cur.y)
		{
			if (achieve[i].obtained == false) {
				(*getpush()) = ((*getpush()) + 1) % 1000;
				float factor = (*getpush()) + 1;
				factor = factor / 2000 + 0.5;
				achieve[i].show.setScale(factor, factor);
				get.push_back(achieve[i].show);
			}
		}
	}
	if (legendTimer.getElapsedTime().asSeconds()>5)
	{
		legendTimer.restart();
	}
	return get;
}
POINT level2::SetActor()
{
	return defaulter[cur.y];
}
level2::level2()
{
	LockAcquired = false;
	defaulter[0].x = 800;
	defaulter[0].y = 50;

	defaulter[1].x = 22;
	defaulter[1].y = 411;

	bosslocation.x = 1;
	bosslocation.y = 0;
	grow = 1;
	int achievecount = 2;

	legend prop;
	Texture *t1;

	prop.obtained = false;
	prop.gridlocation.x = 0;
	prop.gridlocation.y = 1;
	t1 = new Texture();
	t1->loadFromFile(".\\reallevel1\\legend1.png");
	prop.show.setTexture(*t1);
	prop.show.setPosition(753, 588);
	prop.show.setOrigin(Vector2f(prop.show.getLocalBounds().width / 2, prop.show.getLocalBounds().height / 2));
	achieve.push_back(prop);

	prop.obtained = false;
	prop.gridlocation.x = 1;
	prop.gridlocation.y = 0;
	t1 = new Texture();
	t1->loadFromFile(".\\reallevel1\\legend2.png");
	prop.show.setTexture(*t1);
	prop.show.setPosition(1133, 631);
	prop.show.setOrigin(Vector2f(prop.show.getLocalBounds().width / 2, prop.show.getLocalBounds().height / 2));
	achieve.push_back(prop);


	prop.obtained = false;
	prop.gridlocation.x = 1;
	prop.gridlocation.y = 1;
	t1 = new Texture();
	t1->loadFromFile(".\\reallevel2\\legend5.png");
	prop.show.setTexture(*t1);
	prop.show.setPosition(355, 378);
	prop.show.setOrigin(Vector2f(prop.show.getLocalBounds().width / 2, prop.show.getLocalBounds().height / 2));
	achieve.push_back(prop);

	prop.obtained = false;
	prop.gridlocation.x = 1;
	prop.gridlocation.y = 0;
	t1 = new Texture();
	t1->loadFromFile(".\\reallevel2\\legend3.png");
	prop.show.setTexture(*t1);
	prop.show.setPosition(174, 347);
	prop.show.setTextureRect(IntRect(0, 0, t1->getSize().x, t1->getSize().y));
	prop.show.setOrigin(Vector2f(prop.show.getLocalBounds().width / 2, prop.show.getLocalBounds().height / 2));
	achieve.push_back(prop);

	prop.obtained = false;
	prop.gridlocation.x = 0;
	prop.gridlocation.y = 0;
	t1 = new Texture();
	t1->loadFromFile(".\\reallevel2\\legend4.png");
	prop.show.setTexture(*t1);
	prop.show.setTextureRect(IntRect(0, 0, t1->getSize().x, t1->getSize().y));
	prop.show.setPosition(867, 553);
	prop.show.setOrigin(Vector2f(prop.show.getLocalBounds().width / 2, prop.show.getLocalBounds().height / 2));
	achieve.push_back(prop);



	limx = 1366;
	limy = 768;
	max.x = 2;
	max.y = 2;


	Texture *tempmap = new Texture();
	tempmap->loadFromFile(".\\reallevel2\\map.png");
	map.setTexture(*tempmap);
	map.setPosition(limx - 10 - map.getLocalBounds().width, 10);

	mentionlocation.setSize(Vector2f(map.getLocalBounds().width / max.x, map.getGlobalBounds().height / max.y));
	mentionlocation.setFillColor(Color(0, 0, 0, 125));
	mentionlocation.setOutlineColor(Color::Red);
	mentionlocation.setOutlineThickness(1);


	cur.x = 0;
	cur.y = 1;
	updateLocation();


	tolerate = 245;
	current.loadFromFile(".\\reallevel2\\" + str(cur.y*max.x + cur.x) + ".png");
	boundary = current.copyToImage();
	Image temp;
	temp = current.copyToImage();
	for (int i = 0; i < current.getSize().x; i++)
	{
		for (int j = 0; j < current.getSize().y; j++)
		{
			if (temp.getPixel(i, j).a <tolerate) temp.setPixel(i, j, Color::White);
			else {
				temp.setPixel(i, j, Color::Black);

			}

		}

	}
	//current.loadFromImage(temp);
	image.setTexture(current);

}
void level2::moveCharacterUp(character& actor)
{
	if (actor.getPos().top - 10 > 0)
	{
		if (shouldMove(actor.getPos().top + (3 * actor.getPos().height) / 4, actor.getPos().left, actor.getPos().height / 4, actor.getPos().width))
			actor.goUp();
		else {
			mciSendString("play .\\audio\\ouch.wav", NULL, 0, NULL);
			actor.stop();
		}
	}
	else {
		/*if (!EnterBossMode && cur.y - 1 >= 0 && valid((cur.y - 1)*max.x + cur.x))
		{
		cur.y--;
		current.loadFromFile(".\\reallevel2\\" + str(cur.y*max.x + cur.x) + ".png");
		boundary = current.copyToImage();
		actor.setPos(defaulter[cur.y].x, defaulter[cur.y].y);
		updateLocation();
		}
		else*/
		actor.stop();

	}
	actorGetsLegend(actor);
	checkForBoss();
}
void level2::moveCharacterDown(character& actor)
{
	if (actor.getPos().top + actor.getPos().height + 5 < limy)
	{
		if (shouldMove(actor.getPos().top + actor.getPos().height, actor.getPos().left, 5, actor.getPos().width))
			actor.goDown();
		else {
			mciSendString("play .\\audio\\ouch.wav", NULL, 0, NULL);
			actor.stop();
		}
	}
	else {
		/*	if (!EnterBossMode && cur.y + 1 < max.y && valid((cur.y + 1)*max.x + cur.x))
		{
		cur.y++;
		current.loadFromFile(".\\reallevel2\\" + str(cur.y*max.x + cur.x) + ".png");
		boundary = current.copyToImage();
		actor.setPos(defaulter[cur.y].x, defaulter[cur.y].y);
		updateLocation();
		}
		else */

		actor.stop();

	}
	checkForBoss();
	actorGetsLegend(actor);
}
void level2::moveCharacterRight(character& actor)
{
	if (actor.getPos().left + actor.getPos().width + 75 < limx)
	{
		if (shouldMove(actor.getPos().top + (3 * actor.getPos().height) / 4, actor.getPos().left + actor.getPos().width, actor.getPos().height / 4, 25))
			actor.goRight();
		else {
			mciSendString("play .\\audio\\ouch.wav", NULL, 0, NULL);
			actor.stop();
		}
	}
	else {
		if (!(*getEnterBossMode()) && cur.x + 1 < max.x && valid((cur.y)*max.x + cur.x + 1))
		{
			cur.x++;
			current.loadFromFile(".\\reallevel2\\" + str(cur.y*max.x + cur.x) + ".png");
			boundary = current.copyToImage();
			actor.setPos(defaulter[cur.y].x, defaulter[cur.y].y);
			updateLocation();
		}
		else actor.stop();

	}
	actorGetsLegend(actor);
	checkForBoss();
}
void level2::moveCharacterLeft(character& actor)
{
	if (actor.getPos().left - 75 > 0) {
		if (shouldMove(actor.getPos().top + (3 * actor.getPos().height) / 4, actor.getPos().left - 25, actor.getPos().height / 4, 25))
			actor.goLeft();
		else {
			mciSendString("play .\\audio\\ouch.wav", NULL, 0, NULL);
			actor.stop();
		}
	}
	else {
		if (!(*getEnterBossMode()) && cur.x - 1 >= 0 && valid((cur.y)*max.x + cur.x - 1))
		{
			cur.x--;
			current.loadFromFile(".\\reallevel2\\" + str(cur.y*max.x + cur.x) + ".png");
			boundary = current.copyToImage();
			actor.setPos(defaulter[cur.y].x, defaulter[cur.y].y);
			updateLocation();
		}
		else actor.stop();

	}
	actorGetsLegend(actor);
	checkForBoss();
}
Sprite level2::get()
{
	return image;
}