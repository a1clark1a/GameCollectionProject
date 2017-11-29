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
void GameObjects::MaxVelocity(const float & maxSpeed)
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
	MaxVelocity(500);
}

void Player::CollidedWith(GameObjects* object)
{

}

void Player::MakeInvulnerable()
{

}

//Player version of TakeDmg 
void Player::TakeDmg(const float & dmgVal)
{
	if (m_playerHealth > 0.0f)
	{
		m_playerHealth -= dmgVal;
	}
	else
	{
		Destroy();
	}
}

/*********************************************************************
***************BULLET CLASS : DERIVED FROM GAMEOBJECT*****************
*********************************************************************/

//Bullet version's Update that calls GameObject's update and decreases a bullets lifetime overtime
void Bullet::Update(Window* window)
{
	GameObjects::Update(window);
	MaxVelocity(500);
	m_lifeTime -= window->GetDeltaTime()->asSeconds();
	if (m_lifeTime <= 0.0f)
	{
		Destroy();
	}
	OutOfBounds(window);
}

void Bullet::DealDmg(GameObjects* object)
{
	Enemy* enemy = dynamic_cast<Enemy*>(object);
	if (enemy->GetEnemyHealth() > 0.0f)
	{
		enemy->TakeDamage(m_dmgVal);
		Destroy();
	}
	else
	{
		enemy->Destroy();
		Destroy();
	}
}

void Bullet::OutOfBounds(Window* window)
{
	if (m_pos.x < 0.0f)
	{
		Destroy();
	}
	else if (m_pos.x > window->GetWindowSize()->x)
	{
		Destroy();
	}
	if (m_pos.y < 0.0f)
	{
		Destroy();
	}
	else if (m_pos.y > window->GetWindowSize()->y)
	{
		Destroy();
	}
}

/*********************************************************************
***************FASTBULLET CLASS : DERIVED FROM BULLET*****************
*********************************************************************/

FastBullet::FastBullet(const sf::Vector2f & pos, const float & dmgVal, const float & vel)
	:Bullet("Sprites/Effects/Lasers/laserBlue01.png", pos, dmgVal)
	
{
	m_lifeTime = 3.0f;
	m_collisionRadius = 5.f;
	m_sprite.scale(0.5f, 0.5f);
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.35f);
	SetVelocity(vel);
}

//FastBullet version that calls Bullets update and checks for FastBullets lifetime
void FastBullet::Update(Window* window)
{
	Bullet::Update(window);
}

//FastBullet's version that takes a collided object and checks if its an enemy
void FastBullet::CollidedWith(GameObjects* object)
{
	
	Enemy* l_enemy = dynamic_cast<Enemy*>(object);
	if(l_enemy)
	{
		Asteroid* l_asteroid = dynamic_cast<Asteroid*>(object);
		if (l_asteroid)
		{
			object->Destroy();
			Destroy();
		}
		else
		{
			DealDmg(l_enemy);
			Destroy();
		}
	}
}

/*********************************************************************
***************LASERBULLET CLASS : DERIVED FROM BULLET*****************
*********************************************************************/
LaserBullet::LaserBullet(const sf::Vector2f & pos, const float & dmgVal)
	:Bullet("TODO ADD BULLET SPRITE ADDRESS", pos, dmgVal)
{
	
}

LaserBullet::~LaserBullet()
{
	std::cout << "LaserBullet Destructor Called" << std::endl;
	delete m_collisionBox;
}

void LaserBullet::Draw(Window* window)
{
	m_collisionBox->setSize(m_collisionSize);
	m_collisionBox->setOrigin(m_collisionSize.x * 0.5f,m_collisionSize.y * 0.5f);
	m_collisionBox->setPosition(m_pos);
	m_collisionBox->setFillColor(sf::Color::Transparent);
	m_collisionBox->setOutlineThickness(2.0f);
	m_collisionBox->setOutlineColor(sf::Color::Red);
	window->DrawThis(m_collisionBox);
	window->DrawThis(&m_sprite);

}

void LaserBullet::Update(Window* window)
{
	Bullet::Update(window);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_lifeTime = 2.0f;
	}
	else
	{
		m_lifeTime -= window->GetDeltaTime()->asSeconds();
	}

}

void LaserBullet::CollidedWith(GameObjects* object)
{
	Enemy* l_enemy = dynamic_cast<Enemy*>(object);
	if (l_enemy)
	{
		Asteroid* l_asteroid = dynamic_cast<Asteroid*>(l_enemy);
		if (l_asteroid)
		{
			object->Destroy();
			Destroy();
		}
		else
		{
			DealDmg(l_enemy);
		}
	}
}

