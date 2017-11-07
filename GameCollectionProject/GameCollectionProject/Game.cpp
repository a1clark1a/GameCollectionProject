#include "Game.h"

//TODO Implement Abstract Base class definitions

/*********************************************************************
**********************ABSTRACT BASE CLASS*****************************
*********************************************************************/

Game::Game(const std::string winTitle, const sf::Vector2u winSize)
	:m_window(winTitle,winSize)
{
	//TODO Initialize m_mainFont
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


/**************************************************************************************
************************************DERIVED CLASSES************************************
*************************************************************************************** /

//TODO Implement derived game from the base class Game

/*************************SPACESHOOTER***************************/

SpaceShooter::SpaceShooter(const sf::Vector2u winSize)
	:Game("SpaceShooter",winSize)
{
	
}

SpaceShooter::~SpaceShooter()
{
	std::cout << "DERIVED CLASS(SpaceShooter) DESTRUCTOR CALLED" << std::endl;
}


//SpaceShooter Virtual Functions

void SpaceShooter::Update()
{
	m_window.Update();
}

void SpaceShooter::Render()
{
	m_window.Clear();
	//TODO Call derived class Draw functions 
	m_window.Display();
}

void SpaceShooter::AddObject(GameObjects * object)
{
	//TODO Add objects into vector of gameobjects
}

void SpaceShooter::DrawText()
{
	//TODO Create drawable Text for window to tract score, ammo, lives etc
}

void SpaceShooter::DrawBackground()
{
	//TODO Create an infinitely looping background 
}

void SpaceShooter::DrawObjects()
{
	//TODO Create a forloop that draws all objects in gameobject vector
}

//SPACESHOOTER MAIN FUNCTIONS

void SpaceShooter::RespawnPlayer()
{

}

void SpaceShooter::SpawnAI()
{

}

void SpaceShooter::SpawnDestructibles()
{

}

void SpaceShooter::SpawnItem()
{

}

void SpaceShooter::SetSpawnCount()
{

}