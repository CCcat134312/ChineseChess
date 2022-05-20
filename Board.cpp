#include "Board.h"
Board::Board()
{
	nameTable = { {"Chariot", "Horse" , "Elephant","Advisor","King"   ,"Advisor","Elephant","Horse" ,"Chariot"},

				  {"Empty"  , "Empty" , "Empty"   ,"Empty"  ,"Empty"  ,"Empty"  ,"Empty"   ,"Empty" ,"Empty"  },

				  {"Empty"  , "Cannon", "Empty"   ,"Empty"  ,"Empty"  ,"Empty"  ,"Empty"   ,"Cannon","Empty"  },

				  {"Soldier", "Empty" , "Soldier" ,"Empty"  ,"Soldier","Empty"  ,"Soldier" ,"Empty" ,"Soldier"},

				  {"Empty"  , "Empty" , "Empty"   ,"Empty"  ,"Empty"  ,"Empty"  ,"Empty"   ,"Empty" ,"Empty"  },

				  {"Empty"  , "Empty" , "Empty"   ,"Empty"  ,"Empty"  ,"Empty"  ,"Empty"   ,"Empty" ,"Empty"  },

				  {"Soldier", "Empty" , "Soldier" ,"Empty"  ,"Soldier","Empty"  ,"Soldier" ,"Empty" ,"Soldier"},

				  {"Empty"  , "Cannon", "Empty"   ,"Empty"  ,"Empty"  ,"Empty"  ,"Empty"   ,"Cannon","Empty"  },

				  {"Empty"  , "Empty" , "Empty"   ,"Empty"  ,"Empty"  ,"Empty"  ,"Empty"   ,"Empty" ,"Empty"  },

				  {"Chariot", "Horse" , "Elephant","Advisor","King"   ,"Advisor","Elephant","Horse" ,"Chariot"} };

	chessBoard.resize(10);
	for (auto& c : chessBoard)
		c.resize(9);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			std::string color = (i <= 4 && j <= 9) ? "black" : "red";
			sf::Vector2f position = sf::Vector2f(54 + j * 87.5 - 37.5, 50 + i * 85.5 - 37.5);

			if (nameTable[i][j] == "Empty") {
				chessBoard[i][j] = new Empty(position);
			}
			else if (nameTable[i][j] == "King") {
				chessBoard[i][j] = new King(position, color);
			}
			else if (nameTable[i][j] == "Advisor") {
				chessBoard[i][j] = new Advisor(position, color);
			}
			else if (nameTable[i][j] == "Elephant") {
				chessBoard[i][j] = new Elephant(position, color);
			}
			else if (nameTable[i][j] == "Horse") {
				chessBoard[i][j] = new Horse(position, color);
			}
			else if (nameTable[i][j] == "Chariot") {
				chessBoard[i][j] = new Chariot(position, color);
			}
			else if (nameTable[i][j] == "Cannon") {
				chessBoard[i][j] = new Cannon(position, color);
			}
			else if (nameTable[i][j] == "Soldier") {
				chessBoard[i][j] = new Soldier(position, color);
			}
		}
	}

	chosenChessIndex = { -1,-1 };
}

Board::~Board()
{
	for (auto& v : chessBoard)
	{
		for (auto& c : v)
			delete c;
	}
}

