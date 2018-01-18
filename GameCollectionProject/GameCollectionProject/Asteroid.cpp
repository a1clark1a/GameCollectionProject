#include "Asteroid.h"

/**************************************************************************************
*********************************ASTEROID CLASS****************************************
***************************************************************************************/

//Asteroid Constructor - create Asteroid Game
AsteroidGame::AsteroidGame()
	:Game("Asteroid",sf::Vector2f(1400.0f,700.0f))
{
	Setup();
};

						/***************************
						******Virtual Functions*****
						***************************/
						
//Asteroid Update function
void AsteroidGame::Update(float dt)
{
	Game::Update(dt);
	if(!m_isGameOver)
	{
		UpdateGameObj();
	}
}

void AsteroidGame::Render()
{
	m_windowObj.Clear();
	//DRAW BELOW HERE
	CreateBackground();
	DrawObjects();
	DrawText();
	//DRAW ABOVE HERE
	m_windowObj.Display();
}

//Asteroid function to add objects into vector of gameobjects
void AsteroidGame::AddObject(GameObjects* object)
{
	object->SetOwner(this);
	m_gameObjects.push_back(object);
}

//Asteroid version that draws all objects in gameobject vector
void AsteroidGame::DrawObjects()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* l_current = m_gameObjects[i];
		l_current->Draw(&m_windowObj);
	}
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		Ast_Player* l_player = dynamic_cast<Ast_Player*>(m_gameObjects[i]);
		if (l_player)
		{
			m_ammoRemaining = l_player->GetSpecialAmmo();
		}

	}
}

