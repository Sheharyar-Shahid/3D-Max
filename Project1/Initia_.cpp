
#include "intia.h"
#include<string>
#include<iostream>

using namespace std;
using namespace sf;
Text* getsubtitle();
Font* getresource();
	intia::intia()
	{
		getsubtitle()->setPosition(341, 671);

		getsubtitle()->setOutlineColor(Color::Black);
		getsubtitle()->setOutlineThickness(1);
		getsubtitle()->setFillColor(Color::White);
		getsubtitle()->setFont(*getresource());
		getsubtitle()->setCharacterSize(28);

	}
	void intia::set(string msg)
	{

		getsubtitle()->setString(msg);

		wiper.restart();
	}
	Text intia::get()
	{
		if (wiper.getElapsedTime().asSeconds() < 5)
		{
			return *getsubtitle();
		}
		else {
			getsubtitle()->setString("");
			return *getsubtitle();
		}
	}