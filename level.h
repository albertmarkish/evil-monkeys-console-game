#pragma once

#include "logger.h"
#include "drawEngine.h"

#include <list>

using std::list;

enum {
	SPRITE_PLAYER,
	SPRITE_ENEMY,
	SPRITE_FIREBALL
};

enum {
	TILE_EMPTY,
	TILE_WALL
};

//#include "character.h"
class Character;
class Sprite;

class Level
{
public:
	Level(DrawEngine* de, int width = 30, int height = 20);
	~Level();

	void addPlayer(Character *p);
	void update(void);
	void draw(void);
	bool keyPress(char c);

	void addEnemies(int num);
	void addNPC(Sprite* spr);

	bool isWall(int x, int y);

	friend class Sprite;

protected:
	void createLevel(void);

private:
	int width;
	int height;

	char **level;

	Character *player;
	DrawEngine *drawArea;

	Logger logger;

public:
	list <Sprite *> npc;
	list <Sprite *>::iterator Iter;
};

