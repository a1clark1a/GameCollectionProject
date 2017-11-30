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
	virtual void DealDmg(GameObjects* enemy);
	virtual void ShootFunction() {};
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
