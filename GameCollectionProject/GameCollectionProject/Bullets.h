#pragma once
#include "GameObjects.h"

/**************BASE BULLET CLASS:: DERIVED FROM GAMEOBJECTS**********/

//ABSTRACT CLASS
class Bullet : public GameObjects
{
public:
	Bullet(const std::string texturePath, const sf::Vector2f & pos, const float & dmgVal)
		:GameObjects(texturePath, pos) {
		SetDmgVal(dmgVal);
	}
	virtual ~Bullet() { std::cout << "Base Bullet destructor called" << std::endl; };

	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object) = 0;
	virtual void ApplyDrag(float dt) {};
	virtual void Destroy() { GameObjects::Destroy(); }
	virtual void SetDmgVal(const float & dmgVal) { m_dmgVal = dmgVal; }
	virtual void ShootFunction(const float  & dt) {};
	virtual void OutOfBounds(Window* window);

protected:
	float m_lifeTime;
	float m_dmgVal;

};

class FastBullet : public Bullet
{
public:
	FastBullet(const sf::Vector2f & pos, const float & dmgVal, const float & vel);
	virtual ~FastBullet() { std::cout << "Fast Bullet Destructor Called" << std::endl; }

	virtual void CollidedWith(GameObjects* object);
	virtual void Update(Window* window);


};

class QuadBullets : public Bullet
{
public:
	QuadBullets(const sf::Vector2f & pos, const float & dmgVal);
	virtual ~QuadBullets() { std::cout << "QuadBullet Destructor Called" << std::endl; }
	
	virtual void CollidedWith(GameObjects* object);
	virtual void Update(Window* window);

private:
	float m_rotationRate;
};

class PowerBomb : public Bullet
{
public:
	PowerBomb(const std::string texturePath, const sf::Vector2f & pos, const float & dmgVal);
	virtual ~PowerBomb() { std::cout << "PowerBomb Destructor called" << std::endl; }

	virtual void CollidedWith(GameObjects* object);
	virtual void Destroy();



};

class MediumBomb : public PowerBomb
{
public:
	MediumBomb(const sf::Vector2f & pos, const float & dmgVal);
	virtual ~MediumBomb() { std::cout << "MediumBomb Destructor called" << std::endl; }

	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object) { PowerBomb::CollidedWith(object); }
	virtual void Destroy();

private:
	float m_rotationRate;
};

class SmallBomb : public PowerBomb
{
public:
	SmallBomb(const sf::Vector2f & pos, const float & dmgVal);
	virtual ~SmallBomb() { std::cout << "SmallBomb Destructor called" << std::endl; }

	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object){ PowerBomb::CollidedWith(object); }
	virtual void Destroy();

private:
	float m_rotationRate;
};


class EnemyBullet : public Bullet
{
public:
	EnemyBullet(const sf::Vector2f & pos, const float & dmgVal, const float & vel);
	virtual ~EnemyBullet() { std::cout << "EnemyBullet Destructor called" << std::endl; }

	virtual void CollidedWith(GameObjects* object);

};

class EnemyLaserBullet : public Bullet
{
public:
	EnemyLaserBullet(const sf::Vector2f & pos);
	virtual ~EnemyLaserBullet() { std::cout << "EnemyLaserBullet Destructor called" << std::endl; }
};
