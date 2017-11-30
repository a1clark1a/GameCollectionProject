#include "Game.h"
#include "GameObjects.h"
#include "Bullets.h"
#include "Enemy.h"
#include "Player.h"

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
		m_owner->SetScore(enemy->GetScoreVal());
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
	else if (m_pos.y > window->GetWindowSize()->y - 220.0f)
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
	m_collisionBox->setOrigin(m_collisionSize.x * 0.5f, m_collisionSize.y * 0.5f);
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
