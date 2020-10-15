#include "level.h"
#include "character.h"
#include "enemy.h"
#include "logger.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

Level::Level(DrawEngine* de, int w, int h)
{
	drawArea = de;
	width = w;
	height = h;

	player = 0;

	// allocate memory for level
	level = new char* [width];
	for (int i = 0; i < width; i++)
		level[i] = new char[height];

	// random seed
	srand(time(NULL));

	// create the level
	createLevel();

	drawArea->setMap(level);
}

Level::~Level()
{
	for (int i = 0; i < width; i++)
		delete[] level[i];

	delete[] level;
}

void Level::createLevel(void)
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int random = rand() % 100;

			if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
				level[x][y] = TILE_WALL;
			}
			else {
				if (random < 90 || (x < 3 && y < 3)) // prevent blocking of the player
				{
					level[x][y] = TILE_EMPTY;
				}
				else {
					level[x][y] = TILE_WALL;
				}
			}
		}
	}
}

void Level::draw(void)
{
	drawArea->drawBackground();
}

bool Level::keyPress(char c)
{
	if (player) {
		if (player->keyPress(c))
			return true;
	}

	return false;
}

void Level::addEnemies(int num)
{
	int i = num;

	while (i > 0)
	{
		// get a random position within the walls:
		int xpos = int((float(rand() % 100) / 100) * (width - 2) + 1);
		int ypos = int((float(rand() % 100) / 100) * (height - 2) + 1);

		if (level[xpos][ypos] != TILE_WALL) {

			logger.log(Logger::stringFormat("Enemy spawn at %d %d", xpos, ypos));

			Enemy* e = new Enemy(this, drawArea, SPRITE_ENEMY, (float)xpos, float(ypos), 1);
			e->setLogger(&logger);

			e->addGoal(player);

			addNPC((Sprite*)e);

			i--;
		}
	}
}

void Level::addNPC(Sprite* spr)
{
	npc.push_back(spr);
}

bool Level::isWall(int x, int y)
{
	return level[x][y] == TILE_WALL;
}

void Level::addPlayer(Character* p)
{
	player = p;
	player->setLogger(&logger);
}

void Level::update(void)
{
	// process fireballs moving
	for (Iter = npc.begin(); Iter != npc.end(); Iter++) {
		(*Iter)->idleUpdate();

		if ((*Iter)->isAlive() == false) {
			Sprite* temp = *Iter;
			Iter--;
			delete temp;
			npc.remove(temp);
		}
	}
}

