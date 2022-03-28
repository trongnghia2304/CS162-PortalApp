#include "views.h"

int main()
{
#if defined(_DEBUG)
#endif
	RenderWindow window;
	Image icon;
	icon.loadFromFile("content/icon.png");
	window.create(VideoMode(1000.0f, 750.5f), "CS162-Project", Style::Close);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	int page = 1;

	Scene1(window, page);
	logIn(window, page);
	return 0;
}
