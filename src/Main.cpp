#include "views.h"

int main()
{
#if defined(_DEBUG)
#endif
	RenderWindow window;
	Image icon;
	icon.loadFromFile("content/icon.png");
	float scale = 1.5f;
	window.create(VideoMode(1000.0f * scale, 750.0f * scale), "CS162-Project", Style::Close);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	int page = 5;
	bool role;
	while (page > 0 && window.isOpen())
	{
		switch (page)
		{
			case 1: {
				Scene1(window, page, role, scale);
				break;
			}
			case 2: {
				logIn(window, page, role, scale);
				break;
			}
			case 3: {
				studentHome(window, page, scale);
				break;
			}
			case 4: {
				staffHome(window, page, scale);
				break;
			}
			case 5: {
				profile(window, page, scale);
			}
			default: {
				break;
			}
		}
	}

	return 0;
}
