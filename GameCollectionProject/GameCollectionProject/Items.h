#pragma once
#include "Player.h"

/**************ABSTRACT BASE ITEM CLASS:: DERIVED FROM GAMEOBJECTS**********/
class Item : public GameObjects
{
public:
	Item(const std::string texturePath, const sf::Vector2f & pos);
	virtual ~Item() { std::cout << "Items Destructor called" << std::endl; }

	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object) = 0;
	virtual void OutOfBounds(Window* window);

protected:
	virtual void Setup() { m_moveSpd = static_cast<float>(rand() % -5 + -5); };
	float m_moveSpd;
	float m_lifeTime;
};

class GoldCoin : public Item
{
public:
	GoldCoin(const sf::Vector2f & pos);
	virtual ~GoldCoin() { std::cout << "GoldCoin destructor called" << std::endl; }

	virtual void CollidedWith(GameObjects* object);
		
protected:
	virtual void Setup();

private:
	unsigned int m_scoreVal;
};

class SilverCoin : public Item
{
public:
	SilverCoin(const sf::Vector2f & pos);
	virtual ~SilverCoin() { std::cout << "SilverCoin destructor called" << std::endl; }

	virtual void CollidedWith(GameObjects* object);

protected:
	virtual void Setup();

private:
	unsigned int m_scoreVal;
};

class QuadAmmo : public Item
{
public:
	QuadAmmo(const sf::Vector2f & pos);
	virtual ~QuadAmmo() { std::cout << "QuadAmmo destructor called" << std::endl; }

	virtual void CollidedWith(GameObjects* object);

protected:
	virtual void Setup();

private:
	unsigned int m_ammoVal;
};

class PowerAmmo : public Item
{
public:
	PowerAmmo(const sf::Vector2f & pos);
	virtual ~PowerAmmo() { std::cout << "PowerAmmo destructor called" << std::endl; }

	virtual void CollidedWith(GameObjects* object);

protected:
	virtual void Setup();

private:
	unsigned int m_ammoVal;
};