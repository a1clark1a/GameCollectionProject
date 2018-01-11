#include "Enemy.h"

/*********************************************************************
****************ENEMY CLASS : DERIVED FROM GAMEOBJECTS****************
*********************************************************************/

//Enemy version when player collides with an enemy object, if player health > 0 then player takes dmg else destroy
void Enemy::CollidedWith(GameObjects* object)
{
	Player* l_player = dynamic_cast<Player*>(object);
	if (l_player && l_player->GetInvincibilityCD() < 0.0f)
	{
		l_player->Destroy();
		Destroy();
	}
}

void Enemy::TakeDamage(const float dmgVal)
{

	if (m_enemyHealth >= dmgVal)
	{
		m_enemyHealth -= dmgVal;
		if (m_enemyHealth <= 0.0f)
		{
			SetScore();
			Destroy();
		}
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

//Spawn ammo from killing AI;
void Enemy::Destroy()
{
	bool l_shouldSpawnAmmo = rand() % 2 == 0 ? true : false;
	if (l_shouldSpawnAmmo)
	{
		Item* l_item;
		int l_randNum = rand() % 4;
		switch (l_randNum)
		{
		case 0:
			l_item = new QuadAmmo(m_pos);
			m_owner->AddObject(l_item);
			break;
		case 1:
			l_item = new PowerAmmo(m_pos);
			m_owner->AddObject(l_item);
			break;
		default:
			l_randNum = 0;
			break;
		}
	}
	else
	{
		Item* l_item;
		int l_randNum = rand() % 13;					//A chance to spawn a coin
		switch (l_randNum)
		{
		case 0:
			l_item = new GoldCoin(m_pos);
			m_owner->AddObject(l_item);
			break;
		case 1:
			l_item = new SilverCoin(m_pos);
			m_owner->AddObject(l_item);
			break;
		case 2:
			l_item = new HealthPack(m_pos);
			m_owner->AddObject(l_item);
			break;
		}
	}
	GameObjects::Destroy();
}

/*********************************************************************
********************AI CLASS : DERIVED FROM ENEMY*********************
*********************************************************************/

void AI::Draw(Window* window)
{
	GameObjects::Draw(window);
	DrawHealthBar(window);
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

void AI::DrawHealthBar(Window* window)
{
	m_enemyHealthBar->setPosition(m_pos.x - m_sprite.getOrigin().x * 0.5f, m_pos.y - m_sprite.getOrigin().y);
	m_enemyHealthBar->setOrigin(0, m_enemyHealthBar->getLocalBounds().height * 0.5f);
	m_enemyHealthBar->setSize(sf::Vector2f((m_enemyHealth / m_maxHealth) * 100.0f, 20.0f));
	m_enemyHealthBar->setScale(1 * m_sprite.getScale().x, 0.5f * m_sprite.getScale().x);
	m_enemyHealthBar->setFillColor(sf::Color::Red);
	window->DrawThis(m_enemyHealthBar);
}


/*********************************************************************
*****************NORMALAI CLASS : DERIVED FROM AI*********************
*********************************************************************/

NormalAI::NormalAI(const sf::Vector2f & pos)
	:AI("Sprites/Enemies/enemyBlack2.png", pos)
{
	Setup();
}

void NormalAI::Setup()
{
	m_moveInterval = 5.0f;
	m_pauseTimer = 3.0f;
	m_shootingCoolDown = 1.0f;
	SetCollisionRadius(25.0f);
	m_sprite.setScale(0.5f, 0.5f);
	m_moveStates = MOVESTATES::Forward;
	m_maxHealth = 50.0f;
	m_scoreVal = 100;
	m_enemyHealth = m_maxHealth;
	m_line = static_cast<float>(rand() % 150 + 100);
}

void NormalAI::Update(Window* window)
{
	GameObjects::Update(window);
	VelocityLimiter(100.0f);
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
	Setup();
}

void AggroAI::Setup()
{
	m_maxHealth = 50.0f;
	m_scoreVal = 150;
	m_enemyHealth = m_maxHealth;
	m_moveInterval = 2.0f;
	SetCollisionRadius(25.0f);
	m_sprite.setScale(0.5f, 0.5f);
	m_toggle = rand() % 2 == 0 ? 1 : -1;
}

void AggroAI::Update(Window* window)
{
	GameObjects::Update(window);
	VelocityLimiter(100.0f);
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
			m_moveStates = MOVESTATES::Forward;
		}
	}
}


/*********************************************************************
*******************CHASERAI CLASS : DERIVED FROM AI********************
*********************************************************************/

ChaserAI::ChaserAI(const sf::Vector2f & pos)
	:AI("Sprites/Enemies/ufoYellow.png", pos)
{
	Setup();
}

void ChaserAI::Setup()
{
	SetCollisionRadius(30.0f);
	m_sprite.setScale(0.5f, 0.5f);
	m_dmgVal = 10.0f;
	m_destroyDelay = 2.0f;
	m_maxHealth = 20.0f;
	m_enemyHealth = m_maxHealth;
	m_scoreVal = 150;
	m_rotationRate = static_cast<float>(rand() % 45 + 45);				// between 45 - 90
	m_rotationRate *= rand() % 2 == 0 ? 1 : -1;							// chooses if its negative or positive
	
}

void ChaserAI::Update(Window* window)
{
	m_angle += m_rotationRate * window->GetDeltaTime()->asSeconds();
	GameObjects::Update(window);
	VelocityLimiter(200.0f);
	OutOfBounds(window);
}

void ChaserAI::OutOfBounds(Window* window)
{
	if (m_pos.x < 0.0f)
	{
		m_pos.x = window->GetWindowSize()->x;
	}
	else if (m_pos.x > window->GetWindowSize()->x)
	{
		m_pos.x = 0.0f;
	}
	if (m_pos.y > window->GetWindowSize()->y)
	{
		m_destroyDelay -= window->GetDeltaTime()->asSeconds();
		if (m_destroyDelay <= 0.0f)
		{
			Destroy();
		}
	}
}

void ChaserAI::SetTarget(SS_Player* player)
{

	float l_speed = 100.0f;
	sf::Vector2f l_vecDiff = player->GetPlayerPos() - m_pos;
	float l_dist = sqrt(l_vecDiff.x * l_vecDiff.x + l_vecDiff.y * l_vecDiff.y);
	sf::Vector2f l_direction = sf::Vector2f(l_vecDiff.x / l_dist, l_vecDiff.y / l_dist);
	m_vel.x = l_direction.x * l_speed;
	m_vel.y = l_direction.y * l_speed;

}

/*********************************************************************
****************ASTEROID CLASS : DERIVED FROM ENEMY*******************
*********************************************************************/
Asteroid::Asteroid(const std::string texturePath, const sf::Vector2f & pos)
	:Enemy(texturePath, pos)
{
	Setup();
}

void Asteroid::Update(Window* window)
{
	m_angle += m_rotationRate * window->GetDeltaTime()->asSeconds();	//continously rotate an asteroid by rotation rate * time
	GameObjects::Update(window);
	Enemy::OutOfBounds(window);
	VelocityLimiter(500);

}

void Asteroid::Setup()
{
	m_destroyDelay = 2.0f;
	m_rotationRate = static_cast<float>(rand() % 45 + 45);				// between 45 - 90
	m_rotationRate *= rand() % 2 == 0 ? 1 : -1;							// chooses if its negative or positive
	SetLinearAccel(-10.0f);
}

/*********************************************************************
*************LARGE ASTEROID CLASS : DERIVED FROM ASTEROID*************
*********************************************************************/

LargeAsteroid::LargeAsteroid(const sf::Vector2f & pos)
	:Asteroid("Sprites/Meteors/meteorBrown_big4.png", pos)
{
	Setup();
}

void LargeAsteroid::Destroy()
{
	for (int i = 0; i < 3; i++)
	{
		MediumAsteroid* mediumAsteroid = new MediumAsteroid(m_pos);
		mediumAsteroid->SetAngle(static_cast<float>(rand() % 360));
		mediumAsteroid->SetVelocity(100.0f);
		m_owner->AddObject(mediumAsteroid);
	}
	GameObjects::Destroy();
}

void LargeAsteroid::Setup()
{
	m_dmgVal = 15.0f;
	m_scoreVal = 10;
	SetCollisionRadius(50);
}

/*********************************************************************
*************MEDIUM ASTEROID CLASS : DERIVED FROM ASTEROID************
*********************************************************************/
MediumAsteroid::MediumAsteroid(const sf::Vector2f & pos)
	:Asteroid("Sprites/Meteors/meteorBrown_med3.png", pos)
{
	Setup();
}

void MediumAsteroid::Destroy()
{
	for (int i = 0; i < 3; i++)
	{
		SmallAsteroid* smallAsteroid = new SmallAsteroid(m_pos);
		smallAsteroid->SetAngle(static_cast<float>(rand() % 360));
		smallAsteroid->SetVelocity(100.0f);
		m_owner->AddObject(smallAsteroid);
	}
	GameObjects::Destroy();
}

void MediumAsteroid::Setup()
{
	m_dmgVal = 10.0f;
	m_scoreVal = 50;
	SetCollisionRadius(20);
}

/*********************************************************************
**************SMALL ASTEROID CLASS : DERIVED FROM ASTEROID************
*********************************************************************/

SmallAsteroid::SmallAsteroid(const sf::Vector2f & pos)
	:Asteroid("Sprites/Meteors/meteorBrown_tiny1.png", pos)
{
	Setup();
}

void SmallAsteroid::Setup()
{
	m_dmgVal = 5.0f;
	m_scoreVal = 100;
	SetCollisionRadius(10);
}

void SmallAsteroid::Destroy()
{
	Enemy::Destroy();
}