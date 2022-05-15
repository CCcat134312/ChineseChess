#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
protected:
	sf::Texture texture;
	sf::Sprite body;
	std::string name;

public:
	Button();
	Button(std::string);
	Button(sf::Vector2f);
	Button(sf::Vector2f, std::string);
	Button(Button*);
	Button operator=(const Button&);
	void setTexture(std::string);
	bool isClicked(sf::Event&);
	sf::Sprite getBody() { return body; }
	std::string getName() { return name; }
};

