#include "Platform/Platform.hpp"

#include "header.h"

struct Object
{
	Sprite draw;
	Texture txt;
	FloatRect bound;
};

//-------------------Objects to draw-----------------
Object createObject(string s, int x, int y);
Object createObject(string s);
bool isHere(FloatRect& bound, Vector2f& mouse);

//--------------------Scenes---------------------------
void Scene1(RenderWindow& window, int& page);
void logIn(RenderWindow& window, int& page);