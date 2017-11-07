#pragma once
#include "Window.h"

class Game; //Forward Class Declaration

class GameObjects
{
public:
	GameObjects( std::string texturePath, const sf::Vector2u& pos);  //Constructor to take file path of sprite texture, and an initial vector location on screen
	virtual void Draw();
	

protected:
	Game * m_owner;

private:

};