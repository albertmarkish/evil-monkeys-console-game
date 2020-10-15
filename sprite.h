#pragma once

#include "drawEngine.h"
#include "level.h"

enum {
	SPRITE_CLASSID,
	CHARACTER_CLASSID,
	ENEMY_CLASSID,
};

struct vector
{
	float x;
	float y;
};

class Sprite
{
public:
	Sprite(Level *l, DrawEngine* de, int s_index, float x = 1, float y = 1, int i_lives = 1);
	~Sprite();

	vector getPosition(void);
	float getX(void);
	float getY(void);

	virtual void addLives(int num = 1);
	int getLives(void);
	bool isAlive();

	virtual void idleUpdate(void);

	virtual bool move(float x, float y);

	void setLogger(Logger* log);

protected:
	Level* level;

	DrawEngine *drawArea;
	vector pos;
	int spriteIndex;
	int numLives;

	int classID;

	vector facingDirection;
	virtual void draw(float x, float y) = 0;
	void erase(float x, float y);

	bool isValidLevelMove(int xpos, int ypos);

	Logger *logger;
};

