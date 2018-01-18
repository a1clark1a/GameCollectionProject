#include "Player.h"

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
	VelocityLimiter(500);
}

//Player version of TakeDmg 
void Player::TakeDmg(const float & dmgVal)
{
	if (m_playerHealth >= dmgVal)
	{
		m_playerHealth -= dmgVal;
		if (m_playerHealth <= 0.0f)
		{
			Destroy();
		}
	}
	else
	{
		Destroy();
	}
}

//Player version create and draw invincibility shield
void Player::DrawShield(Window* window)
{
	m_invincibilityCooldown -= window->GetDeltaTime()->asSeconds();
	if (m_invincibilityCooldown > 0.0f)
	{
		m_invincibilityRing->setRadius(45.0f);
		m_invincibilityRing->setFillColor(sf::Color::Transparent);
		m_invincibilityRing->setOutlineThickness(10.0f * m_invincibilityCooldown / 3.0f + 1.0f);
		sf::Color l_color = sf::Color::Blue;
		l_color.a = static_cast<sf::Uint8>(255 * m_invincibilityCooldown / 3.0f);
		m_invincibilityRing->setOutlineColor(l_color);
		m_invincibilityRing->setOrigin(45, 45);
		m_invincibilityRing->setPosition(m_pos);
		window->DrawThis(m_invincibilityRing);

		float l_sinVal = sin(m_invincibilityCooldown * 25.0f);
		l_sinVal += 1;
		l_sinVal *= 0.5;
		float l_alpha = l_sinVal * 255;
		sf::Color l_shipColor = sf::Color::White;
		l_shipColor.a = (sf::Uint8)l_alpha;
		m_sprite.setColor(l_shipColor);
	}
	else
	{
		m_sprite.setColor(sf::Color::White);
	}
}

void Player::AddToPlayerHealth(const float & healthVal)
{
	m_playerHealth += healthVal;
	if (m_playerHealth > 200.0f)
	{
		m_playerHealth = 200.0f;
	}
}

/*********************************************************************
***************SS_PLAYER CLASS : DERIVED FROM PLAYER******************
*********************************************************************/

//SS_Player Constructor 
//Needs texture address and initial position to initialize player sprite
SS_Player::SS_Player()
	:Player("Sprites/TopDownShips/ship3.png", sf::Vector2f(800.0f,450.0f))
{	
	Setup();
}

//SS_Player virtual destructor
SS_Player::~SS_Player()
{
	std::cout << "SS_Player's Destructor called" << std::endl;
}

//SS_Player version Setup function
void SS_Player::Setup()
{
	m_invincibilityCooldown = 2.0f;
	m_playerHealth = 200.0f;
	m_quadAmmo = 60;
	m_PowerAmmo = 1;
	m_shootCooldown = 0.2f;
	SetCollisionRadius(40.0f);
	m_sprite.setScale(0.1f, 0.1f);
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.5f);
}

//SS_Player version Draw function
void SS_Player::Draw(Window* window)
{
	DrawShield(window);
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
	m_owner->GetSound()->PlaySound("Audio/Explosion3.wav");
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
	else if (m_pos.y > window->GetWindowSize()->y - 50.0f )
	{
		m_pos.y = window->GetWindowSize()->y-50.0f;
	}
}

//SS_player version that take uses player input to move player ship
//If no input is pressed call SS_Player version's ApplyDrag
void SS_Player::PlayerControls(Window* window)
{
	m_shootCooldown -= window->GetDeltaTime()->asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		SetLinearAccel(800);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		SetLinearAccel(-150);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		SetSideAccel(-150);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		SetSideAccel(150);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		ShootFunction(window->GetDeltaTime()->asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_shootCooldown = 0.0f;
		m_currentWeap = WEAPONTYPE::Fast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_currentWeap = WEAPONTYPE::QuadBlaster;
		m_shootCooldown = 0.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_currentWeap = WEAPONTYPE::Power;
		m_shootCooldown = 0.0f;
	}
	else
	{
		ApplyDrag(window->GetDeltaTime()->asSeconds(), 10.0f);
	}
}

