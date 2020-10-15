#pragma once
#include "sprite.h"

class Level;
class Character;

class Enemy : public Sprite
{
public:
	Enemy(Level *l, DrawEngine *de, int s_index, float x = 1, float y = 1, int i_lives = 1);
	
	void addGoal(Character *g);
	bool move(float x, float y);
	void idleUpdate(void);

protected:
	void simulateAI(void);
	Character* goal;
	virtual void draw(float x, float y);
};

