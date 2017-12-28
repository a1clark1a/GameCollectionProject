#pragma once
#include "Player.h"

/**************BASE ITEM CLASS:: DERIVED FROM GAMEOBJECTS**********/
//ABSTRACT CLASS
class Item : public GameObjects
{
public:
	Item(const std::string texturePath, const sf::Vector2f & pos)
		:GameObjects(texturePath, pos) {};
	virtual ~Item() { std::cout << "Items Destructor called" << std::endl; }

	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object) {};
	virtual void OutOfBounds(Window* window);
	virtual void ShootFunction(const float & dt) {};

protected:
	virtual void Setup() = 0;
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