#include "game.h"

#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

#define GAME_SPEED 133.33 // 30 fps 

bool Game::run(void)
{
	level = new Level(&drawArea, 80, 25);

	drawArea.createBackgroundTile(TILE_EMPTY, ' ');
	drawArea.createBackgroundTile(TILE_WALL, 219);

	drawArea.createSprite(SPRITE_PLAYER, '@');
	drawArea.createSprite(SPRITE_ENEMY, '$');

	player = new Character(level, &drawArea, SPRITE_PLAYER);
	
	level->draw();
	level->addPlayer(player);
	level->addEnemies(1);

	player->move(0, 0);

	char key = ' ';

	startTime = timeGetTime();
	frameCount = 0;
	lastTime = 0;

	while (key != 'q')
	{
		while (!getInput(&key))
		{
			timerUpdate();
		}

		level->keyPress(key);

		//cout << "Here's what you pressed: " << key << endl;
	}

	delete player;
	delete level;

	//TODO: move to DrawEngine class
	cout << frameCount / ((timeGetTime() - startTime) / 1000) << "fps" << endl;
	cout << "End of the game" << endl;

	return true;
}

bool Game::getInput(char* c)
{
	if (_kbhit()) {
		*c = _getch();
		return true;
	}

	return false;
}

void Game::timerUpdate(void)
{
	double currentTime = timeGetTime() - lastTime;

	if (currentTime < GAME_SPEED)
		return;

	level->update();

	frameCount++;

	lastTime = timeGetTime();
}
