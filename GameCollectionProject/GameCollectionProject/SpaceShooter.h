#pragma once
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullets.h"
/**************************************************************************************
**************************SPACESHOOTER : DERIVED FROM GAME*****************************
***************************************************************************************/

class GameObjects;
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

	//Helper/Getter Functions
	virtual void ResetSpawnTimer() { m_timeUntilRespawn = 3.0f; }
	
	//SpaceShooter Functions
	void RespawnPlayer();												// Function to spawn player
	void SpawnAI();														// Function to spawn AI
	void SpawnDestructibles();											// Function to spawn destructibles
	void SpawnItem();													// Function to spawn Coins/Ammo/ExtraLife
	void SetSpawnCount();												// Function to set how many AI and destructible to spawn per level
	void LoopBackground();
	void DrawHealthBarSprite();
	void DrawBorders();
	void ShowWeaponEquipped();

	//SpaceShooter member variables
private:
	SS_Player::WEAPONTYPE m_weaponEquiped;
	sf::RectangleShape m_background2;
	sf::RectangleShape* m_playerHealthBar = new sf::RectangleShape;
	sf::Sprite* m_healthBarSprite = new sf::Sprite;
	sf::Sprite* m_livesBorderSprite = new sf::Sprite;
	sf::Sprite* m_equippedBorderSprite1 = new sf::Sprite;
	sf::Sprite* m_equippedBorderSprite2 = new sf::Sprite;
	sf::Sprite* m_equippedBorderSprite3 = new sf::Sprite;
	sf::Texture* m_healthBarTex = new sf::Texture;
	sf::Texture* m_livesTex = new sf::Texture;
	sf::Texture* m_livesBorderTex = new sf::Texture;
	sf::Texture* m_equippedONBorderTex = new sf::Texture;
	sf::Texture* m_equippedOFFBorderTex = new sf::Texture;
	float m_playerCurrentHealth;
	float m_maxPlayerHealth;
	unsigned int m_quadAmmoRemaining;
	unsigned int m_PowerBombAmmoRemaining;
	unsigned int m_level;
	unsigned int m_livesRemaining;
	unsigned int m_spawnCount;

};