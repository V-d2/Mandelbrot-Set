#include <SFML/Graphics.hpp>

#include <iostream>

#include "ComplexPlane.h"



using namespace sf;

using namespace std;




int main()

{

	int pixelWidth = VideoMode::getDesktopMode().width / 2;

	int pixelHeight = VideoMode::getDesktopMode().height /2;

	cout << "Desktop resolution: " << pixelWidth << "x" << pixelHeight << endl;

	VideoMode vm(pixelWidth, pixelHeight);

	RenderWindow window(vm, "Mandelbrot", Style::Resize | sf::Style::Close);

	ComplexPlane compPlane(pixelWidth, pixelHeight); // create a ComplexPlane object with the same size as the window, it is used to display the Mandelbrot set on the screen


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



	Text text; // text is a drawable object that can be used to draw text to the screen. It is used to display the information about the complex plane on the screen
	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	text.setPosition(10.f, 10.f);





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
					compPlane.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
					compPlane.zoomIn();
					
				}
				if (event.mouseButton.button == sf::Mouse::Right) // if the right mouse button was pressed
				{
					std::cout << "the rigt button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					compPlane.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
					compPlane.zoomOut();

				}
			}
			if(event.type == sf::Event::MouseMoved)
			{
				std::cout << "mouse moved" << std::endl;
				std::cout << "mouse x: " << event.mouseMove.x << std::endl;
				std::cout << "mouse y: " << event.mouseMove.y << std::endl;
				compPlane.setMouseLocation(Vector2i(event.mouseMove.x, event.mouseMove.y)); // set the mouse location in the complex plane to the location of the mouse in the window, it is used to display the coordinates of the mouse in the complex plane on the screen
			}
		}




		///Update

		compPlane.updateRender();




		///Draw
		window.clear(); // clear the window buffer with the default color (black)
		compPlane.loadText(text); // modify the texe object prior to draw it.



		/*
		draw the ComplexPlane object
	    draw the Text object
		*/
		compPlane.draw(window, sf::RenderStates::Default); // draw the complex plane to the window, it is used to display the Mandelbrot set on the screen
		window.draw(text);
		//window.draw(...);		
		
		//window.draw(quad, &texture);
		//window.draw(mesh, &texture);

		window.display();

	}




}