void LaserBullet::Destroy()
{
	//TODO make the sprite slowly vanish before calling Destroy
	Bullet::Destroy();
}

EnemyBullet::EnemyBullet(const sf::Vector2f & pos, const float & dmgVal, const float & vel)
	:Bullet("Sprites/Effects/Lasers/laserBlue01.png", pos, dmgVal)
{
	SetLinearAccel(vel);
	m_dmgVal = 10.0f;
	m_lifeTime = 2.0f;
	m_collisionRadius = 5.f;
	m_sprite.scale(0.5f, 0.5f);
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.35f);
}

void EnemyBullet::CollidedWith(GameObjects* object)
{
	Player* l_player = dynamic_cast<Player*>(object);
	if (l_player)
	{
		if (l_player->GetPlayerHealth() <= 0.0f)
		{
			l_player->Destroy();
			Destroy();
			
		}
		else
		{
			std::cout << "called" << std::endl;
			l_player->TakeDmg(m_dmgVal);
			Destroy();
		}
	}
}

/*********************************************************************
***************SS_PLAYER CLASS : DERIVED FROM PLAYER******************
*********************************************************************/

//SS_Player Constructor 
//Needs texture address and initial position to initialize player sprite
SS_Player::SS_Player()
	:Player("Sprites/TopDownShips/ship2.png", sf::Vector2f(400.0f, 400.0f))
{
	m_playerHealth = 100.0f;
	m_shootCooldown = 0.2f;
	m_shooting = false;
	m_collisionRadius = 45.0f;
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
	SetLinearAccel(0.0f);
	OutOfBounds(window);
	PlayerControls(window);
}

//SS_Player version that calls GameObjects Destroy then resets player spawntime
void SS_Player::Destroy()
{
	GameObjects::Destroy();
	m_owner->ResetSpawnTimer();
}

//SS_Player version that checks if an enemy collides to player then destroy if health < enemy dmg
void SS_Player::CollidedWith(GameObjects* object)
{

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
		SetLinearAccel(1000);
		//TEST
		if (m_shootCooldown <= 0.0f)
		{
			//NormalAI* test = new NormalAI(sf::Vector2f(static_cast<float>(rand() % 700 + 200), -50.0f));
			//AggroAI* test2 = new AggroAI(sf::Vector2f(400.0f, 50.0f));
			//m_owner->AddObject(test);
			//m_owner->AddObject(test2);
			FastAI* test3 = new FastAI(sf::Vector2f(400.0f, 350.0f));
			m_owner->AddObject(test3);
			m_shootCooldown = 0.5f;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		SetLinearAccel(-200);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		SetSideAccel(-200);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		SetSideAccel(200);
		//TEST
		//LargeAsteroid* test = new LargeAsteroid(sf::Vector2f(static_cast<float>(rand() % 400),50.0f));
		//m_owner->AddObject(test);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_shooting = true;
		ShootFunction();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_currentWeap = WEAPONTYPE::Fast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_currentWeap = WEAPONTYPE::Laser;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_currentWeap = WEAPONTYPE::Power;
	}
	else
	{
		ApplyDrag(window->GetDeltaTime()->asSeconds(), 10.0f);
		
	}
	
}

//SS_Player version shoot bullets based on which weapon type equipped
void SS_Player::ShootFunction()
{
	switch(m_currentWeap)
	{ 
	case WEAPONTYPE::Fast:
		if (m_shooting && m_shootCooldown <= 0.0f)
		{
			
			FastBullet* l_fastBullet1 = new FastBullet(sf::Vector2f(m_pos.x + 30.0f, m_pos.y - 30), 10.0f, 500.0f);
			FastBullet* l_fastBullet2 = new FastBullet(sf::Vector2f(m_pos.x - 30.0f, m_pos.y - 30), 10.0f, 500.0f);
			m_owner->AddObject(l_fastBullet1);
			m_owner->AddObject(l_fastBullet2);
			m_shootCooldown = 0.1f;
			break;
		}

	case WEAPONTYPE::Laser:
		if (m_shooting && m_shootCooldown <= 0.0f)
		{
			//TODO shoot laser
			break;
		}

	case WEAPONTYPE::Power:
		if (m_shooting && m_shootCooldown <= 0.0f)
		{
			//TODO shoot Power
			break;
		}

	default: m_currentWeap = WEAPONTYPE::Fast;
		break;


	}
}

void SS_Player::MakeInvulnerable()
{

}

//SS_Player Main Functions



