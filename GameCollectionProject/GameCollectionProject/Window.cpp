#include "Window.h"

/**************************************************************************
*************************PUBLIC MEMBERS***********************************
**************************************************************************/

//Default Constructor
Window::Window()
{
	Setup("Default Title", sf::Vector2f(640, 480));                                 // Call Setup() with pre-made default values(should never be called)
}

//Constructor for assigning window title and window size
//To be initialized by Game constructor to recreate window appropriate for game
Window::Window(const std::string & winTitle, const sf::Vector2f & winSize)          
{
	Setup(winTitle, winSize);														// Call Setup() and pass the arguments taken from constructor
}

//Default Destructor
//To be called when toggling fullscreen or closing window,
Window::~Window()
{
	std::cout << "Window Destructor is called" << std::endl;
	Destroy();																		// Upon deletion of window, call Destroy() to close window
}



//Window Update function to be called in Game Update()
void Window::Update()
{
	l_dt = m_clock.restart();
	sf::Event l_event;																// Event object creation
	while (m_renderWindow.pollEvent(l_event))
	{
		
		if (l_event.type == sf::Event::Closed)
		{
			m_isClosed = true;														// When window is closed set m_isDone to true
		}																			// then the while loop playing the game will end
		else if (l_event.type == sf::Event::KeyPressed && l_event.key.code == sf::Keyboard::F5)
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
void Window::Setup(const std::string & winTitle, const sf::Vector2f & winSize)
{
	m_renderWindowTitle = winTitle; 
	m_renderWindowSize = winSize;
	m_isFullscreen = false;
	m_isClosed = false;
	Create();																		// After assigning values, Call Create() 
																					// to create window with appropriate values
}																		

//Main Function to call to create the actual window using values passed in constructor into Setup()
//To be called from inside Setup()
void Window::Create()
{
	auto l_style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);   // Value for auto type variable is based on value of m_isFullScreen
	m_renderWindow.create
	({ static_cast<unsigned int>(m_renderWindowSize.x), static_cast<unsigned int>(m_renderWindowSize.y), 32 }, m_renderWindowTitle, l_style);
	// create window using the values taken from Constructor parameters passed into Setup()
}