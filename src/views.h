#include "Platform/Platform.hpp"
#include "header.h"
#include "string.h"

struct Object
{
	Sprite draw;
	Texture txt;
	FloatRect bound;
};

struct Info
{
	Font font;
	Text text;
	FloatRect bound;
	bool check = false;
	string s = "";
};

//-------------------Objects/Text to draw-----------------
Object createObject(string s, float x, float y);
Object* createObjectTest(string s, float x, float y);
Object createObject(string s);
bool isHere(FloatRect& bound, Vector2f& mouse);
Info createInfo(string s, float x, float y, float size);
Info createInfo(string s, string info, float x, float y, float size);

//--------------------Scenes---------------------------
void Scene1(RenderWindow& window, int& page, bool& role, const float& scale);
void logIn(RenderWindow& window, int& page, bool role, const float& scale);
void studentHome(RenderWindow& window, int& page, const float& scale);
void staffHome(RenderWindow& window, int& page, const float& scale);

//-----------------Other features--------------------------
