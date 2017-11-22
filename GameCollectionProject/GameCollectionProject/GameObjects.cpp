#include "GameObjects.h"
#include "Game.h"

/*********************************************************************
**********************ABSTRACT BASE CLASS*****************************
*********************************************************************/

//PUBLIC MEMBERS//
//Constructor to initialize GameObject object's texture and initial position
GameObjects::GameObjects(const std::string texturePath, const sf::Vector2f& pos)
	:m_gameObjIsDestroyed(false)
	,m_pos(pos)
	,m_collisionRadius(0.0f)
	,m_angle(0.0f)
	
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

//GameObjects version draws a CollisionSphere on each object
void GameObjects::Draw(Window* window)
{
	CollisionSphere->setRadius(m_collisionRadius);
	CollisionSphere->setOutlineThickness(2.0f);
	CollisionSphere->setFillColor(sf::Color::Transparent);
	CollisionSphere->setPosition(m_pos);
	CollisionSphere->setOrigin(m_collisionRadius, m_collisionRadius);
	CollisionSphere->setOutlineColor(sf::Color::Red);
	window->DrawThis(CollisionSphere);							//Comment out
	window->DrawThis(&m_sprite);

}

//GameObjects version Updates an objects general velocity and movement
void GameObjects::Update(Window* window)
{
	m_vel += m_accel * window->GetDeltaTime()->asSeconds();
	MaxVelocity();
	m_pos += m_vel * window->GetDeltaTime()->asSeconds();
	m_sprite.setPosition(m_pos);
}

//
void GameObjects::SetVelocity(float velAmount)
{

}

//GameObjects version Function to set an objects velocity and its max possible velocity 
void GameObjects::MaxVelocity()
{
	// set the speed by getting the square root of an objects velocity vector
	float l_speed = sqrt(m_vel.x * m_vel.x + m_vel.y * m_vel.y);

	if (l_speed <= 0.1)
	{
		return;
	}
	// Normalized the objects velocity by dividing the objects velocity by the speed
	sf::Vector2f l_normalizedVel = sf::Vector2f(m_vel.x / l_speed, m_vel.y / l_speed);

	if (l_speed > 500)
	{
		l_speed = 500;
	}

	// Set the objects velocity in a given direction by multiplying the normalized velocity to its speed
	m_vel.x = l_normalizedVel.x * l_speed;
	m_vel.y = l_normalizedVel.y * l_speed;
}

//GameObject's version to apply some drag to objects movements when no acceleration
void GameObjects::ApplyDrag(float dt)
{
	if (m_accel.x == 0.0f && m_accel.y == 0.0f)
	{
		float dragAmount = dt* 0.9f;
		m_vel.x -= dragAmount * m_vel.x;
		m_vel.y -= dragAmount * m_vel.y;
	}
}

//GameObjects version
void GameObjects::SetAccel(float accelVal)
{

}

