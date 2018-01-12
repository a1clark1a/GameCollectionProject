#include "GameObjects.h"

/*********************************************************************
**********************ABSTRACT BASE CLASS*****************************
*********************************************************************/

//PUBLIC MEMBERS//
//Constructor to initialize GameObject object's texture and initial position
GameObjects::GameObjects(const std::string texturePath, const sf::Vector2f& pos)
	:m_pos(pos)
{
	Setup(texturePath);
}

//Virtual Destructor
GameObjects::~GameObjects()
{
	delete CollisionSphere;
}

			/***************************
			******Virtual Functions*****
			***************************/

//GameObjects version set texture and origin
void GameObjects::Setup(const std::string texturePath)
{
	m_gameObjIsDestroyed = false;
	m_collisionRadius = 0.0f;
	m_angle = 0.0f;
	m_texture.loadFromFile(texturePath);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.5f);
}

//GameObjects version draws a CollisionSphere on each object
void GameObjects::Draw(Window* window)
{
	CollisionSphere->setRadius(m_collisionRadius);
	CollisionSphere->setOutlineThickness(2.0f);
	CollisionSphere->setFillColor(sf::Color::Transparent);
	CollisionSphere->setPosition(m_pos);
	CollisionSphere->setOrigin(m_collisionRadius, m_collisionRadius);
	CollisionSphere->setOutlineColor(sf::Color::Red);
	//window->DrawThis(CollisionSphere);							//Comment out
	window->DrawThis(&m_sprite);

}

//GameObjects version Updates an objects general velocity and movement
void GameObjects::Update(Window* window)
{
	m_vel += m_accel * window->GetDeltaTime()->asSeconds();
	m_pos += m_vel * window->GetDeltaTime()->asSeconds();
	m_sprite.setRotation(m_angle);
	m_sprite.setPosition(m_pos);
}

//GameObjects version of setting an objects Velocity based on its angle
void GameObjects::SetVelocity(const float & velAmount)
{
	if (velAmount > 0.0f)
	{
		float l_rotInRadians = DEG_TO_RAD * m_angle;
		m_vel = sf::Vector2f(velAmount * sin(l_rotInRadians), -velAmount * cos(l_rotInRadians));
	}
	else
	{
		m_vel = sf::Vector2f(0.0f, 0.0f);
	}
}

//GameObjects version Function to set an objects velocity and its max possible velocity 
void GameObjects::VelocityLimiter(const float & maxSpeed)
{
	// set the speed by getting the square root of an objects velocity vector
	float l_speed = sqrt(m_vel.x * m_vel.x + m_vel.y * m_vel.y);

	if (l_speed <= 0.1)
	{
		return;
	}
	// Normalized the objects velocity by dividing the objects velocity by the speed
	sf::Vector2f l_normalizedVel = sf::Vector2f(m_vel.x / l_speed, m_vel.y / l_speed);

	if (l_speed > maxSpeed)
	{
		l_speed = maxSpeed;
	}

	// Set the objects velocity in a given direction by multiplying the normalized velocity to its speed
	m_vel.x = l_normalizedVel.x * l_speed;
	m_vel.y = l_normalizedVel.y * l_speed;
}

//GameObject's version to apply some drag to objects movements when no acceleration
void GameObjects::ApplyDrag(const float & dt, const float & dragval)
{
	if (m_accel.x == 0.0f && m_accel.y == 0.0f)
	{
		float dragAmount = dt * dragval;
		m_vel.x -= dragAmount * m_vel.x;
		m_vel.y -= dragAmount * m_vel.y;
	}
}

//GameObjects version setting an Objects acceleration based on angle
void GameObjects::SetAccel(const float & accelVal)
{
	if (accelVal > 0.0f)
	{
		float l_rotInRadians = DEG_TO_RAD * m_angle;
		m_accel = sf::Vector2f(accelVal * sin(l_rotInRadians), -accelVal * cos(l_rotInRadians));
	}
	else
	{
		m_accel = sf::Vector2f(0.0f, 0.0f);
	}
}

//GameObjects version to accelerate player forward or backward in a more linear direction
void GameObjects::SetLinearAccel(const float & accelVal)
{
	if (accelVal != 0)
	{
		m_accel = sf::Vector2f(0.0, 10.0f * -accelVal);
	}
	else
	{
		m_accel = sf::Vector2f(0.0f, 0.0f);
	}
}

//GameObjects to accelerate player Left or Right
void GameObjects::SetSideAccel(const float & accelVal)
{
	if (accelVal != 0.0f)
	{
		m_accel = sf::Vector2f(10.0f * accelVal, 0.0f);
	}
	else
	{
		m_accel = sf::Vector2f(0.0f, 0.0f);
	}
}


//GameObjects function checking if object is going out of window
//Redefined in Player
//GameObjects version allows objects comeout of the other side
void GameObjects::OutOfBounds(Window* window)
{
	if (m_pos.x < 0.0f)
	{
		m_pos.x = window->GetWindowSize()->x;
	}
	else if (m_pos.x > window->GetWindowSize()->x)
	{
		m_pos.x = 0.0f;
	}
	if (m_pos.y < 0.0f)
	{
		m_pos.y = window->GetWindowSize()->y;
	}
	else if (m_pos.y > window->GetWindowSize()->y)
	{
		m_pos.y = 0.0f;
	}
}

//Helper/Getter Functions

//Distance formula is the sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))
float GameObjects::GetDistance(const sf::Vector2f & otherVector) const
{
	sf::Vector2f l_vecDifference;																		//Difference between the 2 game object vectors
	l_vecDifference = sf::Vector2f(otherVector.x - m_pos.x, otherVector.y - m_pos.y);					// or simply vecDifference = otherVector - m_pos since vecDifference is a vector; 
	float dist = sqrt(l_vecDifference.x * l_vecDifference.x + l_vecDifference.y * l_vecDifference.y);	// Use the distance formula
	return dist;
}

//GameObjects version Collision check if another object collides with this(invoking) object
bool GameObjects::IsColliding(const GameObjects* otherObj)
{
	bool l_result = false;
	if (this != otherObj && !IsDestroyed() && !otherObj->IsDestroyed() && GetDistance(otherObj->m_pos) < (m_collisionRadius + otherObj->m_collisionRadius))
	{
		l_result = true;
	}
	return l_result;
}







