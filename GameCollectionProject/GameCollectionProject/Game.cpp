#include "Game.h"

/*********************************************************************
**********************ABSTRACT BASE CLASS*****************************
*********************************************************************/


Game::Game(const std::string winTitle, const sf::Vector2f winSize)
	:m_windowObj(winTitle,winSize)
{
	Setup();
}

Game::~Game()
{
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

void Game::Setup()
{
	srand(static_cast<unsigned int>(time(0)));
	m_isGameOver = false;
	LoadTexture();
}

void Game::LoadTexture()
{
	m_mainFont.loadFromFile("Sprites/Fonts/Transformers Movie.ttf");
}
