#pragma once
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
Info createInfo(string s, float x, float y, float size);
Info createInfo(string s, string info, float x, float y, float size);
Info* createInfoTest(string s, string info, float x, float y, float size);

//--------------------Scenes---------------------------

void Scene1(RenderWindow& window, int& page, bool& role, const float& scale);
void logIn(RenderWindow& window, int& page, bool role, const float& scale, ClassNode* class_list, StudentNode* staff_list, StudentNode*& user);
void studentHome(RenderWindow& window, int& page, const float& scale);
void staffHome(RenderWindow& window, int& page, const float& scale);
void profile(RenderWindow& window, int& page, const float& scale, StudentNode* student, bool is_staff);

//-----------------Other features--------------------------

bool isHere(FloatRect& bound, Vector2f& mouse);
void drawWhich(RenderWindow& window, Object a, Object b, Vector2f& mouse);
void drawWhich(RenderWindow& window, Object* a, Object* b, Vector2f& mouse);
void switchPage(FloatRect& bound, Vector2f& mouse, int k, int& page);
void changePos(Object* a, Object* b, float x, float y);
void changePos(Object* a, float x, float y);
void changePos(Info* a, float x, float y);
void texting(Info& text, Uint32 unicode, unsigned int limit);
void texting(Info*& text, Uint32 unicode, unsigned int limit);
// bool empty(sf::String s);
// bool pop_back(sf::String s);