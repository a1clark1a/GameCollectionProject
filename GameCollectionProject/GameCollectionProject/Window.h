#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <string>
#include "time.h"

//Window Class Header for creating specific windows depending on game being played

class Window
{
public:
	//constructors & destructors
	Window();																// default constructor
	Window(const std::string & winTitle, const sf::Vector2u & winSize);		// Main constructor to be used to set the window type
	~Window();																// default destructor
	
	//main interface functions
																			// Pass a pointer to a drawable object 
	void DrawThis(sf::Drawable * drawable) { m_renderWindow.draw(*drawable); }	// inline call m_window object draw method and draw the value that *drawable is pointing to
	void Clear() { m_renderWindow.clear(sf::Color::Black); }						// inline clear window to black
	void Display() { m_renderWindow.display(); }									// inline call to display method of window to show changes made in the window screen
	void Update();															// Activating the Window object
	void ToggleFullscreen();												// Switch Fullscreen on and off

	//Getter functions
	bool isDone() {	return m_isDone; }										// inline Bool function to get value of m_isDone
	bool isFullScreen() { return m_isFullscreen; }							// inline Bool function to get value of m_isFullScreen
	sf::Vector2u* GetWindowSize() { return &m_renderWindowSize; }			// inline get a reference to rendered window size variable;
	sf::Time* GetDeltaTime() { return &dt; }								// inline get a reference to Deltatime and access seconds, milliseconds
	
private:
	//Behind the scenes function
	void Setup(const std::string & winTitle, const sf::Vector2u & winSize); // Function to assign values to member variables;
	void Destroy() { m_renderWindow.close(); }								// function to close window
	void Create();															// actual function to create the window

	sf::RenderWindow m_renderWindow;										// render window
	sf::Vector2u m_renderWindowSize; 
	std::string m_renderWindowTitle;
	sf::Clock m_clock;
	sf::Time dt;															// DeltaTime to access seconds, milliseconds etc
	bool m_isFullscreen;
	bool m_isDone;

};