//Asteroid function to check and play object states and movements
//A forloop function that calls each objects update function
void AsteroidGame::UpdateGameObj()
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

	//For every start of level/game spawn asteroids and loop, if player is found/spawned make player invulnerable
	if (m_spawnAsteroids == true)
	{
		SpawnAsteroids();
		SpawnItems();
		for (int i = int(m_gameObjects.size() - 1); i >= 0; i--)
		{
			GameObjects* l_current = m_gameObjects[i];
			Ast_Player* l_player = dynamic_cast<Ast_Player*>(l_current);
			if(l_player != NULL)
			{
				l_player->MakeInvulnerable();
			}
		}
	}

	//Loop through m_gameObjects vector and call each Update function
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* l_current = m_gameObjects[i];
		l_current->Update(&m_windowObj);
		l_current->ApplyDrag(m_windowObj.GetDeltaTime()->asSeconds(), 0.09f);
		if (dynamic_cast<Asteroid*>(l_current) != NULL)
		{
			m_spawnAsteroids = false;
		}
	}

	//Loop through m_gameObjects vector to check if each GameObjects destroy state is true, delete it 
	for (int i = int(m_gameObjects.size()) - 1; i >= 0; i--)
	{
		GameObjects* l_current = m_gameObjects[i];
		if (l_current->IsDestroyed())
		{
			Ast_Player* l_player = dynamic_cast<Ast_Player*>(l_current);
			if (l_player)
			{
				ResetPlayerSpawnTimer();
				GetSound()->PlaySound("Audio/Explosion.wav");
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
}

void AsteroidGame::DrawText()
{
	sf::Text l_scoreText;
	l_scoreText.setFont(m_mainFont);
	l_scoreText.setString("Score: " + std::to_string(m_score));
	l_scoreText.setCharacterSize(30);
	l_scoreText.setOrigin(l_scoreText.getGlobalBounds().width * 0.5f, l_scoreText.getGlobalBounds().height * 0.5f);
	l_scoreText.setPosition( 80.0f,10.0f);
	m_windowObj.DrawThis(&l_scoreText);

	sf::Text l_highScoreText;
	l_highScoreText.setFont(m_mainFont);
	l_highScoreText.setString("Highscore: " + std::to_string(m_highScore));
	l_highScoreText.setCharacterSize(30);
	l_highScoreText.setOrigin(l_highScoreText.getGlobalBounds().width * 0.5f, l_highScoreText.getGlobalBounds().height * 0.5f);
	l_highScoreText.setPosition(m_windowObj.GetWindowSize()->x - 150.0f,10.0f);
	m_windowObj.DrawThis(&l_highScoreText);

	sf::Text l_levelText;
	l_levelText.setFont(m_mainFont);
	l_levelText.setString("Level: " + std::to_string(m_level));
	l_levelText.setCharacterSize(30);
	l_levelText.setOrigin(l_levelText.getGlobalBounds().width * 0.5f, l_levelText.getGlobalBounds().height * 0.5f);
	l_levelText.setPosition(m_windowObj.GetWindowSize()->x - 150.0f, 50.0f);
	m_windowObj.DrawThis(&l_levelText);

	sf::Text l_ammoText;
	l_ammoText.setFont(m_mainFont);
	l_ammoText.setString("Ammo: " + std::to_string(m_ammoRemaining));
	l_ammoText.setCharacterSize(30);
	l_ammoText.setOrigin(l_ammoText.getGlobalBounds().width * 0.5f, l_ammoText.getGlobalBounds().height * 0.5f);
	l_ammoText.setPosition(80.0f, 100.0f);
	m_windowObj.DrawThis(&l_ammoText);

	// Draw Lives Remaining
	for (unsigned int i = 0; i < m_livesRemaining; i++)
	{
		sf::Sprite l_livesSprite(m_livesTexture);
		l_livesSprite.setScale(sf::Vector2f(0.05f, 0.05f));
		l_livesSprite.setPosition(sf::Vector2f(i * 40.0f, 50.0f));
		m_windowObj.DrawThis(&l_livesSprite);

	}

	//If its gameover draw GameOver text
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

void AsteroidGame::GameOver()
{
	m_isGameOver = true;
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObjects* l_current = m_gameObjects[i];
		l_current->Destroy();
	}
}

void AsteroidGame::CreateBackground()
{
	sf::RectangleShape l_background;
	l_background.setTexture(&m_texture);
	l_background.setSize(sf::Vector2f(m_windowObj.GetWindowSize()->x, m_windowObj.GetWindowSize()->y));
	l_background.setOrigin(sf::Vector2f(0.0f, 0.0f));
	m_windowObj.DrawThis(&l_background);
}

					/***************************
					********Main Functions******
					***************************/

void AsteroidGame::RespawnPlayer()
{
	if (m_livesRemaining > 0)
	{
		m_livesRemaining--;
		Ast_Player* l_player = new Ast_Player();
		AddObject(l_player);
	}
	else
	{
		GameOver();
	}
}

void AsteroidGame::SpawnAsteroids()
{
	m_level++;
	m_sound.PlaySound("Audio/Bounce.wav");
	SetSpawnCount();
	for (unsigned int i = 0; i < m_spawnCountPerLevel; i++)
	{
		Asteroid* l_asteroid;
		switch (rand() % 2)
		{
		case 0:
			l_asteroid = new MediumAsteroid(sf::Vector2f(static_cast<float>(rand() % 900 + 100), static_cast<float>(rand() % 600 + 50)));
			AddObject(l_asteroid);
			l_asteroid->SetAngle(static_cast<float>(rand() % 360));
			l_asteroid->SetVelocity(150.0f);
			break;
		case 1:
			l_asteroid = new LargeAsteroid(sf::Vector2f(static_cast<float>(rand() % 900 + 100), static_cast<float>(rand() % 600 + 50)));
			AddObject(l_asteroid);
			l_asteroid->SetAngle(static_cast<float>(rand() % 360));
			l_asteroid->SetVelocity(150.0f);
			break;
		}
	}
	m_spawnAsteroids = false;
}

void AsteroidGame::SpawnItems()
{
	int l_numOfCoins = rand() % 5 + 1;
	for (int i = 0; i < l_numOfCoins; i++)
	{
		Item* l_coin;
		switch (rand() % 2)
		{
		case 0:
			l_coin = new GoldCoin(sf::Vector2f(static_cast<float>(rand() % 900 + 100), static_cast<float>(rand() % 600 + 50)));
			AddObject(l_coin);
			l_coin->SetVelocity(10.0f);
			break;
		case 1:
			l_coin = new SilverCoin(sf::Vector2f(static_cast<float>(rand() % 900 + 100), static_cast<float>(rand() % 600 + 50)));
			AddObject(l_coin);
			l_coin->SetVelocity(10.0f);
			break;
		default:
			l_coin = new SilverCoin(sf::Vector2f(static_cast<float>(rand() % 900 + 100), static_cast<float>(rand() % 600 + 50)));
			AddObject(l_coin);
			l_coin->SetVelocity(10.0f);
			break;
		}
	}
}

void AsteroidGame::SetScoreOnFile(const int & scoreVal)
{
	m_highScore = m_score;
	std::ofstream myfile("HighScores/H_Asteroid.txt");
	if (myfile.is_open())
	{
		myfile << scoreVal << std::endl;
	}
	else std::cout << "Unable to open file" << std::endl;
}

unsigned int AsteroidGame::ExtractHighsScoreFromFile()
{
	std::string l_line;
	unsigned int l_score;
	std::ifstream myfile("HighScores/H_Asteroid.txt");
	if (myfile.is_open())
	{
		std::getline(myfile, l_line);
		l_score = std::stoi(l_line);
		myfile.close();
	}
	return l_score;
}
					/***************************
					******Private Functions*****
					***************************/

void AsteroidGame::Setup()
{
	m_level = 0;
	m_livesRemaining = 4;
	RespawnPlayer();
	m_spawnAsteroids = true;
	GetSound()->PlayBackgroundMusic("Audio/testSong.ogg");
	LoadTexture();
	m_highScore = ExtractHighsScoreFromFile();
}

void AsteroidGame::LoadTexture()
{
	m_texture.loadFromFile("Sprites/Background/BG4_01.png");
	m_livesTexture.loadFromFile("Sprites/TopDownShips/Player01.png");
}