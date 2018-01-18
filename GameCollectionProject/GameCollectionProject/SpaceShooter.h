#pragma once
#include "Game.h"
#include "Enemy.h"
/**************************************************************************************
**************************SPACESHOOTER : DERIVED FROM GAME*****************************
***************************************************************************************/


/*************************SPACESHOOTER***************************/
class SpaceShooter : public Game
{
public:
	SpaceShooter();														//TODO(In Future) for save progression feature allow reinitialization of game variables through arguments in constructor
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
	(sf::RectangleShape* bg, sf::Texture* bgText, const std::string texturePath, const sf::Vector2f Position);
	virtual void SetScoreOnFile(const int & scoreVal);
	virtual unsigned int ExtractHighsScoreFromFile();

	//SpaceShooter Functions
	void RespawnPlayer();												// Function to spawn player
	void ResetPlayerSpawnTimer() { m_timeUntilRespawn = 3.0f; }
	void ResetObjectSpawnTimer() { m_objectSpawnCoolDown = static_cast<float>(rand() % 2 + 0.5); }
	void ResetSpawnCount() { m_spawnCountPerLevel = rand() % (20 + m_level) + (15 + m_level); }
	void SpawnAI();														// Function to spawn AI
	void SpawnDestructibles();											// Function to spawn destructibles
	void SpawnItem();													// Function to spawn Coins/Ammo/ExtraLife
	void SpawnSystem();													// Function to set how many AI and destructible to spawn per level
	void LoopBackground();
	void DrawHealthBarSprite();
	void DrawBorders();
	void ShowWeaponEquipped();

	//SpaceShooter member variables
private:
	virtual void Setup();
	void LoadTexture();

	SS_Player::WEAPONTYPE m_weaponEquiped;
	sf::RectangleShape m_background2;
	sf::RectangleShape m_playerHealthBar;
	sf::Sprite m_healthBarSprite;
	sf::Sprite m_livesBorderSprite;
	sf::Sprite m_equippedBorderSprite1;
	sf::Sprite m_equippedBorderSprite2;
	sf::Sprite m_equippedBorderSprite3;
	sf::Texture m_healthBarTex;
	sf::Texture m_livesTex;
	sf::Texture m_livesBorderTex;
	sf::Texture m_equippedONBorderTex;
	sf::Texture m_equippedOFFBorderTex;
	float m_playerCurrentHealth;
	float m_maxPlayerHealth;
	float m_timeUntilRespawn;
	float m_objectSpawnCoolDown;
	unsigned int m_quadAmmoRemaining;
	unsigned int m_PowerBombAmmoRemaining;
	unsigned int m_level;
	unsigned int m_livesRemaining;
	unsigned int m_spawnCountPerLevel;
	bool m_allEnemyDestroyed;
	
	
};