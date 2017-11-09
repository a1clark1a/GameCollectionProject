#pragma once
#include "Window.h"

class Game; //Forward Class Declaration

/*********************************************************************
****************************BASE CLASS********************************
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
	virtual void LimitVelocity(float dt);									// Virtual Function to determine maximum velocity for each object(to be called in MoveObject())
	virtual void ApplyDrag();												// Virtual Function to apply some dragging to objects(to be called in MoveObject())
	virtual void SetAccel(float accelVal);									// virtual Function to set acceleration rate
	virtual void MoveObject(float dt);										// virtual Function to increase object position
	virtual void Destroy();													// Virtual Function to set boolean m_gameObjIsDestroyed to true;

	//Main Function
	void SetOwner(Game* owner) { m_owner = owner; }							// Function to to initialize value to m_owner
	void SetPos(const sf::Vector2f& pos) { m_pos = pos; }					// Function to initialize value to GameObject object's m_pos
	void SetCollisionRadius(float radius) { m_collisionRadius = radius; }	// Function to initialize value to GameObject object's m_collisionRadius


	//Helper/Getter Functions
	bool IsDestroyed() { return m_gameObjIsDestroyed; }						// Getter function to get GameObject object state
	bool IsColliding(GameObjects* otherObj);								// Function to check if *this GameObject object collides with another GameObject object
	float GetCollisionRadius() { return m_collisionRadius; }				// Getter function to get a GameObject objects m_collisionRadius value

	//Public memmber variables
	sf::Sprite m_sprite;													// A GameObject object's sprite variable

protected:
	Game * m_owner;															// A pointer to a Game class
	sf::Vector2f m_pos;														// A GameObject object's position
	sf::Vector2f m_vel;														// A GameObject object's velocity
	sf::Vector2f m_accel;													// A GameObject object's acceleration
	sf::Texture m_texture;													// A GameObject object's sprite texture
	float m_angle;
	float m_collisionRadius;
	bool m_gameObjIsDestroyed;


};

/**************************************************************************************
*************************DERIVED CLASSES FOR SPACESHOOTER******************************
***************************************************************************************/

