#include "sprite.h"

Sprite::Sprite(Level* l, DrawEngine* de, int s_index, float x, float y, int i_lives)
{
	level = l;

	drawArea = de;
	
	pos.x = x;
	pos.y = y;

	spriteIndex = s_index;

	numLives = i_lives;

	logger = NULL;

	// initially facing to the right
	facingDirection.x = 1;
	facingDirection.y = 0;

	classID = SPRITE_CLASSID;
}

Sprite::~Sprite()
{
	// erase the dying sprite
	erase(pos.x, pos.y);
}

vector Sprite::getPosition(void)
{
	return pos;
}

float Sprite::getX(void)
{
	return pos.x;
}

float Sprite::getY(void)
{
	return pos.y;
}

void Sprite::addLives(int num)
{
	numLives += num;
}

int Sprite::getLives(void)
{
	return numLives;
}

bool Sprite::isAlive()
{
	return numLives > 0;
}

void Sprite::idleUpdate(void)
{
	// this is for the inherited classes
}

bool Sprite::move(float x, float y)
{
	int xpos = (int)(pos.x + x);
	int ypos = (int)(pos.y + y);
	
	if (isValidLevelMove(xpos, ypos))
	{
		erase(pos.x, pos.y);

		pos.x += x;
		pos.y += y;

		facingDirection.x = x;
		facingDirection.y = y;

		draw(pos.x, pos.y);

		return true;
	}

	return false;
}

void Sprite::setLogger(Logger* log)
{
	logger = log;
}

//void Sprite::draw(float x, float y)
//{
//	logger->log(Logger::stringFormat("Sprite draw at %d %d", x, y));
//	drawArea->drawSprite(spriteIndex, (int)x, (int)y);
//}

void Sprite::erase(float x, float y)
{
	drawArea->eraseSprite((int)x, (int)y);
}

bool Sprite::isValidLevelMove(int xpos, int ypos)
{
	return !level->isWall(xpos, ypos);
}
