#include "SoundManager.h"

/**************************************************************************************
*********************************SOUND MANAGER CLASS***********************************
***************************************************************************************/

SoundManager::SoundManager()
{

}

void SoundManager::PlayBackgroundMusic(const std::string musicPath)
{
	m_music.openFromFile(musicPath);
	m_music.setVolume(50.0f);
	m_music.play();
	m_music.setLoop(true);
}

void SoundManager::PlaySound(const std::string soundPath)
{
	m_buffer.loadFromFile(soundPath);
	m_sound.setBuffer(m_buffer);
	m_sound.setVolume(50.0f);
	m_sound.play();
}