//GameObjects function checking if object is going out of window
//Redefined in Player
//GameObjects version allows objects comeout of the other side
void GameObjects::OutOfBounds(Window* window)
{
	if (m_pos.x < 0)
	{
		m_pos.x = window->GetWindowSize()->x;
	}
	else if (m_pos.x > window->GetWindowSize()->x)
	{
		m_pos.x = 0;
	}
	if (m_pos.y < 0)
	{
		m_pos.y = window->GetWindowSize()->y;
	}
	else if (m_pos.y > window->GetWindowSize()->y)
	{
		m_pos.y = 0;
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
bool GameObjects::IsColliding(const GameObjects* otherObj) const
{
	bool l_result = false;
	if (this != otherObj && !IsDestroyed() && !otherObj->IsDestroyed() && GetDistance(otherObj->m_pos) < (m_collisionRadius + otherObj->m_collisionRadius))
	{
		l_result = true;
	}
	return l_result;
}


/*********************************************************************
***************PLAYER CLASS : DERIVED FROM GAMEOBJECT*****************
*********************************************************************/

void Player::Draw(Window* window)
{
	GameObjects::Draw(window);
}

//A virtual function:: Base version of all Player classes, 
void Player::Update(Window* window)
{
	GameObjects::Update(window);
}

void Player::CollidedWith(GameObjects* object)
{

}

void Player::MakeInvulnerable()
{

}

//SS_Player Constructor 
//Needs texture address and initial position to initialize player sprite
SS_Player::SS_Player(const std::string texturePath, const sf::Vector2f & pos)
	:Player(texturePath, pos)
	, m_playerHealth(100.0f)
{
	m_shootCooldown = 0.2f;
	m_shooting = false;
	SetCollisionRadius(45.0f);
	m_sprite.setScale(0.1f, 0.1f);
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.65f);
}

//SS_Player virtual destructor
SS_Player::~SS_Player()
{
	std::cout << "SS_Player's Destructor called" << std::endl;
}

//SS_Player version Draw function
void SS_Player::Draw(Window* window)
{
	Player::Draw(window);  

}

//SS_Player version Update Function to update player ship state
void SS_Player::Update(Window* window)
{
	Player::Update(window);
	SetAccel(0.0f);
	OutOfBounds(window);
	PlayerControls(window);
	
}

void SS_Player::CollidedWith(GameObjects* object)
{
	Enemy* l_enemy = dynamic_cast<Enemy*>(object);
	if (l_enemy)
	{
		if (m_playerHealth > l_enemy->GetDmgVal())
		{
			//Deal damage to health
			m_playerHealth - l_enemy->GetDmgVal();
			l_enemy->Destroy();
		}
		else
		{
			Destroy();
		}
	}
}

//SS_player version to accelerate player forward or backward
void SS_Player::SetAccel(float accelVal)
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

//SS_Player version of ApplyDrag is redefined to decelerate the player
void SS_Player::ApplyDrag(float dt)
{
	if (m_accel.x == 0.0f && m_accel.y == 0.0f)
	{
		float l_decelerate = dt * 10.0f;
		m_vel.x -= l_decelerate* m_vel.x;
		m_vel.y -= l_decelerate* m_vel.y;
	}
}

//SS_Player version to prevent player from going out of window in the Y direction
//Allow player to loop in the X direction
void SS_Player::OutOfBounds(Window* window)
{
	if (m_pos.x < 0.0f)
	{
		m_pos.x = window->GetWindowSize()->x;
	}
	else if (m_pos.x > window->GetWindowSize()->x)
	{
		m_pos.x = 0.0f;
	}
	if (m_pos.y < 50.0f)
	{
		m_pos.y = 50.0f;
	}
	else if (m_pos.y > window->GetWindowSize()->y - 50.0f)
	{
		m_pos.y = window->GetWindowSize()->y - 50.0f;
	}
}

//SS_player version that take uses player input to move player ship
//If no input is pressed call SS_Player version's ApplyDrag
void SS_Player::PlayerControls(Window* window)
{
	m_shooting = false;
	m_shootCooldown -= window->GetDeltaTime()->asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{

		SetAccel(200);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		SetAccel(-200);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		SetSideAccel(-200);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		SetSideAccel(200);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//TODO call shoot function
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		//TODO call swith weapon function
	}
	else
	{
		ApplyDrag(window->GetDeltaTime()->asSeconds());
		
	}
}

//SS_Player version shoot bullets based on which weapon type equipped
void SS_Player::ShootFunction()
{
	//TODO TRY IT OUT NOT TESTES
	if (m_shooting && m_shootCooldown <= 0.0f)
	{
		FastBullet* l_fastBullet1 = new FastBullet("TODO PUT BULLET SPRITE ADDRESS", sf::Vector2f(m_pos.x + 0.1f, m_pos.y));
		FastBullet* l_fastBullet2 = new FastBullet("TODO PUT BULLET SPRITE ADDRESS", sf::Vector2f(m_pos.x - 0.1f, m_pos.y));
		l_fastBullet1->SetVelocity(1000);
		l_fastBullet2->SetVelocity(1000);
		m_owner->AddObject(l_fastBullet1);
		m_owner->AddObject(l_fastBullet2);
	
		
	}
}

void SS_Player::MakeInvulnerable()
{

}

//SS_Player Main Functions

//SS_player only function to accelerate player Left or Right
void SS_Player::SetSideAccel(float accelVal)
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

