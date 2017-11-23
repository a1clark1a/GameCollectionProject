#pragma once
#include <SFML\Audio.hpp>
#include "Window.h"
#include "GameObjects.h"
#include <vector>



//TODO Create a base class game engine to be used to derive other game engines specifically for each game

/*********************************************************************
**********************ABSTRACT BASE CLASS*****************************
*********************************************************************/
class Game
{
	//REMINDER Members in this section become public to derived classes
	//REMINDER Main User Interface
public:
	//REMINDER  When an a derived object is created its base class Constructor gets called first then followed by the derived constructor
	Game(const std::string winTitle, const sf::Vector2u winSize);												// Constructor to Game
	//REMINDER When an a derived object is destroyed derived object destructor gets called first then followed by base destructor
	virtual ~Game();													// virtual Destructor

	//Virtual Functions
	virtual void Update() { m_windowObj.Update(); }						// Inline call m_windowObj update function then to be redefined in each respective derived classes
	virtual void Render() = 0;											// Pure Virtual Function to clear, draw and display 
	virtual void AddObject(GameObjects * object) = 0;					// Pure Virtual Function to be redefined in each respective derived class
	virtual void SetScore(int scoreVal);								// Function to add Score( maybe redefined to set specific score variable based on game(to be drawn by DrawText())
	virtual void DrawText() = 0;										// Pure Virtual Function to draw the score text, level text, ammo count etc on window(be called in Render())
	virtual void DrawObjects() = 0;										// Virtual Function to draw game objects(be called in Render())
	virtual void ResetSpawnTimer() {};									// VirtualFunction to reset spawn timer
	virtual void UpdateGameObj() {};									// Virtual Function to update each and every game object(if using GameObject)(to be called in Update())
	virtual void GameOver() {};											// Virtual Function to call when game is over, to handle setting of remaining GameObjects' state into destroyed = true
	virtual void CreateBackground() {};									// Virtual Function to draw the background(be called in Render())


	//Main Functions
	

	//Virtual Helper Functions
	virtual Window* GetWindow()  { return &m_windowObj; }				// Inline helper function to acces a reference to m_windowObj object
	
	//REMINDER Members in this section are public ONLY INSIDE a derived class otherwise PRIVATE
protected:

	// Create a Window object to be accessed by derived classes to be able to draw object in window
	Window m_windowObj ;													// Object used to access Window members
	std::vector<GameObjects*> m_gameObjects;								// A vector container of pointers to a gameobject. 
	sf::Font m_mainFont;													// Use one type of font for all games(for now) to be initialized in constructor
	sf::RectangleShape m_background;
	sf::Texture m_bgTexture;
	unsigned int m_score;													// Game score variable
	unsigned int m_highScore = 0;											// Highscore variable 
	bool m_isGameOver;														// A Game's gameover state
	float m_timeUntilRespawn;
	

	//REMINDER Members in this section are unaccessible outside
private:


	
	
};


/**************************************************************************************
************************************DERIVED CLASSES************************************
***************************************************************************************/

//TODO create derived game from the base class Game

/*************************SPACESHOOTER***************************/

class SpaceShooter : public Game
{
public:
	SpaceShooter(const sf::Vector2u winSize);							//TODO(In Future) for save progression feature allow reinitialization of game variables through arguments in constructor
	virtual ~SpaceShooter();

	//Redefined Virtual Functions
	virtual void Update(float dt);										// Call m_windowObj.Update() 
	virtual void Render();
	virtual void AddObject(GameObjects * object);
	virtual void DrawText();
	virtual void DrawObjects();
	virtual void UpdateGameObj();
	virtual void GameOver();
	virtual void CreateBackground
	(sf::RectangleShape* bg,  sf::Texture* bgText, const std::string texturePath,const sf::Vector2f Position);

	//Helper/Getter Functions
	virtual void ResetSpawnTimer() { m_timeUntilRespawn = 3.0f; }

	//SpaceShooter Functions
	void RespawnPlayer();												// Function to spawn player
	void SpawnAI();														// Function to spawn AI
	void SpawnDestructibles();											// Function to spawn destructibles
	void SpawnItem();													// Function to spawn Coins/Ammo/ExtraLife
	void SetSpawnCount();												// Function to set how many AI and destructible to spawn per level
	void LoopBackground();
	

	//SpaceShooter member variables
private:
	sf::RectangleShape m_background2;
	unsigned int m_specialAmmoRemaining;
	unsigned int m_level;
	unsigned int m_livesRemaining;
	unsigned int m_spawnCount;

};

/*************************ASTEROID***************************/

class AsteroidGame : public Game
{
public:
	AsteroidGame();
	virtual ~AsteroidGame();

	//Redefined Virtual Functions
	virtual void Update();
	virtual void Render();
	virtual void AddObject(GameObjects * object);

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