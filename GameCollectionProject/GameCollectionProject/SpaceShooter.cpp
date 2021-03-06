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
}

							/***************************
							******Virtual Functions*****
							***************************/

//Spaceshooter Update function
void SpaceShooter::Update(float dt)
{
	Game::Update(dt);									//Call Base Game Update using scope resolution operator
	if (!m_isGameOver)
	{
		SpawnSystem();
		UpdateGameObj();
	}
}

void SpaceShooter::Render()
{
	m_windowObj.Clear();						//Clear window first
	//DRAW THINGS BELOW HERE
	LoopBackground();							
	ShowWeaponEquipped();
	DrawObjects();
	DrawBorders();
	DrawHealthBarSprite();
	DrawText();
	//DRAW ABOVE HERE
	m_windowObj.Display();						//Display everything

}

//Add objects into vector of gameobjects
void SpaceShooter::AddObject(GameObjects * object)
{
	object->SetOwner(this);
	m_gameObjects.push_back(object);
}

//Drawable Text for window to tract score, ammo, lives etc
void SpaceShooter::DrawText()
{
	sf::Sprite l_livesSprite(m_livesTex);
	l_livesSprite.setOrigin(l_livesSprite.getTextureRect().width * 0.5f, l_livesSprite.getTextureRect().height * 0.5f);
	l_livesSprite.setScale(0.1f, 0.1f);
	l_livesSprite.setPosition(m_livesBorderSprite.getPosition().x, m_livesBorderSprite.getPosition().y);
	m_windowObj.DrawThis(&l_livesSprite);

	sf::Text l_livesRemText;
	l_livesRemText.setFont(m_mainFont);
	l_livesRemText.setString(std::to_string(m_livesRemaining));
	l_livesRemText.setCharacterSize(30);
	l_livesRemText.setPosition(m_livesBorderSprite.getPosition().x - 35.0f,m_livesBorderSprite.getPosition().y - 45.0f);
	m_windowObj.DrawThis(&l_livesRemText);

	sf::Text l_healthTex;
	l_healthTex.setFont(m_mainFont);
	l_healthTex.setString("HEALTH");
	l_healthTex.setCharacterSize(15);
	l_healthTex.setFillColor(sf::Color::Red);
	l_healthTex.setPosition(m_healthBarSprite.getPosition().x + 125.0f, m_healthBarSprite.getPosition().y - 30.0f);
	m_windowObj.DrawThis(&l_healthTex);

	sf::Text l_scoreText;
	l_scoreText.setFont(m_mainFont);
	l_scoreText.setString("Score: " + std::to_string(m_score));
	l_scoreText.setCharacterSize(30);
	l_scoreText.setOrigin(l_scoreText.getGlobalBounds().width * 0.5f, l_scoreText.getGlobalBounds().height * 0.5f);
	l_scoreText.setPosition(m_windowObj.GetWindowSize()->x - 150.0f,m_windowObj.GetWindowSize()->y - 100.0f);
	m_windowObj.DrawThis(&l_scoreText);

	sf::Text l_highScoreText;
	l_highScoreText.setFont(m_mainFont);
	l_highScoreText.setString("Highscore: " + std::to_string(m_highScore));
	l_highScoreText.setCharacterSize(30);
	l_highScoreText.setOrigin(l_highScoreText.getGlobalBounds().width * 0.5f, l_highScoreText.getGlobalBounds().height * 0.5f);
	l_highScoreText.setPosition(m_windowObj.GetWindowSize()->x - 150.0f, m_windowObj.GetWindowSize()->y - 150.0f);
	m_windowObj.DrawThis(&l_highScoreText);

	sf::Text l_levelText;
	l_levelText.setFont(m_mainFont);
	l_levelText.setString("Level: "+ std::to_string(m_level));
	l_levelText.setCharacterSize(30);
	l_levelText.setOrigin(l_levelText.getGlobalBounds().width * 0.5f, l_levelText.getGlobalBounds().height * 0.5f);
	l_levelText.setPosition(m_windowObj.GetWindowSize()->x - 150.0f, 50.0f);
	m_windowObj.DrawThis(&l_levelText);

	sf::Text l_weap1Text;
	l_weap1Text.setFont(m_mainFont);
	l_weap1Text.setString("BLASTER");
	l_weap1Text.setCharacterSize(11);
	l_weap1Text.setRotation(45);
	l_weap1Text.setPosition(m_equippedBorderSprite1.getPosition().x -13.0f,m_equippedBorderSprite1.getPosition().y-25.0f);
	m_windowObj.DrawThis(&l_weap1Text);

	sf::Text l_weap2Text;
	l_weap2Text.setFont(m_mainFont);
	l_weap2Text.setString("LASER");
	l_weap2Text.setCharacterSize(14);
	l_weap2Text.setRotation(45);
	l_weap2Text.setPosition(m_equippedBorderSprite2.getPosition().x - 10.0f, m_equippedBorderSprite2.getPosition().y - 25.0f);
	m_windowObj.DrawThis(&l_weap2Text);

	sf::Text l_weap3Text;
	l_weap3Text.setFont(m_mainFont);
	l_weap3Text.setString("POWER");
	l_weap3Text.setCharacterSize(13);
	l_weap3Text.setRotation(45);
	l_weap3Text.setPosition(m_equippedBorderSprite3.getPosition().x - 11.0f, m_equippedBorderSprite3.getPosition().y - 25.0f);
	m_windowObj.DrawThis(&l_weap3Text);

	sf::Text l_quadAmmoText;
	l_quadAmmoText.setFont(m_mainFont);
	l_quadAmmoText.setString(std::to_string(m_quadAmmoRemaining));
	l_quadAmmoText.setCharacterSize(12);
	l_quadAmmoText.setOrigin(l_quadAmmoText.getGlobalBounds().width * 0.5f, l_quadAmmoText.getGlobalBounds().height * 0.5f);
	l_quadAmmoText.setPosition(m_equippedBorderSprite2.getPosition().x, m_equippedBorderSprite2.getPosition().y - 38.5f);
	m_windowObj.DrawThis(&l_quadAmmoText);

	sf::Text l_powerAmmoText;
	l_powerAmmoText.setFont(m_mainFont);
	l_powerAmmoText.setString(std::to_string(m_PowerBombAmmoRemaining));
	l_powerAmmoText.setCharacterSize(12);
	l_powerAmmoText.setOrigin(l_powerAmmoText.getGlobalBounds().width * 0.5f, l_powerAmmoText.getGlobalBounds().height * 0.5f);
	l_powerAmmoText.setPosition(m_equippedBorderSprite3.getPosition().x, m_equippedBorderSprite3.getPosition().y - 38.5f);
	m_windowObj.DrawThis(&l_powerAmmoText);

	if (m_isGameOver)
	{
		sf::Text l_gameOverText;
		l_gameOverText.setFont(m_mainFont);
		l_gameOverText.setString("GAME OVER!");
		l_gameOverText.setCharacterSize(110);
		l_gameOverText.setOrigin(l_gameOverText.getGlobalBounds().width * 0.5f, l_gameOverText.getGlobalBounds().height * 0.5f);
		l_gameOverText.setPosition(m_windowObj.GetWindowSize()->x * 0.5f, m_windowObj.GetWindowSize()->y * 0.5f);
		m_windowObj.DrawThis(&l_gameOverText);
	}
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
		//Check for an asteroid object to make it move forward
		Asteroid* l_asteroid = dynamic_cast<Asteroid*>(l_current);
		if (l_asteroid)
		{
			l_asteroid->SetLinearAccel(-10.0f);
		}
		l_current->Update(&m_windowObj);
	}
	//Loop through m_gameObjects vector to check if each GameObjects destroy state is true, delete it 
	for (int i = int(m_gameObjects.size()) - 1; i >= 0; i--)
	{
		GameObjects* l_current = m_gameObjects[i];
		if (l_current->IsDestroyed())
		{
			SS_Player* l_player = dynamic_cast<SS_Player*>(l_current);
			if (l_player)
			{
				GetSound()->PlaySound("Audio/Explosion.wav");
				ResetPlayerSpawnTimer();
			}
			delete l_current;
			m_gameObjects.erase(m_gameObjects.begin() + i);
		}
	}
	
	//Loop through m_gameObjects vector to check if any GameObjects object is colliding with another
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* l_current = m_gameObjects[i];
		for (int j = 0; j < m_gameObjects.size(); j++)
		{
			GameObjects* l_other = m_gameObjects[j];
			if (l_current->IsColliding(l_other))
			{
				l_current->CollidedWith(l_other);
			}
		}
	}

	//Loop through m_gameObjects to find the player to for chaserAI to target
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		ChaserAI* l_chaserAI = dynamic_cast<ChaserAI*>(m_gameObjects[i]);
		for (int j = 0; j < m_gameObjects.size(); j++)
		{
			SS_Player* l_player = dynamic_cast<SS_Player*>(m_gameObjects[j]);
			if (l_chaserAI && l_player)
			{
				l_chaserAI->SetTarget(l_player);
			}
		}
	}
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

