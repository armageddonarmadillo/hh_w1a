#pragma once
#include "framework.h"
#include "Drawable.h"
#include "Player.h"
#include "Background.h"
#include "Box.h"
#include "Platform.h"
#include "Enemy.h"
#include "Crab.h"
#include "Spawner.h"
#include "Health.h"

class Game
{
public:
	//game variables
	Player* mc = new Player(100, 100);
	Health* health = new Health();
	Background* bg = new Background("Background3.jpg", 0, 0, 5118, 800, 0.5);
	Background* ground = new Background("Ground.bmp", 0, GROUND, 774, 128, 1);

	//game lists
	list<Box*> boxes;
	list<Platform*> platforms;
	list<Enemy*> enemies;
	list<Spawner*> spawners;

	Game();

	//level loading
	list<list<string>>	load_level(CString lvl);
	void				build_level(list<list<string>> lvl);
	void				start_level(CString lvl);

	//game loop
	void inputs(WPARAM key, bool up);
	void update();
	void render(HDC context);
	void reset_game();
};

