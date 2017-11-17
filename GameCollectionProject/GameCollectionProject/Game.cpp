#include "Game.h"

//TODO Implement Abstract Base class definitions

/*********************************************************************
**********************ABSTRACT BASE CLASS*****************************
*********************************************************************/


Game::Game(const std::string winTitle, const sf::Vector2u winSize)
	:m_windowObj(winTitle,winSize)
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
	:Game("SpaceShooter", winSize)
{
	
}

SpaceShooter::~SpaceShooter()
{
	std::cout << "DERIVED CLASS(SpaceShooter) DESTRUCTOR CALLED" << std::endl;
}


//SpaceShooter Virtual Functions

void SpaceShooter::Update()
{
	Game::Update();
	bool test = true;
	if (test = true)
	{
		SS_Player* player = new SS_Player("Ships/Ship/Ship (15).png", sf::Vector2f(400, 400));
		AddObject(player);
	}
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* current = m_gameObjects[i];
		current->Update(&m_windowObj);
	}
}

void SpaceShooter::Render()
{
	m_windowObj.Clear();
	//TODO Call derived class Draw functions 
	DrawObjects();
	m_windowObj.Display();

}

void SpaceShooter::AddObject(GameObjects * object)
{
	//TODO Add objects into vector of gameobjects
	object->SetOwner(this);
	m_gameObjects.push_back(object);
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
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* current = m_gameObjects[i];
		current->Draw(&m_windowObj);
	}
}

//SPACESHOOTER MAIN FUNCTIONS

void SpaceShooter::RespawnPlayer()
{
	//TODO Function to spawn player after every death

}

void SpaceShooter::SpawnAI()
{
	//TODO Function to create AI 
}

void SpaceShooter::SpawnDestructibles()
{
	//TODO Function to spawn destructible objects( Can Call Spawn Item)
}

void SpaceShooter::SpawnItem()
{
	//TODO Function to spawn items to be picked up
}

void SpaceShooter::SetSpawnCount()
{
	//TODO Function to call to set how many AI to spawn
}