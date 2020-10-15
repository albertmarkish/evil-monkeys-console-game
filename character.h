#pragma once

#include "sprite.h"

class Character : public Sprite
{
public:
	Character(Level *l, DrawEngine* de, int s_index, float x = 1, float y = 1, int lives = 3, 
		char up_key = 'w', char down_key = 's', char left_key = 'a', char right_key = 'd');

	virtual bool keyPress(char c);

protected:
	char upKey;
	char downKey;
	char leftKey;
	char rightKey;

	virtual void draw(float x, float y);
};
