#pragma once
#include "Window.h"
#include "Game.h"
#include "SpaceShooter.h"
#include "Asteroid.h"

/*********************************************************************
**********************MAIN MENU CLASS********************************
*********************************************************************/
class MainMenu
{
public:
	MainMenu();
	~MainMenu() {}
	
	void PlayMenu();
	void Render();
	bool IsProgramOn() const { return m_programIsOn; }
	
private:
	//Private member functions
	void PlayGame();
	void Setup();
	void LoadTexture();
	void CreateText();
	void CreateBackGround();
	void CreateBorders();
	void ChooseGameControls();
	void CloseMenu();

	//Private member variables
	bool m_programIsOn;
	bool m_menuIsOn;
	Window m_windowObj;
	Game* m_game;
	sf::Font m_mainFont;
	sf::Texture m_texture;
	sf::Texture m_border01Texture;
	sf::Texture m_border02Texture;
	sf::Texture m_border06Texture;
	sf::Sprite m_border01;
	sf::Sprite m_border02;
	sf::Sprite m_border03;
	sf::Sprite m_border04;
	sf::Sprite m_border05;
	sf::Sprite m_border06;

};