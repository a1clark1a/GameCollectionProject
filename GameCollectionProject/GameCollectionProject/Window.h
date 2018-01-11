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
	Window();																	// default constructor
	Window(const std::string & winTitle, const sf::Vector2f & winSize);			// Main constructor to be used to set the window type
	~Window();																	// default destructor
	
	//main interface functions
																				// Pass a pointer to a drawable object 
	void DrawThis(sf::Drawable * drawable) { m_renderWindow.draw(*drawable); }	// inline call m_window object draw method and draw the value that *drawable is pointing to
	void Clear() { m_renderWindow.clear(sf::Color::Black); }					// inline clear window to black
	void Display() { m_renderWindow.display(); }								// inline call to display method of window to show changes made in the window screen
	void Update();																// Activating the Window object
	void ToggleFullscreen();													// Switch Fullscreen on and off
	void Destroy() { m_isClosed = true; m_renderWindow.close(); }

	//Getter functions
	bool IsClosed() const {	return m_isClosed; }								// inline Bool function to get value of m_isDone
	bool isFullScreen() const { return m_isFullscreen; }						// inline Bool function to get value of m_isFullScreen
	const sf::Vector2f* GetWindowSize() { return &m_renderWindowSize; }			// inline get a pointer to rendered window size variable;
	const sf::Time* GetDeltaTime() { return &l_dt; }							// inline get a pointer to Deltatime and access seconds, milliseconds
	
private:
	//Behind the scenes function
	void Setup(const std::string & winTitle, const sf::Vector2f & winSize);		// Function to assign values to member variables;
									// function to close window
	void Create();																// actual function to create the window
	sf::RenderWindow m_renderWindow;											// render window
	sf::Vector2f m_renderWindowSize; 
	std::string m_renderWindowTitle;
	sf::Clock m_clock;
	sf::Time l_dt;																// DeltaTime to access seconds, milliseconds etc
	bool m_isFullscreen;														// renderWindow state
	bool m_isClosed;				

};