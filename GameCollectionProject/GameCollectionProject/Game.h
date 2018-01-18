#pragma once
#include "Window.h"
#include "SoundManager.h"
#include <vector>
#include <fstream>

/******Forward Class Declaration*******/
class GameObjects;

/*********************************************************************
**********************ABSTRACT BASE CLASS*****************************
*********************************************************************/
class Game
{
	//REMINDER Members in this section become public to derived classes
	//REMINDER Main User Interface
public:
	//REMINDER  When an a derived object is created its base class Constructor gets called first then followed by the derived constructor
	Game(const std::string winTitle, const sf::Vector2f winSize);												// Constructor to Game
	//REMINDER When an a derived object is destroyed derived object destructor gets called first then followed by base destructor
	virtual ~Game();													// virtual Destructor

	//Virtual Functions
	virtual void Update(float dt) { m_windowObj.Update(); }				// Inline Call m_windowObj update function then to be redefined in each respective derived classes
	virtual void Render() = 0;											// Pure Virtual Function to clear, draw and display 
	virtual void AddObject(GameObjects * object) = 0;					// Pure Virtual Function to be redefined in each respective derived class
	virtual void SetScore(const int & scoreVal);						// Function to add Score
	virtual void SetScoreOnFile(const int & scoreVal) = 0;				// Function to write Highscore on a text file
	virtual unsigned int ExtractHighsScoreFromFile() = 0;
	virtual void DrawText() = 0;										// Pure Virtual Function to draw the score text, level text, ammo count etc on window(be called in Render())
	virtual void GameOver() {};											// Virtual Function to call when game is over, to handle setting of remaining GameObjects' state into destroyed = true
	virtual void CreateBackground() {};									// Virtual Function to draw the background(be called in Render())
	
	//Virtual Helper Functions
	virtual Window* GetWindow()  { return &m_windowObj; }				// Inline helper function to acces a reference to m_windowObj object
	virtual SoundManager* GetSound() { return &m_sound; }
	
	//REMINDER Members in this section are public ONLY INSIDE a derived class otherwise PRIVATE
protected:
	virtual void Setup();
	virtual void LoadTexture();
	SoundManager m_sound;
	Window m_windowObj ;												// Object used to access Window members
	std::vector<GameObjects*> m_gameObjects;							// A vector container of pointers to a gameobject. 
	sf::Font m_mainFont;												// Use one type of font for all games(for now) to be initialized in constructor
	sf::RectangleShape m_background;
	sf::Texture m_bgTexture;
	unsigned int m_score;												// Game score variable
	unsigned int m_highScore;											// Highscore variable 
	bool m_isGameOver;													// A Game's gameover state
	
	

	//REMINDER Members in this section are unaccessible outside
private:

	
};


/*************************TETRIS***************************/

class Tetris : public Game
{

};

/*************************PONG***************************/

class Pong : public Game
{

};