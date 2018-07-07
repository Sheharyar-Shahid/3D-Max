#include "world.h"

bool* getEnterBossMode();
string str(int x);
void Terminate();
intia* getsub();
int devil::revolve()
{
	counter = (counter + 1) % 48;
	return counter + 1;
}


	bool devil::tryHit(character& actor)
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
	bool devil::isStruck(character& actor)
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

	CircleShape  devil::getBeam()
	{
		redbeam.setPosition(image.getPosition().x + image.getLocalBounds().width / 2 - redbeam.getGlobalBounds().width / 2, image.getPosition().y + image.getLocalBounds().height / 2 - redbeam.getGlobalBounds().height / 2);
		return redbeam;
	}
	devil::devil(string folder)
	{
		consider = false;
		hit = false;
		redbeam.setRadius(10);


		redbeam.setFillColor(Color(0, 0, 0, 125));
		redbeam.setOutlineColor(Color::Red);
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
	FloatRect devil::getPos()
	{
		FloatRect  rect = image.getGlobalBounds();
		rect.width = left[0].getSize().x;
		rect.height = left[0].getSize().y;
		return rect;
	}
	Sprite devil::get()
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
					redbeam.setRadius(redbeam.getRadius() + 10);
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
					redbeam.setFillColor(Color::Red);
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
	void devil::stop()
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
	void devil::setPos(int x, int y)
	{
		image.setPosition(x, y);
	}

	void devil::goLeft()
	{
		state = 'l';
		playfor.restart();
		image.setTextureRect(IntRect(0, 0, left[1].getSize().x, left[1].getSize().y));
	}
	void devil::goRight()
	{
		state = 'r';
		playfor.restart();
		image.setTextureRect(IntRect(0, 0, right[1].getSize().x, right[1].getSize().y));
	}

	float level::getFactor()
	{
		grow = (grow + 1) % 8;
		return seq[grow];

	}
	bool level::shouldMove(int top, int left, int height, int width)
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
	bool level::valid(int pos)
	{
		for (size_t i = 0; i < forbiden.size(); i++)
		{
			if (forbiden[i] == pos) return false;
		}
		return true;
	}
	void level::updateLocation()
	{
		if (bosslocation.x == cur.x && bosslocation.y == cur.y)
		{
			for (int i = 0; i < achieve.size(); i++)
			{
				if (achieve[i].obtained == false) goto skip;

			}
			PlaySound(".\\audio\\boss.wav", 0, SND_ASYNC | SND_LOOP);
			(* getEnterBossMode()) = true;
			(*getsub()).set("Devil: So you looking for the key. Here I got for you. You find it in the afterlife\nJack:Haha! Very funny... Lets see!");

		}
	skip:
		mentionlocation.setPosition(Vector2f(map.getGlobalBounds().left + cur.x*mentionlocation.getSize().x, map.getGlobalBounds().top + cur.y*mentionlocation.getSize().y));

	}

	void level::actorGetsLegend(character& actor)
	{
		for (int i = 0; i < achieve.size(); i++)
		{
			if (achieve[i].gridlocation.x == cur.x && achieve[i].gridlocation.y == cur.y)
			{
				if (achieve[i].obtained == false) {

					achieve[i].obtained = actor.getPos().intersects(achieve[i].show.getGlobalBounds());
					if (achieve[i].obtained)
					{
						mciSendString("play .\\audio\\collect.wav", NULL, 0, NULL);
						if (i == 1) (*getsub()).set("This is a wierd mirror!");
						else if (i == 0) (*getsub()).set("Um....Nice Sword");
					}
				}
			}
		}


	}
	RectangleShape level::getLocation()
	{
		return mentionlocation;
	}
	Sprite level::getMap()
	{

		return map;
	}
	vector<Sprite> level::getLegends()
	{
		vector <Sprite> get;
		for (int i = 0; i < achieve.size(); i++)
		{
			if (achieve[i].gridlocation.x == cur.x && achieve[i].gridlocation.y == cur.y)
			{
				if (achieve[i].obtained == false) {

					achieve[i].show.rotate(0.1);
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
	level::level()
	{
		bosslocation.x = 0;
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
		prop.show.setPosition(116, 579);
		prop.show.setOrigin(Vector2f(prop.show.getLocalBounds().width / 2, prop.show.getLocalBounds().height / 2));
		achieve.push_back(prop);

		prop.obtained = false;
		prop.gridlocation.x = 1;
		prop.gridlocation.y = 1;
		t1 = new Texture();
		t1->loadFromFile(".\\reallevel1\\legend2.png");
		prop.show.setTexture(*t1);
		prop.show.setPosition(645, 200);

		prop.show.setOrigin(Vector2f(prop.show.getLocalBounds().width / 2, prop.show.getLocalBounds().height / 2));
		achieve.push_back(prop);




		limx = 1366;
		limy = 768;
		max.x = 2;
		max.y = 2;


		Texture *tempmap = new Texture();
		tempmap->loadFromFile(".\\reallevel1\\map.png");
		map.setTexture(*tempmap);
		map.setPosition(limx - 10 - map.getLocalBounds().width, 10);

		mentionlocation.setSize(Vector2f(map.getLocalBounds().width / max.x, map.getGlobalBounds().height / max.y));
		mentionlocation.setFillColor(Color(0, 0, 0, 125));
		mentionlocation.setOutlineColor(Color::Red);
		mentionlocation.setOutlineThickness(1);


		cur.x = 0;
		cur.y = 0;
		updateLocation();


		tolerate = 250;
		current.loadFromFile(".\\reallevel1\\" + str(cur.y*max.x + cur.x) + ".png");
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
	void level::moveCharacterUp(character& actor)
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
			if (!(* getEnterBossMode()) && cur.y - 1 >= 0 && valid((cur.y - 1)*max.x + cur.x))
			{
				cur.y--;
				current.loadFromFile(".\\reallevel1\\" + str(cur.y*max.x + cur.x) + ".png");
				boundary = current.copyToImage();
				actor.setPos(500, 300);
				updateLocation();
			}
			else actor.stop();

		}
		actorGetsLegend(actor);
	}
	void level::moveCharacterDown(character& actor)
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
			if (!(* getEnterBossMode()) && cur.y + 1 < max.y && valid((cur.y + 1)*max.x + cur.x))
			{
				cur.y++;
				current.loadFromFile(".\\reallevel1\\" + str(cur.y*max.x + cur.x) + ".png");
				boundary = current.copyToImage();
				actor.setPos(500, 300);
				updateLocation();
			}
			else actor.stop();

		}
		actorGetsLegend(actor);
	}
	void level::moveCharacterRight(character& actor)
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
			if (!(* getEnterBossMode()) && cur.x + 1 < max.x && valid((cur.y)*max.x + cur.x + 1))
			{
				cur.x++;
				current.loadFromFile(".\\reallevel1\\" + str(cur.y*max.x + cur.x) + ".png");
				boundary = current.copyToImage();
				actor.setPos(500, 300);
				updateLocation();
			}
			else actor.stop();

		}
		actorGetsLegend(actor);
	}
	void level::moveCharacterLeft(character& actor)
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
			if (!(* getEnterBossMode()) && cur.x - 1 >= 0 && valid((cur.y)*max.x + cur.x - 1))
			{
				cur.x--;
				current.loadFromFile(".\\reallevel1\\" + str(cur.y*max.x + cur.x) + ".png");
				boundary = current.copyToImage();
				actor.setPos(500, 300);
				updateLocation();
			}
			else actor.stop();

		}
		actorGetsLegend(actor);
	}
	Sprite level::get()
	{
		return image;
	}