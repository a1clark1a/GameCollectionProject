#include "SpaceShooter.h"

/**************************************************************************************
*********************************SPACESHOOTER CLASS************************************
***************************************************************************************/

//SpaceShooter Constructor - create SpaceShooterGame
SpaceShooter::SpaceShooter()
	:Game("SpaceShooter", sf::Vector2f(1600.0f,900.0f))
{
	Setup();
}

SpaceShooter::~SpaceShooter()
{
	std::cout << "DERIVED CLASS(SpaceShooter) DESTRUCTOR CALLED" << std::endl;

}


//SpaceShooter Virtual Functions

void SpaceShooter::Update(float dt)
{
	Game::Update();									//Call Base Game Update using scope resolution operator
	LoopBackground();								//Call outside of if to make sure the background loops even if game is over
	if (!m_isGameOver)
	{
		UpdateGameObj();
	}
}

void SpaceShooter::Render()
{
	m_windowObj.Clear();
	//TODO Call derived class Draw functions 
	m_windowObj.DrawThis(&m_background);
	m_windowObj.DrawThis(&m_background2);
	DrawObjects();
	DrawBorders();
	DrawHealthBarSprite();
	DrawText();
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

	sf::Sprite l_livesSprite(*m_livesTex);
	l_livesSprite.setOrigin(l_livesSprite.getTextureRect().width * 0.5f, l_livesSprite.getTextureRect().height * 0.5f);
	l_livesSprite.setScale(0.1f, 0.1f);
	l_livesSprite.setPosition(m_livesBorderSprite->getPosition().x, m_livesBorderSprite->getPosition().y);
	m_windowObj.DrawThis(&l_livesSprite);

	sf::Text l_livesRemText;
	l_livesRemText.setFont(m_mainFont);
	l_livesRemText.setString(std::to_string(m_livesRemaining));
	l_livesRemText.setCharacterSize(30);
	l_livesRemText.setPosition(m_livesBorderSprite->getPosition().x - 35.0f,m_livesBorderSprite->getPosition().y - 45.0f);
	m_windowObj.DrawThis(&l_livesRemText);

	sf::Text l_healthTex;
	l_healthTex.setFont(m_mainFont);
	l_healthTex.setString("HEALTH");
	l_healthTex.setCharacterSize(15);
	l_healthTex.setFillColor(sf::Color::Red);
	l_healthTex.setPosition(m_healthBarSprite->getPosition().x + 125.0f, m_healthBarSprite->getPosition().y - 30.0f);
	m_windowObj.DrawThis(&l_healthTex);

	sf::Text l_scoreText;
	l_scoreText.setFont(m_mainFont);
	l_scoreText.setString(std::to_string(m_score));
	l_scoreText.setCharacterSize(30);
	l_scoreText.setPosition(m_windowObj.GetWindowSize()->x - 150.0f,m_windowObj.GetWindowSize()->y - 100.0f);
	m_windowObj.DrawThis(&l_scoreText);

	sf::Text l_weap1Text;
	l_weap1Text.setFont(m_mainFont);
	l_weap1Text.setString("BLASTER");
	l_weap1Text.setCharacterSize(11);
	l_weap1Text.setRotation(45);
	l_weap1Text.setPosition(m_equippedBorderSprite1->getPosition().x -13.0f,m_equippedBorderSprite1->getPosition().y-25.0f);
	m_windowObj.DrawThis(&l_weap1Text);

	sf::Text l_weap2Text;
	l_weap2Text.setFont(m_mainFont);
	l_weap2Text.setString("LASER");
	l_weap2Text.setCharacterSize(14);
	l_weap2Text.setRotation(45);
	l_weap2Text.setPosition(m_equippedBorderSprite2->getPosition().x - 10.0f, m_equippedBorderSprite2->getPosition().y - 25.0f);
	m_windowObj.DrawThis(&l_weap2Text);

	sf::Text l_weap3Text;
	l_weap3Text.setFont(m_mainFont);
	l_weap3Text.setString("POWER");
	l_weap3Text.setCharacterSize(13);
	l_weap3Text.setRotation(45);
	l_weap3Text.setPosition(m_equippedBorderSprite3->getPosition().x - 11.0f, m_equippedBorderSprite3->getPosition().y - 25.0f);
	m_windowObj.DrawThis(&l_weap3Text);

	sf::Text l_quadAmmoText;
	l_quadAmmoText.setFont(m_mainFont);
	l_quadAmmoText.setString(std::to_string(m_quadAmmoRemaining));
	l_quadAmmoText.setCharacterSize(12);
	l_quadAmmoText.setOrigin(l_quadAmmoText.getGlobalBounds().width * 0.5f, l_quadAmmoText.getGlobalBounds().height * 0.5f);
	l_quadAmmoText.setPosition(m_equippedBorderSprite2->getPosition().x, m_equippedBorderSprite2->getPosition().y - 38.5f);
	m_windowObj.DrawThis(&l_quadAmmoText);

	sf::Text l_powerAmmoText;
	l_powerAmmoText.setFont(m_mainFont);
	l_powerAmmoText.setString(std::to_string(m_PowerBombAmmoRemaining));
	l_powerAmmoText.setCharacterSize(12);
	l_powerAmmoText.setOrigin(l_powerAmmoText.getGlobalBounds().width * 0.5f, l_powerAmmoText.getGlobalBounds().height * 0.5f);
	l_powerAmmoText.setPosition(m_equippedBorderSprite3->getPosition().x, m_equippedBorderSprite3->getPosition().y - 38.5f);
	m_windowObj.DrawThis(&l_powerAmmoText);

}

