#include "Game.h"

//TODO Implement Abstract Base class definitions

/*********************************************************************
**********************ABSTRACT BASE CLASS*****************************
*********************************************************************/


Game::Game(const std::string winTitle, const sf::Vector2u winSize)
	:m_windowObj(winTitle,winSize)
	,m_isGameOver(false)
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
	,m_livesRemaining(4)
	,m_level(0)
	,m_specialAmmoRemaining(100)
	,m_timeUntilRespawn(2.0f)
	
{
	//TODO 
	m_isGameOver = false;
	CreateBackground(m_background, m_bgTexture, "Background/longBGStars.png", sf::Vector2f(0.0f, 0.0f));
	CreateBackground(m_background2, m_bgTexture, "Background/longBGStars.png", sf::Vector2f(0.0f, -1200.0f));
}

SpaceShooter::~SpaceShooter()
{
	std::cout << "DERIVED CLASS(SpaceShooter) DESTRUCTOR CALLED" << std::endl;
	delete m_background, m_background2, m_bgTexture;
}


//SpaceShooter Virtual Functions

void SpaceShooter::Update(float dt)
{
	Game::Update();									//Call Base Game Update using scope resolution operator
	if(!m_isGameOver)
	{			
		RespawnPlayer(dt);
		UpdateGameObj();
		LoopBackground();
		//std::cout << m_background.getPosition().y << std::endl;
	}
}

void SpaceShooter::Render()
{
	m_windowObj.Clear();
	//TODO Call derived class Draw functions 
	m_windowObj.DrawThis(m_background);
	m_windowObj.DrawThis(m_background2);
	DrawText();
	DrawObjects();
	m_windowObj.Display();

}

//Add objects into vector of gameobjects
void SpaceShooter::AddObject(GameObjects * object)
{
	object->SetOwner(this);
	m_gameObjects.push_back(object);
}

//TODO Create drawable Text for window to tract score, ammo, lives etc
void SpaceShooter::DrawText()
{
	sf::Texture livesTexture;
	livesTexture.loadFromFile("Ships/TopDownShips/ship2.png");
	for (int i = 0; i < m_livesRemaining; i++)
	{
		sf::Sprite livesSprite(livesTexture);
		livesSprite.setScale(sf::Vector2f(0.05f, 0.05f));
		livesSprite.setPosition(sf::Vector2f(i * 40, 50));
		m_windowObj.DrawThis(&livesSprite);
	}
}

//Create a background 
void SpaceShooter::CreateBackground
(sf::RectangleShape* bg, sf::Texture* bgText, std::string texturePath, sf::Vector2f Position)
{
	bgText->loadFromFile(texturePath);
	bg->setTexture(bgText);
	bg->setSize(sf::Vector2f(800.0f,1200.0f));
	bg->setOrigin(sf::Vector2f(0.0f,0.0f));
	bg->setPosition(sf::Vector2f(Position));
}

//A forloop function that draws all objects in gameobject vector
void SpaceShooter::DrawObjects()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* current = m_gameObjects[i];
		current->Draw(&m_windowObj);
	}
}

//A forloop function that calls each objects update function
void SpaceShooter::UpdateGameObj()
{
	//Loop through m_gameObjects vector and call each Update function
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* current = m_gameObjects[i];
		current->Update(&m_windowObj);
	}

	//Loop through m_gameObjects vector can check if each GameObjects destroy state is true, 
	//If its the player , delete it then reset the m_timeUntilRespawn
	for (int i = m_gameObjects.size() - 1; i >= 0; i--)
	{
		GameObjects* current = m_gameObjects[i];
		SS_Player* player = dynamic_cast<SS_Player*>(current);
		if (player->IsDestroyed())
		{
			
			delete player;
			m_gameObjects.erase(m_gameObjects.begin() + i);
			m_timeUntilRespawn = 2.0f;

		}
		else if(current->IsDestroyed())
		{
			
			delete current;
			m_gameObjects.erase(m_gameObjects.begin() + i);
		}
	}
}

//Set m_isGameOver state to true then call Destroy() on all GameObjects
void SpaceShooter::GameOver()
{
	m_isGameOver = true;
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* current = m_gameObjects[i];
		current->Destroy();
	}
}

//SPACESHOOTER MAIN FUNCTIONS

//Spawn player after every death, checking for m_timeUntilRespawn and m_livesRemaining
void SpaceShooter::RespawnPlayer(float dt)
{
	
	if (m_timeUntilRespawn > 0)
	{
		m_timeUntilRespawn -= dt;
		if (m_timeUntilRespawn <= 0)
		{
			if (m_livesRemaining > 0)
			{
				m_livesRemaining--;
				SS_Player* player = new SS_Player("Ships/TopDownShips/ship2.png", sf::Vector2f(400.0f, 400.0f));
				AddObject(player);
			}
			else
			{
				GameOver();
			}
		}
	}

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

//A Function to loop the background by dynamically deleting and recreating a new background
void SpaceShooter::LoopBackground()
{
	//TODO create a linear interpolation function for a smoother background movement
	m_background->setPosition(m_background->getPosition().x, m_background->getPosition().y + 0.05f);
	m_background2->setPosition(m_background2->getPosition().x, m_background2->getPosition().y + 0.05f);
	if (m_background->getPosition().y > 800)
	{
		delete m_background;
		m_background = new sf::RectangleShape;
		CreateBackground(m_background, m_bgTexture, "Background/longBGStars.png", sf::Vector2f(0.0f, -1200.0f));
	}
	if (m_background2->getPosition().y > 800)
	{
		delete m_background2;
		m_background2 = new sf::RectangleShape;
		CreateBackground(m_background2, m_bgTexture, "Background/longBGStars.png", sf::Vector2f(0.0f, -1200.0f));
	}

	

}