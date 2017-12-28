#include "Bullets.h"

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

//Bullet version's OutOfBounds when bullet goes out of window call Destroy
void Bullet::OutOfBounds(Window* window)
{
	if (m_pos.x < -1.0f)
	{
		Destroy();
	}
	else if (m_pos.x > window->GetWindowSize()->x + 1.0f)
	{
		Destroy();
	}
	if (m_pos.y < -1.0f)
	{
		Destroy();
	}
	else if (m_pos.y > window->GetWindowSize()->y + 1.0f)
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
	SetVelocity(vel);
	Setup();
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
	if (l_enemy)
	{
		Asteroid* l_asteroid = dynamic_cast<Asteroid*>(object);
		if (l_asteroid)
		{
			object->Destroy();
			Destroy();
		}
		else
		{
			l_enemy->TakeDamage(m_dmgVal);
			Destroy();
		}
	}
}

void FastBullet::Setup()
{
	m_lifeTime = 3.0f;
	m_collisionRadius = 5.f;
	m_sprite.scale(0.5f, 0.5f);
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.35f);
}

/*********************************************************************
***************QUADBULLET CLASS : DERIVED FROM BULLET*****************
*********************************************************************/
QuadBullets::QuadBullets(const sf::Vector2f & pos, const float & dmgVal)
	:Bullet("Sprites/Effects/Lasers/laserBlue08.png", pos, dmgVal)
{
	Setup();
}


//QuadBullet's version's Update that calls Bullet's update, rotates bullet and decreases a bullets lifetime overtime
void QuadBullets::Update(Window* window)
{
	m_angle += m_rotationRate * window->GetDeltaTime()->asSeconds();
	Bullet::Update(window);
}

//QuadBullet's version that takes a collided object and checks if its an enemy
void QuadBullets::CollidedWith(GameObjects* object)
{
	Enemy* l_enemy = dynamic_cast<Enemy*>(object);
	if (l_enemy)
	{
		Asteroid* l_asteroid = dynamic_cast<Asteroid*>(object);
		if (l_asteroid)
		{
			object->Destroy();
			Destroy();
		}
		else
		{
			l_enemy->TakeDamage(m_dmgVal);
			Destroy();
		}
	}
}

void QuadBullets::Setup()
{
	m_lifeTime = 3.0f;
	m_collisionRadius = 15.0f;
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.5f);
	m_rotationRate = static_cast<float>(rand() % 180 + 180);
	m_rotationRate *= rand() % 2 == 0 ? 1 : -1;
}

/*********************************************************************
***************POWERBOMB CLASS : DERIVED FROM BULLET*****************
*********************************************************************/
PowerBomb::PowerBomb(const std::string texturePath,const sf::Vector2f & pos, const float & dmgVal)
	:Bullet(texturePath, pos, dmgVal) 
{
	Setup();
}

void PowerBomb::CollidedWith(GameObjects* object)
{
	Enemy* l_enemy = dynamic_cast<Enemy*>(object);
	if (l_enemy)
	{
		Asteroid* l_asteroid = dynamic_cast<Asteroid*>(object);
		if (l_asteroid)
		{
			object->Destroy();
			Destroy();
		}
		else
		{
			l_enemy->TakeDamage(m_dmgVal);
			Destroy();
		}
	}
}

void PowerBomb::Destroy()
{
	for (int i = 0; i < 6; i++)
	{
		MediumBomb* l_mediumBomb = new MediumBomb(m_pos, 50.0f);
		l_mediumBomb->SetAngle(static_cast<float>(rand() % 360));
		l_mediumBomb->SetVelocity(200.0f);
		m_owner->AddObject(l_mediumBomb);
	}
	GameObjects::Destroy();
}

void PowerBomb::Setup()
{
	m_angle = -90.0f;
	m_lifeTime = 5.0f;
	m_collisionRadius = 60.0f;
	m_sprite.setOrigin(m_sprite.getTextureRect().width - 50.0f, m_sprite.getTextureRect().height * 0.5f);
}

/*********************************************************************
***************MEDIUMBOMB CLASS : DERIVED FROM BULLET*****************
*********************************************************************/
MediumBomb::MediumBomb(const sf::Vector2f & pos, const float & dmgVal)
	:PowerBomb("Sprites/Effects/Lasers/laserBlue10.png", pos, dmgVal)
{
	Setup();
}

void MediumBomb::Update(Window* window)
{
	m_angle += m_rotationRate * window->GetDeltaTime()->asSeconds();
	Bullet::Update(window);
}

void MediumBomb::Destroy()
{
	for (int i = 0; i < 10; i++)
	{
		SmallBomb* l_smallBomb = new SmallBomb(m_pos, 20.0f);
		l_smallBomb->SetAngle(static_cast<float>(rand() % 360));
		l_smallBomb->SetVelocity(400.0f);
		m_owner->AddObject(l_smallBomb);
	}
	GameObjects::Destroy();
}

void MediumBomb::Setup()
{
	m_lifeTime = 5.0f;
	m_collisionRadius = 20.0f;
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.5f);
	m_rotationRate = static_cast<float>(rand() % 180 + 180);
	m_rotationRate *= rand() % 2 == 0 ? 1 : -1;
}

/*********************************************************************
***************SMALLBOMB CLASS : DERIVED FROM BULLET******************
*********************************************************************/
SmallBomb::SmallBomb(const sf::Vector2f & pos, const float & dmgVal)
	:PowerBomb("Sprites/Effects/Lasers/laserBlue11.png", pos, dmgVal)
{
	Setup();
}

void SmallBomb::Update(Window* window)
{
	m_angle += m_rotationRate * window->GetDeltaTime()->asSeconds();
	Bullet::Update(window);
}

void SmallBomb::Destroy()
{
	GameObjects::Destroy();
}

void SmallBomb::Setup()
{
	m_lifeTime = 5.0f;
	m_sprite.setScale(0.5f, 0.5f);
	m_collisionRadius = 10.0f;
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.5f);
	m_rotationRate = static_cast<float>(rand() % 180 + 180);
	m_rotationRate *= rand() % 2 == 0 ? 1 : -1;
}

/*********************************************************************
***************ENEMYBULLET CLASS : DERIVED FROM BULLET*****************
*********************************************************************/
EnemyBullet::EnemyBullet(const sf::Vector2f & pos, const float & dmgVal, const float & vel)
	:Bullet("Sprites/Effects/Lasers/laserBlue01.png", pos, dmgVal)
{
	SetLinearAccel(vel);
	Setup();
}

void EnemyBullet::CollidedWith(GameObjects* object)
{
	Player* l_player = dynamic_cast<Player*>(object);
	if (l_player && l_player->GetInvincibilityCD() < 0.0f)
	{
		l_player->TakeDmg(m_dmgVal);
		Destroy();
	}
}

void EnemyBullet::Setup()
{
	m_dmgVal = 10.0f;
	m_lifeTime = 2.0f;
	m_collisionRadius = 5.f;
	m_sprite.scale(0.5f, 0.5f);
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.35f);
}