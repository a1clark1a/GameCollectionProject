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
	MaxVelocity(500);
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

//Player version reset invulnerability
void Player::MakeInvulnerable()
{
	m_invincibilityCooldown = 2.0f;
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
	m_shooting = false;
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
		//TEST
		if (m_shootCooldown <= 0.0f)
		{
			NormalAI* test = new NormalAI(sf::Vector2f(static_cast<float>(rand() % 700 + 200), -50.0f));
			AggroAI* test2 = new AggroAI(sf::Vector2f(400.0f, 50.0f));
			m_owner->AddObject(test);
			m_owner->AddObject(test2);
			ChaserAI* test3 = new ChaserAI(sf::Vector2f(400.0f, 350.0f));
			m_owner->AddObject(test3);
			m_shootCooldown = 0.5f;
			GoldCoin* test4 = new GoldCoin(sf::Vector2f(static_cast<float>(rand() % 300 + 200), 150.0f));
			m_owner->AddObject(test4);
			SilverCoin* test5 = new SilverCoin(sf::Vector2f(static_cast<float>(rand() % 300 + 200), 150.0f));
			m_owner->AddObject(test5);
			QuadAmmo* test6 = new QuadAmmo(sf::Vector2f(static_cast<float>(rand() % 300 + 200), 150.0f));
			m_owner->AddObject(test6);
			PowerAmmo* test7 = new PowerAmmo(sf::Vector2f(static_cast<float>(rand() % 300 + 200), 150.0f));
			m_owner->AddObject(test7);
		}
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
		//TEST
		//LargeAsteroid* test = new LargeAsteroid(sf::Vector2f(static_cast<float>(rand() % 400),50.0f));
		//m_owner->AddObject(test);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_shooting = true;
		ShootFunction(window->GetDeltaTime()->asSeconds());
	}
	else
	{
		ApplyDrag(window->GetDeltaTime()->asSeconds(), 10.0f);
		m_shooting = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_currentWeap = WEAPONTYPE::Fast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_currentWeap = WEAPONTYPE::QuadBlaster;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_currentWeap = WEAPONTYPE::Power;
	}
}

//SS_Player version shoot bullets based on which weapon type equipped
void SS_Player::ShootFunction(const float  & dt)
{
	switch (m_currentWeap)
	{
	case WEAPONTYPE::Fast:
		if (m_shooting && m_shootCooldown <= 0.0f)
		{
			for (int i = 0; i < 2; i++)
			{
				FastBullet* l_fastBullet = new FastBullet(sf::Vector2f(m_pos.x + ( i < 1 ? 15.0f : -15.0f), m_pos.y - 20), 10.0f, 700.0f);
				m_owner->AddObject(l_fastBullet);
				m_shootCooldown = 0.1f;
			}
		}
		break;
	case WEAPONTYPE::QuadBlaster:
		if (m_shooting && m_shootCooldown <= 0.0f && m_quadAmmo > 0)
		{
			for (int i = 0; i < 4; i++)
			{
				QuadBullets* l_quadBullets = new QuadBullets(sf::Vector2f(m_pos.x, m_pos.y - 30.0f), 20.0f);
				l_quadBullets->SetAngle(m_angle - 15.0f + (i < 2 ? -15.0f : 15.0f) * i);
				l_quadBullets->SetVelocity(800.0f);
				m_owner->AddObject(l_quadBullets);
				m_shootCooldown = 0.5f;
				m_quadAmmo--;
			}
			
		}
		break;
	case WEAPONTYPE::Power:
		if (m_shooting && m_shootCooldown <= 0.0f && m_PowerAmmo > 0)
		{
			PowerBomb* l_PowerBomb = new PowerBomb("Sprites/Effects/Lasers/blueflame_big.png", sf::Vector2f(m_pos.x, m_pos.y - 30.0f), 100.0f);
			l_PowerBomb->SetLinearAccel(100.0f);
			m_owner->AddObject(l_PowerBomb);
			m_shootCooldown = 5.0f;
			m_PowerAmmo--;
		}
		break;

	default: m_currentWeap = WEAPONTYPE::Fast;
		break;


	}
}

