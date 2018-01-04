#pragma once
#include "Player.h"

/**************ABSTRACT BASE ENEMY CLASS:: DERIVED FROM GAMEOBJECTS**********/
class Enemy : public GameObjects										
{
public:
	Enemy(const std::string texturePath, const sf::Vector2f & pos)
		:GameObjects(texturePath, pos) { };
	virtual ~Enemy() { std::cout << "Enemy Destructor called" << std::endl; }

	virtual void Draw(Window* window) = 0;
	virtual void Update(Window* window) { GameObjects::Update(window); OutOfBounds(window); }
	virtual void CollidedWith(GameObjects* object);
	virtual void OutOfBounds(Window* window);

	//Main Functions
	void TakeDamage(const float dmgVal);

	//helper functions
	const float GetDmgVal() const { return m_dmgVal; };
	const float GetEnemyHealth() const { return m_enemyHealth; }
	const unsigned int GetScoreVal() const { return m_scoreVal; }

protected:
	virtual void Setup() = 0;
	unsigned int m_scoreVal;
	float m_maxHealth;
	float m_enemyHealth;
	float m_dmgVal;
	float m_destroyDelay;
	
};

/**************ABSTRACT BASE AI CLASS:: DERIVED FROM ENEMY**********/
class AI : public Enemy													
{
public:
	AI::AI(const std::string texturePath, const sf::Vector2f & pos)
		:Enemy(texturePath, pos) {};
	virtual ~AI() { std::cout << "AI Destructor called" << std::endl; }

	virtual void Draw(Window* window);									//Virtual Function that can be redefined to call GameObject Draw function and draw health bar on screen
	virtual void Behavior(const float & dt);							//Virtual Function that can be redifined to have specific behaviors for each derived AI types
	virtual void Move(const float & dt) = 0;
	virtual void ShootFunction(const float & dt) {};
	virtual void DrawHealthBar(Window* window);
	virtual void Destroy();

	enum class AISTATES { Moving, Shooting };
	enum class MOVESTATES { Forward, Left, Right, Pause };

protected:
	virtual void Setup() = 0;
	AISTATES m_aiStates;
	MOVESTATES m_moveStates;
	float m_moveInterval;
	float m_pauseTimer;
	float m_shootingCoolDown;
	float m_line;
	sf::RectangleShape* m_enemyHealthBar = new sf::RectangleShape;
};

class NormalAI : public AI
{
public:
	NormalAI::NormalAI(const sf::Vector2f & pos);
	virtual ~NormalAI() { std::cout << "NormalAI destructor called" << std::endl; }

	
	virtual void Update(Window* window);
	virtual void OutOfBounds(Window* window);
	virtual void Move(const float & dt);
	virtual void ShootFunction(const float & dt);

protected:
	virtual void Setup();
};

class AggroAI : public AI
{
public:
	AggroAI::AggroAI(const sf::Vector2f & pos);
	virtual ~AggroAI() { std::cout << "AggroAI destructor called" << std::endl; }

	virtual void Update(Window* window);
	virtual void OutOfBounds(Window* window);
	virtual void SetLinearAccel(const float & accelVal_x, const float & accelVal_y);
	virtual void Move(const float & dt);
	virtual void ShootFunction(const float & dt);

protected:
	virtual void Setup();

private:
	int m_toggle;
};

class ChaserAI : public AI
{
public:
	ChaserAI::ChaserAI(const sf::Vector2f & pos);
	virtual ~ChaserAI() { std::cout << "FastAI destructor called" << std::endl; }

	virtual void Update(Window* window);
	virtual void OutOfBounds(Window* window);
	virtual void SetTarget(SS_Player* player);
	virtual void Move(const float & dt) {};

protected:
	virtual void Setup();

private:
	float m_rotationRate;
};


class BossAI : public AI
{
	BossAI(const sf::Vector2f & pos);
	virtual ~BossAI() { std::cout << "BossAI destructor called" << std::endl; }

	virtual void Update(Window* window);
	virtual void OutOfBounds(Window* window);
	virtual void Behavior(const float & dt);
	virtual void Move(const float & dt);
	virtual void ShootingFunction(const float & dt);
	virtual void Destroy();

protected:
	virtual void Setup();
};

/**************ABSTRACT BASE ASTEROID CLASS:: DERIVED FROM GAMEOBJECTS**********/
class Asteroid : public Enemy											
{
public:
	Asteroid(const std::string texturePath, const sf::Vector2f & pos);
	virtual ~Asteroid() { std::cout << "Asteroid Destructor called" << std::endl; }

	virtual void Draw(Window* window) { GameObjects::Draw(window); }
	virtual void Update(Window* window);
	virtual void ApplyDrag(float dt) = 0;
	virtual void Destroy() = 0;

protected:
	virtual void Setup();

private:
	float m_rotationRate;

};

class LargeAsteroid : public Asteroid
{
public:
	LargeAsteroid(const sf::Vector2f & pos);
	virtual ~LargeAsteroid() { std::cout << "LargeAsteroid Destructor called" << std::endl; }
	virtual void Destroy();
	virtual void ApplyDrag(float dt) {};

protected:
	virtual void Setup();
};

class MediumAsteroid : public Asteroid
{
public:
	MediumAsteroid(const sf::Vector2f & pos);
	virtual ~MediumAsteroid() { std::cout << "MediumAsteroid Destructor called" << std::endl; }
	virtual void Destroy();
	virtual void ApplyDrag(float dt) {};

protected:
	virtual void Setup();
};

class SmallAsteroid : public Asteroid
{
public:
	SmallAsteroid(const sf::Vector2f & pos);
	virtual ~SmallAsteroid() { std::cout << "SmallAsteroid Destructor called" << std::endl; }
	virtual void ApplyDrag(float dt) {};
	virtual void Destroy();

protected:
	virtual void Setup();
};