#include "Game.h"

//TODO Implement Abstract Base class definitions

/*********************************************************************
**********************ABSTRACT BASE CLASS*****************************
*********************************************************************/


Game::Game(const std::string winTitle, const sf::Vector2f winSize)
	:m_windowObj(winTitle,winSize)
	,m_isGameOver(false)
{
	//TODO Initialize m_mainFont
	m_mainFont.loadFromFile("Sprites/Fonts/Transformers Movie.ttf");
	srand(static_cast<unsigned int>(time(0)));
}

Game::~Game()
{
	std::cout << "BASE CLASS DESTRUCTOR CALLED" << std::endl;
}

void Game::SetScore(int scoreVal)
{
	m_score += scoreVal;
	if (m_score > m_highScore)
	{
		m_highScore = m_score;
	}
	//TODO allow to save Highscore unto text file
	
}


