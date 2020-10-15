#include "character.h"

Character::Character(Level *l, DrawEngine* de, int s_index, float x, float y, int lives, char up_key, char down_key, char left_key, char right_key)
	: Sprite(l, de, s_index, x, y, lives)
{
	upKey = up_key;
	downKey = down_key;
	leftKey = left_key;
	rightKey = right_key;

	classID = CHARACTER_CLASSID;
}

bool Character::keyPress(char c)
{
	if (c == upKey) {
		return move(0, -1);
	} 
	else if (c == downKey) {
		return move(0, 1);
	}
	else if (c == leftKey) {
		return move(-1, 0);
	}
	else if (c == rightKey) {
		return move(1, 0);
	}

	return false;
}

void Character::draw(float x, float y)
{
	logger->log(Logger::stringFormat("Character draw at %4.2f %4.2f", x, y));
	drawArea->drawSprite(spriteIndex, (int)x, (int)y);
}