/*********************************************************************
****************ENEMY CLASS : DERIVED FROM GAMEOBJECTS****************
*********************************************************************/

//Enemy version when player collides with an enemy object, if player health > 0 then player takes dmg else destroy
void Enemy::CollidedWith(GameObjects* object)
{
	Player* l_player = dynamic_cast<Player*>(object);
	if (l_player)
	{
		if (l_player->GetPlayerHealth() > 0)
		{
			//Player takes damage 
			l_player->TakeDmg(m_dmgVal);
			Destroy();
			
		}
		else
		{
			l_player->Destroy();
		}
	}
}

void Enemy::TakeDamage(const float dmgVal)
{
	
	if (m_enemyHealth > 0.0f)
	{
		m_enemyHealth -= dmgVal;
	}
	else
	{
		Destroy();
	}
}

//Enemy version checking when an Enemy objects goes out of the window
void Enemy::OutOfBounds(Window* window)
{
	
	if (m_pos.x < 0.0f)
	{
		m_pos.x = window->GetWindowSize()->x;
	}
	else if (m_pos.x > window->GetWindowSize()->x)
	{
		m_pos.x = 0.0f;
	}
	else if (m_pos.y > window->GetWindowSize()->y)
	{
		//Once an Enemy objects goes out of the window in the positive Y direction destroy it after l_delay reaches 0
		m_destroyDelay -= window->GetDeltaTime()->asSeconds();
		if (m_destroyDelay <= 0.0f)
		{
			Destroy();
		}
	}
	else if (m_pos.y < 0.0f)
	{
		//Once an Enemy objects goes out of the window in the negative Y direction change its velocity to a positive value after l_delay reaches 0
		m_destroyDelay -= window->GetDeltaTime()->asSeconds();
		if (m_destroyDelay <= 0.0f)
		{
			SetLinearAccel(-100.0f);
		}
	}
}

/*********************************************************************
********************AI CLASS : DERIVED FROM ENEMY*********************
*********************************************************************/

void AI::Draw(Window* window)
{
	GameObjects::Draw(window);
	//TODO draw health bar here
}

void AI::Behavior(const float & dt)
{
	switch (m_aiStates)
	{
	case AISTATES::Moving:
		Move(dt);
		break;
	case AISTATES::Shooting:
		ShootFunction(dt);
		break;
	}
}

/*********************************************************************
*****************NORMALAI CLASS : DERIVED FROM AI*********************
*********************************************************************/

NormalAI::NormalAI(const sf::Vector2f & pos)
	:AI("Sprites/Enemies/enemyBlack2.png", pos)
{
	m_moveInterval = 5.0f;
	m_pauseTimer = 3.0f;
	m_shootingCoolDown = 1.0f;
	SetCollisionRadius(25.0f);
	m_sprite.setScale(0.5f, 0.5f);
	m_moveStates = MOVESTATES::Forward;
	m_enemyHealth = 50.0f;
	m_line = static_cast<float>(rand() % 150 + 100);
}

void NormalAI::Update(Window* window)
{
	GameObjects::Update(window);
	MaxVelocity(100.0f);
	Behavior(window->GetDeltaTime()->asSeconds());
	OutOfBounds(window);
}

void NormalAI::OutOfBounds(Window* window)
{
	
	if (m_pos.y > m_line && m_moveStates == MOVESTATES::Forward)
	{
		SetLinearAccel(0.0f);
		m_vel.y = 0.0f;
		m_moveStates = rand() % 2 == 0 ? MOVESTATES::Left : MOVESTATES::Right;
	}
	else if (m_pos.y < 0.0f)
	{
		SetLinearAccel(-50.0f);
	}

	if (m_pos.x < 50.0f)
	{
		m_pos.x = 50.0f;
		m_vel.x = 0.0f;
		m_moveStates = MOVESTATES::Right;
	}
	else if (m_pos.x > window->GetWindowSize()->x - 50.0f)
	{
		m_pos.x = window->GetWindowSize()->x - 50.0f;
		m_vel.x = 0.0f;
		m_moveStates = MOVESTATES::Left;
	}
	else if (m_pos.y > window->GetWindowSize()->y)
	{
		//Once an Enemy objects goes out of the window in the positive Y direction destroy it after l_delay reaches 0
		m_destroyDelay -= window->GetDeltaTime()->asSeconds();
		if (m_destroyDelay <= 0.0f)
		{
			Destroy();
		}
	}
}

