#include "Viewer.h"

Viewer::Viewer()
{
	this->window = nullptr;
	this->boardBackground = nullptr;
	this->title = nullptr;
}

Viewer::~Viewer()
{
	if (this->window != nullptr)
		delete this->window;
	if (this->boardBackground != nullptr)
		delete this->boardBackground;
	if (this->title != nullptr)
		delete this->title;
}

void Viewer::initMainPage()
{
	if (this->window != nullptr)
		delete this->window;
	sf::VideoMode videoMode(480, 500);
	this->window = new sf::RenderWindow(videoMode, "Main menu", sf::Style::Titlebar | sf::Style::Close);

	this->titleTexture.loadFromFile("image/title.png");
	this->title = new sf::Sprite();
	this->title->setTexture(titleTexture);
	this->title->setPosition(90, 30);

	this->startButton.setName("start_button");
	this->startButton.setPosition({ 117,150 });
	this->startButton.setTexture("image/start_button.png");

	this->loadButton.setName("load_button");
	this->loadButton.setPosition({ 117,250 });
	this->loadButton.setTexture("image/load_button.png");

	this->exitButton.setName("exit_button");
	this->exitButton.setPosition({ 117,350 });
	this->exitButton.setTexture("image/exit_button.png");
}

void Viewer::initGamePage()
{
	if (this->window != nullptr)
		delete this->window;
	sf::VideoMode videoMode(810, 875);
	this->window = new sf::RenderWindow(videoMode, "ChineseChess", sf::Style::Titlebar | sf::Style::Close);
	// Board init
	this->boardTexture.loadFromFile("image/board.jpg");
	this->boardBackground = new sf::Sprite();
	this->boardBackground->setTexture(boardTexture);
	this->boardBackground->setPosition(20, 20);
}

void Viewer::initEndPage()
{
}

void Viewer::initReplayPage()
{
}

int Viewer::updateMainPage(sf::Event ev)
{
	int flowControl = 0;
	switch (ev.type)
	{
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::MouseButtonPressed:
		std::cout << ev.mouseButton.x << " " << ev.mouseButton.y << '\n';
		if (startButton.isClicked(ev))
		{
			flowControl = 1;	// enter game page
			return flowControl;
			// initGamePage();
		}
		else if (exitButton.isClicked(ev))
		{
			window->close();
		}
		else if (loadButton.isClicked(ev))
		{
			std::cout << "load button have been clicked.\n";
		}
		// start, replay and exit button
		break;
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Escape)
			window->close();
		break;
	}
	return flowControl;
}

int Viewer::updateGamePage(sf::Event ev,Board* board)
{
	int flowControl = 1;
	Chess* clickChess = nullptr;
	switch (ev.type)
	{
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::MouseButtonPressed:
		// click Board
		clickChess = board->clickBoard(ev);
		if (clickChess != nullptr)
		{
			std::cout << clickChess->getName() << ' ' << clickChess->getColor() << "\n";
		}
		break;
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Escape)
			window->close();
		if (ev.key.code == sf::Keyboard::Delete)
		{
			Point index = board->getChosenChessIndex();
			if (index.x != -1 && index.y != -1)
			{
				board->removeChess(index);
				board->setChosenChessIndex({ -1,-1 });
			}
		}
		break;
	}
	return flowControl;
}

int Viewer::updateEndPage(sf::Event ev)
{
	int flowControl = 2;
	return flowControl;
}

void Viewer::updateReplayPage()
{
}

void Viewer::showMainPage()
{
	window->clear(sf::Color::White);
	window->draw(*title);
	window->draw(startButton.getBody());
	window->draw(loadButton.getBody());
	window->draw(exitButton.getBody());
	window->display();
}

void Viewer::showGamePage(Board* board)
{
	window->clear(sf::Color::White);
	window->draw(*this->boardBackground);
	board->drawBoard(window);
	window->display();
}

void Viewer::showEndPage()
{
}

void Viewer::showReplayPage()
{
}