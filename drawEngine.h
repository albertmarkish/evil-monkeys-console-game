#pragma once

class DrawEngine
{
public:
	DrawEngine(int xSize = 80, int ySize = 25);
	~DrawEngine();

	int createSprite(int index, char c);
	void deleteSprite(int index);

	void eraseSprite(int posx, int posy);
	void drawSprite(int index, int posx, int posy);

	void createBackgroundTile(int index, char c);

	void setMap(char **data);
	void drawBackground(void);

protected:
	char** map;
	int screenWidth, screenHeight;
	char spriteImage[16];
	char tileImage[16];

private:
	void gotoxy(int x, int y);
	void cursorVisibility(bool visibility);
};