void NormalAI::Move(const float & dt)
{
	m_moveInterval -= dt;
	if (m_moveInterval <= 0)
	{
		m_moveStates = MOVESTATES::Pause;
	}
	switch (m_moveStates)
	{
	case MOVESTATES::Left:
			SetSideAccel(-10.0f);
			break;
		
	case MOVESTATES::Right:
			SetSideAccel(10.0f);
			break;
	case MOVESTATES::Pause:
			m_pauseTimer = 3.0f;
			SetSideAccel(0.0f);
			m_vel.x = 0.0f;
			m_aiStates = AISTATES::Shooting;
			m_moveInterval = 5.0f;
			break;
	case MOVESTATES::Forward:
			break;
	}

}

void NormalAI::ShootFunction(const float & dt)
{
	if (m_aiStates == AISTATES::Shooting)
	{
		m_shootingCoolDown -= dt;
		m_pauseTimer -= dt;
		if (m_pauseTimer > 0.0f)
		{
			if (m_shootingCoolDown <= 0.0f)
			{
				EnemyBullet* l_eBullet = new EnemyBullet(m_pos, m_dmgVal, -200.0f);
				m_owner->AddObject(l_eBullet);
				m_shootingCoolDown = 2.0f;
			}

		}
		else
		{
			std::cout << "This triggered: " << std::endl;
			m_aiStates = AISTATES::Moving;
			m_moveStates = rand() % 2 == 0 ? MOVESTATES::Right : MOVESTATES::Left;
		}
	}
}

/*********************************************************************
*******************AGGROAI CLASS : DERIVED FROM AI********************
*********************************************************************/
AggroAI::AggroAI(const sf::Vector2f & pos)
	:AI("Sprites/Enemies/enemyGreen1.png", pos)
{
	//SETUP here
	m_enemyHealth = 50.0f;
	m_moveInterval = 2.0f;
	SetCollisionRadius(25.0f);
	m_sprite.setScale(0.5f, 0.5f);
	m_toggle = rand() % 2 == 0 ? 1 : -1;
}

void AggroAI::Update(Window* window)
{
	GameObjects::Update(window);
	MaxVelocity(100.0f);
	Behavior(window->GetDeltaTime()->asSeconds());
	OutOfBounds(window);
}

void AggroAI::OutOfBounds(Window* window)
{
	if (m_pos.x < 100.0f)
	{
		m_vel.x = 0.f;
		m_moveStates = MOVESTATES::Right;
	}
	else if (m_pos.x > window->GetWindowSize()->x - 100.0f)
	{
		m_vel.x = 0.f;
		m_moveStates = MOVESTATES::Left;
	}
	if (m_pos.y > window->GetWindowSize()->y)
	{
		m_destroyDelay -= window->GetDeltaTime()->asSeconds();
		if (m_destroyDelay <= 0.0f)
		{
			Destroy();
		}
	}
	else
	{
		m_moveStates = MOVESTATES::Forward;
	}
}

void AggroAI::SetLinearAccel(const float & accelVal_x, const float & accelVal_y)
{
	if (accelVal_x != 0 && accelVal_y != 0)
	{
		m_accel = sf::Vector2f(10.0f * accelVal_x, 10.0f * -accelVal_y);
	}
	else
	{
		m_accel = sf::Vector2f(0.0f, 0.0f);
	}
}

void AggroAI::Move(const float & dt)
{
	m_moveInterval -= dt;
	if (m_moveInterval <= 0)
	{
		m_moveStates = MOVESTATES::Pause;
	}
	switch (m_moveStates)
	{
	case MOVESTATES::Left:
		SetLinearAccel(-15.0f, -5.0f);
		break;
	case MOVESTATES::Right:
		SetLinearAccel(15.0f, -5.0f);
		break;
	case MOVESTATES::Pause:
		m_pauseTimer = 3.0f;
		m_vel = (sf::Vector2f(0.0f, 0.0f));
		SetLinearAccel(0.0f, 0.0f);
		m_aiStates = AISTATES::Shooting;
		m_moveInterval = 2.0f;
		break;
	case MOVESTATES::Forward:
		SetLinearAccel(15.0f * m_toggle, -5.0f);
		break;

	}
}

void AggroAI::ShootFunction(const float & dt)
{
	if (m_aiStates == AISTATES::Shooting)
	{
		m_shootingCoolDown -= dt;
		m_pauseTimer -= dt;
		if (m_pauseTimer > 0.0f)
		{
			if (m_shootingCoolDown <= 0.0f)
			{
				EnemyBullet* l_eBullet = new EnemyBullet(m_pos, m_dmgVal, -200.0f);
				m_owner->AddObject(l_eBullet);
				m_shootingCoolDown = 2.0f;
			}

		}
		else
		{
			m_toggle = rand() % 2 == 0 ? 1 : -1;
			m_aiStates = AISTATES::Moving;
			m_moveStates =MOVESTATES::Forward;
		}
	}
}

