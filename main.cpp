#include <SFML/Graphics.hpp>

#include <iostream>

#include "ComplexPlane.h"



using namespace sf;

using namespace std;




int main()

{

	int pixelWidth = VideoMode::getDesktopMode().width;

	int pixelHeight = VideoMode::getDesktopMode().height;

	cout << "Desktop resolution: " << pixelWidth << "x" << pixelHeight << endl;

	VideoMode vm(pixelWidth, pixelHeight);

	RenderWindow window(vm, "Mandelbrot", Style::Resize | sf::Style::Close);

	//ComplexPlane  compPlane; // default constructor sets up the complex plane to be the same size as the window, with the origin at the center of the screen


	Texture texture; // texture is an image that can be drawn to the screen. It is loaded from a file and can be used to draw sprites, shapes, etc.
	if (!texture.loadFromFile("images/image.png")) {
	    
		cerr << "Failed to load image.png" << endl;
		return -1;
	}

	sf::Font font; // font is a typeface that can be used to draw text to the screen. It is loaded from a file and can be used to draw text with different sizes, styles, etc.
	if (!font.loadFromFile("fonts/arial.ttf")) {
		cerr << "Failed to load arial.ttf" << endl;
		return -1;
	}


	




	/*

	sf::Texture texture;
	if (!texture.loadFromFile("image.png")) {
		cerr << "Failed to load image.png" << endl;
		return -1;
	}

	sf::Vector2u size = texture.getSize();
	
	sf::VertexArray quad(sf::Quads, 4);

	// screen size (where it appears)
	quad[0].position = sf::Vector2f(600, 0);
	quad[1].position = sf::Vector2f(1200, 0);
	quad[2].position = sf::Vector2f(1200, 600);
	quad[3].position = sf::Vector2f(600, 600);

	// FULL texture mapping
	quad[0].texCoords = sf::Vector2f(0, 0);
	quad[1].texCoords = sf::Vector2f(size.x, 0);
	quad[2].texCoords = sf::Vector2f(size.x, size.y);
	quad[3].texCoords = sf::Vector2f(0, size.y);
	*/



	/*

	
	sf::VertexArray mesh(sf::Triangles, 6);
	
	// ---------- Triangle 1 ----------
	mesh[0].position = { 100, 100 };
	mesh[1].position = { 300, 100 };
	mesh[2].position = { 300, 300 };

	mesh[0].texCoords = { 0, 0 };
	mesh[1].texCoords = { (float)size.x, 0 };
	mesh[2].texCoords = { (float)size.x, (float)size.y };
	*/
	
	/*
	// ---------- Triangle 2 ----------
	mesh[3].position = { 50, 100 };
	mesh[4].position = { 300, 300 };
	mesh[5].position = { 50, 300 };

	mesh[3].texCoords = { 0, 0 };
	mesh[4].texCoords = { (float)size.x, (float)size.y };
	mesh[5].texCoords = { 0, (float)size.y };
	*/


	//square with image texture





	while (window.isOpen())

	{

		///Input

		// Check if the Escape key is pressed to close the window
		if (Keyboard::isKeyPressed(Keyboard::Escape))

		{
			window.close();

		}

		
		Event event; // event is a struct that holds information about an event that happened (like a key press, mouse click, etc.)

		// Check for events (like key presses, mouse clicks, etc.)
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) // if the event is that the window was closed
			{
				// Quit the game when the window is closed
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) // if the event is that a mouse button was pressed
			{
				if (event.mouseButton.button == sf::Mouse::Left) // if the left mouse button was pressed
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl; // event.mouseButton.x is the x coordinate of the mouse when the button was pressed
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					//ComplexPlane::zoomIn();
					//ComplexPlane::setCenter();
				}
				if (event.mouseButton.button == sf::Mouse::Right) // if the right mouse button was pressed
				{
					std::cout << "the rigt button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					//ComplexPlane::zoomOut();
					//ComplexPlane::setCenter();

				}
			}
			if(event.type == sf::Event::MouseMoved)
			{
				std::cout << "mouse moved" << std::endl;
				std::cout << "mouse x: " << event.mouseMove.x << std::endl;
				std::cout << "mouse y: " << event.mouseMove.y << std::endl;
				//ComplexPlane::setMouseLocation(x, y);
			}
		}




		///Update

		//mplexPlane::updateRender();
		//mplexPlane::loadText ();





		///Draw
		window.clear(); // clear the window buffer with the default color (black)






		//window.draw(...);		
		
		//window.draw(quad, &texture);
		//window.draw(mesh, &texture);

		window.display();

	}




}