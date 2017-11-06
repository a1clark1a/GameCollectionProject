/************************************************************************************************
************GAME COLLECTION PROJECT : PUT TOGETHER ALL MY SFML PROJECTS INTO ONE PROJECT*********
************************************************************************************************/
#include "Window.h"

//TODO Create ABSTRACT Game engine class to derive Game Engine class for each new game to be added to the project
//TODO Create GameObjects class for handling the creation of objects to draw in window
//TODO Create Window class for creating an SFML window
//TODO Create a SoundManager Class to handle playing sounds  and background Music
//TODO (In future) Create SpriteManager Class to handle sprite animations and sprite drawing functions to every sprite in each game class



int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Base Setup!");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				//close window button clicked
				window.close();
			}
		}
		
		window.clear(sf::Color::Black);
		//Draw here
		window.display();
	}


}