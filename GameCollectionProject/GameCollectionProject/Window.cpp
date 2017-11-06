#include "Window.h"

/**************************************************************************
*************************PUBLIC MEMBERS***********************************
**************************************************************************/
//Default Constructor
Window::Window()
{
	Setup("Default Title", sf::Vector2u(640, 480));                                 // Call Setup() with pre-made default values(should never be called)
}

//Constructor for assigning window title and window size
//To be invoked by specific game type to recreate window appropriate for game
Window::Window(const std::string & winTitle, const sf::Vector2u & winSize)          
{
	Setup(winTitle, winSize);														// Call Setup() and pass the arguments taken from constructor
}

//Default Destructor
//To be called when toggling fullscreen or closing window,
Window::~Window()
{
	Destroy();																		// Upon deletion of window, call Destroy() to close window
}


//Window Update function to be called in Game Update()
void Window::Update()
{
	sf::Event event;																// Event object creation
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_isDone = true;														// When window is closed set m_isDone to true
		}																			// then the while loop playing the game will end
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
		{
			ToggleFullscreen();														// Call function to toggle Full Screen 
		}
	}
	

}


//Function to handle setting boolean m_isFullscreen to appropriate value then Destroying and Recreating window
//To be called from inside Update() when f5 is pressed
void Window::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;												// Toggle value to opposite of current value (if 1 then 0, if 0 then 1)
	Destroy();																		// Then call Destroy() to close window
	Create();																		// Then call Create() to resetup window with new m_isFullScreen value
}



/**************************************************************************
*************************PRIVATE MEMBERS***********************************
**************************************************************************/


//Main Function to assign values passed from Constructor to initialize values for window object
//to be called from inside constructor
void Window::Setup(const std::string & winTitle, const sf::Vector2u & winSize)
{
	m_windowTitle = winTitle; 
	m_windowSize = winSize;
	m_isFullscreen = false;
	m_isDone = false;
	Create();																		// After assigning values, Call Create() 
																					// to create window with appropriate values
}																		

//Main Function to call to create the actual window using values passed in constructor into Setup()
//To be called from inside Setup()
void Window::Create()
{
	auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);   // Value for auto type variable is based on value of m_isFullScreen
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);// create window using the values taken from Constructor parameters passed 
																				  // into Setup()
}