void SpaceShooter::SetScoreOnFile(const int & scoreVal)
{
	m_highScore = m_score;
	std::ofstream myfile("HighScores/H_SpaceShooter.txt");
	if (myfile.is_open())
	{
		myfile << scoreVal << std::endl;
	}
	else std::cout << "Unable to open file" << std::endl;
}

unsigned int SpaceShooter::ExtractHighsScoreFromFile()
{
	std::string l_line;
	unsigned int l_score;
	std::ifstream myfile("HighScores/H_SpaceShooter.txt");
	if (myfile.is_open())
	{
		std::getline(myfile, l_line);
		l_score = std::stoi(l_line);
		myfile.close();
	}
	return l_score;
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

//Function to create AI 
void SpaceShooter::SpawnAI()
{
	AI *l_ai;
	switch (rand() % 3)
	{
	case 0:
		l_ai = new NormalAI(sf::Vector2f(static_cast<float>(rand() % 900 + 200), -10.0f + 1.0f));
		AddObject(l_ai);
		break;
	case 1:
		l_ai = new AggroAI(sf::Vector2f(static_cast<float>(rand() % 900 + 200), -10.0f + 1.0f));
		AddObject(l_ai);
		break;
	case 2:
		l_ai = new ChaserAI(sf::Vector2f(static_cast<float>(rand() % 900 + 200), -10.0f + 1.0f));
		AddObject(l_ai);
		break;
	}
}

//Function to spawn destructible objects( Can Call Spawn Item)
void SpaceShooter::SpawnDestructibles()
{
	Asteroid* l_asteroid;
	switch(rand() % 2)
	{
	case 0:
		l_asteroid = new MediumAsteroid(sf::Vector2f(static_cast<float>(rand() % 900 + 100), -200.0f));
		AddObject(l_asteroid);
		break;
	case 1:
		l_asteroid = new LargeAsteroid(sf::Vector2f(static_cast<float>(rand() % 900 + 100), -200.0f));
		AddObject(l_asteroid);
		break;
	}
}

void SpaceShooter::SpawnItem()
{
	Item* l_item;
	switch (rand() % 5)
	{
	case 0:
		 l_item = new GoldCoin(sf::Vector2f(static_cast<float>(rand() % 800 + 100), -10.0f + -1.0f));
		AddObject(l_item);
		break;
	case 1:
		l_item= new SilverCoin(sf::Vector2f(static_cast<float>(rand() % 800 + 100), -10.0f + -1.0f));
		AddObject(l_item);
		break;
	case 2:
		l_item = new QuadAmmo(sf::Vector2f(static_cast<float>(rand() % 800 + 100), -10.0f + -1.0f));
		AddObject(l_item);
		break;
	case 3:
		l_item = new PowerAmmo(sf::Vector2f(static_cast<float>(rand() % 800 + 100), -100.0f + -1.0f));
		AddObject(l_item);
		break;
	case 4:
		l_item = new HealthPack(sf::Vector2f(static_cast<float>(rand() % 800 + 100), -10.0f + -1.0f));
		AddObject(l_item);
		break;
	}
}

//Gameplay behaviour to handle how objects spawn in game
void SpaceShooter::SpawnSystem()
{
	m_objectSpawnCoolDown -= m_windowObj.GetDeltaTime()->asSeconds();
	for (unsigned int i = m_spawnCountPerLevel; i > 0; i--)
	{
		switch (rand() % 6)
		{
		case 0:
			if (m_objectSpawnCoolDown <= 0 && m_spawnCountPerLevel > 0)
			{
				SpawnAI();
				ResetObjectSpawnTimer();
				m_spawnCountPerLevel--;
			}
			break;
		case 1:
			if (m_objectSpawnCoolDown <= 0 && m_spawnCountPerLevel > 0)
			{
				SpawnDestructibles();
				ResetObjectSpawnTimer();
				m_spawnCountPerLevel--;
			}
			break;
		case 2:
			if (m_objectSpawnCoolDown <= 0 && m_spawnCountPerLevel > 0)
			{
				ResetObjectSpawnTimer();
				SpawnItem();
				m_spawnCountPerLevel--;
			}
			break;
		default:
			if (m_objectSpawnCoolDown <= 0 && m_spawnCountPerLevel > 0)
			{
				SpawnAI();
				ResetObjectSpawnTimer();
				m_spawnCountPerLevel--;
			}
			break;
		}
	}
	if(m_spawnCountPerLevel <= 0)
	{
		m_level++;
		std::cout << "Level is: " << m_level << std::endl;
		ResetSpawnCount();
	}
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
	m_windowObj.DrawThis(&m_background);
	m_windowObj.DrawThis(&m_background2);
}

void SpaceShooter::DrawHealthBarSprite()
{
	m_healthBarSprite.setTexture(m_healthBarTex);
	m_healthBarSprite.setOrigin(0.0f, m_healthBarSprite.getTextureRect().height * 0.5f);
	m_healthBarSprite.setPosition(m_livesBorderSprite.getPosition().x + 50.0f, m_livesBorderSprite.getPosition().y);
	m_healthBarSprite.setScale(0.2f, 0.2f);
	m_windowObj.DrawThis(&m_healthBarSprite);

	m_playerHealthBar.setOrigin(0.0f, 0.0f);
	m_playerHealthBar.setSize(sf::Vector2f(m_playerCurrentHealth / m_maxPlayerHealth * 100.0f, 24.0f));
	m_playerHealthBar.setScale(2.35f, 0.60f);
	m_playerHealthBar.setPosition(m_livesBorderSprite.getPosition().x + 84, m_livesBorderSprite.getPosition().y - 3.0f);
	m_playerHealthBar.setFillColor(sf::Color::Green);
	m_windowObj.DrawThis(&m_playerHealthBar);

	
}
void SpaceShooter::DrawBorders()
{
	m_livesBorderSprite.setTexture(m_livesBorderTex);
	m_livesBorderSprite.setOrigin(m_livesBorderSprite.getTextureRect().width * 0.5f, m_livesBorderSprite.getTextureRect().height * 0.5f);
	m_livesBorderSprite.setScale(0.5f, 0.5f);
	m_livesBorderSprite.setPosition(90.0f, 70.0f);
	m_windowObj.DrawThis(&m_livesBorderSprite);

	m_equippedBorderSprite1.setOrigin(m_equippedBorderSprite1.getTextureRect().width * 0.5f, m_equippedBorderSprite1.getTextureRect().height * 0.5f);
	m_equippedBorderSprite1.setScale(0.25f, 0.25f);
	m_equippedBorderSprite1.setPosition(50.0f, m_windowObj.GetWindowSize()->y - 300.0f);
	m_windowObj.DrawThis(&m_equippedBorderSprite1);

	
	m_equippedBorderSprite2.setOrigin(m_equippedBorderSprite2.getTextureRect().width * 0.5f, m_equippedBorderSprite2.getTextureRect().height * 0.5f);
	m_equippedBorderSprite2.setScale(0.25f, 0.25f);
	m_equippedBorderSprite2.setPosition(50.0f, m_windowObj.GetWindowSize()->y - 200.0f);
	m_windowObj.DrawThis(&m_equippedBorderSprite2);

	
	m_equippedBorderSprite3.setOrigin(m_equippedBorderSprite3.getTextureRect().width * 0.5f, m_equippedBorderSprite3.getTextureRect().height * 0.5f);
	m_equippedBorderSprite3.setScale(0.25f, 0.25f);
	m_equippedBorderSprite3.setPosition(50.0f, m_windowObj.GetWindowSize()->y - 100.0f);
	m_windowObj.DrawThis(&m_equippedBorderSprite3);

}

void SpaceShooter::ShowWeaponEquipped()
{
	switch (m_weaponEquiped)
	{
	case SS_Player::WEAPONTYPE::Fast:
		m_equippedBorderSprite1.setTexture(m_equippedONBorderTex);
		m_equippedBorderSprite2.setTexture(m_equippedOFFBorderTex);
		m_equippedBorderSprite3.setTexture(m_equippedOFFBorderTex);
		break;
	case SS_Player::WEAPONTYPE::QuadBlaster:
		m_equippedBorderSprite1.setTexture(m_equippedOFFBorderTex);
		m_equippedBorderSprite2.setTexture(m_equippedONBorderTex);
		m_equippedBorderSprite3.setTexture(m_equippedOFFBorderTex);
		break;
	case SS_Player::WEAPONTYPE::Power:
		m_equippedBorderSprite1.setTexture(m_equippedOFFBorderTex);
		m_equippedBorderSprite2.setTexture(m_equippedOFFBorderTex);
		m_equippedBorderSprite3.setTexture(m_equippedONBorderTex);
		break;
	default: 
		m_weaponEquiped = SS_Player::WEAPONTYPE::Fast;
		break;
	}
}

void SpaceShooter::Setup()
{
	m_level = 1;
	m_livesRemaining = 4;
	m_maxPlayerHealth = 200.0f;
	RespawnPlayer();
	ResetObjectSpawnTimer();
	ResetSpawnCount();
	CreateBackground(&m_background, &m_bgTexture, "Sprites/Background/longBGStars.png", sf::Vector2f(0.0f, 0.0f));
	CreateBackground(&m_background2, &m_bgTexture, "Sprites/Background/longBGStars.png", sf::Vector2f(0.0f, -m_windowObj.GetWindowSize()->y));
	GetSound()->PlayBackgroundMusic("Audio/Donic_-_Donic_-_Rubik_039_s_Cube_Original_Mix_.wav");
	m_highScore = ExtractHighsScoreFromFile();
	LoadTexture();
}

void SpaceShooter::LoadTexture()
{
	m_healthBarTex.loadFromFile("Sprites/GUI/HealthBar02.png");
	m_livesTex.loadFromFile("Sprites/TopDownShips/ship3.png");
	m_livesBorderTex.loadFromFile("Sprites/GUI/Border04.png");
	m_equippedONBorderTex.loadFromFile("Sprites/GUI/Box03.png");
	m_equippedOFFBorderTex.loadFromFile("Sprites/GUI/Box04.png");
	
}