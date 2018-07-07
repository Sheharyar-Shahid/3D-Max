#ifndef intia_h
#define intia_h
#include<SFML\Graphics.hpp>
#include<iostream>

struct intia {
	sf::Clock wiper;
	intia();
	sf::Text get();
	void set(std::string);

};
#endif