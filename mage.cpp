#include "mage.h"
#include "fireball.h"

Mage::Mage(Level* l, DrawEngine* de, int s_index, float x, float y, 
	int lives, char spell_key, char up_key, char down_key, char left_key, char right_key)
	: Character(l, de, s_index, x, y, lives, up_key, down_key, left_key, right_key)
{
	spellKey = spell_key;
	classID = MAGE_CLASSID;
}

bool Mage::keyPress(char c)
{
	bool isKeypressHandled = Character::keyPress(c);

	if (!isKeypressHandled) {
		if (c == spellKey) {
			castSpell();
			return true;
		}
	}

	return isKeypressHandled;
}

void Mage::castSpell(void)
{
	Beep(4000, 100);

	int fb_xPos = (int)position.x + facingDirection.x;
	int fb_yPos = (int)position.y + facingDirection.y;

	Fireball* fb = new Fireball(level, drawArea, SPRITE_FIREBALL, fb_xPos, fb_yPos, facingDirection.x, facingDirection.y);

	fb->setLogger(logger);

	level->addNPC(fb);
}
