#include "Items.h"

/*********************************************************************
*****************ITEM CLASS : DERIVED FROM GAMEOBJECT*****************
*********************************************************************/
Item::Item(const std::string texturePath, const sf::Vector2f & pos)
	:GameObjects(texturePath, pos)
{
	Setup();
}


//Item's version Update that decreases item lifetime overtime
void Item::Update(Window* window)
{
	m_lifeTime -= window->GetDeltaTime()->asSeconds();
	SetLinearAccel(m_moveSpd);
	VelocityLimiter(50.0f);
	GameObjects::Update(window);
	if (m_lifeTime <= 0.0f)
	{
		Destroy();
	}
	OutOfBounds(window);
}

void Item::OutOfBounds(Window* window)
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
*****************GOLDCOIN CLASS : DERIVED FROM ITEM*******************
*********************************************************************/
GoldCoin::GoldCoin(const sf::Vector2f & pos)
	:Item("Sprites/Effects/Power-ups/GoldMoney.png", pos)
{
	Setup();
}

//GoldCoin's version of CollidedWith that adds score points to player
void GoldCoin::CollidedWith(GameObjects* object)
{
	Player* l_player = dynamic_cast<Player*>(object);
	if (l_player)
	{
		m_owner->SetScore(m_scoreVal);
		Destroy();
	}
}

//GoldCoin's version of Setup
void GoldCoin::Setup()
{
	m_lifeTime = 20.0f;
	m_scoreVal = 500;
	m_sprite.setScale(0.5f, 0.5f);
	m_collisionRadius = 20.0f;
}

/*********************************************************************
****************SILVERCOIN CLASS : DERIVED FROM ITEM******************
*********************************************************************/
SilverCoin::SilverCoin(const sf::Vector2f & pos)
	:Item("Sprites/Effects/Power-ups/SilverMoney.png", pos)
{
	Setup();
}

//SilverCoin's version of CollidedWith that adds score points to player
void SilverCoin::CollidedWith(GameObjects* object)
{
	Player* l_player = dynamic_cast<Player*>(object);
	if (l_player)
	{
		m_owner->SetScore(m_scoreVal);
		Destroy();
	}
}

//SilverCoin's version of Setup
void SilverCoin::Setup()
{
	m_lifeTime = 20.0f;
	m_scoreVal = 300;
	m_sprite.setScale(0.5f, 0.5f);
	m_collisionRadius = 20.0f;
}

/*********************************************************************
*****************QUADAMMO CLASS : DERIVED FROM ITEM******************
*********************************************************************/
QuadAmmo::QuadAmmo(const sf::Vector2f & pos)
	:Item("Sprites/Effects/Power-ups/powerupGreen_bolt.png", pos)
{
	Setup();
}

//QuadAmmo's version of CollidedWith that adds score points to player
void QuadAmmo::CollidedWith(GameObjects* object)
{
	SS_Player* l_player = dynamic_cast<SS_Player*>(object);
	if (l_player)
	{
		l_player->SetQuadAmmo(m_ammoVal);
		Destroy();
	}
}

//QuadAmmo's version of Setup
void QuadAmmo::Setup()
{
	m_lifeTime = 20.0f;
	m_ammoVal = 20;
	m_collisionRadius = 10.0f;
}

/*********************************************************************
*****************POWERAMMO CLASS : DERIVED FROM ITEM******************
*********************************************************************/
PowerAmmo::PowerAmmo(const sf::Vector2f & pos)
	:Item("Sprites/Effects/Power-ups/powerupBlue_bolt.png", pos)
{
	Setup();
}

//PowerAmmo's version of CollidedWith that adds score points to player
void PowerAmmo::CollidedWith(GameObjects* object)
{
	SS_Player* l_player = dynamic_cast<SS_Player*>(object);
	if (l_player)
	{
		l_player->SetPowerAmmo(m_ammoVal);
		Destroy();
	}
}

//PowerAmmo's version of Setup
void PowerAmmo::Setup()
{
	m_lifeTime = 20.0f;
	m_ammoVal = 1;
	m_collisionRadius = 10.0f;
}