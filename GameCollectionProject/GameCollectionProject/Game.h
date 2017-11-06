#pragma once
#include <SFML\Audio.hpp>
#include "Window.h"
#include "GameObject.h"
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
	Game();												//Constructor to Game
	virtual ~Game();									//virtual Destructor

	//Virtual Functions
	virtual void Update() = 0;							// Pure Virtual Function to be redefined in each respective derived classes
	virtual void Render();								//Virtual Function to clear, draw and display 
	virtual void AddObject(GameObjects * object) = 0;  //Pure Virtual Function to be redefined in each respective derived class
	virtual void SetScore(int scoreVal);               //Function to add Score(Redefined to set specific score variable based on game(to be drawn by DrawText())
	virtual void DrawText();						   //Function to draw the score text, level text, ammo count etc on window(be called in Render())
	

	
	//Main Functions


	//Virtual Helper Functions
	virtual Window* GetWindow() { return m_window; }
	
	//REMINDER Members in this section are public ONLY INSIDE a derived class otherwise PRIVATE
protected:

	Window * m_window;								// Create a Window object to be accessed by derived classes to be able to draw object in window
	std::vector<GameObjects*> m_gameObjects;		// Create a vector container of pointers to a gameobject. 
	sf::Font m_mainFont;
						//Score variables for each Game
	//TODO make into a container to hold multiple values of each games scores for different replays
	int m_spaceShooterScore = 0;
	int m_asteroidScore = 0;						
	int m_tetrisScore = 0;
	int m_pongScore = 0;
						//Highscore variables for each Game
	int m_spaceShooterHighScore = 0;
	int m_asteroidHighScore = 0;						
	int m_tetrisHighScore = 0;
	int m_pongHighScore = 0;

	//REMINDER Members in this section are unaccessible outside 
private:


	
	
};


/**************************************************************************************
************************************DERIVED CLASSES************************************
***************************************************************************************/

//TODO create derived game engine from the base class Game

/*************************SPACESHOOTER***************************/

class SpaceShooter : public Game
{
public:
	SpaceShooter();
	virtual ~SpaceShooter();

	//Redefined Virtual Functions
	virtual void Update();
	virtual void Render();
	virtual void AddObject(GameObjects * object);

	//SpaceShooter Functions
	void RespawnPlayer();			//Function to spawn player
	void SpawnAI();					//Function to spawn AI
	void SpawnDestructibles();		//Function to spawn destructibles
	void SetSpawnCount();           //Function to set how many AI and destructible to spawn per level
	
	//SpaceShooter member variables
private:
	int m_level = 0;
	int m_livesRemaining;
	int m_specialAmmoRemaining;
	int m_spawnCount;

	

};

/*************************ASTEROID***************************/

class Asteroid : public Game
{
public:

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