//Create a background 
void SpaceShooter::CreateBackground
(sf::RectangleShape* bg, sf::Texture* bgText, const std::string texturePath, const sf::Vector2f Position)
{
	bgText->loadFromFile(texturePath);
	bg->setTexture(bgText);
	bg->setSize(sf::Vector2f(m_windowObj.GetWindowSize()->x, m_windowObj.GetWindowSize()->y));
	bg->setOrigin(sf::Vector2f(0.0f, 0.0f));
	bg->setPosition(sf::Vector2f(Position));
}

//A forloop function that draws all objects in gameobject vector
void SpaceShooter::DrawObjects()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* l_current = m_gameObjects[i];
		l_current->Draw(&m_windowObj);
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		SS_Player* l_player = dynamic_cast<SS_Player*>(m_gameObjects[i]);
		if (l_player)
		{
			m_weaponEquiped = l_player->GetWeapEquipped();
			m_playerCurrentHealth = l_player->GetPlayerHealth();
			m_quadAmmoRemaining = l_player->GetQuadAmmo();
			m_PowerBombAmmoRemaining = l_player->GetPowerAmmo();
		}
		
	}
}

//A forloop function that calls each objects update function
void SpaceShooter::UpdateGameObj()
{
	//If player dies, timer goes up then decreases to allow respawn of player
	if (m_timeUntilRespawn > 0)
	{
		m_timeUntilRespawn -= m_windowObj.GetDeltaTime()->asSeconds();
		if (m_timeUntilRespawn <= 0)
		{
			RespawnPlayer();
		}
	}

	//Loop through m_gameObjects vector and call each Update function
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* l_current = m_gameObjects[i];
		l_current->Update(&m_windowObj);
	}

	//Loop through m_gameObjects vector to check if each GameObjects destroy state is true, 
	for (int i = int(m_gameObjects.size()) - 1; i >= 0; i--)
	{
		GameObjects* l_current = m_gameObjects[i];
		if (l_current->IsDestroyed())
		{

			delete l_current;
			m_gameObjects.erase(m_gameObjects.begin() + i);
		}

	}

	//Loop through m_gameObjects vector to check if any GameObjects object is colliding with another
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* l_current = m_gameObjects[i];
		ChaserAI* l_fastAI = dynamic_cast<ChaserAI*>(l_current);
		for (int j = 0; j < m_gameObjects.size(); j++)
		{
			GameObjects* l_other = m_gameObjects[j];
			SS_Player* l_player = dynamic_cast<SS_Player*>(l_other);
			
			if (l_current->IsColliding(l_other))
			{
				l_current->CollidedWith(l_other);
			}
			if (l_fastAI && l_player)
			{
				l_fastAI->SetTarget(l_player);
			}
		}
	}

	ShowWeaponEquipped();
}

