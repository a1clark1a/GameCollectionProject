#include "MainMenu.h"

/**************************************************************************************
***********************************MAINMENU CLASS**************************************
***************************************************************************************/

MainMenu::MainMenu()
	:m_windowObj("MAIN MENU" ,sf::Vector2f(1000.0f,800.0f))
{
	Setup();
}

/**************************************************************************
*************************PUBLIC MEMBERS***********************************
**************************************************************************/

void MainMenu::PlayMenu()
{
	if(m_menuIsOn)
	{
		if (m_windowObj.IsClosed())
		{
			m_programIsOn = false;
		}
		m_windowObj.Update();
		ChooseGameControls();
		Render();
	}
	else
	{
		PlayGame();
	}
}

void MainMenu::Render()
{
	m_windowObj.Clear();
	//DRAW BELOW HERE
	CreateBackGround();
	CreateBorders();
	CreateText();
	//DRAW ABOVE HERE
	m_windowObj.Display();

}

/**************************************************************************
*************************PRIVATE MEMBERS***********************************
**************************************************************************/

void MainMenu::CreateText()
{
	sf::Text l_spaceShootText;
	l_spaceShootText.setFont(m_mainFont);
	l_spaceShootText.setString("1: SpaceShooter");
	l_spaceShootText.setCharacterSize(20);
	l_spaceShootText.setOrigin(l_spaceShootText.getGlobalBounds().width * 0.5f, l_spaceShootText.getGlobalBounds().height * 0.5f);
	l_spaceShootText.setPosition(m_border02.getPosition().x,m_border02.getPosition().y);
	m_windowObj.DrawThis(&l_spaceShootText);

	sf::Text l_asteroidText;
	l_asteroidText.setFont(m_mainFont);
	l_asteroidText.setString("2: Asteroid");
	l_asteroidText.setCharacterSize(20);
	l_asteroidText.setOrigin(l_asteroidText.getGlobalBounds().width * 0.5f, l_asteroidText.getGlobalBounds().height * 0.5f);
	l_asteroidText.setPosition(m_border03.getPosition().x, m_border03.getPosition().y);
	m_windowObj.DrawThis(&l_asteroidText);

	sf::Text l_pongText;
	l_pongText.setFont(m_mainFont);
	l_pongText.setString("3: Pong(In Progress)");
	l_pongText.setCharacterSize(20);
	l_pongText.setOrigin(l_pongText.getGlobalBounds().width * 0.5f, l_pongText.getGlobalBounds().height * 0.5f);
	l_pongText.setPosition(m_border04.getPosition().x, m_border04.getPosition().y);
	m_windowObj.DrawThis(&l_pongText);

	sf::Text l_tetrisText;
	l_tetrisText.setFont(m_mainFont);
	l_tetrisText.setString("4: Tetris(In Progress)");
	l_tetrisText.setCharacterSize(20);
	l_tetrisText.setOrigin(l_tetrisText.getGlobalBounds().width * 0.5f, l_tetrisText.getGlobalBounds().height * 0.5f);
	l_tetrisText.setPosition(m_border05.getPosition().x, m_border05.getPosition().y);
	m_windowObj.DrawThis(&l_tetrisText);

	sf::Text l_mainText;
	l_mainText.setFont(m_mainFont);
	l_mainText.setString("Game Collection Project");
	l_mainText.setCharacterSize(30);
	l_mainText.setOutlineThickness(1.0f);
	l_mainText.setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	l_mainText.setOrigin(l_mainText.getGlobalBounds().width * 0.5f, l_mainText.getGlobalBounds().height * 0.8f);
	l_mainText.setPosition(m_border06.getPosition().x, m_border06.getPosition().y);
	m_windowObj.DrawThis(&l_mainText);

}

void MainMenu::CreateBackGround()
{
	sf::RectangleShape l_background;
	l_background.setTexture(&m_texture);
	l_background.setSize(sf::Vector2f(m_windowObj.GetWindowSize()->x, m_windowObj.GetWindowSize()->y));
	l_background.setOrigin(sf::Vector2f(0.0f, 0.0f));
	m_windowObj.DrawThis(&l_background);
}