/*********************************************************************
*******************FASTAI CLASS : DERIVED FROM AI********************
*********************************************************************/

FastAI::FastAI(const sf::Vector2f & pos)
	:AI("Sprites/Enemies/enemyRed1.png", pos)
{
	//TODO Setup here
	//SetAccel(100.0f);
}

void FastAI::Update(Window* window)
{
	GameObjects::Update(window);
	OutOfBounds(window);
	
}

void FastAI::OutOfBounds(Window* window)
{
	
}

void FastAI::Move(const float & dt)
{
	//TEST
	
}

void FastAI::SetTarget(SS_Player* player)
{
	float l_speed = 100.0f;
	//float l_pDist = GetDistance(player->GetPlayerPos());
	//sf::Vector2f direction = sf::Vector2f(m_vel.x / l_pDist, m_vel.y / l_pDist);
	sf::Vector2f vecdiff = player->GetPlayerPos() - m_pos;
	float dist = sqrt(vecdiff.x * vecdiff.x + vecdiff.y * vecdiff.y);
	sf::Vector2f direction = sf::Vector2f(vecdiff.x / dist, vecdiff.y / dist);
	m_vel.x = direction.x * l_speed;
	m_vel.y = direction.y *l_speed;
}

/*********************************************************************
****************ASTEROID CLASS : DERIVED FROM ENEMY*******************
*********************************************************************/
Asteroid::Asteroid(const std::string texturePath, const sf::Vector2f & pos)
	:Enemy(texturePath, pos)
{
	m_destroyDelay = 2.0f;
	m_rotationRate = static_cast<float>(rand() % 45 + 45);				// between 45 - 90
	m_rotationRate *= rand() % 2 == 0 ? 1 : -1;							// chooses if its negative or positive
	SetLinearAccel(-10.0f);
}

void Asteroid::Update(Window* window)
{
	m_angle += m_rotationRate * window->GetDeltaTime()->asSeconds();	//continously rotate an asteroid by rotation rate * time
	GameObjects::Update(window);
	Enemy::OutOfBounds(window);
	MaxVelocity(500);
	
}

/*********************************************************************
*************LARGE ASTEROID CLASS : DERIVED FROM ASTEROID*************
*********************************************************************/

LargeAsteroid::LargeAsteroid(const sf::Vector2f & pos)
	:Asteroid("Sprites/Meteors/meteorBrown_big4.png", pos)
{
	m_dmgVal = 15.0f;
	m_scoreVal = 10;
	SetCollisionRadius(50);
}

void LargeAsteroid::Destroy()
{
	
	m_owner->SetScore(m_scoreVal);
	for (int i = 0; i < 3; i++)
	{
		MediumAsteroid* mediumAsteroid = new MediumAsteroid(m_pos);
		mediumAsteroid->SetAngle(static_cast<float>(rand() % 360));
		mediumAsteroid->SetVelocity(100.0f);
		m_owner->AddObject(mediumAsteroid);
	}
	GameObjects::Destroy();
}

/*********************************************************************
*************MEDIUM ASTEROID CLASS : DERIVED FROM ASTEROID************
*********************************************************************/

MediumAsteroid::MediumAsteroid(const sf::Vector2f & pos)
	:Asteroid("Sprites/Meteors/meteorBrown_med3.png", pos)
{
	m_dmgVal = 10.0f;
	m_scoreVal = 50;
	SetCollisionRadius(20);
}

void MediumAsteroid::Destroy()
{
	m_owner->SetScore(m_scoreVal);
	for (int i = 0; i < 3; i++)
	{
		SmallAsteroid* smallAsteroid = new SmallAsteroid(m_pos);
		smallAsteroid->SetAngle(static_cast<float>(rand() % 360));
		smallAsteroid->SetVelocity(100.0f);
		m_owner->AddObject(smallAsteroid);
	}
	GameObjects::Destroy();
}

/*********************************************************************
**************SMALL ASTEROID CLASS : DERIVED FROM ASTEROID************
*********************************************************************/

SmallAsteroid::SmallAsteroid(const sf::Vector2f & pos)
	:Asteroid("Sprites/Meteors/meteorBrown_tiny1.png", pos)
{
	m_dmgVal = 5.0f;
	m_scoreVal = 100;
	SetCollisionRadius(10);
}

