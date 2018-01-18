#pragma once
#include "Game.h"
#include "Enemy.h"
/**************************************************************************************
******************************ASTEROID : DERIVED FROM GAME*****************************
***************************************************************************************/


/*************************ASTEROID***************************/
class AsteroidGame : public Game
{
public:
	AsteroidGame();
	virtual ~AsteroidGame() {};

	//Redefined Virtual Functions
	virtual void Update(float dt);
	virtual void Render();
	virtual void AddObject(GameObjects * object);
	virtual void UpdateGameObj();
	virtual void DrawText();
	virtual void DrawObjects();
	virtual void GameOver();
	virtual void CreateBackground();					
	virtual void SetScoreOnFile(const int & scoreVal);	
	virtual unsigned int ExtractHighsScoreFromFile();

	//Asteroid Functions
	void RespawnPlayer();
	void ResetPlayerSpawnTimer() { m_timeUntilRespawn = 3.0f; }
	void SpawnAsteroids();
	void SpawnItems();
	void SetSpawnCount() { m_spawnCountPerLevel = (rand() % (1 + m_level) + (5 + m_level)) + m_level; }

private:
	virtual void Setup();
	void LoadTexture();

	float m_timeUntilRespawn;
	bool m_spawnAsteroids;
	unsigned int m_level;
	unsigned int m_livesRemaining;
	unsigned int m_spawnCountPerLevel;
	unsigned int m_ammoRemaining;
	sf::Texture m_texture;
	sf::Texture m_livesTexture;
};