void MainMenu::CreateBorders()
{
	m_border01.setTexture(m_border01Texture);
	m_border01.setScale(1.0f,1.0f);
	m_border01.setOrigin(m_border01.getTextureRect().width * 0.5f, m_border01.getTextureRect().height * 0.5f);
	m_border01.setPosition(m_windowObj.GetWindowSize()->x * 0.5f, m_windowObj.GetWindowSize()->y * 0.5f);
	m_windowObj.DrawThis(&m_border01);

	m_border02.setTexture(m_border02Texture);
	m_border02.setScale(1.1f, 1.0f);
	m_border02.setOrigin(m_border02.getTextureRect().width * 0.5f, m_border02.getTextureRect().height * 0.5f);
	m_border02.setPosition(m_border01.getPosition().x - 150.0f, m_border01.getPosition().y);
	m_windowObj.DrawThis(&m_border02);

	m_border03.setTexture(m_border02Texture);
	m_border03.setScale(1.1f, 1.0f);
	m_border03.setOrigin(m_border03.getTextureRect().width * 0.5f, m_border03.getTextureRect().height * 0.5f);
	m_border03.setPosition(m_border02.getPosition().x, m_border02.getPosition().y + 100.0f);
	m_windowObj.DrawThis(&m_border03);

	m_border04.setTexture(m_border02Texture);
	m_border04.setScale(1.1f, 1.0f);
	m_border04.setOrigin(m_border04.getTextureRect().width * 0.5f, m_border04.getTextureRect().height * 0.5f);
	m_border04.setPosition(m_border02.getPosition().x + 300.0f, m_border02.getPosition().y);
	m_windowObj.DrawThis(&m_border04);

	m_border05.setTexture(m_border02Texture);
	m_border05.setScale(1.1f, 1.0f);
	m_border05.setOrigin(m_border05.getTextureRect().width * 0.5f, m_border05.getTextureRect().height * 0.5f);
	m_border05.setPosition(m_border04.getPosition().x, m_border04.getPosition().y + 100.0f);
	m_windowObj.DrawThis(&m_border05);

	m_border06.setTexture(m_border06Texture);
	m_border06.setScale(1.2f, 1.3f);
	m_border06.setOrigin(m_border06.getTextureRect().width * 0.5f, m_border06.getTextureRect().height * 0.5f);
	m_border06.setPosition(m_border01.getPosition().x, m_border01.getPosition().y - 250.0f);
	m_windowObj.DrawThis(&m_border06);
}

void MainMenu::ChooseGameControls()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_game = new SpaceShooter();
		CloseMenu();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_game = new AsteroidGame();
		CloseMenu();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		//Create Pong;
		//CloseMenu();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		//Create Tetris
		//CloseMenu();
	}
}

void MainMenu::PlayGame()
{
	while(!m_game->GetWindow()->IsClosed())
	{
		m_game->Update(m_game->GetWindow()->GetDeltaTime()->asSeconds());
		m_game->Render();
	}
	if (m_game->GetWindow()->IsClosed())
	{
		m_programIsOn = false;
	}
}

void MainMenu::Setup()
{
	m_programIsOn = true;
	m_menuIsOn = true;
	LoadTexture();
}

void MainMenu::LoadTexture()
{
	m_texture.loadFromFile("Sprites/Background/BG.png");
	m_border01Texture.loadFromFile("Sprites/GUI/BGBorder01.png");
	m_border02Texture.loadFromFile("Sprites/GUI/hollow01.png");
	m_border06Texture.loadFromFile("Sprites/GUI/Border02.png");
	m_mainFont.loadFromFile("Sprites/Fonts/Transformers Movie.ttf");
}

void MainMenu::CloseMenu()
{
	m_menuIsOn = false;
	m_windowObj.Destroy();
}