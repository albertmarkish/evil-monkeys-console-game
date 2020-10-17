#include "enemy.h"
#include "character.h"

#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Enemy::Enemy(Level* l, DrawEngine* de, int s_index, float x, float y, int i_lives) : Sprite(l, de, s_index, x, y, i_lives)
{
	goal = 0;
	classID = ENEMY_CLASSID;
}

void Enemy::draw(float x, float y)
{
	//logger->log(Logger::stringFormat("Enemy draw at %4.2f %4.2f", x, y));
	drawArea->drawSprite(spriteIndex, (int)x, (int)y);
}

bool Enemy::isGoalCollision(int x, int y)
{
	return (int)goal->getX() == x && (int)goal->getY() == y;
}

bool Enemy::move(float x, float y)
{
	int xpos = (int)(position.x + x);
	int ypos = (int)(position.y + y);

	if (isValidLevelMove(xpos, ypos) && !isNpcCollision(xpos, ypos))
	{
		erase(position.x, position.y);

		position.x += x;
		position.y += y;

		facingDirection.x = x;
		facingDirection.y = y;

		draw(position.x, position.y);

		if (isGoalCollision(xpos, ypos)) {
			goal->addLives(-1); // take player's life
			Beep(220, 500);
			logger->log(Logger::stringFormat("%d Lives Remaining!", goal->getLives()));
		}

		return true;
	}

	return false;
}

void Enemy::idleUpdate(void)
{
	if (goal)
		simulateAI();
}

void Enemy::simulateAI(void)
{
	vector goal_pos = goal->getPosition();
	
	vector direction;

	//TODO: what is this calculation
	direction.x = goal_pos.x - position.x;
	direction.y = goal_pos.y - position.y;

	float mag = sqrt(direction.x * direction.x + direction.y * direction.y);

	direction.x = direction.x / (mag * 5);
	direction.y = direction.y / (mag * 5);
	
	if (!move(direction.x, direction.y)) {
		// search for a free way to move:
		// get random in range of -1, 0, 1:
		while (!move(rand() % 3 - 1, rand() % 3 - 1)) {
		}
	}
}

void Enemy::addGoal(Character* g)
{
	goal = g;
}


