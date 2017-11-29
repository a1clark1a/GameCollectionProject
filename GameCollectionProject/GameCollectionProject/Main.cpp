/************************************************************************************************
*********GAME COLLECTION PROJECT : PUT TOGETHER ALL OF MY SFML PROJECTS INTO ONE PROJECT*********
************************************************************************************************/
#include "SpaceShooter.h"
//TODO Create ABSTRACT Game engine class to derive Game Engine class for each new game to be added to the project
//TODO Create GameObjects class for handling the creation of objects to draw in window
//TODO Create Window class for creating an SFML window
//TODO Create a SoundManager Class to handle playing sounds  and background Music
//TODO (In future) Create SpriteManager Class to handle sprite animations and sprite drawing functions to every sprite in each game class
//TODO Create a Main Menu Class to handle creation of Game type based on player choice
//TODO (In future) Particle Effect class


//CURRENTLY BEING USED FOR DEBUGGING PURPOSE
int main()
{
	
	SpaceShooter shooter(sf::Vector2f(800,800));
	while (!shooter.GetWindow()->IsClosed())
	{
		
		
		shooter.Update(shooter.GetWindow()->GetDeltaTime()->asSeconds());
		shooter.Render();
	}
	
}