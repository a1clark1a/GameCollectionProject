#pragma once
#include "Window.h"
#define DEG_TO_RAD (0.0174532925f)

class Game;																	 //Forward Class Declaration
class SpaceShooter;

/*********************************************************************
***************************ABSTRACT BASE CLASS************************
*********************************************************************/
class GameObjects
{
public:

	GameObjects(const std::string texturePath, const sf::Vector2f& pos);	// Constructor to take file path of sprite texture, and an initial vector location on screen
	virtual ~GameObjects();													// Virtual Destructor

	//Virtual Functions
	virtual void Draw(Window* window);										// Virtual Function to draw a transparent collision sphere around object for collision detection
	virtual void Update(Window* window);									// Virtual Function responsible to velocity values etc and checking of objects position
	virtual void SetVelocity(float velAmount);								// Virtual Function to set velocity of a game object
	virtual void MaxVelocity();												// Virtual Function to determine maximum velocity for each object(to be called in MoveObject())
	virtual void ApplyDrag(float dt, float dragVal);						// Virtual Function to apply some dragging to objects(to be called in MoveObject())
	virtual void SetAccel(float accelVal);									// virtual Function to set acceleration rate
	virtual void SetLinearAccel(float accelVal);							// virutal Function  to allow forward and backward acceleration
	virtual void SetSideAccel(float accelVal);
	virtual void Destroy() { m_gameObjIsDestroyed = true; }					// Virtual Function to set boolean m_gameObjIsDestroyed to true;
	virtual void CollidedWith(GameObjects* object) {};						// Virtual Function to call when this object collides with an GameObjects object
	virtual void OutOfBounds(Window* window);								// Virtual Function to call when going object goes out of window
	virtual void ShootFunction() {};										// Virtual Function to be redefined by specific objects to handle shooting
	
	//Main Function
	void SetOwner(Game* owner) { m_owner = owner; };						// Function to to assign value to m_owner
	void SetPos(const sf::Vector2f& pos) { m_pos = pos; }					// Function to assign value to GameObject object's m_pos
	void SetAngle(const float angle) { m_angle = angle; }					// Function to assign value to GameObjects object's m_angle
	void SetCollisionRadius(float radius) { m_collisionRadius = radius; }	// Function to assign value to GameObject object's m_collisionRadius
	

	//Helper/Getter Functions	
	bool IsDestroyed() const { return m_gameObjIsDestroyed; }						// Getter function to get GameObject object state
	float GetCollisionRadius() const { return m_collisionRadius; }			// Getter function to get a GameObject objects m_collisionRadius value
	float GetAngle() const { return m_angle; }								// Getter function to get a GameObject objects m_angle;
	float GetDistance(const sf::Vector2f & otherVector) const;				// Uses Distance Formula
	bool IsColliding(const GameObjects* otherObj);					// Function to check if *this GameObject object collides with another GameObject object

	//Public memmber variables
	sf::Sprite m_sprite;													// A GameObject object's sprite variable

protected:
	Game * m_owner;															// A pointer to a Game class
	sf::Vector2f m_pos;														// A GameObject object's position
	sf::Vector2f m_vel;														// A GameObject object's velocity
	sf::Vector2f m_accel;													// A GameObject object's acceleration
	sf::Texture m_texture;													// A GameObject object's sprite texture
	sf::CircleShape *CollisionSphere = new sf::CircleShape;					// A GameObject object's collision sphere object
	float m_angle;															// A GameObject object's rotation angle
	float m_collisionRadius;												// The CollisionSphere's Radius
	bool m_gameObjIsDestroyed;												// A GameObject object's state


};

/**************************************************************************************
***********************************DERIVED CLASSES*************************************
***************************************************************************************/


/**************BASE PLAYER CLASS:: DERIVED FROM GAMEOBJECTS**********/
class Player : public GameObjects
{
public:
	Player(const std::string texturePath, const sf::Vector2f & pos)
		:GameObjects(texturePath, pos) {}								// Initialize a GameObjects texture and pos using the arguments passed to Player constructor
	virtual ~Player()													// Virtual destructor
	{ std::cout << "Base Player Class's Destructor called " << std::endl; }

	virtual void Draw(Window* window);									// Virtual Function to call GameObject's Draw using scope resoultion operator and for other drawing
	virtual void Update(Window* window);								// Virtual Function responsible for updating Player State
	virtual void CollidedWith(GameObjects* object);						// Virtual Function to call when this object collides with an GameObjects object
	virtual void MakeInvulnerable();									// Virtual Function to reset a player invulnerability upon respawn
	virtual void PlayerControls(Window* window) {};						// Virtual Function to handle player input
	virtual void ShootFunction() {};									// Virtual Function to handle player's different type of shooting capabilities 

	//Main Functions
	virtual void TakeDmg(const float & dmgVal);

	//Helper/Getter Functions
	float GetPlayerHealth() const { return m_playerHealth; }

protected:
	bool m_shooting;													// A player's shooting state				
	float m_shootCooldown;												// A player's shooting cooldown value
	float m_invincibilityCooldown;										// A player's invincibility cooldown value
	float m_playerHealth;
	unsigned int m_currentWeap;
};

