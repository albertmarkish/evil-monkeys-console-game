#pragma once

#include "logger.h"
#include "drawEngine.h"
#include "character.h"
#include "level.h"

class Game {
	public:
		bool run(void);

	protected:
		bool getInput(char* c);
		void timerUpdate(void);

private:
	Level* level;
	Character* player;

	double frameCount;
	double startTime;
	double lastTime;

	DrawEngine drawArea;

	Logger logger;
};

