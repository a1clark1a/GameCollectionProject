#pragma once
#include <SFML\Graphics.hpp>
#include <string>

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
	void DrawThis(sf::Drawable * drawable) { m_window.draw(*drawable); }	// inline call m_window object draw method and draw the value that *drawable is pointing to
	void Clear() { m_window.clear(sf::Color::Black); }						// inline clear window to black
	void Display() { m_window.display(); }									// inline call to display method of window to show changes made in the window screen
	void Update();															// Activating the Window object
	void ToggleFullscreen();												// Switch Fullscreen on and off

	//Getter functions
	bool isDone() {	return m_isDone; }										// inline Bool function to get value of m_isDone
	bool isFullScreen() { return m_isFullscreen; }							// inline Bool function to get value of m_isFullScreen
	sf::Vector2u GetWindowSize() { return m_windowSize; }					// inline get window size value;
	
private:
	//Behind the scenes function
	void Setup(const std::string & winTitle, const sf::Vector2u & winSize); // Function to assign values to member variables;
	void Destroy() { m_window.close(); }									// function to close window
	void Create();															// actual function to create the window

	sf::RenderWindow m_window;												// window object
	sf::Vector2u m_windowSize; 
	std::string m_windowTitle;
	bool m_isFullscreen;
	bool m_isDone;

};