//SS_Player version shoot bullets based on which weapon type equipped
void SS_Player::ShootFunction(const float  & dt)
{
	switch (m_currentWeap)
	{
	case WEAPONTYPE::Fast:
		if (m_shootCooldown <= 0.0f && m_invincibilityCooldown <= 0.0f)
		{
			for (int i = 0; i < 2; i++)
			{
				FastBullet* l_fastBullet = new FastBullet("Sprites/Effects/Lasers/laserBlue01.png",sf::Vector2f(m_pos.x + ( i < 1 ? 15.0f : -15.0f), m_pos.y - 20), 10.0f, 700.0f);
				m_owner->AddObject(l_fastBullet);
			}
			m_owner->GetSound()->PlaySound("Audio/Laser_Shoot.wav");
			m_shootCooldown = 0.1f;
		}
		break;
	case WEAPONTYPE::QuadBlaster:
		if (m_shootCooldown <= 0.0f && m_quadAmmo > 0 && m_invincibilityCooldown <= 0.0f)
		{
			for (int i = 0; i < 4; i++)
			{
				QuadBullets* l_quadBullets = new QuadBullets(sf::Vector2f(m_pos.x, m_pos.y - 30.0f), 20.0f);
				l_quadBullets->SetAngle(m_angle - 15.0f + (i < 2 ? -15.0f : 15.0f) * i);
				l_quadBullets->SetVelocity(800.0f);
				m_owner->AddObject(l_quadBullets);
				m_quadAmmo--;
			}
			m_owner->GetSound()->PlaySound("Audio/QuadBomb.wav");
			m_shootCooldown = 0.3f;
		}
		break;
	case WEAPONTYPE::Power:
		if (m_shootCooldown <= 0.0f && m_PowerAmmo > 0 && m_invincibilityCooldown <= 0.0f)
		{
			PowerBomb* l_PowerBomb = new PowerBomb("Sprites/Effects/Lasers/blueflame_big.png", sf::Vector2f(m_pos.x, m_pos.y - 30.0f), 100.0f);
			l_PowerBomb->SetLinearAccel(100.0f);
			m_owner->AddObject(l_PowerBomb);
			m_owner->GetSound()->PlaySound("Audio/PowerBomb.wav");
			m_shootCooldown = 5.0f;
			m_PowerAmmo--;
		}
		break;
	}
}

/*********************************************************************
***************AST_PLAYER CLASS : DERIVED FROM PLAYER******************
*********************************************************************/

//Ast_Player Constructor 
//Needs texture address and initial position to initialize player sprite
Ast_Player::Ast_Player()
	:Player("Sprites/TopDownShips/Player01.png", sf::Vector2f(700.0f, 350.0f))
{
	Setup();
}

//Ast_Player virtual destructor
Ast_Player::~Ast_Player()
{
	std::cout << "Ast_Player's Destructor called" << std::endl;
}

void Ast_Player::Setup()
{
	m_invincibilityCooldown = 2.0f;
	m_playerHealth = 1.0f;
	m_specialAmmo = 60;
	m_shootCooldown = 0.2f;
	SetCollisionRadius(40.0f);
	m_sprite.setScale(0.1f, 0.1f);
	m_sprite.setOrigin(m_sprite.getTextureRect().width * 0.5f, m_sprite.getTextureRect().height * 0.5f);
}

void Ast_Player::Draw(Window* window)
{
	DrawShield(window);
	Player::Draw(window);
}

void Ast_Player::Update(Window* window)
{
	Player::Update(window);
	OutOfBounds(window);
	PlayerControls(window);
}

void Ast_Player::Destroy()
{
	GameObjects::Destroy();
	m_owner->GetSound()->PlaySound("Audio/Explosion3.wav");
}

void Ast_Player::CollidedWith(GameObjects* object)
{

}

void Ast_Player::PlayerControls(Window* window)
{
	m_shootCooldown -= window->GetDeltaTime()->asSeconds();
	SetAccel(0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		SetAngle(GetAngle() + 180 * window->GetDeltaTime()->asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		SetAngle(GetAngle() - 180 * window->GetDeltaTime()->asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		SetAccel(400.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{

		ShootFunction(window->GetDeltaTime()->asSeconds());
	}
}

void Ast_Player::ShootFunction(const float & dt)
{
	if (m_shootCooldown <= 0.0f  && m_invincibilityCooldown <= 0.0f)
	{
		bool l_tripleShot = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
		m_shootCooldown = l_tripleShot ? 0.5f : 0.2f;

		if (l_tripleShot && m_specialAmmo > 0)
		{
			for (int i = 0; i < 3; i++)
			{
				FastBullet* l_bullet = new FastBullet("Sprites/Effects/Lasers/laserBlue08.png",m_pos,10.0f, 0.0f);
				l_bullet->SetAngle(m_angle - 15.0f + i * 15.0f);
				l_bullet->SetVelocity(500.0f);
				m_owner->AddObject(l_bullet);
				m_specialAmmo--;
			}
			m_owner->GetSound()->PlaySound("Audio/QuadBomb.wav");
		}
		else
		{
			FastBullet* l_bullet = new FastBullet("Sprites/Effects/Lasers/laserBlue08.png",m_pos,10.0f,0.0f);
			l_bullet->SetAngle(m_angle);
			l_bullet->SetVelocity(500.0f);
			m_owner->AddObject(l_bullet);
			m_owner->GetSound()->PlaySound("Audio/Laser_Shoot1.wav");
		}
	}
}