#pragma once
#include "sprite.h"

class Fireball : public Sprite
{
public:
    Fireball(Level* level, DrawEngine* de, int s_index, float x = 1, float y = 1, float xDir = 0,
        float yDir = 0, int i_lives = 1);

    virtual void idleUpdate(void);

    virtual void draw(float x, float y);

protected:
};

