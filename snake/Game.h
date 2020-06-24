#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include "AssetMan.h"
#include "StateMan.h"


using namespace std;
using namespace Engine;
using namespace sf;

enum AssetID
{
	MAIN_FONT = 0,
	SECOND_FONT,
	GRASS,
	WALL,
	SNAKE,
	FOOD
};

struct Content
{
	unique_ptr<AssetMan>assets_s;
	unique_ptr<StateMan>states_s;
	unique_ptr<RenderWindow>window_s;

	Content() 
	{
		assets_s = make_unique<AssetMan>();
		states_s = make_unique<StateMan>();
		window_s = make_unique<RenderWindow>();
	}
};
class Game
{
private:
	shared_ptr<Content>context_s;
	const Time TIME_PER_FRAME = seconds(1.f / 60.f);
public:
	Game();
	~Game();
	void Run();
};

