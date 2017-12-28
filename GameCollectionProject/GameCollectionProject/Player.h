#pragma once
#include "GameObjects.h"
#include "Enemy.h"  //Temporary must remove after TEST is removed
#include "Items.h" //Temporary must remove after TEST is removed
#include "Bullets.h"

/******Forward Class Declaration*******/
class Window;

/**************************************************************************************
*********************PLAYER CLASSES : DERIVED FROM GAMEOBJECTS*************************
***************************************************************************************/

/**************BASE PLAYER CLASS:: DERIVED FROM GAMEOBJECTS**********/
//AN ABSTRACT CLASS
class Player : public GameObjects
{
public:
	Player(const std::string texturePath, const sf::Vector2f & pos)
		:GameObjects(texturePath, pos) {}								// Initialize a GameObjects texture and pos using the arguments passed to Player constructor
	virtual ~Player()													// Virtual destructor
	{
		std::cout << "Base Player Class's Destructor called " << std::endl;
	}

	virtual void Draw(Window* window);									// Virtual Function to call GameObject's Draw using scope resoultion operator and for other drawing
	virtual void Update(Window* window);								// Virtual Function responsible for updating Player State
	virtual void CollidedWith(GameObjects* object) = 0;					// Virtual Function to call when this object collides with an GameObjects object
	virtual void PlayerControls(Window* window) {};						// Virtual Function to handle player input
	virtual void TakeDmg(const float & dmgVal);
	virtual void MakeInvulnerable();
	virtual void DrawShield(Window* window);

	//Helper/Getter Functions
	const float GetPlayerHealth() const { return m_playerHealth; }
	float GetInvincibilityCD() { return m_invincibilityCooldown; }
	sf::Vector2f GetPlayerPos() { return m_pos; }
	

protected:
	virtual void Setup() = 0;
	bool m_shooting;													// A player's shooting state	
	float m_invincibilityCooldown;										// A player's invincibility cooldown value
	float m_shootCooldown;												// A player's shooting cooldown value
	float m_playerHealth;
	sf::CircleShape* m_invincibilityRing = new sf::CircleShape;
};

/***********PLAYER FOR SPACESHOOTER :: DERIVED FROM PLAYER CLASS**********/
class SS_Player : public Player
{
public:
	SS_Player();
	virtual ~SS_Player();

	
	virtual void Draw(Window* window);
	virtual void Update(Window* window);
	virtual void Destroy();
	virtual void CollidedWith(GameObjects* object);
	virtual void OutOfBounds(Window* window);
	virtual void PlayerControls(Window* window);
	virtual void ShootFunction(const float  & dt);

	//Getter Functions/Helper
	const unsigned int GetQuadAmmo() const { return m_quadAmmo; }
	const unsigned int GetPowerAmmo() const { return m_PowerAmmo; }
	void SetQuadAmmo(unsigned int val) { m_quadAmmo += val; }
	void SetPowerAmmo(unsigned int val) { m_PowerAmmo += val; }
	WEAPONTYPE GetWeapEquipped() { return m_currentWeap; }

protected:
	virtual void Setup();
	WEAPONTYPE m_currentWeap;

private:
	unsigned int m_quadAmmo;
	unsigned int m_PowerAmmo;

};