//Set m_isGameOver state to true then call Destroy() on all GameObjects
void SpaceShooter::GameOver()
{
	m_isGameOver = true;
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* l_current = m_gameObjects[i];
		l_current->Destroy();
	}
}

//SPACESHOOTER MAIN FUNCTIONS

//Spawn player after every death, checking for m_livesRemaining
void SpaceShooter::RespawnPlayer()
{

	if (m_livesRemaining > 0)
	{
		m_livesRemaining--;
		SS_Player* player = new SS_Player();
		AddObject(player);
	}
	else
	{
		GameOver();
	}

}

void SpaceShooter::SpawnAI()
{
	//TODO Function to create AI 
}

//Function to spawn destructible objects( Can Call Spawn Item)
void SpaceShooter::SpawnDestructibles()
{
	//Divides the spawncount by 2 and spawns a destructible by quotient
	for (unsigned int i = 0; i < (m_spawnCount / 2); i++)
	{
		Asteroid* asteroid;
		int l_randNum = rand() % 2;

		//Before spawn a rand number chooses which destructible to spawn or to cal SpawnItem() function
		if (l_randNum == 0)
		{
			asteroid = new MediumAsteroid(sf::Vector2f(static_cast<float>(rand() % 1000), -200.0f));
			AddObject(asteroid);
		}
		else if (l_randNum == 1)
		{
			SpawnItem();
		}
		else
		{
			asteroid = new LargeAsteroid(sf::Vector2f(static_cast<float>(rand() % 1000), -200.0f));
			AddObject(asteroid);
		}
	}
}

void SpaceShooter::SpawnItem()
{
	//TODO Function to spawn items to be picked up
}

void SpaceShooter::SetSpawnCount()
{
	//TODO Function to call to set how many AI to spawn
}

//A Function to loop the background 
void SpaceShooter::LoopBackground()
{
	m_background.setPosition(m_background.getPosition().x, m_background.getPosition().y + 50.0f * m_windowObj.GetDeltaTime()->asSeconds());
	m_background2.setPosition(m_background2.getPosition().x, m_background2.getPosition().y + 50.0f * m_windowObj.GetDeltaTime()->asSeconds());
	if (m_background.getPosition().y > m_windowObj.GetWindowSize()->y)
	{
		m_background.setPosition(sf::Vector2f(0.0f, -m_windowObj.GetWindowSize()->y));
	}
	if (m_background2.getPosition().y > m_windowObj.GetWindowSize()->y)
	{
		m_background2.setPosition(sf::Vector2f(0.0f, -m_windowObj.GetWindowSize()->y));
	}
}

