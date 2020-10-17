#include "sprite.h"

Sprite::Sprite(Level* l, DrawEngine* de, int s_index, float x, float y, int i_lives)
{
	level = l;

	drawArea = de;
	
	position.x = x;
	position.y = y;

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
	erase(position.x, position.y);
}

vector Sprite::getPosition(void)
{
	return position;
}

float Sprite::getX(void)
{
	return position.x;
}

float Sprite::getY(void)
{
	return position.y;
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
	int xpos = (int)(position.x + x);
	int ypos = (int)(position.y + y);
	
	if (isValidLevelMove(xpos, ypos))
	{
		erase(position.x, position.y);

		position.x += x;
		position.y += y;

		facingDirection.x = x;
		facingDirection.y = y;

		draw(position.x, position.y);

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
	return xpos >=0 && ypos >= 0 && !level->isWall(xpos, ypos);
}

bool Sprite::isNpcCollision(int x, int y)
{
	if (level->npc.empty()) {
		return false;
	}

	list <Sprite*>::iterator Iter;

	for (Iter = level->npc.begin(); Iter != level->npc.end(); Iter++) {
		if ((*Iter) != this && (int)(*Iter)->getX() == x && (int)(*Iter)->getY() == y) {
			//logger->log(Logger::stringFormat("NPC collision at %d %d", x, y));
			return true;
		}
	}

	return false;
}
