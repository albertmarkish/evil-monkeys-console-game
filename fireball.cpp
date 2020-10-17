#include "fireball.h"

Fireball::Fireball(Level* level, DrawEngine* de, int s_index, float x, float y, 
	float xDir, float yDir, int i_lives) : Sprite(level, de, s_index, x, y, i_lives)
{
	facingDirection.x = xDir;
	facingDirection.y = yDir;

	classID = FIREBALL_CLASSID;
}

void Fireball::idleUpdate(void)
{
	if (Sprite::move(facingDirection.x, facingDirection.y)) {
		list <Sprite*>::iterator Iter;

		for (Iter = level->npc.begin(); Iter != level->npc.end(); Iter++) {
			if ((*Iter)->classID != classID && (int)(*Iter)->getX() == (int)position.x && (int)(*Iter)->getY() == (int)position.y) {
				Beep(400, 500);
				(*Iter)->addLives(-1);
				addLives(-1); // eliminate the fireball
			}
		}
	}
	else {
		addLives(-1); // fireball hits a wall
	}
}

void Fireball::draw(float x, float y)
{
	drawArea->drawSprite(spriteIndex, (int)x, (int)y);
}
