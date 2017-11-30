#pragma once
#include "Window.h"
#include "math.h"
#define DEG_TO_RAD (0.0174532925f)


class Game;																	 //Forward Class Declaration
class SS_Player;

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
	virtual void SetVelocity(const float & velAmount);						// Virtual Function to set velocity of a game object
	virtual void MaxVelocity(const float & maxSpeed);						// Virtual Function to determine maximum velocity for each object(to be called in MoveObject())
	virtual void ApplyDrag(const float & dt, const float & dragVal);		// Virtual Function to apply some dragging to objects(to be called in MoveObject())
	virtual void SetAccel(const float & accelVal);							// virtual Function to set acceleration rate
	virtual void SetLinearAccel(const float & accelVal);					// virutal Function  to allow forward and backward acceleration
	virtual void SetSideAccel(const float & accelVal);
	virtual void Destroy() { m_gameObjIsDestroyed = true; }					// Virtual Function to set boolean m_gameObjIsDestroyed to true;
	virtual void CollidedWith(GameObjects* object) {};						// Virtual Function to call when this object collides with an GameObjects object
	virtual void OutOfBounds(Window* window);								// Virtual Function to call when going object goes out of window
	virtual void ShootFunction() = 0;										// Virtual Function to be redefined by specific objects to handle shooting
	
	//Main Function
	void SetOwner(Game* owner) { m_owner = owner; };						// Function to to assign value to m_owner
	void SetPos(const sf::Vector2f& pos) { m_pos = pos; }					// Function to assign value to GameObject object's m_pos
	void SetAngle(const float angle) { m_angle = angle; }					// Function to assign value to GameObjects object's m_angle
	void SetCollisionRadius(float radius) { m_collisionRadius = radius; }	// Function to assign value to GameObject object's m_collisionRadius
	enum class WEAPONTYPE  { Fast, Laser, Power };

	//Helper/Getter Functions	
	bool IsDestroyed() const { return m_gameObjIsDestroyed; }				// Getter function to get GameObject object state
	float GetCollisionRadius() const { return m_collisionRadius; }			// Getter function to get a GameObject objects m_collisionRadius value
	float GetAngle() const { return m_angle; }								// Getter function to get a GameObject objects m_angle;
	float GetDistance(const sf::Vector2f & otherVector) const;				// Uses Distance Formula
	bool IsColliding(const GameObjects* otherObj);							// Function to check if *this GameObject object collides with another GameObject object

	//Public memmber variables
												

protected:
	Game * m_owner;															// A pointer to a Game class
	sf::Sprite m_sprite;													// A GameObject object's sprite variable
	sf::Vector2f m_pos;														// A GameObject object's position
	sf::Vector2f m_vel;														// A GameObject object's velocity
	sf::Vector2f m_accel;													// A GameObject object's acceleration
	sf::Texture m_texture;													// A GameObject object's sprite texture
	sf::CircleShape *CollisionSphere = new sf::CircleShape;					// A GameObject object's collision sphere object
	float m_angle;															// A GameObject object's rotation angle
	float m_collisionRadius;												// The CollisionSphere's Radius
	bool m_gameObjIsDestroyed;												// A GameObject object's state
	

};

/**************BASE ITEM CLASS:: DERIVED FROM GAMEOBJECTS**********/
//ABSTRACT CLASS
class Item : public GameObjects
{
public:
	Item(const std::string texturePath, const sf::Vector2f & pos);
	virtual ~Item();

	virtual void Draw(Window* window);
	virtual void Update(Window* window);
	virtual void CollidedWith(GameObjects* object) = 0;
	virtual void ShootFunction() {};

protected:
	float m_lifeTime;
};



