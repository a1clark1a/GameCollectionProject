#pragma once
#include <SFML\Audio.hpp>
#include <iostream>
/*********************************************************************
**********************SOUND MANAGER CLASS*****************************
*********************************************************************/
class SoundManager
{
public:
	SoundManager();
	~SoundManager() { std::cout << "Soundmanager destructor called: " << std::endl; }

	void PlayBackgroundMusic(const std::string musicPath);
	void PlaySound(const std::string soundPath);
	
private:
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;
	sf::Music m_music;
	
};