/**************BASE BULLET CLASS:: DERIVED FROM GAMEOBJECTS**********/
class Bullet : public GameObjects
{
public:
	Bullet(const std::string texturePath, const sf::Vector2f & pos, const float & dmgVal)
		:GameObjects(texturePath, pos) { SetDmgVal(dmgVal); }
	virtual ~Bullet(){ std::cout << "Base Bullet destructor called" << std::endl; };

	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object) {};
	virtual void ApplyDrag(float dt) {};
	virtual void Destroy() { GameObjects::Destroy(); }
	virtual void SetDmgVal(const float & dmgVal) { m_dmgVal = dmgVal; }
	virtual void DealDmg(GameObjects* enemy);
	
protected:
	float m_lifeTime;
	float m_dmgVal;

};

class FastBullet : public Bullet
{
public:
	FastBullet(const sf::Vector2f & pos, const float & dmgVal);
	virtual ~FastBullet() { std::cout << "Fast Bullet Destructor Called" << std::endl; }

	virtual void CollidedWith(GameObjects* object);
	virtual void Update(Window* window);
	

};

class LaserBullet : public Bullet
{
public:
	LaserBullet(const sf::Vector2f & pos, const float & dmgVal);
	virtual ~LaserBullet();

	virtual void Draw(Window* window);
	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object);
	virtual void Destroy();
	virtual void SetVelocity(float velAmount) {};

private:
	sf::Vector2f m_spriteSize;
	sf::Vector2f m_collisionSize;
	sf::RectangleShape* m_collisionBox = new sf::RectangleShape;
};

class PowerBomb : public Bullet
{
public:
	PowerBomb(const std::string texturePath, const sf::Vector2f & pos);
	virtual ~PowerBomb();

	virtual void Draw(Window* window);
	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object);
	virtual void Destroy();



};

class MediumBomb : public PowerBomb
{
public:
	MediumBomb(const sf::Vector2f & pos);
	virtual ~MediumBomb();

	virtual void Update();
	virtual void CollidedWith(GameObjects* object);
	virtual void Destroy();
};

class SmallBomb : public PowerBomb
{
public:
	SmallBomb(const sf::Vector2f & pos);
	virtual ~SmallBomb();

	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object);
	virtual void Destroy();

};


/**************BASE ITEM CLASS:: DERIVED FROM GAMEOBJECTS**********/
class Item : public GameObjects
{
public:
	Item(const std::string texturePath, const sf::Vector2f & pos);
	virtual ~Item();

	virtual void Draw(Window* window);
	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object) {};
	
protected:
	float m_lifeTime;
};

/***************************************************************************************
*************************GAMEOBJECTS FOR SPACESHOOTER GAME******************************
****************************************************************************************/

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
	virtual void ShootFunction();
	virtual void MakeInvulnerable();
	

	//Main Functions
	


	
};

/**************BASE ENEMY CLASS:: DERIVED FROM GAMEOBJECTS**********/
class Enemy : public GameObjects
{
public:
	Enemy(const std::string texturePath, const sf::Vector2f & pos)
		:GameObjects(texturePath, pos) { };
	virtual ~Enemy() { std::cout << "Enemy Destructor called" << std::endl; }

	virtual void Update(Window* window) { GameObjects::Update(window); OutOfBounds(window); }
	virtual void CollidedWith(GameObjects* object);
	virtual void TakeDamage(const float dmgVal);
	virtual void OutOfBounds(Window* window);

	//helper functions
	const float GetDmgVal() const { return m_dmgVal; };
	const float GetEnemyHealth() const { return m_enemyHealth; }
	const unsigned int GetScoreVal() const { return m_scoreVal; }

protected:
	unsigned int m_scoreVal;
	float m_enemyHealth;
	float m_dmgVal;
	float l_delay;
};




/***************************************************************************************
****************GAMEOBJECTS FOR ASTEROID GAME(CAN BE USED IN SPACESHOOTER)**************
****************************************************************************************/

/**************BASE ASTEROID CLASS:: DERIVED FROM GAMEOBJECTS**********/
class Asteroid : public Enemy
{
public:
	Asteroid(const std::string texturePath, const sf::Vector2f & pos);
	virtual ~Asteroid() { std::cout << "Asteroid Destructor called" << std::endl; }

	virtual void Update(Window* window);
	virtual void ApplyDrag(float dt) {};

private:
	float m_rotationRate;

};

class LargeAsteroid : public Asteroid
{
public:
	LargeAsteroid(const sf::Vector2f & pos);
	virtual ~LargeAsteroid() { std::cout << "LargeAsteroid Destructor called" << std::endl; }
	virtual void Destroy();
};

class MediumAsteroid : public Asteroid
{
public:
	MediumAsteroid(const sf::Vector2f & pos);
	virtual ~MediumAsteroid() { std::cout << "MediumAsteroid Destructor called" << std::endl; }
	virtual void Destroy();
};

class SmallAsteroid : public Asteroid
{
public:
	SmallAsteroid(const sf::Vector2f & pos);
	virtual ~SmallAsteroid() { std::cout << "SmallAsteroid Destructor called" << std::endl; }
};