void SpaceShooter::DrawHealthBarSprite()
{
	m_healthBarSprite->setTexture(*m_healthBarTex);
	m_healthBarSprite->setOrigin(0.0f, m_healthBarSprite->getTextureRect().height * 0.5f);
	m_healthBarSprite->setPosition(m_livesBorderSprite->getPosition().x + 50.0f, m_livesBorderSprite->getPosition().y);
	m_healthBarSprite->setScale(0.2f, 0.2f);
	m_windowObj.DrawThis(m_healthBarSprite);

	m_playerHealthBar->setOrigin(0.0f, 0.0f);
	m_playerHealthBar->setSize(sf::Vector2f(m_playerCurrentHealth / m_maxPlayerHealth * 100.0f, 24.0f));
	m_playerHealthBar->setScale(2.35f, 0.60f);
	m_playerHealthBar->setPosition(m_livesBorderSprite->getPosition().x + 84, m_livesBorderSprite->getPosition().y - 3.0f);
	m_playerHealthBar->setFillColor(sf::Color::Green);
	m_windowObj.DrawThis(m_playerHealthBar);

	
}
void SpaceShooter::DrawBorders()
{
	m_livesBorderSprite->setTexture(*m_livesBorderTex);
	m_livesBorderSprite->setOrigin(m_livesBorderSprite->getTextureRect().width * 0.5f, m_livesBorderSprite->getTextureRect().height * 0.5f);
	m_livesBorderSprite->setScale(0.5f, 0.5f);
	m_livesBorderSprite->setPosition(90.0f, 70.0f);
	m_windowObj.DrawThis(m_livesBorderSprite);

	m_equippedBorderSprite1->setOrigin(m_equippedBorderSprite1->getTextureRect().width * 0.5f, m_equippedBorderSprite1->getTextureRect().height * 0.5f);
	m_equippedBorderSprite1->setScale(0.25f, 0.25f);
	m_equippedBorderSprite1->setPosition(50.0f,200);
	m_windowObj.DrawThis(m_equippedBorderSprite1);

	
	m_equippedBorderSprite2->setOrigin(m_equippedBorderSprite2->getTextureRect().width * 0.5f, m_equippedBorderSprite2->getTextureRect().height * 0.5f);
	m_equippedBorderSprite2->setScale(0.25f, 0.25f);
	m_equippedBorderSprite2->setPosition(50.0f, 300);
	m_windowObj.DrawThis(m_equippedBorderSprite2);

	
	m_equippedBorderSprite3->setOrigin(m_equippedBorderSprite3->getTextureRect().width * 0.5f, m_equippedBorderSprite3->getTextureRect().height * 0.5f);
	m_equippedBorderSprite3->setScale(0.25f, 0.25f);
	m_equippedBorderSprite3->setPosition(50.0f, 400.0f);
	m_windowObj.DrawThis(m_equippedBorderSprite3);

}

void SpaceShooter::ShowWeaponEquipped()
{
	switch (m_weaponEquiped)
	{
	case SS_Player::WEAPONTYPE::Fast:
		m_equippedBorderSprite1->setTexture(*m_equippedONBorderTex);
		m_equippedBorderSprite2->setTexture(*m_equippedOFFBorderTex);
		m_equippedBorderSprite3->setTexture(*m_equippedOFFBorderTex);
		break;
	case SS_Player::WEAPONTYPE::QuadBlaster:
		m_equippedBorderSprite1->setTexture(*m_equippedOFFBorderTex);
		m_equippedBorderSprite2->setTexture(*m_equippedONBorderTex);
		m_equippedBorderSprite3->setTexture(*m_equippedOFFBorderTex);
		break;
	case SS_Player::WEAPONTYPE::Power:
		m_equippedBorderSprite1->setTexture(*m_equippedOFFBorderTex);
		m_equippedBorderSprite2->setTexture(*m_equippedOFFBorderTex);
		m_equippedBorderSprite3->setTexture(*m_equippedONBorderTex);
		break;
	default: 
		m_weaponEquiped = SS_Player::WEAPONTYPE::Fast;
		break;
	}
}

void SpaceShooter::Setup()
{
	m_level = 0;
	m_livesRemaining = 4;
	m_maxPlayerHealth = 200.0f;
	ResetSpawnTimer();
	CreateBackground(&m_background, &m_bgTexture, "Sprites/Background/longBGStars.png", sf::Vector2f(0.0f, 0.0f));
	CreateBackground(&m_background2, &m_bgTexture, "Sprites/Background/longBGStars.png", sf::Vector2f(0.0f, -m_windowObj.GetWindowSize()->y));
	LoadTexture();
}

void SpaceShooter::LoadTexture()
{
	m_healthBarTex->loadFromFile("Sprites/GUI/HealthBar02.png");
	m_livesTex->loadFromFile("Sprites/TopDownShips/ship3.png");
	m_livesBorderTex->loadFromFile("Sprites/GUI/Border04.png");
	m_equippedONBorderTex->loadFromFile("Sprites/GUI/Box03.png");
	m_equippedOFFBorderTex->loadFromFile("Sprites/GUI/Box04.png");
	
}