Chess* Board::clickBoard(sf::Event& ev, sf::RenderWindow* window)
{
	for (int i = 0; i < chessBoard.size(); i++)
	{
		for (int j = 0; j < chessBoard[i].size(); j++)
		{
			if (chessBoard[i][j]->isClicked(ev))
			{
				int tempX = chosenChessIndex.x, tempY = chosenChessIndex.y;
				if (tempX != -1 && tempY != -1)
				{
					//�M�����ܥi��
					for (int x = 0; x < chessBoard.size(); x++)
					{
						for (int y = 0; y < chessBoard[x].size(); y++)
						{
							chessBoard[x][y]->canMove_flag = false;
						}
					}
					// �p�G�P�_�o�ӴѤl��Move�W�h�A�i�H���ʨ�{�b�諸��m = > swap
					if (chessBoard[tempX][tempY]->canMove(tempX, tempY, i, j, chessBoard) == true) {
					
						// if the color is opposite, eat it and swap
						// otherwise just swap

						//�ʵe
						sf::Texture tmpTexture;
						tmpTexture.create(window->getSize().x, window->getSize().y);
						tmpTexture.update(*window);

						for (int frame = 0; frame < 60; frame++) {

							int step_x =( (chessBoard[i][j]->getBody().getPosition().x) - (chessBoard[tempX][tempY]->getBody().getPosition().x) )/ 60;
							int step_y = ((chessBoard[i][j]->getBody().getPosition().y) - (chessBoard[tempX][tempY]->getBody().getPosition().y) ) / 60;
							sf::Vector2f position = sf::Vector2f((chessBoard[tempX][tempY]->getBody().getPosition().x) + step_x * frame, (chessBoard[tempX][tempY]->getBody().getPosition().y) + step_y * frame);
							
							sf::Sprite sp;
							sp = chessBoard[tempX][tempY]->getBody();
							sp.setPosition(position);

							window->clear();
							sf::Sprite sp_bg;
							sp_bg.setTexture(tmpTexture);
							window->draw(sp_bg);
							window->draw(sp);
							window->display();
							sf::Time delayTime = sf::milliseconds(2);
							sf::sleep(delayTime);
						}
						std::string thitRoundColor;
						thitRoundColor = roundCount % 2 == 0 ? "red" : "black";
						//�p�G�Y��king�N�P�_���
					
						if (chessBoard[i][j]->getName() == "king") {
							winner = thitRoundColor;
							return chessBoard[i][j];
						}
						if (chessBoard[tempX][tempY]->getColor() != chessBoard[i][j]->getColor()) {
							this->removeChess({ i,j });
						}
						Chess* temp = chessBoard[i][j];
						chessBoard[i][j] = chessBoard[tempX][tempY];
						chessBoard[tempX][tempY] = temp;
						swapChess(chessBoard[i][j], chessBoard[tempX][tempY]);
						chosenChessIndex = { -1,-1 };

					
						
						for (int _i = 0; _i < chessBoard.size(); _i++)//���ʧ��ˬd�P��C�ӴѤl�O�_�y���N�x
						{
							for (int _j = 0; _j < chessBoard[_i].size(); _j++)
							{
								if (chessBoard[_i][_j]->getColor() == thitRoundColor) {
									Chess*  myChess = chessBoard[_i][_j];

									for (int x = 0; x < chessBoard.size(); x++)//���ʧ��ˬd�O�_�N�x
									{
										for (int y = 0; y < chessBoard[x].size(); y++)
										{
											if (myChess->canMove(_i, _j, x, y, chessBoard) && chessBoard[x][y]->getName() == "king") {
												checkmate = thitRoundColor;
												
											}
										}
									}
								}
							}
						}
						roundCount++;
						return temp;
					}

					// �L�k���ʡA�NDo Nothing
					else {
						chosenChessIndex = { -1,-1 };
						continue;
					}
				}
				else if (chessBoard[i][j]->getName() != "empty")
				{
					// store
					std::string thitRoundColor;
					thitRoundColor = roundCount % 2 == 0 ? "red" : "black";
					if (thitRoundColor == chessBoard[i][j]->getColor()) {
						chosenChessIndex = { i,j };

						for (int x = 0; x < chessBoard.size(); x++)
						{
							for (int y = 0; y < chessBoard[x].size(); y++)
							{
								chessBoard[x][y]->canMove_flag = chessBoard[i][j]->canMove(i, j, x, y, chessBoard);
							}
						}
					}
					return chessBoard[i][j];
				}
				else // click on empty position
				{
					for (int x = 0; x < chessBoard.size(); x++)
					{
						for (int y = 0; y < chessBoard[x].size(); y++)
						{
							chessBoard[x][y]->canMove_flag =false;
						}
					}
					return chessBoard[i][j];
				}
			}
		}
	}
	return nullptr;
}

void Board::swapChess(Chess* a, Chess* b)
{
	sf::Vector2f tempPos = a->getBody().getPosition();
	a->getBody().setPosition(b->getBody().getPosition());
	b->getBody().setPosition(tempPos);
}

void Board::removeChess(Point target)
{
	if (chessBoard[target.x][target.y]->getName() != "empty") {
		std::string path= "image/" + chessBoard[target.x][target.y]->getColor() + "/" + chessBoard[target.x][target.y]->getName() + ".png";
		removedChess.push_back(path);
		removedCount++;
	}
	delete chessBoard[target.x][target.y];
	sf::Vector2f position = sf::Vector2f(54 + target.y * 87.5 - 37.5, 50 + target.x * 85.5 - 37.5);
	chessBoard[target.x][target.y] = new Empty(position);
	
}

void Board::drawBoard(sf::RenderWindow* window)
{
	for (auto& v : chessBoard)
		for (auto& c : v) {
			sf::Sprite sp = c->getBody();
			
			if(c->canMove_flag){
				if (c->getName() == "empty") {
					sf::CircleShape shape(37.f);
					shape.setPosition(sp.getPosition());
					shape.setFillColor(sf::Color::Color(255,0,0,120));
					
					window->draw(shape);
					continue;

				}
				else {
					sp.setColor(sf::Color::Red);
					window->draw(sp);
					
				}
				
			}
			
			window->draw(sp);
		}
	for (int i = 0; i < removedCount; i++) {
		std::string path = removedChess[i];
		sf::Vector2f position = sf::Vector2f(850+(i/8)*100,75+(i%8)*100);
		sf::Texture texture;
		texture.loadFromFile(path);
		sf::Sprite sp ;
		sp.setTexture(texture);
		sp.setPosition(position);
		window->draw(sp);
	}

	std::string thitRoundColor;
	thitRoundColor = roundCount % 2 == 0 ? "red" : "black";
	sf::Font font;
	font.loadFromFile("font/arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Current Player : "+ thitRoundColor);
	sf::Vector2f position = sf::Vector2f(850 , 10);
	text.setPosition(position);
	text.setCharacterSize(50); // in pixels, not points!
	text.setFillColor(sf::Color::Black);
	window->draw(text);
	
	if (checkmate != "") {
		window->display();
		std::string msg;
		if (checkmate == "red")msg = "����N�x";
		if (checkmate == "black")msg = "�¤�N�x";
		MessageBoxA(NULL, msg.c_str(), "����", MB_OKCANCEL | MB_ICONEXCLAMATION);
		checkmate="";
	}
	if (winner != "") {
		std::string msg;
		
		if (winner == "red")msg = "�������";
		if (winner == "black")msg = "�¤����";
		MessageBoxA(NULL, msg.c_str(), "����", MB_OKCANCEL | MB_ICONEXCLAMATION);
		winner = "";
	}
}

void Board::update()
{
	for (auto& v : chessBoard) {
		for (auto& c : v) {
			c->update();
		}
	}
}
