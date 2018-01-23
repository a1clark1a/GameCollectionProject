/************************************************************************************************
*********GAME COLLECTION PROJECT : PUT TOGETHER ALL OF MY SFML PROJECTS INTO ONE PROJECT*********
************************************************************************************************/
#include "SpaceShooter.h"
#include "MainMenu.h"
//TODO (In future) Create SpriteManager Class to handle sprite animations and sprite drawing functions to every sprite in each game class
//TODO (In future) Particle Effect class

int main()
{
	
	MainMenu menu;
	while (menu.IsProgramOn())
	{
		menu.PlayMenu();
	}
	
}