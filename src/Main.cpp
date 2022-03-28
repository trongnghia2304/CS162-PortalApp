#include "Header.h"
#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;
#if defined(_DEBUG)
#endif

	RenderWindow window;
	Image icon;
	icon.loadFromFile("content/icon.png");
	// in Windows at least, this must be called before creating the window
	//float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(VideoMode(1000.0f, 750.5f), "CS162-Project", Style::Close);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Texture shapeTexture;
	shapeTexture.loadFromFile("content/First.png");

	Sprite shape(shapeTexture);
	Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
