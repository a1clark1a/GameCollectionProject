#include "GameObjects.h"

/*********************************************************************
**********************ABSTRACT BASE CLASS*****************************
*********************************************************************/

//PUBLIC MEMBERS//
//Constructor to initialize GameObject object's texture and initial position
GameObjects::GameObjects(const std::string texturePath, const sf::Vector2f& pos)
	:m_gameObjIsDestroyed(false)
	,m_pos(pos)
	,m_collisionRadius(0)
	,m_angle(0)
	
{
	m_texture.loadFromFile(texturePath);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.5f);
}

//Virtual Destructor
GameObjects::~GameObjects()
{
	std::cout << " Abstract Base Class Game Object's Destructor() is called" << std::endl;
	delete CollisionSphere;
}

//Virtual Functions

//A virtual function : Base version draws a CollisionSphere on object
void GameObjects::Draw(Window* window)
{
	CollisionSphere->setRadius(m_collisionRadius);
	CollisionSphere->setOutlineThickness(2);
	CollisionSphere->setFillColor(sf::Color::Transparent);
	CollisionSphere->setPosition(m_pos);
	CollisionSphere->setOrigin(m_collisionRadius, m_collisionRadius);
	CollisionSphere->setOutlineColor(sf::Color::Red);
	window->DrawThis(CollisionSphere);
	window->DrawThis(&m_sprite);

}

//A virtual function: Base version Updates an objects general velocity and movement
void GameObjects::Update(Window* window)
{
	
}

//
void GameObjects::SetVelocity(float velAmount)
{

}

void GameObjects::MaxVelocity(float dt)
{
	
}

void GameObjects::ApplyDrag(float dt)
{

}

void GameObjects::SetAccel(float accelVal)
{

}

void GameObjects::OutOfBounds()
{

}


//Helper/Getter Functions

//Distance formula is the sqrt( (x1-x2)sqred + (y1-y2)sqred)
float GameObjects::GetDistance(const sf::Vector2f & otherVector) const
{
	sf::Vector2f vecDifference;																 //Difference between the 2 game object vectors
	vecDifference = sf::Vector2f(otherVector.x - m_pos.x, otherVector.y - m_pos.y);			 // or simply vecDifference = otherVector - m_pos; (
	float dist = sqrt(vecDifference.x * vecDifference.x + vecDifference.y * vecDifference.y);
	return dist;
}

//Collision check if another object collides with this(invoking) object
bool GameObjects::IsColliding(const GameObjects* otherObj) const
{
	bool result = false;
	if (this != otherObj && !IsDestroyed() && !otherObj->IsDestroyed() && GetDistance(otherObj->m_pos) < (m_collisionRadius + otherObj->m_collisionRadius))
	{
		result = true;
	}
	return result;
}

//PRIVATE MEMBERS//