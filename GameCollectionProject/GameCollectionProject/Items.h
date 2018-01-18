#pragma once
#include "Player.h"
/**************ABSTRACT BASE ITEM CLASS:: DERIVED FROM GAMEOBJECTS**********/
class Item : public GameObjects
{
public:
	Item(const std::string texturePath, const sf::Vector2f & pos);
	virtual ~Item() { }  

	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object) = 0;
	virtual void OutOfBounds(Window* window);

protected:
	virtual void Setup() { m_moveSpd = -1.0f * static_cast<float>(rand() % 20 + 10); m_lifeTime = 30.0f; };
	float m_moveSpd;
	float m_lifeTime;
	unsigned int m_val;
};

class GoldCoin : public Item
{
public:
	GoldCoin(const sf::Vector2f & pos);
	virtual ~GoldCoin() {} 

	virtual void CollidedWith(GameObjects* object);
		
protected:
	virtual void Setup();
};

class SilverCoin : public Item
{
public:
	SilverCoin(const sf::Vector2f & pos);
	virtual ~SilverCoin() {} 

	virtual void CollidedWith(GameObjects* object);

protected:
	virtual void Setup();
};

class HealthPack : public Item
{
public:
	HealthPack(const sf::Vector2f & pos);
	virtual ~HealthPack() {}  

	virtual void CollidedWith(GameObjects* object);

protected:
	virtual void Setup();
};

class QuadAmmo : public Item
{
public:
	QuadAmmo(const sf::Vector2f & pos);
	virtual ~QuadAmmo() {}  

	virtual void CollidedWith(GameObjects* object);

protected:
	virtual void Setup();
};

class PowerAmmo : public Item
{
public:
	PowerAmmo(const sf::Vector2f & pos);
	virtual ~PowerAmmo() {} 

	virtual void CollidedWith(GameObjects* object);

protected:
	virtual void Setup();
};